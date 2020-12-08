#include <bits/stdc++.h>


void insertion_sort(std::vector<int> &array);
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

    insertion_sort(array);
    print_array(array);
  }
  else if(ind == 2)
  {
    std::cout << "\nimport numbers(enter any charachter key to end):" << '\n';
    std::vector<int> array;
    int tmp;
    while(std::cin >> tmp)
      array.push_back(tmp);

    insertion_sort(array);
    print_array(array);
  }
  else
    std::cout << "wrong option" << '\n';

  std::cout << '\n';

  return 0;
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

void print_array(std::vector<int> &array)
{
  for(auto &a : array)
    std::cout << a << ' ';
  std::cout << '\n';
}
