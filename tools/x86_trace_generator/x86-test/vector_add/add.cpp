#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>


using namespace std;

const int LEN = 1e6;

struct arg_s {
  int *x, *y;
  int len;
};

void *add_pim(void *par) {
  arg_s *arg = (arg_s *)par;

  int len = arg->len;
  int *x = arg->x;
  int *y = arg->y;

  for (int i = 0; i < len; i++) {
    x[i] = 1;
    y[i] = 2;
  }

  for (int i = 0; i < len; i++) {
    x[i] += y[i];
  }

  return x;
}

int main (int argc, char **argv) {
  int *x_cpu, *y_cpu;
  int *x_pim, *y_pim;

  //main thread
  x_cpu = (int *)malloc(sizeof(int)*LEN);
  y_cpu = (int *)malloc(sizeof(int)*LEN);
  for (int i = 0; i < LEN; i++) {
    x_cpu[i] = 1;
    y_cpu[i] = 2;
  }

  for (int i = 0; i < LEN; i++) {
    x_cpu[i] += y_cpu[i];
  }
  

  // child thread
  x_pim = (int *)malloc(sizeof(int)*LEN);
  y_pim = (int *)malloc(sizeof(int)*LEN);

  arg_s arg = {x_pim, y_pim, LEN};
  pthread_t child;
  
  pthread_create(&child, NULL, add_pim, &arg);
  pthread_join(child, (void **)&x_pim);

  bool ok = true;
  for (int i = 0; i< LEN; i++) {
    int diff = x_pim[i] - x_cpu[i];
    if (diff) {
      cout << "[*] something went wrong" << endl;
      ok = false;
      break;
    }
  }

  if (ok)
    cout << "success" << endl;
  else
    cout << "fail" << endl;

  free(x_cpu);
  free(y_cpu);
  free(x_pim);
  free(y_pim);

  return 0;
}
