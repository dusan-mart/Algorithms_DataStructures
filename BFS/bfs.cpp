#include <bits/stdc++.h>

class graph{
public:
  graph(int v);
  void add_edge(int op1, int op2);
  void BFS(int start);
private:
  int vertices;
  std::list<int> *adj;
};

int main(){

  graph g(5);
  g.add_edge(2, 3);
  g.add_edge(2, 4);
  g.add_edge(4, 1);
  g.add_edge(1, 0);
  g.add_edge(0, 2);
  g.add_edge(3, 4);
  g.BFS(2);

  return 0;
}

graph::graph(int v)
{
  vertices = v;
  adj = new std::list<int>[v];
}

void graph::add_edge(int op1, int op2)
{
  adj[op1].push_back(op2);
  //for bidirectional graphs
  //adj[op2].push_back[op1];
}

void graph::BFS(int start)
{
  std::queue<int> q_v;
  std::vector<bool> visited(vertices, false);

  visited[start] = true;
  q_v.push(start);

  while(!q_v.empty())
  {
    int current = q_v.front();
    q_v.pop();
    std::cout << current << " ";

    for(auto i = adj[current].begin(); i != adj[current].end(); ++i)
    {
      if(!visited[*i])
      {
        q_v.push(*i);
        visited[*i] = true;
      }
    }
  }

  std::cout << '\n';
  return;
}
