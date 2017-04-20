#include <cmath>
#include <cstdio>
#include <cstring>
const int maxn = 200100;
const int inf = 0x3f3f3f;
int n, m, f[maxn], g[maxn], h[maxn], k[maxn], block;
int id(int x) {
  if (block != 0)
    return (x - 1) / block + 1;
  return 1;
}
int main(int argc, char const *argv[]) {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d", &n);
  block = (int)sqrt(n);
  memset(f, -1, sizeof(f));
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    f[i] = i + x;
    if (f[i] > n)
      f[i] = -1;
    k[i] = -1;
    h[i] = -1;
    g[i] = inf;
  }
  k[n + 1] = 0;
  for (int i = n; i >= 1; i--) {
    if (f[i] != -1) {
      k[i] = k[f[i]] + 1;
      if (id(i) == id(f[i])) {
        g[i] = g[f[i]] + 1;
        h[i] = h[f[i]];
      } else {
        g[i] = 1;
        h[i] = f[i];
      }
    } else {
      k[i] = 1;
      g[i] = 1;
      h[i] = -1;
    }
  }
  scanf("%d", &m);
  while (m--) {
    int opt;
    scanf("%d", &opt);
    if (opt == 1) {
      if (block == 0) {
        printf("0\n");
        continue;
      }
      int x;
      scanf("%d", &x);
      x++;
      int ans = 1;
      while (f[x] != -1) {
        if (h[x] != -1) {
          ans += g[x];
          x = h[x];
        } else {
          x = f[x];
          ans++;
        }
      }
      printf("%d\n", ans);
    }
    if (opt == 2) {
      if (block == 0)
        continue;
      int x, y;
      scanf("%d %d", &x, &y);
      x++;
      f[x] = x + y;
      k[x] = k[y] + 1;
      if (f[x] > n)
        f[x] = -1;
      if (id(y) == id(x))
        g[x] = g[y] + 1, h[x] = h[y];
      else
        g[x] = y, h[x] = 1;
      for (int i = x; id(i) == id(x) && i; i--) {
        if (f[i] != -1) {
          k[i] = k[f[i]] + 1;
          if (id(i) == id(f[i])) {
            g[i] = g[f[i]] + 1;
            h[i] = h[f[i]];
          } else {
            g[i] = 1;
            h[i] = f[i];
          }
        } else {
          k[i] = 1;
          g[i] = 1;
          h[i] = -1;
        }
      }
    }
  }
  return 0;
}
