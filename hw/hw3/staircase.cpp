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

vector<vector<int>> get_staircase_ways(const int num_stairs) {
  vector<vector<int>> ways;
  if (num_stairs <= 0)
    ways.push_back(vector<int>());
  else
    for (int i = 1; i <= 3; i++)
      if (num_stairs >= i) {
        vector<vector<int>> result = get_staircase_ways(num_stairs - i);
        for (long unsigned int j = 0; j < result.size(); j++)
          result[j].push_back(i);
        for (const vector<int> single_res : result)
          ways.push_back(single_res);
      }
  return ways;

}

int main(int argc, char * const argv[]) {
  // reads and parses command line arguments.
  // Calls other functions to produce correct output.
  if (argc != 2) {
    cerr << "Usage: ./staircase <num_stairs>" << endl;
    return 1;
  }
  int num_stairs;
  istringstream iss(argv[1]);
  if (!(iss >> num_stairs)) {
    cerr << "Error: input is not an integer." << endl;
    return 1;
  }
  vector<vector<int>> staircase_ways = get_staircase_ways(num_stairs);
  for (long unsigned int i = 0; i < staircase_ways.size(); i++) {
    cout << i + 1 << ". [";
    if (staircase_ways.size() > 0) {
      cout << staircase_ways[i][0];
      for (long unsigned int j = 1; j < staircase_ways[i].size(); j++)
        cout << ", " << staircase_ways[i][j];
    }
    cout << "]\n";
  }
}
