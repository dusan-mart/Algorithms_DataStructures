#include <bits/stdc++.h>

class graph{
public:
  graph(int v);
  void add_edge(int op1, int op2);
  void dfs(int start);
private:
  int vertices;
  std::list<int> *adj;
  void dfs_helper(int start, std::vector<bool> &visited);
};

int main(){

  graph g(5);
  g.add_edge(2,4);
  g.add_edge(2,3);
  g.add_edge(4,0);
  g.add_edge(3,4);
  g.add_edge(3,1);

  g.dfs(2);

  return 0;
}


graph::graph(int v)
  : vertices(v)
{
  adj = new std::list<int>[v];
}

void graph::add_edge(int op1, int op2)
{
  adj[op1].push_back(op2);
}

void graph::dfs(int start)
{
  std::vector<bool> visited(vertices, false);
  dfs_helper(start, visited);
  return;
}
void graph::dfs_helper(int start, std::vector<bool> &visited)
{
  if(visited[start])
    return;

  visited[start] = true;
  std::cout << start << ' ';

  while (!adj[start].empty())
  {
    int curr = *adj[start].begin();
    adj[start].pop_front();
    dfs_helper(curr, visited);
  }
  return;
}
