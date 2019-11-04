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
  static bool compareChars(char &elem2, char &elem1);
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
 * compareChars
 * 
 * compare characters, with the letters being
 * the same for upper and lowercase
 */
bool FindAnagrams::compareChars(char &elem2, char &elem1)
{
  if (elem1 >= 'a' && elem1 <= 'z')
  {
    elem1 = elem1 - 'a' + 'A';
  }
  if (elem2 >= 'a' && elem2 <= 'z')
  {
    elem2 = elem2 - 'a' + 'A';
  }
  return elem2 < elem1;
}

/**
 * getSortedKey
 * 
 * gets the sorted key for a given word
 */
std::string FindAnagrams::getSortedKey(std::string word)
{
  std::sort(word.begin(), word.end(), compareChars);
  return word;
}

/**
 * FindAnagrams constructor
 * 
 * creates FinAnagram object from
 * filename of dictionary
 */
FindAnagrams::FindAnagrams(std::string filename)
{
  dictionaryFilename = filename;
  std::ifstream dictionaryFile(dictionaryFilename);
  std::string word;
  while (std::getline(dictionaryFile, word))
  {
    // std::cout << line << std::endl;
    std::string key = getSortedKey(word);
    words[key].push_back(word);
    if (words[key].size() < mostAnagrams)
      continue;
    else if (words[key].size() > mostAnagrams && words[key].size() > 1)
    {
      mostAnagrams = words[key].size();
      mostAnagramKeys.clear();
    }
    mostAnagramKeys.push_back(key);
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
