/*******************************************************************************
 * Name        : anagramfinder.cpp
 * Author      : Joshua Schmidt
 * Version     : 1.0
 * Date        : 11/3/2019
 * Description : Find all the anagrams.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
#include <random>
#include <thread>
#include <mutex>

#define MAP_SIZE 150000 // default size of map
#define MIN_FOR_MULTITHREAD 1000

const int primeNums[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

/**
 * class for finding anagrams
 */
class FindAnagrams
{
public:
  explicit FindAnagrams(std::string filename);
  void printAnagrams();

private:
  unsigned long long getKey(std::string & word);
  std::string dictionaryFilename;
  unsigned long mostAnagrams = 0;
  std::default_random_engine generator;
  std::unordered_map<unsigned long long, std::vector<std::string>> words;
  std::vector<unsigned long long> mostAnagramKeys;
  std::vector<std::string> input;
  unsigned int num_threads;
  std::mutex map_lock;
  void addToMap(unsigned long start, unsigned long end);
  void swapLongs(unsigned long long &elem1, unsigned long long &elem2);
  long partitionKeys(unsigned long long keys[], long left, long right);
  void quickSortKeys(unsigned long long keys[], long left, long right);
};

/**
 * printAnagrams
 * 
 * output the anagrams for given object
 */
void FindAnagrams::printAnagrams()
{
  if (mostAnagrams == 0)
  {
    std::cout << "No anagrams found.\n";
    return;
  }
  std::cout << "Max anagrams: " << mostAnagrams;
  // first sort the elements in the keys
  for (unsigned long i = 0; i < mostAnagramKeys.size(); i++)
    std::sort(words[mostAnagramKeys[i]].begin(),
              words[mostAnagramKeys[i]].end(),
              std::less<std::string>());
  // then sort based on first element for each key
  if (mostAnagramKeys.size() > 0)
    quickSortKeys(&mostAnagramKeys[0], 0, mostAnagramKeys.size() - 1);
  for (unsigned long i = 0, j; i < mostAnagramKeys.size(); i++)
  {
    std::cout << '\n';
    for (j = 0; j < mostAnagrams; j++)
      std::cout << words[mostAnagramKeys[i]][j] << '\n';
  }
}

/**
 * swapStrings
 * 
 * swap strings in array
 */
void FindAnagrams::swapLongs(unsigned long long &elem1, unsigned long long &elem2)
{
  unsigned long long temp = elem1;
  elem1 = elem2;
  elem2 = temp;
}

/**
 * partitionKeys
 * 
 * partitions keys using Lomuto with
 * random partition index
 */
long FindAnagrams::partitionKeys(unsigned long long keys[], long left, long right)
{
  std::uniform_int_distribution<long> dist(left, right);
  unsigned long randIndex = dist(generator);
  swapLongs(keys[randIndex], keys[left]);
  std::string pivot = words[keys[left]][0];
  long s = left;
  for (long i = left + 1; i <= right; i++)
    if (words[keys[i]][0] < pivot)
      swapLongs(keys[++s], keys[i]);
  swapLongs(keys[left], keys[s]);
  return s;
}

/**
 * quickSortKeys
 * 
 * quick sort the array based on first element in words
 */
void FindAnagrams::quickSortKeys(unsigned long long keys[], long left, long right)
{
  if (left < right)
  {
    long partition = partitionKeys(keys, left, right);
    quickSortKeys(keys, left, partition - 1);
    quickSortKeys(keys, partition + 1, right);
  }
}

/**
 * getSortedKey
 * 
 * gets the sorted key for a given word
 */
unsigned long long FindAnagrams::getKey(std::string & word)
{
  unsigned long long res = 1;
  for (int i = 0; i < (int)word.length(); i++)
  {
    if (word[i] >= 'a' && word[i] <= 'z')
      res *= primeNums[word[i] - 'a'];
    else if (word[i] >= 'A' && word[i] <= 'Z')
      res *= primeNums[word[i] - 'A'];
    else
      return 0;
  }
  return res;
}

void FindAnagrams::addToMap(unsigned long start, unsigned long end)
{
  for (unsigned long i = start; i < end; i++)
  {
    unsigned long long key = getKey(input[i]);
    if (key == 0)
      continue;
    map_lock.lock();
    words[key].push_back(input[i]);
    if (words[key].size() < mostAnagrams)
    {
      map_lock.unlock();
      continue;
    }
    else if (words[key].size() > mostAnagrams && words[key].size() > 1)
    {
      mostAnagrams = words[key].size();
      mostAnagramKeys.clear();
    }
    mostAnagramKeys.push_back(key);
    map_lock.unlock();
  }
}

/**
 * FindAnagrams constructor
 * 
 * creates FinAnagram object from
 * filename of dictionary
 */
FindAnagrams::FindAnagrams(std::string filename)
{
  words.reserve(MAP_SIZE);
  num_threads = std::thread::hardware_concurrency();
  dictionaryFilename = filename;
  std::ifstream dictionaryFile(dictionaryFilename);
  std::string word;
  while (std::getline(dictionaryFile, word))
  {
    // std::cout << word << std::endl;
    input.push_back(word);
  }
  if (input.size() > MIN_FOR_MULTITHREAD)
  {
    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < num_threads - 1; i++)
    {
      threads.push_back(std::thread(&FindAnagrams::addToMap, this, (float)i / num_threads * input.size(), (float)(i + 1) / num_threads * input.size()));
    }
    threads.push_back(std::thread(&FindAnagrams::addToMap, this, (float)(num_threads - 1) / num_threads * input.size(), input.size()));
    for (std::thread &t : threads)
      t.join();
  }
  else
  {
    addToMap(0, input.size());
  }
}

/**
 * testFileExists
 * 
 * checks if the file exists in the directory
 */
inline bool testFileExists(const std::string &name)
{
  if (FILE *file = fopen(name.c_str(), "r"))
  {
    fclose(file);
    return true;
  }
  else
    return false;
}

/**
 * main function
 * 
 * runs through validation
 */
int main(const int argc, char *const argv[])
{
  if (argc != 2)
  {
    std::cout << "Usage: ./anagramfinder <dictionary file>\n";
    return -1;
  }
  const std::string fileName = argv[1];
  if (!testFileExists(fileName))
  {
    std::cout << "Error: File '" << fileName << "' not found.\n";
    return -1;
  }
  FindAnagrams(std::string(fileName)).printAnagrams();
}
