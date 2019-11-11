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
#include <chrono>

#define MAP_SIZE 150000 // default size of map
#define MAX_CHAR 127    // max ascii character
#define MIN_CHAR 0      // min ascii character
#define MIN_FOR_MULTITHREAD 1000

/**
 * class for finding anagrams
 */
class FindAnagrams
{
public:
  explicit FindAnagrams(std::string filename);
  void printAnagrams();

private:
  std::string getSortedKey(std::string word);
  std::string dictionaryFilename;
  unsigned long mostAnagrams = 0;
  std::default_random_engine generator;
  std::unordered_map<std::string, std::vector<std::string>> words;
  std::vector<std::string> mostAnagramKeys;
  std::vector<std::string> input;
  unsigned int num_threads;
  std::mutex map_lock;
  void addToMap(unsigned long start, unsigned long end);
  void swapStrings(std::string &elem1, std::string &elem2);
  long partitionKeys(std::string keys[], long left, long right);
  void quickSortKeys(std::string keys[], long left, long right);
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
void FindAnagrams::swapStrings(std::string &elem1, std::string &elem2)
{
  std::string temp = elem1;
  elem1 = elem2;
  elem2 = temp;
}

/**
 * partitionKeys
 * 
 * partitions keys using Lomuto with
 * random partition index
 */
long FindAnagrams::partitionKeys(std::string keys[], long left, long right)
{
  std::uniform_int_distribution<long> dist(left, right);
  unsigned long randIndex = dist(generator);
  swapStrings(keys[randIndex], keys[left]);
  std::string pivot = words[keys[left]][0];
  long s = left;
  for (long i = left + 1; i <= right; i++)
    if (words[keys[i]][0] < pivot)
      swapStrings(keys[++s], keys[i]);
  swapStrings(keys[left], keys[s]);
  return s;
}

/**
 * quickSortKeys
 * 
 * quick sort the array based on first element in words
 */
void FindAnagrams::quickSortKeys(std::string keys[], long left, long right)
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
std::string FindAnagrams::getSortedKey(std::string word)
{
  for (unsigned long i = 0; i < word.length(); i++)
  {
    if (word[i] > MAX_CHAR || word[i] < MIN_CHAR)
      return "";
    if (word[i] >= 'a' && word[i] <= 'z')
      word[i] = word[i] - 'a' + 'A';
  }
  std::sort(word.begin(), word.end(), std::less<char>());
  return word;
}

void FindAnagrams::addToMap(unsigned long start, unsigned long end)
{
  std::cout << "start " << start << " end " << end << '\n';
  auto starttime = std::chrono::high_resolution_clock::now();
  for (unsigned long i = start; i < end; i++)
  {
    std::string key = getSortedKey(input[i]);
    if (key.length() == 0)
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
  auto endtime = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endtime - starttime);
  std::cout << "Time taken by function: "
            << duration.count() << " microseconds\n";
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
