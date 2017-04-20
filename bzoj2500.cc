#include <algorithm>
#include <cctype>
#include <cstdio>
#include <map>
const int maxn = 1e2;
// std::map<int, int> mp;
int read() {
  char ch = getchar();
  int x = 0, f = 1;
  while (!isdigit(ch)) {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
struct edge {
  int to, val, next;
  edge(int a, int b, int c) : to(a), val(b), next(c) {}
  edge() {}
} e[maxn << 1];
struct ps {
  int pos, val;
  ps() {}
  ps(int a, int b) : pos(a), val(b) {}
} q[maxn], p[maxn];
int n, m, cnt;
int rqy[maxn], rqy2[maxn], head[maxn], dist[maxn], like[maxn], ans[maxn],
    up[maxn];
int Ans, pfront = 1, qfront = 1, pback, qback;
void add_edge(int u, int v, int w) {
  e[++cnt] = edge(v, w, head[u]);
  head[u] = cnt;
}
void add(int u, int v, int w) {
  add_edge(u, v, w);
  add_edge(v, u, w);
}
void dfs(int u, int fa) {
  // belong[u] = chain;
  for (int i = head[u]; i; i = e[i].next) {
    if (e[i].to != fa) {
      dist[e[i].to] = dist[u] + e[i].val;
      dfs(e[i].to, u);
      if (rqy[e[i].to] + e[i].val >= rqy[u]) {
        rqy2[u] = rqy[u];
        rqy[u] = rqy[e[i].to] + e[i].val;
        like[u] = e[i].to;
      } else if (rqy[e[i].to] + e[i].val >= rqy2[u])
        rqy2[u] = rqy[e[i].to] + e[i].val;
    }
  }
}
void dfs2(int u, int fa) {
  for (int i = head[u]; i; i = e[i].next) {
    if (e[i].to != fa) {
      up[e[i].to] = std::max(up[e[i].to], up[u] + e[i].val);
      if (e[i].to != like[u])
        up[e[i].to] = std::max(up[e[i].to], rqy[u] + e[i].val);
      else
        up[e[i].to] = std::max(up[e[i].to], rqy2[u] + e[i].val);
      dfs2(e[i].to, u);
    }
  }
}
void init() {
  scanf("%d %d", &n, &m);
  for (int i = 2; i <= n; i++) {
    int x = read(), y = read();
    add(x, i, y);
  }
}
void solve_tree() {
  /*
  开始的脑残想法:
  每个点要么走向他的子树, 要么回到根, 走向根的另一颗子树
  然而这么做是不对的, 其实很容易构造, 就是构造一下链的情况就可以了,
  所以以后做这种题目想出算法之后一定要多尝试几种不同的树的形态, 比如: 链, 菊花,
  类菊花, 等等, 这样, 保证了算法的正确性之后再开始编写程序, 不要想当然.
  脑残眼残害人啊!!!
  */
  dfs(1, 0);
  dfs2(1, 0);
  for (int i = 1; i <= n; i++) ans[i] = std::max(rqy[i], up[i]);
  for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
}
void solve_seq() {
  //设立两个单调队列,维护最大值和最小值
  for (int i = 1; i <= n; i++) {
    int x = ans[i];
    while (x < p[pback].val && pfront <= pback) pback--;
    p[++pback] = ps(i, x);
    while (x < q[qback].val && qfront <= qback) qback--;
    q[++qback] = ps(i, x);
    while (abs(p[pfront].val - q[qfront].val) > m && pfront < pback &&
           qfront < qback)
      pfront++, qfront++;
    Ans = std::max(Ans, q[qback].pos - q[qfront].pos + 1);
  }
}
void solve() {
  solve_tree();
  solve_seq();
  printf("%d\n", Ans);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  init();
  solve();
  return 0;
}
