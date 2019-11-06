struct Node {
  Node *left, *right;
};

int count_leaves(Node *n) {
  if (n == nullptr)
    return 0;
  if (n->left == nullptr && n->right == nullptr)
    return 1;
  return count_leaves(n->left) + count_leaves(n->right);
}
