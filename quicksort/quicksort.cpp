#include <bits/stdc++.h>

#define MAX_ARRAY 25 //maximum size of array
#define MAX_NO 200  // maximum for member value

void quicksort(std::vector<int> &array);
void quicksort_helper(std::vector<int> &array, int start, int end);
int partition(std::vector<int> &array, int start, int end);
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

    quicksort(array);
    print_array(array);
  }
  else if(ind == 2)
  {
    std::cout << "\nimport numbers(enter any charachter key to end):" << '\n';
    std::vector<int> array;
    int tmp;
    while(std::cin >> tmp)
      array.push_back(tmp);

    quicksort(array);
    print_array(array);
  }
  else
    std::cout << "wrong option" << '\n';

  std::cout << '\n';

  return 0;
}



void quicksort(std::vector<int> &array)
{
  quicksort_helper(array, 0, array.size()-1);
  return;
}


void quicksort_helper(std::vector<int> &array, int start, int end)
{
  if(start >= end)
    return;
  int tmp = partition(array, start, end);
  quicksort_helper(array, start, tmp-1);
  quicksort_helper(array, tmp+1, end);
}

int partition(std::vector<int> &array, int start, int end)
{
  int j = start-1;
  int key = array[end];
  for(int i = start; i < end; ++i)
  {
    if(array[i] < key)
    {
      j++;
      std::swap(array[i], array[j]);
    }
  }
  std::swap(array[end],array[j+1]);
  return j+1;
}

void print_array(std::vector<int> &array)
{
  for(auto &a : array)
    std::cout << a << ' ';
  std::cout << '\n';
}
