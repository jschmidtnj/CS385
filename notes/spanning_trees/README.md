# spanning trees

A **spanning tree** of an undirected connected graph is its connected acyclic subgraph (a tree) that contains all the vertices of the graph. If such a graph has weights assigned to its edges, a minimum spanning tree is its spanning tree of the smallest weight, where the weight of a tree is defined as the sum of the weights on all its edges.

## prim's algorithm

greedy algorithm

tree vertices | remaining vertices
a(-,-) | b(a, 3), c(-, inf), d(-, inf), e(a, 6), f(a, 3)
b(a, 3) | c(b, 1), d(-, inf), e(a, 6), f(b, 4)
c(b, 1) | d(c, 6), e(a, 6), f(b, 4)
f(b, 4) | d(f, 5), e(f, 2)
e(f, 2) | d(f, 5)
d(f, 5)

- running time for adjacency matrix + unordered array priority queue is $\theta(V)$, where V is the number of vertices
- adjacency list + min heap priority queue is faster
  - deletion, insertion, decrease-key is $O(logV)$
  - $|V|$ for building the loop
  - $|V| - 1$ for deletion of the smallest element
  - $|E|$ comparisons - sum of the lengths of all adjacency list ($2 \cdot |V|$)
  - this results in $(E + V) \cdot log(V)$
  - $V-1 <= E$
  - $E \cdot log V$
- can also use Kruskal's algorithm

## union find (part of Kruskal's)

- makeset(x) - requires the creation of a single-node tree. theta(1) * n = theta(n)
- union(x, y) - attaches the root of y's subtree to the root of x's subtree - theta(1)
- find(x) - follow the pointer chain from x to the root - O(n)
- no cycle means find(x) != find(y)
