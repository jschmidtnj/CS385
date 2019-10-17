/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : Joshua Schmidt
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : 10/16/2019
 * Description   : Implements the quickselect algorithm found on page 160 in
 *                 Algorithms, 3e by Anany Levitin.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * swap
 * 
 * swap elements in array fast
 */
void swap(int array[], int index1, int index2)
{
  int temp = array[index1];
  array[index1] = array[index2];
  array[index2] = temp;
}

/**
 * lomuto_partition
 * 
 * gets a partition for the array
 * first makes it a bit faster by getting the median
 * of the array
 */
size_t lomuto_partition(int array[], size_t left, size_t right)
{
  int mid = left + ((right - left) / 2);
  // median of left, right and middle
  if (array[left] < array[right])
  {
    if (array[right] < array[mid])
    {
      swap(array, right, left);
    }
    else if (array[right] >= array[mid])
    {
      swap(array, right, mid);
    }
  }
  else
  {
    if (array[right] > array[mid])
    {
      swap(array, right, left);
    }
    else if (array[left] >= array[mid])
    {
      swap(array, left, mid);
    }
  }
  int p = array[left];
  size_t s = left;
  for (size_t i = left + 1; i <= right; i++)
    if (array[i] < p)
      swap(array, ++s, i);
  swap(array, left, s);
  return s;
}

/**
 * quick_select
 * 
 * algorithm for selecting the nth smallest
 * element in the array
 */
int quick_select(int array[], size_t left, size_t right, size_t k)
{
  size_t s = lomuto_partition(array, left, right);
  while (s != k - 1)
  {
    if (s > k - 1)
    {
      right = s - 1;
    }
    else
    {
      left = s + 1;
    }
    s = lomuto_partition(array, left, right);
  }
  return array[s];
}

/**
 * quick_select
 * 
 * main function calling the helper function
 */
int quick_select(int array[], const size_t length, size_t k)
{
  return quick_select(array, 0, length - 1, k);
}

/**
 * main function call
 */
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " <k>" << endl;
    return 1;
  }

  int k;
  istringstream iss;
  iss.str(argv[1]);
  if (!(iss >> k) || k <= 0)
  {
    cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
    return 1;
  }

  cout << "Enter sequence of integers, each followed by a space: " << flush;
  int value, index = 0;
  vector<int> values;
  string str;
  str.reserve(11);
  char c;
  iss.clear();
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
          return 1;
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

  int num_values = values.size();
  if (num_values == 0)
  {
    cerr << "Error: Sequence of integers not received." << endl;
    return 1;
  }
  // error checking k against the size of the input
  if (k > num_values)
  {
    cerr << "Error: Cannot find smallest element " << k << " with only " << num_values << " value" << (num_values != 1 ? "s" : "") << "." << endl;
    return 1;
  }
  int *array = new int[num_values];
  copy(values.begin(), values.end(), array);
  // call the quick_select function and display the result
  cout << "Smallest element " << k << ": " << quick_select(array, num_values, k);
  delete[] array;
}
