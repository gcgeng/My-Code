#include <cstdio>
int main() {
  int f[1000][1000];
  for (int i = 1; i < 1000; ++i)
    for (int j = 1; j < 1000; j++) {
      f[j][i]++;
    }
  return 0;
}
