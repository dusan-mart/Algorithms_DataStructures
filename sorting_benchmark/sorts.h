#include <vector>
#include <iostream>
#include <algorithm>

//custom full quicksort
void quicksort(std::vector<int> &array);
void quicksort_helper(std::vector<int> &array, int start, int end);
int partition(std::vector<int> &array, int start, int end);

//heap sort
void heapify(std::vector<int> &array, int value);
std::vector<int> heap_sort(std::vector<int> &array);

//quicksort, bubble sort for arrays <=64
void bubble_sort(std::vector<int> &array, size_t start, size_t end);
void quickBubble_helper(std::vector<int> &array, int start, int end);

//finding median for perfect partition, worst case O(nlogn)
void quicksort_median(std::vector<int> &array);
void quicksort_helper_median(std::vector<int> &array, int start, int end);
void heapify_from_bottom(std::vector<int> &array, int value);
void heapify_from_top(std::vector<int> &array, int value);
int partition_find_median(std::vector<int> &array, int start, int end);

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
void quickBubble_sort(std::vector<int> &array)
{
  quickBubble_helper(array, 0, array.size()-1);
  return;
}

void quickBubble_helper(std::vector<int> &array, int start, int end)
{
  if(start >= end)
    return;
  if((end - start) <= 64)
  {
    bubble_sort(array, start, end);
    return;
  }
  int tmp = partition(array, start, end);
  quickBubble_helper(array, start, tmp-1);
  quickBubble_helper(array, tmp+1, end);
}

void bubble_sort(std::vector<int> &arr, size_t start, size_t end)
{
  for(size_t i = start; i < end; ++i)
   for(size_t j = start; j < end-i-1; ++j)
   {
     if(arr[j] > arr[j+1])
      std::swap(arr[j], arr[j+1]);
   }
}

void quicksort_median(std::vector<int> &array)
{
  quicksort_helper_median(array, 0, array.size()-1);
  return;
}


void quicksort_helper_median(std::vector<int> &array, int start, int end)
{
  if(start >= end)
    return;
  if((end - start) <= 64)
  {
    bubble_sort(array, start, end);
    return;
  }
  int tmp = partition_find_median(array, start, end);
  quicksort_helper(array, start, tmp-1);
  quicksort_helper(array, tmp+1, end);
}

int partition_find_median(std::vector<int> &array, int start, int end)
{

  std::vector<int> left;//min heap
  std::vector<int> right;//max heap
  for(int i = start; i <= end; ++i)
  {
    left.push_back(array[i]);
    heapify_from_bottom(left, left.size()-1);

    if(left.size() > (right.size()+1))
    {
      right.push_back((-1)*left[0]);
      heapify_from_bottom(right, right.size()-1);

      left[0] = left.back();
      left.pop_back();
      heapify_from_top(left, 0);
    }
  }
  if((-1)*right[0] < left[0])
  {
    std::swap(left[0], right[0]);
    heapify_from_top(left, 0);
    heapify_from_top(right, 0);
  }

  int median = left[0];
  int index = end;
  for(int i = start; i <= end; ++i)
  {
    if((array[i] <= median+1) || (array[i] <= median+1))
    {
      index = i;
      break;
    }
  }
  std::swap(array[index], array[end]);

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


void heapify_from_bottom(std::vector<int> &array, int value)
{
  if(!array.size())
    return;
  int key = array[value];

  int parent = (value-1)/2;

  if((parent >= 0) && (key > array[parent]))
  {
    std::swap(array[value], array[parent]);
    heapify_from_bottom(array, parent);
  }
}

void heapify_from_top(std::vector<int> &array, int value)
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
    heapify_from_top(array, max_index);
  }
}
