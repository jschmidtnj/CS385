/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Joshua Schmidt
 * Version     : 1.0
 * Date        : 10/1/2019
 * Description : Complete the waterjug puzzle.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class WaterJugs
{
public:
  WaterJugs(vector<int> capacities, vector<int> goals)
      : _capacities(capacities), _goals(goals){};

private:
  vector<int> _capacities, _goals, _state;
  void print_initial_state();
};

void WaterJugs::print_initial_state()
{
  cout << "Initial state. (";
  for (long unsigned int i = 0; i < _capacities.size() - 1; i++)
    cout << "0, ";
  cout << _capacities.back() << ')' << endl;
}

int main(int argc, const char *argv[])
{
  if (argc != 7)
  {
    cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
    return -1;
  }
  istringstream iss;
  vector<int> capacities;
  for (int i = 1; i <= 3; i++)
  {
    iss.str(argv[i]);
    int current;
    if (!((iss >> current) && ((i == 3 && current > 0) || (i != 3 && current >= 0))))
    {
      cerr << "Error: Invalid capacity \'" << argv[i] << "\' for jug " << char(i + 64) << '.' << endl;
      return -1;
    }
    capacities.push_back(current);
    iss.clear();
  }
  vector<int> goals;
  for (int i = 4; i <= 6; i++)
  {
    iss.str(argv[i]);
    int current;
    if (!((iss >> current) && current >= 0))
    {
      cerr << "Error: Invalid goal \'" << argv[i] << "\' for jug " << char(i + 61) << '.' << endl;
      return -1;
    }
    goals.push_back(current);
    iss.clear();
  }
  for (unsigned long int i = 0; i < capacities.size(); i++)
  {
    if (capacities[i] < goals[i])
    {
      cerr << "Error: Goal cannot exceed capacity of jug " << char(i + 65) << '.' << endl;
      return -1;
    }
  }
  int goals_sum = 0;
  for (const int &goal : goals)
    goals_sum += goal;
  if (capacities.back() != goals_sum)
  {
    cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
    return -1;
  }
  WaterJugs jugs(capacities, goals);
}
