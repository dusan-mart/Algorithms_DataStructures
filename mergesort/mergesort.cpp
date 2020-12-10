#include <bits/stdc++.h>

#define MAX_ARRAY 25 //maximum size of array
#define MAX_NO 200  // maximum for member value


void mergesort(std::vector<int> &array);
void mergesort_helper(std::vector<int> &array, int start, int end);
void merge(std::vector<int> &array, int start, int middle, int end);
void print_array(std::vector<int> &array);
void insertion_sort(std::vector<int> &array);


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

    mergesort(array);
    print_array(array);
  }
  else if(ind == 2)
  {
    std::cout << "\nimport numbers(enter any charachter key to end):" << '\n';
    std::vector<int> array;
    int tmp;
    while(std::cin >> tmp)
      array.push_back(tmp);

    mergesort(array);
    print_array(array);
  }
  else
    std::cout << "wrong option" << '\n';

  std::cout << '\n';


  return 0;
}




void mergesort(std::vector<int> &array)
{
  mergesort_helper(array, 0, array.size() - 1);
}

void mergesort_helper(std::vector<int> &array, int start, int end)
{
  //hybrid sort,could use insertion sort for subsets below arbitary size
  //insertion sort has lower overhead on very small data sets
  // if((end - start) < 5)
  // {
  //   insertion_sort(array);
  //   return;
  // }
  if(start >= end)
    return;
  int middle = start + (end - start)/2;
  mergesort_helper(array, start, middle);
  mergesort_helper(array, middle + 1, end);
  merge(array, start, middle, end);

  return ;

}


void merge(std::vector<int> &array, int start, int middle, int end)
{
  std::vector<int> left;
  std::vector<int> right;

  for(int i = start; i <= middle; ++i)
    left.push_back(array[i]);

  for(int i = middle + 1; i <= end; ++i)
    right.push_back(array[i]);

  int size_left = middle - start + 1;
  int size_right = end - middle;

  int i = 0;
  int j = 0;
  int main_counter = start;

  while(i < size_left && j < size_right)
  {
    if(left[i] < right[j])
    {
      array[main_counter] = left[i];
      i++;
    }
    else
    {
      array[main_counter] = right[j];
      j++;
    }
    main_counter++;
  }

  while(i < size_left)
  {
    array[main_counter] = left[i];
    i++;
    main_counter++;
  }

  while(j < size_right)
  {
    array[main_counter] = right[j];
    j++;
    main_counter++;
  }
  return;
}

void print_array(std::vector<int> &array)
{
  for(auto &a : array)
    std::cout << a << ' ';
  std::cout << '\n';
}

void insertion_sort(std::vector<int> &array)
{
  for(unsigned i = 1; i < array.size(); ++i)
  {
    int key = array[i];
    int j = i-1;

    while((j >= 0) && (array[j] > key))
    {
      array[j+1] = array[j];
      j--;
    }
    array[j+1] = key;
  }
}
