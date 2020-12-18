#include <bits/stdc++.h>

#define MAX_ARRAY 25 //maximum size of array
#define MAX_NO 200  // maximum for member value


void heapify(std::vector<int> &array, int value);
std::vector<int> heap_sort(std::vector<int> &array);
void print_array(std::vector<int> &array);

int main(){

  int ind;
  std::cout << "1. random array\n2. custom array" << '\n';
  std::cin >> ind;

  if(ind == 1)
  {
    srand((unsigned) time(0));
    int n = rand() % MAX_ARRAY;

    std::vector<int> array;
    for(int i = 0; i < n; ++i)
      array.push_back(rand() % MAX_NO);

    std::vector<int> sorted_array;
    sorted_array = heap_sort(array);
    print_array(sorted_array);
  }
  else if(ind == 2)
  {
    std::cout << "\nimport numbers(enter any charachter key to end):" << '\n';
    std::vector<int> array;
    int tmp;
    while(std::cin >> tmp)
      array.push_back(tmp);


    std::vector<int> sorted_array;
    sorted_array = heap_sort(array);
    print_array(sorted_array);
  }
  else
    std::cout << "wrong option" << '\n';

  std::cout << '\n';

  return 0;
}


std::vector<int> heap_sort(std::vector<int> &array)
{
  for(int i = array.size()/2-1; i >= 0; --i)
  {
    heapify(array,i);
  }

  std::vector<int> tmp;
  int n = array.size();
  for(int i = 0; i < n; i++)
  {
    tmp.push_back(array[0]);
    array[0] = array.back();
    array.pop_back();
    heapify(array, 0);
  }
  return tmp;
}


void heapify(std::vector<int> &array, int value)
{
  int max = array[value];
  int max_index = value;

  int left_child = 2*value + 1;
  int right_child = 2*value + 2;

  int n = array.size();
  if(left_child < n && array[left_child] > max)
  {
    max_index = left_child;
    max = array[left_child];
  }
  if(right_child < n && array[right_child] > max)
  {
    max_index = right_child;
    max = array[right_child];
  }
  if(value != max_index)
  {
    std::swap(array[value], array[max_index]);
    heapify(array, max_index);
  }
}

void print_array(std::vector<int> &array)
{
  for(auto &a : array)
    std::cout << a << ' ';
  std::cout << '\n';
}
