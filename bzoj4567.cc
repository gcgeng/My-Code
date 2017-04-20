#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define ll long long
#define pa std::pair<int, int>
const int maxn = 100000 + 100;
const int maxlen = 520000 + 100;
int n;
struct edge {
  int to, next;
} e[maxn << 1];
char str[maxlen];
int rt = 1, sz = 1, ch[maxlen][26], len, id[maxlen], tot, head[maxn],
    size[maxn], f[maxn], cnt, fa[maxn];
std::vector<pa> v[maxn << 1];
inline void ins(int id) {
  int p = rt;
  for (int i = len; i >= 1; i--) {
    int x = str[i] - 'a';
    if (!ch[p][x]) {
      ch[p][x] = ++sz;
    }
    p = ch[p][x];
  }
  ::id[p] = id;
}
inline void add_edge(int u, int v) {
  e[++tot].to = v;
  e[tot].next = head[u];
  fa[v] = u;
  head[u] = tot;
}
void dfs(int x, int fa) {
  if (id[x]) {
    add_edge(fa, id[x]);
    fa = id[x];
  }
  for (int i = 0; i < 26; i++) {
    if (ch[x][i])
      dfs(ch[x][i], fa);
  }
}
void dfs2(int x) {
  size[x] = 1;
  for (int i = head[x]; i; i = e[i].next) {
    int y = e[i].to;
    dfs2(y);
    v[x].push_back(std::make_pair(size[y], y));
    size[x] += size[y];
  }
  std::sort(v[x].begin(), v[x].end());
}
void getf(int x) {
  if (x)
    f[x] = ++cnt;
  for (int i = 0; i < v[x].size(); i++)
    getf(v[x][i].second);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", str + 1);
    len = strlen(str + 1);
    ins(i);
  }
  dfs(1, 0);
  dfs2(0);
  getf(0);
  ll ans = 0;
  for (int i = 1; i <= n; i++)
    ans += f[i] - f[fa[i]];
  printf("%lld", ans);
}
