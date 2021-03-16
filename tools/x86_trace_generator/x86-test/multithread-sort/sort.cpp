// Program to implement merge sort using multi-threading
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// number of elements in array
#define MAX 1000000

// number of threads
#define THREAD_MAX 2

using namespace std;

// array of size MAX
int a[MAX];
int part = 0;
int n=0, i=0;

void *printArray(int first, int last);

// merge function for merging two parts
void merge(int low, int mid, int high)
{
  int* left = new int[mid - low + 1];
  int* right = new int[high - mid];

  // n1 is size of left part and n2 is size
  // of right part
  int n1 = mid - low + 1, n2 = high - mid, i, j;

  // storing values in left part
  for (i = 0; i < n1; i++)
    left[i] = a[i + low];

  // storing values in right part
  for (i = 0; i < n2; i++)
    right[i] = a[i + mid + 1];

  int k = low;
  i = j = 0;

  // merge left and right in ascending order
  while (i < n1 && j < n2) {
    if (left[i] <= right[j])
      a[k++] = left[i++];
    else
      a[k++] = right[j++];
  }

  // insert remaining values from left
  while (i < n1) {
    a[k++] = left[i++];
  }

  // insert remaining values from right
  while (j < n2) {
    a[k++] = right[j++];
  }
}

// merge sort function
void merge_sort(int low, int high)
{
  // calculating mid point of array
  int mid = low + (high - low) / 2;
  if (low < high) {

    // calling first half
    merge_sort(low, mid);

    // calling second half
    merge_sort(mid + 1, high);

    // merging the two halves
    merge(low, mid, high);
  }
}

// thread function for multi-threading
void* merge_sort(void* arg)
{
  // which part out of 2 parts

  int thread_part = part++;

  printf("Thread [%d]\n",thread_part);

  // calculating low and high
  int low = thread_part * (MAX / 2);
  int high = (thread_part + 1) * (MAX / 2) - 1;


  // evaluating mid point
  int mid = low + (high - low) / 2;
  if (low < high) {
    merge_sort(low, mid);
    merge_sort(mid + 1, high);
    merge(low, mid, high);
  }
}

//print content of array 
void *printArray(int first, int last)
{
  for (int i = first; i < last; i++)
    cout << a[i] << " ";
  printf("\n");
}

// merge both parts from both threads
void* mergeFinal(void* arg)
{
  merge(0, (MAX - 1)/2, MAX - 1);
}


bool is_sorted() {
  for (int i = 1; i < MAX; i++ ) 
    if (a[i] < a[i-1]) 
      return false;

  return true;
}

#define MAX_VAL  1000
#define MIN_VAL  1

// Main Code
int main(int argc, char *argv[])
{

  srand(time(NULL));

  for(int i = 0; i < MAX; i++) {
    a[i] = rand() % MAX_VAL + MIN_VAL;
  }

  pthread_t threads[THREAD_MAX], merge_thread;

  for (int i = 0; i < THREAD_MAX; i++)
    pthread_create(&threads[i], NULL, merge_sort, (void*)NULL);

  for (int i = 0; i < THREAD_MAX; i++)
    pthread_join(threads[i], NULL);

  pthread_create(&merge_thread, NULL, mergeFinal, (void*)NULL);
  pthread_join(merge_thread, NULL);

  printf("array size : %.1f MB\n", (float)4*MAX/1000000);
  if (is_sorted())
    printf("[*] sorting success\n");
  else
    printf("[*] sorting fail\n");

  long long sum = 0;
  for (int i = 0; i < MAX; i++) {
    sum += a[i];
  }
  printf("[*] sum : %lld\n", sum);


  printf("end test\n");
  return 0;
}
