#include <algorithm>
#include <cstdio>
#include <cstring>
#define ll long long
const ll maxn = 500100 << 1;
char s[maxn], str[maxn];
ll head[maxn], f[maxn];
ll ans;
ll n, cnt = 1;
struct edge {
  ll to, next;
} e[maxn];
void add_edge(ll u, ll v) {
  e[++cnt].to = v;
  e[cnt].next = head[u];
  head[u] = cnt;
}
struct Suffix_Automaton {
  ll fa[maxn], trans[maxn][26], len[maxn], right[maxn];
  ll last, root, sz;
  bool flag[maxn];
  void init() {
    memset(flag, 0, sizeof(flag));
    sz = 0;
    last = root = ++sz;
  }
  void insert(ll x) {
    ll p = last, np = last = ++sz;
    len[np] = len[p] + 1;
    flag[np] = 1;
    right[np] = right[p] + 1;
    for (; !trans[p][x]; p = fa[p])
      trans[p][x] = np;
    if (p == 0)
      fa[np] = root;
    else {
      ll q = trans[p][x];
      if (len[q] == len[p] + 1) {
        fa[np] = q;
      } else {
        ll nq = ++sz;
        fa[nq] = fa[q];
        memcpy(trans[nq], trans[q], sizeof(trans[q]));
        len[nq] = len[p] + 1;
        fa[q] = fa[np] = nq;
        for (; trans[p][x] == q; p = fa[p])
          trans[p][x] = nq;
      }
    }
  }
  void pre() {
    for (ll i = 1; i <= sz; i++) {
      if (fa[i])
        add_edge(fa[i], i);
    }
  }
  void print() {
    for (ll i = 1; i <= sz; i++) {
      printf("%3lld ", i);
    }
    printf("\n");
    for (ll i = 1; i <= sz; i++) {
      printf("%3lld ", len[i]);
    }
    printf("\n");
    for (ll i = 1; i <= sz; i++)
      if (flag[i]) {
        printf("%lld:", i);
        for (ll j = 1; j <= len[i]; j++)
          printf("%c", str[right[i] - (len[i] - j + 1) + 1]);
        printf("\n");
      }
    printf("\n");
  }
} sam;
void dfs(ll x) {
  ll ct = 0;
  f[x] = sam.flag[x] ? 1 : 0;
  for (ll i = head[x]; i; i = e[i].next) {
    dfs(e[i].to);
    ans -= 1ll * 2 * (1ll * f[e[i].to] * ct) * (sam.len[x]);
    ct += f[e[i].to];
  }
  if (f[x] == 1) {
    ans -= 1ll * 2 * (1ll * ct) * (sam.len[x]);
  }
  f[x] += ct;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%s", s + 1);
  n = strlen(s + 1);
  sam.init();
  for (ll i = 1; i <= n; i++) {
    ans += (n * i) - i * i + ((n * n - i * i + n - i) >> 1);
    str[i] = s[n - i + 1];
  }
  for (ll i = 1; i <= n; i++)
    sam.insert(str[i] - 'a');
  sam.pre();
  // sam.print();
  // printf("%lld\n", ans);
  dfs(sam.root);
  printf("%lld\n", ans);
}
