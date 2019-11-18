class Node
{
public:
  Node *left;
  Node *right;
  int x, y;
  Node(int x_val, int y_val)
  {
    x = x_val;
    y = y_val;
  }
};

void test()
{
  int num_nodes = 5;
  int **nodes = new int *[num_nodes];
  int **paths = new int *[num_nodes];
  for (int i = 0; i < num_nodes; i++)
  {
    nodes[i] = new int[num_nodes];
    paths[i] = new int[num_nodes];
  }
  for (int i = 0; i < num_nodes; i++)
    for (int j = 0; j < num_nodes; j++)
    {
      if (i == j)
        nodes[i][j] = 0;
      else
        nodes[i][j] = 1; // distance of 1 to all nodes ?
      paths[i][j] = -1;
    }
  for (int k = 0; k < num_nodes; k++)
    for (int i = 0; i < num_nodes; i++)
      for (int j = 0; j < num_nodes; j++)
      {
        if (i != k && j != k)
        {
          int potential_min = nodes[i][k] + nodes[k][j];
          if (potential_min < nodes[i][j])
          {
            // changed current
            nodes[i][j] = potential_min;
            paths[i][j] = k;
          }
        }
      }
  int from = 2;
  int to = 1;
  std::stack<Node *> node_path_stack;
  Node root(from, to);
  node_path_stack.push(&root);
  while (!node_path_stack.empty())
  {
    Node *current_node = node_path_stack.top();
    int current_val = nodes[current_node->x][current_node->y];
    if (current_val >= 0)
    {
      //current_node->left = &Node(current_node->x, current_val);
      //current_node->right = &Node(current_val, current_node->y);
      node_path_stack.push(current_node->left);
      node_path_stack.push(current_node->right);
    }
    node_path_stack.pop();
  }
  std::vector<Node *> path;
  node_path_stack.push(&root);
  Node *curr = &root;
  while (curr != nullptr || !node_path_stack.empty())
  {
    while (curr->left != nullptr)
    {
      curr = curr->left;
      node_path_stack.push(curr);
    }
    curr = node_path_stack.top();
    node_path_stack.pop();
    if (curr->left == nullptr && curr->right == nullptr)
      path.push_back(curr);
    curr = curr->right;
  }
  for (int i = 0; i < num_nodes; i++)
    delete[] nodes[i];
}