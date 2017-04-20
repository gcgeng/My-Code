#include <cstdio>
const int mod = 1e9 + 7;
const int maxn = 1e5 + 1e2;
int n, m, cnt;
int f[maxn][18], log_2[maxn], lc[maxn * 18], rc[maxn * 18], fa[maxn * 18];
void init() {
  cnt = 0;
  for (int i = 1; i <= n; i++) {
    if ((1 << (cnt + 1)) <= i)
      cnt++;
    log_2[i] = cnt;
  }
  cnt = 0;
  for (int j = 0; (1 << j) <= n; j++) {
    for (int i = 1; i + (1 << (j)) - 1 <= n; i++) {
      f[i][j] = ++cnt;
      if (j) {
        lc[cnt] = f[i][j - 1];
        rc[cnt] = f[i + (1 << (j - 1))][j - 1];
      }
    }
  }
  for (int i = 1; i <= cnt; i++)
    fa[i] = i;
}
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int a, int b) {
  int x = find(a), y = find(b);
  if (x != y)
    fa[x] = y;
}
int main() {
  scanf("%d %d", &n, &m);
  init();
  while (m--) {
    int s1, s2, e1, e2;
    scanf("%d %d %d %d", &s1, &e1, &s2, &e2);
    int len = log_2[e1 - s1 + 1];
    merge(f[s1][len], f[s2][len]);
    merge(f[e1 - (1 << len) + 1][len], f[e2 - (1 << len) + 1][len]);
  }
  int t;
  for (int i = cnt; i > n; i--) {
    if ((t = find(i)) != i) {
      merge(lc[i], lc[t]);
      merge(rc[i], rc[t]);
    }
  }
  t = 0;
  for (int i = 1; i <= n; i++) {
    t += ((find(i)) == i);
  }
  int ans = 9;
  for (int i = 1; i < t; i++)
    ans = (1ll * ans * 10) % mod;
  printf("%d\n", ans);
}
