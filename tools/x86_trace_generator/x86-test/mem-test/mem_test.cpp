#include <stdlib.h>
#include <stdio.h>

void foo(char *y) {
  int *x = (int*)malloc(sizeof(int) * 4);
}

int main (int argc, char **argv) {
  free(NULL);
  foo(new char[10]);
  return 0;
}
