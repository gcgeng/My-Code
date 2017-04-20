#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
const int maxn = 500500;
const int maxm = maxn << 1;
const int defl = 2001;
const int maxk = 4109;
const int inf = 100000000;
int n, s, t, cnt = 1;
struct edge {
  int to, next, cap;
} e[maxm << 1];
struct point {
  int x, y, t, c;
  bool operator<(const point b) const {
    return (this->x < b.x) || (this->x == b.x && this->y < b.y);
  }
  bool operator==(const point b) const {
    return (this->x == b.x) && (this->y == b.y);
  }
} p[maxn];
int mat[maxk][maxk], idx[maxk][maxk], ans;
int head[maxn], dist[maxn], cur[maxn];
void add(int u, int v, int w) {
  e[++cnt].to = v;
  e[cnt].next = head[u];
  e[cnt].cap = w;
  head[u] = cnt;
}
void add_edge(int u, int v, int w) {
  add(u, v, w);
  add(v, u, 0);
}
void bfs(int s, int t) {
  memset(dist, -1, sizeof(dist));
  dist[s] = 0;
  std::queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i; i = e[i].next) {
      int v = e[i].to;
      if (e[i].cap > 0 && dist[v] == -1) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }
}
int dfs(int s, int t, int flow) {
  if (s == t) return flow;
  for (int& i = cur[s]; i; i = e[i].next) {
    int u = e[i].to;
    if (e[i].cap > 0 && dist[u] > dist[s]) {
      int d = dfs(u, t, std::min(flow, e[i].cap));
      if (d) {
        e[i].cap -= d;
        e[i ^ 1].cap += d;
        return d;
      }
    }
  }
  return 0;
}
int dinic(int s, int t) {
  int ans = 0;
  while (1) {
    bfs(s, t);
    if (dist[t] == -1) break;
    memcpy(cur, head, sizeof(head));
    int d;
    while ((d = dfs(s, t, inf))) ans += d;
  }
  return ans;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int x, y, z, c;
    scanf("%d %d %d %d", &x, &y, &z, &c);
    x += defl - z, y += defl - z, p[i].t = (x + y) % 3;
    c *= (x + y) % 3 ? 10 : 11;
    p[i].x = x, p[i].y = y;
    mat[x][y] += c;
    ans += c;
  }
  std::sort(p + 1, p + 1 + n);
  n = std::unique(p + 1, p + 1 + n) - p - 1;
  s = 0, t = 2 * n + 1;
  for (int i = 1; i <= n; i++)
    idx[p[i].x][p[i].y] = i, p[i].c = mat[p[i].x][p[i].y];
  for (int i = 1; i <= n; i++)
    if (p[i].t == 1)
      add_edge(s, i, p[i].c);
    else if (p[i].t == 0)
      add_edge(i, i + n, p[i].c);
    else
      add_edge(i, t, p[i].c);
  for (int i = 1; i <= n; i++)
    if (!p[i].t) {
      int x = p[i].x, y = p[i].y;
      if (idx[x + 1][y]) add_edge(idx[x + 1][y], i, inf);
      if (idx[x][y + 1]) add_edge(idx[x][y + 1], i, inf);
      if (idx[x - 1][y - 1]) add_edge(idx[x - 1][y - 1], i, inf);
      if (idx[x - 1][y]) add_edge(i + n, idx[x - 1][y], inf);
      if (idx[x][y - 1]) add_edge(i + n, idx[x][y - 1], inf);
      if (idx[x + 1][y + 1]) add_edge(i + n, idx[x + 1][y + 1], inf);
    }
  ans -= dinic(s, t);
  printf("%d.%d", ans / 10, ans % 10);
  return 0;
}
