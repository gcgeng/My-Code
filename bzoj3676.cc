#include <algorithm>
#include <cstdio>
#define ll long long
#include <cstring>
const int maxn = 600010;
int n;
ll ans;
int p[maxn];
char str[maxn];
struct Suffix_Automaton {
  int trans[maxn][26], fa[maxn][20], pos[maxn], len[maxn], size[maxn];
  int last, root, sz;
  int v[maxn], q[maxn], dep[maxn];
  void init() {
    sz = 0;
    last = root = ++sz;
  }
  void insert(int x, int id) {
    int p = last, np = last = ++sz;
    len[np] = len[p] + 1;
    pos[id] = np;
    size[np] = 1;
    for (; !trans[p][x]; p = fa[p][0])
      trans[p][x] = np;
    if (p == 0)
      fa[np][0] = root;
    else {
      int q = trans[p][x];
      if (len[q] == len[p] + 1) {
        fa[np][0] = q;
      } else {
        int nq = ++sz;
        for (int i = 0; i < 26; i++)
          trans[nq][i] = trans[q][i];
        fa[nq][0] = fa[q][0];
        len[nq] = len[p] + 1;
        fa[q][0] = fa[np][0] = nq;
        for (; trans[p][x] == q; p = fa[p][0])
          trans[p][x] = nq;
      }
    }
  }
  void pre() {
    for (int i = 1; i <= sz; i++)
      v[len[i]]++;
    for (int i = 1; i <= n; i++)
      v[i] += v[i - 1];
    for (int i = sz; i >= 1; i--)
      q[v[len[i]]--] = i;
    for (int i = sz; i >= 1; i--) {
      int t = q[i];
      size[fa[t][0]] += size[t];
    }
    for (int i = 1; i <= sz; i++) {
      int t = q[i];
      dep[t] = dep[fa[t][0]] + 1;
      for (int j = 1; (1 << j) <= dep[t]; j++)
        fa[t][i] = fa[fa[t][i - 1]][i - 1];
    }
  }
  void query(int l, int r) {
    int ret = pos[r];
    for (int i = 19; i >= 0; i--) {
      int t = fa[ret][i];
      if (len[t] >= r - l + 1)
        ret = t;
    }
    ans = std::max(ans, (ll)size[ret] * (r - l + 1));
  }
} sam;
void manacher() {
  int mx = 1, id = 1;
  for (int i = n; i; i--)
    str[i * 2] = '#', str[i * 2 - 1] = str[i];
  n <<= 1;
  for (int i = 2; i <= n; i++) {
    p[i] = std::min(p[id * 2 - i], mx - i);
    while (i - p[i] > 0 && str[i - p[i]] == str[i + p[i]]) {
      int al = (i - p[i]) / 2 + 1;
      int ar = (i + p[i] + 1) / 2;
      // printf("%d %d\n", al, ar);
      sam.query(al, ar);
      p[i]++;
    }
    if (i + p[i] > mx)
      mx = i + p[i], id = i;
  }
}
int main() {
#ifndef ONLINE_JUDGE
// freopen("input", "r", stdin);
#endif
  scanf("%s", str + 1);
  n = strlen(str + 1);
  str[0] = '+', str[n + 1] = '-';
  sam.init();
  for (int i = 1; i <= n; i++) {
    sam.insert(str[i] - 'a', i);
  }
  sam.pre();
  manacher();
  printf("%lld\n", ans);
}
