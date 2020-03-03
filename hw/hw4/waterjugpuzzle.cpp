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

#define NUM_JUGS 3

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
  // in the future make this a flat vector to allow for more dimensions
  vector<vector<State>> _complete_state;
  bool found_solution = false;
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
  if (!found_solution)
  {
    cout << "No solution." << endl;
    return;
  }
  cout << "Initial state. (";
  for (long unsigned int i = 0; i < _capacities.size() - 1; i++)
    cout << "0, ";
  cout << _capacities.back() << ')' << endl;
  stack<State *> steps;
  for (State *current = &_complete_state[_goals[0]][_goals[1]]; current->levels != _complete_state[0][0].levels; current = current->parent)
  {
    steps.push(current);
  }
  State *last = &_complete_state[0][0];
  for (State *current; steps.size() > 0; steps.pop())
  {
    current = &_complete_state[steps.top()->levels[0]][steps.top()->levels[1]];
    int from_index = -1, to_index = -1, amount_poured = 0;
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
         << " from " << char(from_index + 'A') << " to " << char(to_index + 'A') << ". (";
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
  _complete_state.resize(_capacities[0] + 1);
  for (vector<State> &second_state : _complete_state)
    second_state.resize(_capacities[1] + 1);
  queue<State> mainqueue;
  mainqueue.push(State(vector<int>{0, 0, _capacities.back()}, NULL));
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
      found_solution = true;
      break;
    }
    for (unsigned long int from = 0; from < current.levels.size(); from++)
    {
      for (unsigned long int to = 0; to < current.levels.size(); to++)
      {
        if (from != to && current.levels[from] != 0 && current.levels[to] < _capacities[to])
        {
          int remaining_space = _capacities[to] - current.levels[to];
          int amount_poured = remaining_space > current.levels[from] ? current.levels[from] : remaining_space;
          vector<int> new_levels = current.levels;
          new_levels[from] -= amount_poured;
          new_levels[to] += amount_poured;
          mainqueue.push(State(new_levels, &_complete_state[current.levels[0]][current.levels[1]]));
        }
      }
    }
    mainqueue.pop();
  }
}

/**
 * main function
 * 
 * entry point
 */
int main(int argc, const char *argv[])
{
  if (argc != NUM_JUGS * 2 + 1)
  {
    cerr << "Usage: " << argv[0];
    for (int i = 0; i < NUM_JUGS; i++) {
      cout << " <cap " << char('A' + i) << '>';
    }
    for (int i = 0; i < NUM_JUGS; i++) {
      cout << " <goal " << char('A' + i) << '>';
    }
    cout << endl;
    return EXIT_FAILURE;
  }
  istringstream iss;
  vector<int> capacities;
  capacities.reserve(NUM_JUGS);
  int current;
  for (int i = 1; i <= NUM_JUGS; i++)
  {
    iss.str(argv[i]);
    if (!((iss >> current) && ((i == 3 && current > 0) || (i != 3 && current >= 0))))
    {
      cerr << "Error: Invalid capacity \'" << argv[i] << "\' for jug " << char(i + 'A' - 1) << '.' << endl;
      return EXIT_FAILURE;
    }
    capacities.push_back(current);
    iss.clear();
  }
  vector<int> goals;
  goals.reserve(NUM_JUGS);
  for (int i = 1 + NUM_JUGS; i <= 2 * NUM_JUGS; i++)
  {
    iss.str(argv[i]);
    if (!((iss >> current) && current >= 0))
    {
      cerr << "Error: Invalid goal \'" << argv[i] << "\' for jug " << char(i + 'A' - 4) << '.' << endl;
      return EXIT_FAILURE;
    }
    goals.push_back(current);
    iss.clear();
  }
  for (unsigned long int i = 0; i < capacities.size(); i++)
  {
    if (capacities[i] < goals[i])
    {
      cerr << "Error: Goal cannot exceed capacity of jug " << char(i + 'A') << '.' << endl;
      return EXIT_FAILURE;
    }
  }
  int goals_sum = 0;
  for (const int &goal : goals)
    goals_sum += goal;
  if (capacities.back() != goals_sum)
  {
    cerr << "Error: Total gallons in goal state must be equal to the capacity of jug " << char(NUM_JUGS - 1 + 'A') << "." << endl;
    return EXIT_FAILURE;
  }
  WaterJugs jugs(capacities, goals);
  jugs.print_solution();
}
