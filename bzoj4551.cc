#include <cstdio>
#define init int l = t[k].l, r = t[k].r, mid = (l + r) >> 1
const int maxn = 201000;
int n, Q, cnt;
struct edge {
  int to, next;
} e[maxn << 1];
struct seg {
  int l, r, data;
} t[maxn << 2];
int head[maxn], q[maxn], bl[maxn], belong[maxn], size[maxn], dfn, like[maxn],
    tag[maxn], fa[maxn], deep[maxn];
void add_edge(int u, int v) {
  e[++cnt].to = v;
  e[cnt].next = head[u];
  head[u] = cnt;
}
void dfs1(int x) {
  size[x] = 1;
  for (int i = head[x]; i; i = e[i].next) {
    if (e[i].to != fa[x]) {
      fa[e[i].to] = x;
      deep[e[i].to] = deep[x] + 1;
      dfs1(e[i].to);
      size[x] += size[e[i].to];
      if (size[e[i].to] > size[like[x]])
        like[x] = e[i].to;
    }
  }
}
void dfs2(int x, int chain) {
  bl[x] = ++dfn;
  q[dfn] = x;
  belong[x] = chain;
  if (like[x])
    dfs2(like[x], chain);
  for (int i = head[x]; i; i = e[i].next) {
    if (e[i].to != fa[x] && e[i].to != like[x]) {
      dfs2(e[i].to, e[i].to);
    }
  }
}
void build(int k, int l, int r) {
  t[k].l = l, t[k].r = r, t[k].data = (l <= 1 && 1 <= r) ? 1 : 0;
  if (l == r)
    return;
  int mid = (l + r) >> 1;
  build(k << 1, l, mid);
  build(k << 1 | 1, mid + 1, r);
}
void update(int k) {
  t[k].data = t[k << 1 | 1].data ? t[k << 1 | 1].data : t[k << 1].data;
}
void modify(int k, int pos, int val) {
  init;
  if (l == r) {
    if (deep[val] > deep[t[k].data])
      t[k].data = val;
    return;
  }
  if (pos <= mid)
    modify(k << 1, pos, val);
  else
    modify(k << 1 | 1, pos, val);
  update(k);
}
int query(int k, int x, int y) {
  init;
  if (x <= l && r <= y) {
    return t[k].data;
  }
  int ans = 0;
  if (x <= mid) {
    int t = query(k << 1, x, y);
    if (deep[t] > deep[ans])
      ans = t;
  }
  if (y > mid) {
    int t = query(k << 1 | 1, x, y);
    if (deep[t] > deep[ans])
      ans = t;
  }
  return ans;
}
void ask(int x, int f) {
  int ans = 0;
  while (belong[x] != belong[f]) {
    int t = query(1, bl[belong[x]], bl[x]);
    ans = t ? t : 0;
    if (ans)
      break;
    x = fa[belong[x]];
  }
  int t = query(1, bl[belong[x]], bl[x]);
  ans = t ? t : 0;
  printf("%d\n", ans);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d %d", &n, &Q);
  deep[0] = -1;
  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    add_edge(x, y);
    add_edge(y, x);
  }
  dfs1(1);
  dfs2(1, 1);
  build(1, 1, dfn);
  while (Q--) {
    char op[5];
    scanf("%s", op);
    if (op[0] == 'Q') {
      int x;
      scanf("%d", &x);
      ask(x, 1);
    } else {
      int x;
      scanf("%d", &x);
      tag[x] = 1;
      modify(1, bl[x], x);
    }
  }
}
