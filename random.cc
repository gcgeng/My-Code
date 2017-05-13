#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#define random(x) rand() % x + 1
using namespace std;
int main() {
  srand(time(NULL));
  int n = random(10);
  int k = random(2*n);
  while(k > (n / 2) * (n - n / 2)) k = random(2*n);
  printf("%d %d", n, k);
  return 0;
}
