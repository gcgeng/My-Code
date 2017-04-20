#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#define random(x) rand() % x + 1
using namespace std;
int main() {
  srand(time(NULL));
  int n = 10, m = 1;
  cout << n << ' ' << m << endl;
  for (int i = 2; i <= n; i++) {
    int x = random(i - 1), y = random(m * 4);
    while (!x || !y) x = random(i - 1), y = random(m * 4);
    cout << x << ' ' << y << endl;
  }
  return 0;
}
