/*******************************************************************************
 * Name        : staircase.cpp
 * Author      : Joshua Schmidt
 * Version     : 1.0
 * Date        : 9/23/2019
 * Description : Output all staircase values.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void swap(vector<int>& x, vector<int>& y) {
  vector<int> temp = x;
  x = y;
  y = temp;
}

void sort_by_column(vector<vector<int>> &arr, const int &column)
{
  for (long unsigned int i = 0; i < arr.size(); i++) {
    int swap_index = i;
    for (long unsigned int j = i + 1; j < arr.size(); j++) {
      if ((int)arr[i].size() >= (column + 1) && arr[j][column] < arr[swap_index][column]) {
        if (column == 0 || arr[j][column] == arr[swap_index][column - 1])
          swap_index = j;
      }
    }
    if (swap_index != (int)i) {
      cout << "swap " << swap_index << '\n';
      swap(arr[swap_index], arr[i]);
    }
  }
}

vector<vector<int>> get_ways(const int num_stairs)
{
  vector<vector<int>> ways;
  if (num_stairs <= 0)
    ways.push_back(vector<int>());
  else
    for (int i = 1; i <= 3; i++)
      if (num_stairs >= i)
      {
        vector<vector<int>> result = get_ways(num_stairs - i);
        for (long unsigned int j = 0; j < result.size(); j++)
          result[j].push_back(i);
        for (const vector<int> single_res : result)
          ways.push_back(single_res);
      }
  return ways;
}

void display_ways(const vector<vector<int>> &staircase_ways, const int num_stairs)
{
  long unsigned int num_ways = staircase_ways.size();
  cout << num_ways << " way" << (num_ways != 1 ? "s" : "")
       << " to climb " << num_stairs << " stair"
       << (num_stairs != 1 ? "s" : "") << "." << endl;
  for (long unsigned int i = 0; i < num_ways; i++)
  {
    cout << i + 1 << ". [";
    if (staircase_ways[i].size() > 0)
    {
      cout << staircase_ways[i][0];
      for (long unsigned int j = 1; j < staircase_ways[i].size(); j++)
        cout << ", " << staircase_ways[i][j];
    }
    cout << "]\n";
  }
}

int main(int argc, char *const argv[])
{
  // reads and parses command line arguments.
  // Calls other functions to produce correct output.
  if (argc != 2)
  {
    cerr << "Usage: ./staircase <number of stairs>" << endl;
    return 1;
  }
  int num_stairs;
  istringstream iss(argv[1]);
  if (!(iss >> num_stairs && num_stairs > 0))
  {
    cerr << "Error: Number of stairs must be a positive integer." << endl;
    return 1;
  }
  vector<vector<int>> staircase_ways = get_ways(num_stairs);
  sort_by_column(staircase_ways, 0);
  sort_by_column(staircase_ways, 1);
  display_ways(staircase_ways, num_stairs);
}
