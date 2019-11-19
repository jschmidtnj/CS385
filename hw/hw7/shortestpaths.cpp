/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Joshua Schmidt and Alexander Rubino
 * Version     : 1.0
 * Date        : November 18, 2019
 * Description : Implementation of shortest paths.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <bits/stdc++.h>

/**
 * ShortestPaths
 * 
 * class declaration for shortest paths
 * object used to get shortest paths between
 * 2 elements using floyd's algorithm
 */
class ShortestPaths
{
public:
  explicit ShortestPaths(const std::string fileName);
  void printDistanceMatrix();
  void printPathLengths();
  void printIntermediate();
  void printPaths();
  void processFile();
  ~ShortestPaths();

private:
  struct Node
  {
    Node *left;
    Node *right;
    unsigned long *x;
    unsigned long *y;
    bool assignedChildren = false;
    Node(unsigned long *x_val, unsigned long *y_val)
    {
      x = x_val;
      y = y_val;
    }
  };
  std::string matrixFilename;
  unsigned int numNodes = 0;
  unsigned long maxDistance = 0;
  unsigned long maxPath = 0;
  bool deleteArrays = false;
  unsigned long **distanceMatrix;
  unsigned long **pathMatrix;
  unsigned long **intermediateMatrix;
  unsigned int numDigits(unsigned int num);
  void printMatrix(unsigned long maxVal, unsigned long **array, bool chars);
};

/**
 * numDigits
 * gets the number of digits
 * in a given number
 */
unsigned int ShortestPaths::numDigits(unsigned int num)
{
  if (num == 0)
    return 1;
  unsigned int count;
  for (count = 0; num > 0; count++)
    num /= 10;
  return count;
}

/**
 * printPaths
 * 
 * prints the paths in arrow notation
 * to get between any 2 points
 */

void ShortestPaths::printPaths()
{
  for (unsigned long i = 0; i < numNodes; i++)
  {
    for (unsigned long j = 0; j < numNodes; j++)
    {
      std::cout << char('A' + i) + std::string(" -> ") + char('A' + j) + ", distance: ";
      if (pathMatrix[i][j] == ULONG_MAX)
      {
        std::cout << "infinity, path: none\n";
        continue;
      }
      std::cout << pathMatrix[i][j] << ", path: ";
      // print the path here
      std::vector<unsigned long> path;
      if (i == j)
      {
        path.push_back(i);
      }
      else
      {
        Node *root = new Node(&i, &j);
        Node *current = root;
        std::stack<Node *> nodeStack;
        nodeStack.push(current);
        while (!nodeStack.empty())
        {
          current = nodeStack.top();
          nodeStack.pop();
          if (!current->assignedChildren)
          {
            unsigned long *val = &intermediateMatrix[*current->x][*current->y];
            if (*val == ULONG_MAX)
            {
              current->left = nullptr;
              current->right = nullptr;
            }
            else
            {
              current->left = new Node(current->x, val);
              current->right = new Node(val, current->y);
            }
            current->assignedChildren = true;
          }
          if (current->right != nullptr)
            nodeStack.push(current->right);
          if (current->left != nullptr)
            nodeStack.push(current->left);
          if (current->left == nullptr && current->right == nullptr)
            path.push_back(*current->x);
        }
        path.push_back(j);
        // delete tree
        std::queue<Node *> nodeQueue;
        nodeQueue.push(root);
        Node *front;
        while (!nodeQueue.empty())
        {
          front = nodeQueue.front();
          nodeQueue.pop();
          if (front->left)
            nodeQueue.push(front->left);
          if (front->right)
            nodeQueue.push(front->right);
          delete front;
        }
      }
      std::cout << char('A' + path[0]);
      for (unsigned long k = 1; k < path.size(); k++)
        std::cout << " -> " << char('A' + path[k]);
      if (i != numNodes - 1 || j != numNodes - 1)
        std::cout << '\n';
    }
  }
}

/**
 * printIntermediate
 * 
 * prints the intermediate matrix
 */
void ShortestPaths::printIntermediate()
{
  std::cout << "Intermediate vertices:\n";
  printMatrix(1, intermediateMatrix, true);
}

/**
 * printPathLengths
 * 
 * prints the max path lengths matrix
 */
void ShortestPaths::printPathLengths()
{
  std::cout << "Path lengths:\n";
  printMatrix(maxPath, pathMatrix, false);
}

/**
 * printDistanceMatrix
 * 
 * public method for printing the distance matrix
 */
void ShortestPaths::printDistanceMatrix()
{
  std::cout << "Distance matrix:\n";
  printMatrix(maxDistance, distanceMatrix, false);
}

/**
 * printMatrix
 * 
 * prints matrix values
 */
void ShortestPaths::printMatrix(unsigned long maxVal, unsigned long **array, bool chars)
{
  unsigned int maxDigits = numDigits(maxVal);
  for (unsigned int i = 0; i < maxDigits; i++)
    std::cout << ' ';
  std::cout << " A";
  for (unsigned int i = 1; i < numNodes; i++)
  {
    for (unsigned int i = 0; i < maxDigits; i++)
      std::cout << ' ';
    std::cout << char('A' + i);
  }
  std::cout << '\n';
  for (unsigned int i = 0; i < numNodes; i++)
  {
    std::cout << char('A' + i);
    for (unsigned int j = 0; j < numNodes; j++)
    {
      unsigned int numSpaces = array[i][j] == ULONG_MAX ? maxDigits : maxDigits - numDigits(array[i][j]) + 1;
      for (unsigned int k = 0; k < numSpaces; k++)
        std::cout << ' ';
      if (array[i][j] == ULONG_MAX)
        std::cout << "-";
      else
      {
        if (chars)
          std::cout << char('A' + array[i][j]);
        else
          std::cout << array[i][j];
      }
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

/**
 * destructor
 * 
 * ShortestPaths destructor for deleting arrays on the heap
 */
ShortestPaths::~ShortestPaths()
{
  if (deleteArrays)
  {
    for (unsigned int i = 0; i < numNodes; i++)
    {
      delete[] distanceMatrix[i];
      delete[] pathMatrix[i];
      delete[] intermediateMatrix[i];
    }
    delete[] distanceMatrix;
    delete[] pathMatrix;
    delete[] intermediateMatrix;
  }
}

/**
 * processFile
 * 
 * uses the file string to process the file and
 * get the shortest path data in the necessary arrays
 */
void ShortestPaths::processFile()
{
  std::ifstream pathFile(matrixFilename);
  std::string line;
  std::getline(pathFile, line);
  std::istringstream iss;
  iss.str(line);
  int potentialNumNodes;
  if (!(iss >> potentialNumNodes) || potentialNumNodes <= 0)
    throw std::invalid_argument("Error: Invalid number of vertices '" + line + "' on line 1.");
  iss.clear();
  numNodes = potentialNumNodes;
  distanceMatrix = new unsigned long *[numNodes];
  pathMatrix = new unsigned long *[numNodes];
  intermediateMatrix = new unsigned long *[numNodes];
  for (unsigned int i = 0; i < numNodes; i++)
  {
    distanceMatrix[i] = new unsigned long[numNodes];
    pathMatrix[i] = new unsigned long[numNodes];
    intermediateMatrix[i] = new unsigned long[numNodes];
    for (unsigned int j = 0; j < numNodes; j++)
    {
      if (i == j)
        distanceMatrix[i][j] = 0;
      else
        distanceMatrix[i][j] = ULONG_MAX;
      pathMatrix[i][j] = distanceMatrix[i][j];
      intermediateMatrix[i][j] = ULONG_MAX;
    }
  }
  deleteArrays = true;
  unsigned int lineNum = 1;
  std::stringstream linestream;
  std::string splitSegment;
  std::vector<std::string> splitLine;
  while (std::getline(pathFile, line))
  {
    lineNum++;
    linestream.str(line);
    while (std::getline(linestream, splitSegment, ' '))
      splitLine.push_back(splitSegment);
    linestream.clear();
    if (splitLine.size() != 3)
      throw std::invalid_argument("Error: Invalid edge data '" + line + "' on line " + std::to_string(lineNum) + ".");
    const char endChar = char('A' + numNodes - 1);
    for (unsigned int i = 0; i < 2; i++)
      if (splitLine[i].length() != 1 || splitLine[i][0] < 'A' || splitLine[i][0] > endChar)
        throw std::invalid_argument("Error: " + std::string(i == 0 ? "Starting" : "Ending") + " vertex '" + splitLine[i] + "' on line " + std::to_string(lineNum) + " is not among valid values A-" + endChar + ".");
    iss.str(splitLine[2]);
    int potentialEdgeWeight;
    if (!(iss >> potentialEdgeWeight) || potentialEdgeWeight <= 0)
      throw std::invalid_argument("Error: Invalid edge weight '" + splitLine[2] + "' on line " + std::to_string(lineNum) + ".");
    iss.clear();
    unsigned long edgeWeight = potentialEdgeWeight;
    if (edgeWeight > maxDistance)
      maxDistance = edgeWeight;
    distanceMatrix[splitLine[0][0] - 'A'][splitLine[1][0] - 'A'] = edgeWeight;
    pathMatrix[splitLine[0][0] - 'A'][splitLine[1][0] - 'A'] = edgeWeight;
    splitLine.clear();
  }
  for (unsigned int k = 0; k < numNodes; k++)
    for (unsigned int i = 0; i < numNodes; i++)
      for (unsigned int j = 0; j < numNodes; j++)
      {
        if (pathMatrix[i][k] == ULONG_MAX || pathMatrix[k][j] == ULONG_MAX)
          continue;
        if (pathMatrix[i][k] > pathMatrix[i][j] || pathMatrix[k][j] > pathMatrix[i][j])
          continue;
        unsigned long potentialMin = pathMatrix[i][k] + pathMatrix[k][j];
        if (potentialMin < pathMatrix[i][j])
        {
          pathMatrix[i][j] = potentialMin;
          intermediateMatrix[i][j] = k;
        }
      }
  for (unsigned int i = 0; i < numNodes; i++)
    for (unsigned int j = 0; j < numNodes; j++)
      if (pathMatrix[i][j] != ULONG_MAX && pathMatrix[i][j] > maxPath)
        maxPath = pathMatrix[i][j];
}

/**
 * simple constructor used just for setting
 * filename for shortestpaths finding object
 */
ShortestPaths::ShortestPaths(const std::string fileName)
{
  matrixFilename = fileName;
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
 * main function with initial argument
 * insertion logic
 */
int main(const int argc, char *const argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: ./shortestpaths <filename>\n";
    return -1;
  }
  const std::string fileName = argv[1];
  if (!testFileExists(fileName))
  {
    std::cerr << "Error: Cannot open file '" << fileName << "'.\n";
    return -1;
  }
  ShortestPaths paths(fileName);
  try
  {
    paths.processFile();
  }
  catch (const std::exception &exc)
  {
    // just print exception message
    std::cerr << exc.what();
    return -1;
  }
  paths.printDistanceMatrix();
  paths.printPathLengths();
  paths.printIntermediate();
  paths.printPaths();
}
