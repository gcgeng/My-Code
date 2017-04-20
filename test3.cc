#include <cstdio>
#include <cstring>
#define ll long long
const int maxn = 200100;
int n, q, cnt = 1, dfn = 0;
int val[maxn], l[maxn], r[maxn], bit[maxn], head[maxn];
struct edge {
  int to, next;
} e[maxn << 1];
void add_edge(int u, int v) {
  e[++cnt].to = v;
  e[cnt].next = head[u];
  head[u] = cnt;
}
void add(int u, int v) {
  add_edge(u, v);
  add_edge(v, u);
}
void dfs(int x, int fa) {
  l[x] = ++dfn;
  for (int i = head[x]; i; i = e[i].next) {
    if (e[i].to != fa) {
      dfs(e[i].to, x);
    }
  }
  r[x] = dfn;
}
void change(int x, int val) {
  for (int i = x; i <= n; i += i & (-i))
    bit[i] += val;
}
int query(int pos) {
  int ret = 0;
  for (int i = pos; i; i -= i & (-i))
    ret += bit[i];
  return ret;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d %d", &n, &q);
  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    add(x, y);
  }
  dfs(1, 0);
  for (int i = 1; i <= n; i++)
    scanf("%d", &val[i]);
  for (int i = 1; i <= n; i++) {
    change(l[i], val[i]);
  }
  while (q--) {
    int opt, x;
    scanf("%d %d", &opt, &x);
    if (opt == 1) {
      int v;
      scanf("%d", &v);
      val[x] = v;
      memset(bit, 0, sizeof(bit));
      for (int i = 1; i <= n; i++) {
        change(l[i], val[i]);
      }
    } else {
      memset(bit, 0, sizeof(bit));
      dfn = 0;
      dfs(x, 0);
      for (int i = 1; i <= n; i++) {
        change(l[i], val[i]);
      }
      ll ans = 0;
      for (int i = 1; i <= n; i++) {
        ll tmp = (query(r[i]) - query(l[i] - 1));
        tmp *= tmp;
        ans += tmp;
      }
      printf("%lld\n", ans);
    }
  }
}
