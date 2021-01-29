#include <bits/stdc++.h>

struct point{
  point()
    : x(0), y(0){}

  point(int a, int b)
    : x(a), y(b){}

  int x,y;
};

std::vector<point> find_closure(std::vector<point> &points);

// utility funtions
int euc_distance(point p_1, point p_2);

// Slope of line segment (p1, p2): σ = (y2 - y1)/(x2 - x1)
// Slope of line segment (p2, p3): τ = (y3 - y2)/(x3 - x2)
// If  σ > τ, the orientation is clockwise (right turn)
// Using above values of σ and τ, we can conclude that,
// the orientation depends on sign of  below expression:
//// (y2 - y1)*(x3 - x2) - (y3 - y2)*(x2 - x1)
//
// Above expression is negative when σ < τ, counterclockwise
int orientation(point p_1, point p_2, point p_3);
//return point below top
point get_second(std::stack<point> &st);

int main(){

  std::vector<point> points;
  // emplace can direcly construct object if given param.
  points.emplace_back(0,2);
  points.emplace_back(1,1);
  points.emplace_back(2,2);
  points.emplace_back(2,4);
  points.emplace_back(5,5);
  points.emplace_back(1,2);
  points.emplace_back(3,1);
  points.emplace_back(2,6);

  std::vector<point> result;
  result = find_closure(points);

  for(auto &a : result)
    std::cout << a.x << a.y << '\n';

  return 0;
}



std::vector<point> find_closure(std::vector<point> &points)
{
  // starting point is most bottom(min y)
  // if multiple minimums, leftmost(min x)

  int min_y = points[0].y;
  int min_index = 0;

  for(int i = 1; i < static_cast<int>(points.size()); ++i)
  {
    if(points.at(i).y < min_y)
    {
      min_y = points.at(i).y;
      min_index = i;
    }
    if(points.at(i).y == min_y)
      if(points.at(i).x < points.at(min_index).x)
      {
        min_y = points.at(i).y;
        min_index = i;
      }
  }

  std::swap(points[0], points[min_index]);

  point p_0 = points[0];
  //  instead of computing polar angles around points[0]
  //  use the orientation to compare angles without actually computing them
  std::sort(points.begin()+1, points.end(),
            [p_0](point &p_1, point &p_2)
  {
    // 0  colinear
    // 1  clockwise
    // 2  counterclockwise
    int tmp = 0;
    if((tmp = orientation(p_0, p_1, p_2)) == 0)
    {
      return (euc_distance(p_0, p_2) >= euc_distance(p_0, p_1))? true : false;
    }
    else
    {
      return (tmp == 2)? true: false;
    }
  });
  // after sorting, check if two or more points have the same angle.
  int m = 1;
  int n = points.size();
  for(int i = 1; i < n; ++i)
  {
    while ((i < n-1) && (orientation(p_0, points[i],points[i+1]) == 0))
    {
          i++;
    }
    //remove all except furthest
    points[m] = points[i];
    m++;
  }
  if (m < 3)
  {
    std::cout << "closure not possibles" << '\n';
    return {};
  }

  // first two points in sorted array are part of convex hull
  // check other m-2, one by one,
  // remove if not coutnerclockwise(they dont make left turn)

  std::stack<point> st;
  st.push(points[0]);
  st.push(points[1]);
  st.push(points[2]);

  for (int i = 3; i < m; i++)
  {

     // remove if it is not left turn
     while (orientation(get_second(st), st.top(), points[i]) != 2)
     {
       st.pop();
     }
     st.push(points[i]);
  }
  std::vector<point> result;
  //resulting hull closure in stack
  while (!st.empty())
  {
      point p = st.top();
      result.emplace_back(p);
      st.pop();
  }
  return result;
}

// 0  colinear
// 1  clockwise
// 2  counterclockwise
int orientation(point p_1, point p_2, point p_3)
{
    int tmp = (p_2.y - p_1.y) * (p_3.x - p_2.x) -
              (p_2.x - p_1.x) * (p_3.y - p_2.y);

    if (tmp == 0)
      return 0;  // colinear
    return (tmp > 0)? 1: 2;
}
point get_second(std::stack<point> &st)
{
    point p = st.top();
    st.pop();
    point res = st.top();
    st.push(p);
    return res;
}
int euc_distance(point p_1, point p_2)
{
    return sqrt((p_1.x - p_2.x)*(p_1.x - p_2.x) +
          (p_1.y - p_2.y)*(p_1.y - p_2.y));
}
