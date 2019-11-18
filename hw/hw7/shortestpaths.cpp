#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <bits/stdc++.h>

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
    int x, y;
    Node(int x_val, int y_val)
    {
      x = x_val;
      y = y_val;
    }
  };
  std::string matrixFilename;
  unsigned int numNodes = 0;
  unsigned int maxDistance = 0;
  unsigned int maxPath = 0;
  bool deleteArrays = false;
  unsigned int **distanceMatrix;
  unsigned int **pathMatrix;
  unsigned int **intermediateMatrix;
  unsigned int numDigits(unsigned int num);
  void printMatrix(unsigned int maxVal, unsigned int **array, bool chars);
};

/**
 * numDigits gets the number of digits
 * in a given int
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

void ShortestPaths::printPaths()
{
  for (unsigned int i = 0; i < numNodes; i++)
  {
    for (unsigned int j = 0; j < numNodes; j++)
    {
      std::cout << char('A' + i) + std::string(" -> ") + char('A' + j) + ", distance: ";
      if (pathMatrix[i][j] == UINT_MAX) {
        std::cout << "infinity, path: none\n";
        continue;
      }
      std::cout << pathMatrix[i][j] << ", path: ";
      // print the path here
      std::vector<unsigned int> path;
      Node *root = new Node(i, j);
      Node *current = root;
      std::stack<Node *> nodeStack;
      std::unordered_set<unsigned int> pathSet;
      pathSet.reserve(numNodes * 2);
      while (current != nullptr || !nodeStack.empty())
      {
        while (current != nullptr)
        {
          unsigned int val = intermediateMatrix[current->x][current->y];
          if (val == UINT_MAX)
          {
            current->left = nullptr;
            current->right = nullptr;
          }
          else
          {
            current->left = new Node(current->x, val);
            current->right = new Node(val, current->y);
          }
          nodeStack.push(current);
          current = current->left;
        }
        current = nodeStack.top();
        nodeStack.pop();
        if (pathSet.find(current->x) == pathSet.end()) {
          path.push_back(current->x);
          pathSet.insert(current->x);
        }
        if (pathSet.find(current->y) == pathSet.end()) {
          path.push_back(current->y);
          pathSet.insert(current->y);
        }
        current = current->right;
      }
      // delete tree
      std::queue<Node *> nodeQueue;
      nodeQueue.push(root);
      Node *front;
      while (!nodeQueue.empty()) {
        front = nodeQueue.front();
        nodeQueue.pop();
        if (front->left)
          nodeQueue.push(front->left);
        if (front->right)
          nodeQueue.push(front->right);
        delete front;
      }
      std::cout << char('A' + path[0]);
      for (unsigned long k = 1; k < path.size(); k++)
        std::cout << " -> " << char('A' + path[k]);
      std::cout << '\n';
    }
  }
  std::cout << '\n';
}

void ShortestPaths::printIntermediate()
{
  std::cout << "Intermediate vertices:\n";
  printMatrix(1, intermediateMatrix, true);
}

void ShortestPaths::printPathLengths()
{
  std::cout << "Path lengths:\n";
  printMatrix(maxPath, pathMatrix, false);
}

void ShortestPaths::printDistanceMatrix()
{
  std::cout << "Distance matrix:\n";
  printMatrix(maxDistance, distanceMatrix, false);
}

void ShortestPaths::printMatrix(unsigned int maxVal, unsigned int **array, bool chars)
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
      unsigned int numSpaces = array[i][j] == UINT_MAX ? maxDigits : maxDigits - numDigits(array[i][j]) + 1;
      for (unsigned int k = 0; k < numSpaces; k++)
        std::cout << ' ';
      if (array[i][j] == UINT_MAX)
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
  distanceMatrix = new unsigned int *[numNodes];
  pathMatrix = new unsigned int *[numNodes];
  intermediateMatrix = new unsigned int *[numNodes];
  for (unsigned int i = 0; i < numNodes; i++)
  {
    distanceMatrix[i] = new unsigned int[numNodes];
    pathMatrix[i] = new unsigned int[numNodes];
    intermediateMatrix[i] = new unsigned int[numNodes];
    for (unsigned int j = 0; j < numNodes; j++)
    {
      if (i == j)
        distanceMatrix[i][j] = 0;
      else
        distanceMatrix[i][j] = UINT_MAX;
      pathMatrix[i][j] = distanceMatrix[i][j];
      intermediateMatrix[i][j] = UINT_MAX;
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
    unsigned int edgeWeight = potentialEdgeWeight;
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
        if (pathMatrix[i][k] == UINT_MAX || pathMatrix[k][j] == UINT_MAX)
          continue;
        unsigned int potentialMin = pathMatrix[i][k] + pathMatrix[k][j];
        if (potentialMin < pathMatrix[i][j])
        {
          pathMatrix[i][j] = potentialMin;
          intermediateMatrix[i][j] = k;
        }
      }
  for (unsigned int i = 0; i < numNodes; i++)
    for (unsigned int j = 0; j < numNodes; j++)
      if (pathMatrix[i][j] != UINT_MAX && pathMatrix[i][j] > maxPath)
        maxPath = pathMatrix[i][j];
}

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
