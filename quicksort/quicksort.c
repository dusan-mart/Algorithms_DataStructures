#include <stdio.h>


int quicksort(int arr[], int start, int end);
int partition(int arr[], int start, int end);



int main(){

  printf("Insert number of elements of array:\n");
  int n;
  scanf("%d", &n);

  int i;
  int arr[n];

  printf("Insert %d numbers:\n", n);
  for(i = 0; i < n; ++i)
  {
    int tmp;
    scanf("%d", &tmp);
    arr[i] = tmp;
  }
  quicksort(arr, 0, n-1);


  printf("Sorted array: ");
  for(i = 0; i < n; ++i)
  {
    printf("%d ", arr[i]);
  }
  printf("\n\n");
  return 0;
}

int quicksort(int arr[], int start, int end)
{
  if(start >= end)
    return 1;

  int mid = partition(arr, start, end);
  quicksort(arr, start, mid-1);
  quicksort(arr, mid+1, end);
}

int partition(int arr[], int start, int end)
{
  int i,j;
  j = start - 1;

  int key = arr[end];
  for(i = start; i < end; ++i)
  {
    if(arr[i] < key)
    {
      j++;
      int tmp = arr[j];
      arr[j] = arr[i];
      arr[i] = tmp;
    }
  }
  int tmp = arr[end];
  arr[end] = arr[j+1];
  arr[j+1] = tmp;
  return j+1;
}
