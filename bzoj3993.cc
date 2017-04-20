#include <algorithm>
#include <cmath>
#include <cstdio>
#include <queue>
const double eps = 1e-9;
#define ld long double
const int maxn = 110 << 1;
const int inf = 0x3f3f3f;
struct edge {
  int to, next;
  ld cap;
  edge(int a = 0, int b = 0, ld c = 0) : to(a), next(b), cap(c) {}
} e[1500005];
int cnt = 1, n, m, s, t, v;
ld L, R;
int head[maxn], mi[maxn], A[maxn], B[maxn], tod;
ld dist[maxn];
void add_edge(int u, int v, ld c) {
  e[++cnt] = edge(v, head[u], c);
  head[u] = cnt;
}
void add(int u, int v, ld c) {
  add_edge(u, v, c);
  add_edge(v, u, 0);
}
void bfs(int s) {
  std::fill(dist, dist + v, -1);
  dist[s] = 0;
  std::queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = e[i].next) {
      if (dist[e[i].to] == -1 && e[i].cap > eps) {
        dist[e[i].to] = dist[u] + e[i].cap;
        q.push(e[i].to);
      }
    }
  }
}
ld dfs(int s, int t, ld flow) {
  if (s == t)
    return flow;
  for (int i = head[s]; i; i = e[i].next) {
    // printf("%.2f ", e[i].cap);
    if (e[i].cap > eps && dist[e[i].to] > dist[s]) {
      ld d = dfs(e[i].to, t, std::min(e[i].cap, flow));
      if (d > eps) {
        e[i].cap -= d;
        e[i ^ 1].cap += d;
        return d;
      }
    }
  }
  return 0;
}
ld dinic(int s, int t) {
  ld flow = 0;
  while (1) {
    bfs(s);
    if (dist[t] == -1)
      return flow;
    ld d;
    while ((d = dfs(s, t, inf)))
      flow += d;
  }
  return flow;
}
bool check(ld mid) {
  for (int i = 2; i <= cnt; i += 2)
    e[i].cap += e[i ^ 1].cap, e[i ^ 1].cap = 0;
  for (int i = head[s]; i; i = e[i].next)
    e[i].cap = mid * B[e[i].to];
  ld flow = dinic(s, t);
  return std::fabs(flow - (ld)tod) <= eps;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d %d", &n, &m);
  s = 0, t = n + m + 1, v = t + 1, L = 0, R = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &A[i]);
    mi[i] = inf;
  }
  for (int i = 1; i <= m; i++)
    scanf("%d", &B[i]);
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      int x;
      scanf("%d", &x);
      if (x == 1) {
        add(i, j + m, inf);
        mi[j] = std::min(mi[j], B[i]);
      }
    }
    add(0, i, inf);
  }
  for (int i = 1; i <= n; i++) {
    R += A[i] / mi[i];
    add(i + m, t, A[i]);
    tod += A[i];
  }
  //  printf("%d\n", tod);
  R = 5e6;
  while (R - L > eps) {
    ld mid = (L + R) / 2;
    if (check(mid))
      R = mid;
    else
      L = mid;
  }
  printf("%.7Lf", (L + R) / 2);
}
