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
#include <queue>
#include <stack>

using namespace std;

/**
 * WaterJugs class
 * 
 * contains methods for getting the solution to
 * the waterjug problem and printing it
 */
class WaterJugs
{
public:
  explicit WaterJugs(vector<int> capacities, vector<int> goals);
  void print_solution();

private:
  /**
   * State struct
   * 
   * used for storing the state of the waterjugs at a given time (current levels),
   * and parent state
   */
  struct State
  {
    explicit State() {}
    explicit State(vector<int> levels, State *parent) : levels(levels), parent(parent){};
    vector<int> levels;
    State *parent = NULL;
  };
  vector<int> _capacities, _goals;
  vector<vector<State>> _complete_state;
  State *_final_state = NULL;
  void find_solution();
};

/**
 * Waterjugs constructor
 * 
 * constructor by default finds the solution
 */
WaterJugs::WaterJugs(vector<int> capacities, vector<int> goals) : _capacities(capacities), _goals(goals)
{
  find_solution();
}

/**
 * Waterjugs print_solution
 * 
 * prints the solution of the Waterjug problem
 */
void WaterJugs::print_solution()
{
  if (_final_state == NULL)
  {
    cout << "No solution." << endl;
    return;
  }
  cout << "Initial state. (";
  for (long unsigned int i = 0; i < _capacities.size() - 1; i++)
    cout << "0, ";
  cout << _capacities.back() << ')' << endl;
  stack<State *> steps;
  for (State *current = _final_state; current->levels != _complete_state[0][0].levels; current = current->parent)
  {
    steps.push(current);
  }
  State *last = &_complete_state[0][0];
  for (State *current; steps.size() > 0; steps.pop())
  {
    current = &_complete_state[steps.top()->levels[0]][steps.top()->levels[1]];
    int from_index = -1, to_index = -1, amount_poured;
    for (long unsigned int i = 0; i < _capacities.size(); i++)
    {
      if (last->levels[i] != current->levels[i])
      {
        if (last->levels[i] > current->levels[i])
        {
          from_index = i;
          amount_poured = last->levels[i] - current->levels[i];
          if (to_index != -1)
            break;
        }
        else
        {
          to_index = i;
          if (from_index != -1)
            break;
        }
      }
    }
    cout << "Pour " << amount_poured << " gallon" << (amount_poured != 1 ? "s" : "")
         << " from " << char(from_index + 65) << " to " << char(to_index + 65) << ". (";
    cout << current->levels[0];
    for (long unsigned int i = 1; i < _capacities.size(); i++)
      cout << ", " << current->levels[i];
    cout << ")\n";
    last = current;
  }
}

/**
 * Waterjugs find_solution
 * 
 * finds the solution to the waterjug problem
 */
void WaterJugs::find_solution()
{
  _complete_state.resize(_capacities[2]);
  for (vector<State> &second_state : _complete_state)
    second_state.resize(_capacities[2]);
  queue<State> mainqueue;
  mainqueue.push(State(vector<int>{0, 0, _capacities.back()}, NULL));
  State last_state;
  while (mainqueue.size() > 0)
  {
    State current = mainqueue.front();
    if (!_complete_state[current.levels[0]][current.levels[1]].levels.empty())
    {
      mainqueue.pop();
      continue;
    }
    _complete_state[current.levels[0]][current.levels[1]] = current;
    if (current.levels == _goals)
    {
      _final_state = &_complete_state[current.levels[0]][current.levels[1]];
      break;
    }
    for (unsigned long int i = 0; i < current.levels.size(); i++)
    {
      for (unsigned long int j = 0; j < current.levels.size(); j++)
      {
        if (i != j && current.levels[i] != 0 && current.levels[j] < _capacities[j])
        {
          int remaining_space = _capacities[j] - current.levels[j];
          int amount_poured = remaining_space - current.levels[i] > 0 ? current.levels[i] : remaining_space;
          vector<int> new_levels = current.levels;
          new_levels[i] = current.levels[i] - amount_poured;
          new_levels[j] = current.levels[j] + amount_poured;
          mainqueue.push(State(new_levels, &_complete_state[current.levels[0]][current.levels[1]]));
        }
      }
    }
    mainqueue.pop();
    last_state = current;
  }
}

/**
 * main function
 * 
 * entry point
 */
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
  jugs.print_solution();
}
