#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

extern "C" {
  int PIM_FUNC_START(int arg) {return 1;}
  int PIM_FUNC_END(int arg) {return 1;}
  int SIM_BEGIN(int arg) {return 1;}
  int SIM_END(int arg) {return 1;}
}

string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

string get_rand_string(int len) {
  usleep(1000000);
  srand(time(0));
  int cnt = (int) alphabet.size();
  string ret = "";
  for (int i = 0; i < len; i++) {
    int idx = rand() % cnt;
    ret += alphabet[idx];
  }
  return ret;
}

vector<int> get_pi(string key) {
  int m = (int) key.size();
  int j = 0;
  vector<int> pi(m, 0);
  for (int i = 1; i < m; i++) {
    while (j > 0 && key[i] != key[j]) 
      j = pi[j-1];
    if (key[i] == key[j])
      pi[i] = ++j;
  }
  return pi;
}

// TODO 
// PIM_FUNC_START && PIM_FUNC_END requires fine grained managing of code ..
// is there any better method??????
vector<int> kmp(string big, string key) {
  SIM_BEGIN(1);
  vector<int> ans;
  auto pi = get_pi(key);
  int n = (int)big.size();
  int m = (int)key.size();
  int j = 0;
  for (int i = 0; i < n; i++) {
    while (1) {

      if (j <= 0)
        break;

      PIM_FUNC_START(1);
      if (big[i] == key[j])
        break;
      PIM_FUNC_END(1);

      j = pi[j-1];
    }

    PIM_FUNC_START(1);
    if (big[i] != key[j])
      continue;
    PIM_FUNC_END(1);

    if (j == m - 1) {
      ans.push_back(i - m + 1);
      j = pi[j];
    } else {
      j++;
    }
  }
  SIM_END(1);
  return ans;
}

int main (int argc, char **argv) {
  if (argc != 3) {
    printf("usage : ./main [key length] [big length]\n");
    exit(0);
  }
  int key_len = atoi(argv[1]);
  int big_len = atoi(argv[2]);

  auto key = get_rand_string(key_len);
  auto big = get_rand_string(big_len);

/* cout << "key : " << key << endl; */
/* cout << "big : " << big << endl; */

  auto ans = kmp(big, key);
  
  for (auto idx : ans) 
    cout << idx << ", ";
  cout << endl;
  return 0;
}
