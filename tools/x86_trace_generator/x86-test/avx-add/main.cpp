#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>


extern "C" {
  int PIM_FUNC_START(int arg) {return 1;}
  int PIM_FUNC_END(int arg) {return 1;}
  int SIM_BEGIN(int arg) {return 1;}
  int SIM_END(int arg) {return 1;}
}
const int sz = 1e8;

float *a;
float *b;
float *c;

void foo();

void fill_arrays(){
  for (int i=0; i<sz; i++){
    b[i] = 1.0;
    c[i] = 2.0;
  }
}

int check_arrays(){
  int ret = 0;
  for (int i=0; i<sz; i++){
    if (a[i] == 3)
      continue;
    else
      printf("FAIL, corruption in arithmetic");
    ret =  -1;
    break;
  }
  return ret;
}


int main(int argc, char **argv){

  // we need to allocate aligned memory
  // not sure if aligned_allloc uses avx instructions??
  a = (float *)aligned_alloc(32, sizeof(float) * sz);
  b = (float *)aligned_alloc(32, sizeof(float) * sz);
  c = (float *)aligned_alloc(32, sizeof(float) * sz);
  fill_arrays();

  SIM_BEGIN(1);
  foo();
  SIM_END(1);

  if (check_arrays())
    return -1;

  printf("Works !!!\n");
  
  free(a);
  free(b);
  free(c);

  return 0;
}

void foo(){
  __m256 result,B,C;
  for (int i=0; i<sz; i+=sizeof(__m256)/sizeof(float)){
    // start pim recording
    PIM_FUNC_START(1);

    B =  _mm256_load_ps(&b[i]);
    C =  _mm256_load_ps(&c[i]);
    result = _mm256_add_ps(B,C);
    _mm256_store_ps(&a[i], result);

    // end pim recording
    PIM_FUNC_END(1);

  }
}
