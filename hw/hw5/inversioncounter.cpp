/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      :
 * Version     : 1.0
 * Date        :
 * Description : Counts the number of inversions in an array.
 * Pledge      :
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

// uncomment next line to run debug for MAX_LEN entries
// `time ./inversioncounter` to see how long it takes
// #define DEBUG
#define MAX_LEN 100000

using namespace std;

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 * does this with a double for loop, for worst case of n(n+1)/2
 */

long count_inversions_slow(int array[], int length)
{
  long num_inversions = 0;
  for (int i = 0; i < length - 1; i++)
    for (int j = i + 1; j < length; j++)
      if (array[j] < array[i])
        num_inversions++;
  return num_inversions;
}

/**
 * merge helper function used in mergesort
 * merges the unsorted arrays and returns the
 * number of inversions for a given array,
 * equal to  count += mid - 1 for each iteration
 */
long merge(int array[], int scratch[], int low, int mid, int high)
{
  int i = low, j = mid, k = low;
  long count = 0;
  // while j is not high
  // and i is less than mid - 1
  while ((j <= high) && (i <= mid - 1))
  { // add lower to scratch
    if (array[i] <= array[j])
    {
      scratch[k] = array[i];
      i++;
    }
    else
    {
      scratch[k] = array[j];
      j++;
      count += (mid - i); // add to inversion counter
    }
    k++;
  }
  // copy remaining elements into temp array
  for (; i <= mid - 1; i++, k++)
    scratch[k] = array[i];
  for (; j <= high; j++, k++)
    scratch[k] = array[j];
  // copy temp array into array
  for (i = low; i <= high; i++)
    array[i] = scratch[i];
  return count;
}

/**
 * runs a merge sort algorithm but adding the
 * returned count of inversions to the result
 */
static long mergesort(int array[], int scratch[], int low, int high)
{
  long res = 0L;
  if (low < high)
  {
    int mid = low + (high - low) / 2;
    res += mergesort(array, scratch, low, mid);
    res += mergesort(array, scratch, mid + 1, high);
    res += merge(array, scratch, low, mid + 1, high);
  }
  return res;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length)
{
  int *scratch = new int[length];
  long res = mergesort(array, scratch, 0, length - 1);
  delete[] scratch;
  return res;
}

/**
 * creates a very long input for testing purposes
 */
vector<int> getLongTest()
{
  vector<int> res;
  res.reserve(MAX_LEN);
  for (int i = MAX_LEN; i > 0; i--) {
    res.push_back(i);
    // cout << i << " ";
  }
  return res;
}

/**
 * main function with error checking
 */
int main(int argc, char *argv[])
{
  if (argc > 2)
  {
    cerr << "Usage: ./inversioncounter [slow]" << endl;
    return -1;
  }
  bool fast = true;
  if (argc == 2)
  {
    string arg = argv[1];
    if (arg == "slow")
    {
      fast = false;
    }
    else
    {
      cerr << "Error: Unrecognized option '" << arg << "'." << endl;
      return -1;
    }
  }

#ifndef DEBUG
  cout << "Enter sequence of integers, each followed by a space: " << flush;
  istringstream iss;
  int value, index = 0;
  vector<int> values;
  string str;
  str.reserve(11);
  char c;
  while (true)
  {
    c = getchar();
    const bool eoln = c == '\r' || c == '\n';
    if (isspace(c) || eoln)
    {
      if (str.length() > 0)
      {
        iss.str(str);
        if (iss >> value)
        {
          values.push_back(value);
        }
        else
        {
          cerr << "Error: Non-integer value '" << str
               << "' received at index " << index << "." << endl;
          return -1;
        }
        iss.clear();
        ++index;
      }
      if (eoln)
      {
        break;
      }
      str.clear();
    }
    else
    {
      str += c;
    }
  }
#else
  vector<int> values = getLongTest();
#endif
  int len = values.size();
  if (len == 0)
  {
    cerr << "Error: Sequence of integers not received." << endl;
    return -1;
  }
  long res;
  if (fast)
  {
    res = count_inversions_fast(&values[0], len);
  }
  else
  {
    res = count_inversions_slow(&values[0], len);
  }
  cout << "Number of inversions: " << res << endl;
}
