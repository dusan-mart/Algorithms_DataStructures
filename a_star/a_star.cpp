#include <bits/stdc++.h>

struct node{
  int x;
  int y;
  std::vector<node*> adj;
  node* parent;// used for recreating path

  bool visited = false;
  bool obstacle = false;

  int current_min_path;
  double total_path;// current minimal path + estimated rest of path(heuristic)
};

bool a_star(int start_x, int start_y, int end_x, int end_y);

//dimensions of grid
#define WIDTH 10
#define HEIGHT 10

int main()
{
  //graph is grid
  //00 01 ... 0n
  //10 11 ... 1n
  //.         .
  //.         .
  //.         .
  //m0 ..... mn
  //arg: x and y coor of start and end
  //start_x, start_y, end_x, end_y
  a_star(0,0,9,9);
  //inside function, obstacle nodes can be defined

  return 0;
}


bool a_star(int start_x, int start_y, int end_x, int end_y)
{
  node *grid = nullptr;
  int grid_width = WIDTH;
  int grid_height = HEIGHT;

  grid = new node[grid_width * grid_height];
  for (int i = 0; i < grid_width; ++i)
    for (int j = 0; j < grid_height; ++j)
    {
      grid[j * grid_width + i].x = i;
      grid[j * grid_width + i].y = j;
      grid[j * grid_width + i].obstacle = false;
      grid[j * grid_width + i].parent = nullptr;
      grid[j * grid_width + i].visited = false;
  	}

  //connexting nodes in grid, making adjacencies
  //we connect with upper, left, right and down node
  //adding j-1, i+1, j+1, i-1 combinations, could connect diagonally
  for (int i = 0; i < grid_width; ++i)
    for (int j = 0; j < grid_height; ++j)
    {
      if(j > 0)
        grid[j * grid_width + i].adj.push_back(&grid[(j - 1) * grid_width + (i + 0)]);
      if(j < (grid_height-1))
        grid[j * grid_width + i].adj.push_back(&grid[(j + 1) * grid_width + (i + 0)]);
      if(i > 0)
        grid[j * grid_width + i].adj.push_back(&grid[(j + 0) * grid_width + (i - 1)]);
      if(i < (grid_width-1))
        grid[j * grid_width + i].adj.push_back(&grid[(j + 0) * grid_width + (i + 1)]);
    }

  for (int i = 0; i < grid_width; ++i)
    for (int j = 0; j < grid_height; ++j)
    {
      grid[j * grid_width + i].visited = false;
      grid[j * grid_width + i].total_path = std::numeric_limits<double>::max();
      grid[j * grid_width + i].current_min_path = std::numeric_limits<int>::max();
      grid[j * grid_width + i].parent = nullptr;	// No parents
    }
  //DEFINING OBSTACLES
  //ex: (5,5)
  grid[5*grid_width + 5].obstacle = true;


  auto heuristic = [](node* a, node* b)
  {
    return sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
  };

  //start and end nodes
  node* node_start = &grid[start_y * grid_width + start_x];
  std::cout << "start node: " << grid[start_y * grid_width + start_x].x << grid[start_y * grid_width + start_x].y << '\n';

  node* node_end = &grid[ end_y * grid_width + end_x];
  std::cout << "end node: " << grid[end_y * grid_width + end_x].x << grid[end_y * grid_width + end_x].y << '\n';


  node* current = node_start;
  node_start->current_min_path = 0;
  node_start->total_path = heuristic(node_start, node_end);
  std::list<node*> not_visited;
  not_visited.push_back(node_start);

  while (!not_visited.empty() && current != node_end)
  {
    // we sort all not visited nodes by total path value
		not_visited.sort([](const node* lhs, const node* rhs){ return lhs->total_path < rhs->total_path; } );

    // disregard if node is already visited
    while(!not_visited.empty() && not_visited.front()->visited)
			not_visited.pop_front();

		if (not_visited.empty())
		  break;

		current = not_visited.front();
		current->visited = true;

		// check each of this node's neighbours
		for (auto neighbour : current->adj)
		{
      if (!neighbour->visited && !neighbour->obstacle)
		    not_visited.push_back(neighbour);

      double tmp_distance = current->current_min_path + heuristic(current, neighbour);


			if (tmp_distance < neighbour->current_min_path)
			{
        neighbour->parent = current;
				neighbour->current_min_path = tmp_distance;

				neighbour->total_path = neighbour->current_min_path + heuristic(neighbour, node_end);
			}
		}
	}
  //printing path
  //going backwards and checking parent nodes
  std::cout << "-----finish-----" << '\n';
  if (node_end != nullptr)
	{
    node *p = node_end;
		while (p->parent != nullptr)
		{
      std::cout << p->x << "__" << p->y << '\n';
      p = p->parent;
		}
    std::cout << p->x << "__" << p->y << '\n';
	}
  std::cout << "-----start-----" << '\n';

  return true;
}
