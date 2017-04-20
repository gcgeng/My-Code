#include <algorithm>
#include <cstdio>
int n, m;
const int maxn = 50010;
const int maxm = 100010;
const int maxv = maxn + maxm;
struct edge {
  int u, v, a, b;
} e[maxm << 1];
bool cmp1(edge a, edge b) { return a.a < b.a; }
int f[maxn], val[maxv], fa[maxv], ch[maxv][2], rev[maxv], max[maxv];
int findf(int x) { return f[x] == x ? x : f[x] = findf(f[x]); }
void pushdown(int x) {
  if (rev[x]) {
    rev[x] ^= 1;
    rev[ch[x][0]] ^= 1;
    rev[ch[x][1]] ^= 1;
    std::swap(ch[x][0], ch[x][1]);
  }
}
void update(int x) {
  max[x] = x;
  if (val[max[ch[x][0]]] > val[max[x]])
    max[x] = max[ch[x][0]];
  if (val[max[ch[x][1]]] > val[max[x]])
    max[x] = max[ch[x][1]];
}
bool isroot(int x) { return (ch[fa[x]][0] != x) && (ch[fa[x]][1] != x); }
void zig(int x) {
  int y = fa[x], z = fa[y], l = (ch[y][1] == x), r = l ^ 1;
  if (!isroot(y))
    ch[z][ch[z][1] == y] = x;
  fa[ch[y][l] = ch[x][r]] = y;
  fa[ch[x][r] = y] = x;
  fa[x] = z;
  update(y);
  update(x);
}
void splay(int x) {
  int s[maxv], top = 0;
  s[++top] = x;
  for (int i = x; !isroot(i); i = fa[i])
    s[++top] = fa[i];
  while (top)
    pushdown(s[top--]);
  for (int y; !isroot(x); zig(x))
    if (!isroot(y = fa[x]))
      zig((ch[y][0] == x) == (ch[fa[y]][0] == y) ? y : x);
  update(x);
}
void access(int x) {
  for (int t = 0; x; t = x, x = fa[x]) {
    splay(x);
    ch[x][1] = t;
    update(x);
  }
}
void makeroot(int x) {
  access(x);
  splay(x);
  rev[x] ^= 1;
}
void link(int x, int y) {
  makeroot(x);
  fa[x] = y;
}
void cut(int x, int y) {
  makeroot(x);
  access(y);
  splay(y);
  ch[y][0] = fa[x] = 0;
  update(y);
}
void split(int x, int y) {
  makeroot(y);
  access(x);
  splay(x);
}
int ans = 0x3f3f3f;
int main() {
  freopen("input", "r", stdin);
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++)
    f[i] = i;
  for (int i = 1; i <= m; i++) {
    scanf("%d %d %d %d", &e[i].u, &e[i].v, &e[i].a, &e[i].b);
  }
  std::sort(e + 1, e + 1 + m, cmp1);
  for (int i = 1; i <= m; i++) {
    int u = e[i].u, v = e[i].v, x = findf(u), y = findf(v);
    if (x == y) {
      split(u, v);
      int t = max[u];
      if (val[t] > e[i].b) {
        cut(e[t - n].u, t);
        cut(e[t - n].v, t);
      } else {
        if (findf(1) == findf(n)) {
          split(1, n);
          int t = max[1];
          ans = std::min(ans, e[i].a + val[t]);
        }
        continue;
      }
    }
    if (x != y) {
      f[x] = y;
    }
    val[n + i] = e[i].b;
    max[n + i] = n + i;
    link(u, i + n);
    link(v, i + n);
    if (findf(1) == findf(n)) {
      split(1, n);
      int t = max[1];
      ans = std::min(ans, e[i].a + val[t]);
    }
  }
  printf("%d\n", ans == 0x3f3f3f ? -1 : ans);
}
