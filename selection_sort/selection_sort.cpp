#include <bits/stdc++.h>

#define MAX_ARRAY 25 //maximum size of array
#define MAX_NO 200  // maximum for member value

int find_min(std::vector<int> &array, int start);
void selection_sort(std::vector<int> &array);
void print_array(std::vector<int> &array);

int main(){

  int ind;
  std::cout << "1. random array\n2. custom array" << '\n';
  std::cin >>  ind;

  if(ind == 1)
  {
    srand((unsigned) time(0));
    int n = rand() % MAX_ARRAY;

    std::vector<int> array;
    for(int i = 0; i < n; ++i)
      array.push_back(rand() % MAX_NO);

    selection_sort(array);
    print_array(array);
  }
  else if(ind == 2)
  {
    std::cout << "\nimport numbers(enter any charachter key to end):" << '\n';
    std::vector<int> array;
    int tmp;
    while(std::cin >> tmp)
      array.push_back(tmp);

    selection_sort(array);
    print_array(array);
  }
  else
    std::cout << "wrong option" << '\n';

  std::cout << '\n';
  return 0;
}


int find_min(std::vector<int> &array, int start)
{
  int min = array[start];
  int index = start;
  for(unsigned i = start+1; i < array.size(); ++i)
  {
    if(min > array[i])
    {
      min = array[i];
      index = i;
    }
  }
  return index;
}


void selection_sort(std::vector<int> &array)
{
  for(unsigned i = 0; i < array.size(); ++i)
  {
    int min = find_min(array, i);
    std::swap(array[i], array[min]);
  }
}

void print_array(std::vector<int> &array)
{
  for(auto &a : array)
    std::cout << a << ' ';
  std::cout << '\n';
}
