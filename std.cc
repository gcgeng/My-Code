#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
const int maxn = 1000000 + 100;
struct edge {
  int to, val, next;
  edge(int a, int b, int c) : to(a), val(b), next(c) {}
  edge() {}
} e[maxn << 2];
int n, m, xx, cnt = 0;
int a[maxn], head[maxn], fa[maxn], ans[maxn], dist[maxn];
void add_edge(int u, int v, int val) {
  e[++cnt] = edge(v, val, head[u]);
  head[u] = cnt;
}
void add(int u, int v, int val) {
  add_edge(u, v, val);
  add_edge(v, u, val);
}
void dfs(int u, int fa) {
  int tmp = 0;
  for (int i = head[u]; i; i = e[i].next) {
    if (e[i].to != fa) {
      dist[e[i].to] = dist[u] + e[i].val;
      dfs(e[i].to, u);
      if (ans[e[i].to] + e[i].val > tmp) tmp = ans[e[i].to] + e[i].val;
    }
  }
  ans[u] = tmp;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d %d", &n, &m);
  fa[1] = 0;
  for (int i = 2; i <= n; i++) {
    scanf("%d %d", &fa[i], &xx);
    add(fa[i], i, xx);
  }
  for (int i = 1; i <= n; i++) {
    memset(dist, 0, sizeof(dist));
    memset(ans, 0, sizeof(ans));
    dfs(i, 0);
    a[i] = ans[i];
  }
  for (int i = 1; i <= n; i++) printf("%d ", a[i]);
  // return 0;
  int ans = 0;
  for (int l = 1; l <= n; l++)
    for (int r = l; r <= n; r++) {
      bool flag = true;
      for (int i = l; i <= r; i++) {
        for (int j = i + 1; j <= r; j++) {
          if (abs(a[i] - a[j]) > m) {
            flag = false;
          }
        }
      }
      if (flag) ans = std::max(ans, r - l + 1);
    }
  printf("%d\n", ans);
  return 0;
}
