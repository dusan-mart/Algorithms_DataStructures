#include <bits/stdc++.h>

class graph{
public:
  graph(int v);
  void add_edge(int op1, int op2, int weight);
  void dijkstra(int start);

private:
  int vertices;
  std::list<std::pair<int, int>> *adj;
};

int main(){

  graph g(10);
  g.add_edge(2, 3, 4);
  g.add_edge(3, 5, 1);
  g.add_edge(2, 4, 2);
  g.add_edge(6, 8, 7);
  g.add_edge(8, 9, 1);
  g.add_edge(1, 4, 3);
  g.add_edge(4, 7, 5);
  g.add_edge(7, 8, 2);
  g.add_edge(1, 0, 3);
  g.add_edge(4, 1, 2);
  g.add_edge(0, 6, 8);
  g.add_edge(1, 9, 2);

  g.dijkstra(2);
  return 0;
}

void graph::dijkstra(int start)
{
  std::vector<int> min_path(vertices);
  std::vector<int> visited(vertices);

  for(int i = 0; i < vertices; ++i)
  {
    min_path[i] = INT_MAX;
    visited[i] = false;
  }

  min_path[start] = 0;

  //we will check all vertices
  for(int i = 0; i < vertices; ++i)
  {
    //get nearest, not visited node from paths
    int min = INT_MAX;
    int index;

    for(int j = 0; j < vertices; ++j)
    {
      if(!visited[j] && (min_path[j] < min))
      {
        min = min_path[j];
        index = j;
      }
    }

    std::cout << "current node: " << index << '\n';

    //check all adjacent nodes
    for(auto &a : adj[index])
    {
      int vertic_tmp = a.first;
      int weight = a.second;
      //relaxation
      if((!visited[vertic_tmp]) && (min_path[vertic_tmp] > (min_path[index] + weight)))
      {
        min_path[vertic_tmp] = min_path[index] + weight;
      }
    }
    visited[index] = true;
  }

  std::cout << "\nMin paths from start("<< start << ") to the nodes:" << '\n';
  for(int i = 0; i < vertices; ++i)
    std::cout << "\t" << i << "_______" << min_path[i] << '\n';
}


graph::graph(int v)
{
  vertices = v;
  adj = new std::list<std::pair<int, int>>[v];
}
void graph::add_edge(int op1, int op2, int weight)
{
  adj[op1].push_back(std::make_pair(op2, weight));
}
