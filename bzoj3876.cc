#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int inf = INT_MAX;
const int maxn = 305 * 4;
const int M = 10000;
struct edge1 {
  int from;
  int to;
  int low;
  int high;
  int cost;
};
vector<edge1> es;
struct edge {
  int from;
  int to;
  int cap;
  int cost;
};
vector<edge> edges;
vector<int> G[maxn];
inline void add_edge(int from, int to, int cap, int cost) {
  edges.push_back((edge){from, to, cap, cost});
  edges.push_back((edge){to, from, 0, -cost});
  int m = edges.size();
  G[from].push_back(m - 2);
  G[to].push_back(m - 1);
}
inline int read() {
  char c = getchar();
  int f = 1, x = 0;
  while (!isdigit(c)) {
    if (c == '-')
      f = -1;
    c = getchar();
  }
  while (isdigit(c))
    x = x * 10 + c - '0', c = getchar();
  return x * f;
}
int n, s, t, V;
void build_network() {
  for (int i = 0; i < es.size(); i++) {
    edge1 &e = es[i];
    add_edge(e.from, e.to, e.high - e.low, e.cost);
    add_edge(e.from, e.to, e.low, e.cost - M);
  }
}
int dist[maxn], a[maxn], pree[maxn], inq[maxn];
bool spfa(int s, int t, int &cost) {
  for (int i = 0; i < V; i++)
    dist[i] = inf;
  memset(pree, 0, sizeof(pree));
  memset(inq, 0, sizeof(inq));
  a[s] = inf;
  dist[s] = 0;
  queue<int> q;
  q.push(s);
  inq[s] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    inq[u] = 0;
    for (int i = 0; i < G[u].size(); i++) {
      edge &e = edges[G[u][i]];
      if (e.cap > 0 && dist[e.to] > dist[u] + e.cost) {
        pree[e.to] = G[u][i];
        dist[e.to] = dist[u] + e.cost;
        a[e.to] = min(e.cap, a[u]);
        if (!inq[e.to]) {
          q.push(e.to);
          inq[e.to] = 1;
        }
      }
    }
  }
  if (dist[t] >= inf)
    return false;
  cost += a[t] * dist[t];
  int u = t;
  while (u != s) {
    edges[pree[u]].cap -= a[t];
    edges[pree[u] ^ 1].cap += a[t];
    u = edges[pree[u]].from;
  }
  return true;
}
int mcmf(int s, int t) {
  int cost = 0;
  while (spfa(s, t, cost))
    ;
  //    cout << "Hey:" << cost << endl;
  return cost;
}
int main() {
  //  freopen("input", "r", stdin);
  scanf("%d", &n);
  s = 0, t = n + 1, V = t + 1;
  int cnt = 0;
  es.push_back((edge1){s, 1, 0, inf, 0});
  for (int i = 1; i <= n; i++) {
    int k;
    k = read();
    for (int j = 0; j < k; j++) {
      int a, b;
      a = read();
      b = read();
      es.push_back((edge1){i, a, 1, inf, b});
      cnt += 1;
    }

    es.push_back((edge1){i, t, 0, inf, 0});
  }
  build_network();
  int ans = mcmf(s, t);
  printf("%d", ans + M * cnt);
}
