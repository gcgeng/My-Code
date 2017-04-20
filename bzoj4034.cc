#include <cstdio>
#define lowbit(i) (i) & -(i)
const int maxn = 101000;
#define ll long long
ll bit[2][maxn];
ll n, m, cnt = 0;
void change(ll id, ll pos, ll val) {
  for (ll i = pos; i <= n; i += lowbit(i)) {
    bit[id][i] += val;
  }
}
ll query(ll id, ll pos) {
  ll ans = 0;
  for (ll i = pos; i; i -= lowbit(i)) {
    ans += bit[id][i];
  }
  return ans;
}
struct edge {
  ll to, next;
} e[maxn << 1];
ll l[maxn], r[maxn], dfn = 0, val[maxn], deep[maxn], head[maxn], q[maxn];
void add(ll x, ll y) {
  e[++cnt].to = y;
  e[cnt].next = head[x];
  head[x] = cnt;
}
void add_edge(ll x, ll y) {
  add(x, y);
  add(y, x);
}
void dfs(ll x, ll fa) {
  l[x] = ++dfn;
  q[dfn] = x;
  for (ll i = head[x]; i; i = e[i].next) {
    if (e[i].to != fa) {
      deep[e[i].to] = deep[x] + 1;
      dfs(e[i].to, x);
    }
  }
  r[x] = dfn;
}
int main() {
  //  freopen("haoi2015_t2.in", "r", stdin);
  //  freopen("haoi2015_t2.out", "w", stdout);
  scanf("%lld %lld", &n, &m);
  for (ll i = 1; i <= n; i++) {
    scanf("%lld", &val[i]);
  }
  for (ll i = 1; i < n; i++) {
    ll x;
    ll y;
    scanf("%lld %lld", &x, &y);
    add_edge(x, y);
  }
  dfs(1, 0);
  for (ll i = 1; i <= n; i++) {
    change(1, l[i], val[i]);
    change(1, r[i] + 1, -val[i]);
  }
  while (m--) {
    ll opt, x, y;
    scanf("%lld %lld", &opt, &x);
    if (opt == 1) {
      scanf("%lld", &y);
      change(1, l[x], y);
      change(1, r[x] + 1, -y);
    }
    if (opt == 2) {
      scanf("%lld", &y);
      change(0, l[x], y);
      change(1, l[x], -deep[x] * y + y);
      change(0, r[x] + 1, -y);
      change(1, r[x] + 1, deep[x] * y - y);
    }
    if (opt == 3) {
      printf("%lld\n", query(0, l[x]) * deep[x] + query(1, l[x]));
    }
  }
}
