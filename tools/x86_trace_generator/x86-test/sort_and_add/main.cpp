#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

#define all(x) x.begin(), x.end()

const int MAX_ITER = 1e2;
const int MAX_VAL = 1000;
const int MIN_VAL = 1;

vector<int> arr;

extern "C" {
  int PIM_FUNC_START(int arg) { return 1; }
  int PIM_FUNC_END(int arg) { return 1; }
  int SIM_BEGIN(int arg) { return 1; }
  int SIM_END(int arg = 1) { return 1; }
}


int main (int argc, char **argv) {

  SIM_BEGIN(1);
  for (int i = 0; i < MAX_ITER; i++) {
    int x = rand() % MAX_VAL + MIN_VAL;
    arr.push_back(x);
  }

  sort(all(arr));

  PIM_FUNC_START(1);
  long long sum = 0;
  for (int i = 0; i < (int)arr.size(); i++) {
    sum += arr[i];
  }
  PIM_FUNC_END(1);

  SIM_END(1);

  printf("sum : %lld\n", sum);
}


