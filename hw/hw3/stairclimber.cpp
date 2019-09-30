/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Joshua Schmidt
 * Version     : 1.0
 * Date        : 9/23/2019
 * Description : Output all staircase values.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

/**
 * algorithm to get all the ways to climb the stairs
 */
vector<vector<int>> get_ways(const int num_stairs)
{
  vector<vector<int>> ways;
  if (num_stairs <= 0) {
    ways.push_back(vector<int>());
  } else {
    for (int i = 1; i <= 3; i++) {
      if (num_stairs >= i) {
        vector<vector<int>> result = get_ways(num_stairs - i);
        for (vector<int>& res : result)
          res.insert(res.begin(), i);
        ways.insert(ways.end(), result.begin(), result.end());
      }
    }
  }
  return ways;
}

/**
 * num_digits gets the number of digits
 * in a given int
 */
int num_digits(int num)
{
  int count;
  for (count = 0; num > 0; count++)
    num /= 10;
  return count;
}

/**
 * displays all the ways to climb the stairs
 */
void display_ways(const vector<vector<int>> &staircase_ways, const int num_stairs)
{
  long unsigned int num_ways = staircase_ways.size();
  cout << num_ways << " way" << (num_ways != 1 ? "s" : "")
       << " to climb " << num_stairs << " stair"
       << (num_stairs != 1 ? "s" : "") << "." << endl;
  const int max_num_width = num_digits((int)num_ways);
  for (long unsigned int i = 0; i < num_ways; i++)
  {
    for (int j = 0; j < max_num_width - num_digits(i + 1); j++)
      cout << ' ';
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
    cerr << "Usage: ./stairclimber <number of stairs>" << endl;
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
  display_ways(staircase_ways, num_stairs);
}
