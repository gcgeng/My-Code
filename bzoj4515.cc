#include <algorithm>
#include <cstdio>
using namespace std;
#define ll long long
const ll inf = 123456789123456789LL;
const ll maxn = 200100;
ll ans;
ll n, m, cnt = 1;
struct edge {
  ll to, next;
  ll w;
} e[maxn << 1];
ll head[maxn], size[maxn], belong[maxn], vis[maxn], fa[maxn][18];
ll deep[maxn], dep[maxn];
ll pl[maxn], que[maxn], sz = 0, fu = 0;
void add_edge(ll u, ll v, ll w) {
  e[++cnt].to = v;
  e[cnt].w = w;
  e[cnt].next = head[u];
  head[u] = cnt;
}
void add(ll u, ll v, ll w) {
  add_edge(u, v, w);
  add_edge(v, u, w);
}
void dfs1(ll x) {
  vis[x] = size[x] = 1;
  for (ll i = 1; i <= 17; i++) {
    if (dep[x] < (1 << i))
      break;
    fa[x][i] = fa[fa[x][i - 1]][i - 1];
  }
  for (ll i = head[x]; i; i = e[i].next) {
    if (!vis[e[i].to]) {
      deep[e[i].to] = deep[x] + e[i].w;
      dep[e[i].to] = dep[x] + 1;
      fa[e[i].to][0] = x;
      dfs1(e[i].to);
      size[x] += size[e[i].to];
    }
  }
}
void dfs2(ll x, ll chain) {
  pl[x] = ++sz;
  que[sz] = x;
  belong[x] = chain;
  ll k = 0;
  for (ll i = head[x]; i; i = e[i].next)
    if (dep[e[i].to] > dep[x] && size[k] < size[e[i].to])
      k = e[i].to;
  if (!k)
    return;
  dfs2(k, chain);
  for (ll i = head[x]; i; i = e[i].next) {
    if (e[i].to != k && dep[e[i].to] > dep[x])
      dfs2(e[i].to, e[i].to);
  }
}
struct seg {
  ll l, r;
  ll minn, id;
} t[maxn << 2];
struct Line {
  ll k, b;
  ll id;
  Line(ll a = 0, ll bb = 0, ll i = 0) : k(a), b(bb), id(i) {}
  inline ll getf(ll x) { return k * deep[x] + b; }
} lim[maxn << 2];
inline bool cmp(Line a, Line b, ll x) {
  return a.getf(x) != b.getf(x) ? a.getf(x) < b.getf(x) : a.id < b.id;
}
void build(ll k, ll l, ll r) {
  t[k].l = l, t[k].r = r, t[k].minn = inf;
  if (l == r) {
    return;
  }
  ll mid = (l + r) >> 1;
  build(k << 1, l, mid);
  build(k << 1 | 1, mid + 1, r);
}
void up(ll k) {
  ll l = t[k].l, r = t[k].r;
  if (l < r) {
    t[k].minn = std::min(t[k << 1 | 1].minn, t[k << 1].minn);
  } else
    t[k].minn = inf;
  if (t[k].id) {
    t[k].minn = std::min(t[k].minn, std::min(lim[t[k].id].getf(que[l]),
                                             lim[t[k].id].getf(que[r])));
  }
}
void update(ll k, Line v) {
  ll l = t[k].l, r = t[k].r, mid = (l + r) >> 1;
  if (t[k].id == 0) {
    t[k].id = v.id;
  } else {
    Line tmp = lim[t[k].id];
    ll x1 = v.getf(que[l]), y1 = v.getf(que[r]);
    ll x2 = tmp.getf(que[l]), y2 = tmp.getf(que[r]);
    if (x1 <= x2 && y1 <= y2) {
      t[k].id = v.id;
    } else if (x1 >= x2 && y1 >= y2)
      return;
    else if (v.k < tmp.k) {
      ll tp = (v.b - tmp.b) / (tmp.k - v.k) + 1;
      if (tp <= deep[que[mid]]) {
        Line wtf = lim[t[k].id];
        t[k].id = v.id;
        v = wtf;
        update(k << 1, v);
      } else
        update(k << 1 | 1, v);
    } else {
      ll tp = (tmp.b - v.b - 1) / (v.k - tmp.k);
      if (tp > deep[que[mid]]) {
        Line wtf = lim[t[k].id];
        t[k].id = v.id;
        v = wtf;
        update(k << 1 | 1, v);
      } else
        update(k << 1, v);
    }
  }
  up(k);
}

void Insert(ll k, ll x, ll y, Line v) {
  ll l = t[k].l, r = t[k].r, mid = (l + r) >> 1;
  if (x <= l && r <= y) {
    update(k, v);
    return;
  }
  if (x <= mid)
    Insert(k << 1, x, y, v);
  if (y > mid)
    Insert(k << 1 | 1, x, y, v);
  up(k);
}
void Alice(ll s, ll t, Line v) {
  while (belong[s] != belong[t]) {
    Insert(1, pl[belong[s]], pl[s], v);
    s = fa[belong[s]][0];
  }
  Insert(1, pl[t], pl[s], v);
}
ll lca(ll x, ll y) {
  for (; belong[x] != belong[y]; x = fa[belong[x]][0])
    if (deep[belong[x]] < deep[belong[y]])
      std::swap(x, y);
  return (deep[x] < deep[y]) ? x : y;
}
void query(ll k, ll x, ll y) {
  ll l = t[k].l, r = t[k].r, mid = (l + r) >> 1;
  if (x == l && r == y) {
    ans = std::min(ans, t[k].minn);
    return;
  }
  if (t[k].id)
    ans = std::min(
        ans, std::min(lim[t[k].id].getf(que[x]), lim[t[k].id].getf(que[y])));
  if (y <= mid)
    query(k << 1, x, y);
  else if (x > mid)
    query(k << 1 | 1, x, y);
  else {
    query(k << 1, x, mid);
    query(k << 1 | 1, mid + 1, y);
  }
}
void Bob(ll x, ll f) {
  while (belong[x] != belong[f]) {
    query(1, pl[belong[x]], pl[x]);
    x = fa[belong[x]][0];
  }
  query(1, pl[f], pl[x]);
}
int main() {
  freopen("menci_game.in", "r", stdin);
  freopen("menci_game.out", "w", stdout);
  scanf("%lld %lld", &n, &m);
  for (ll i = 1; i < n; i++) {
    ll u, v;
    ll w;
    scanf("%lld %lld %lld", &u, &v, &w);
    add(u, v, w);
  }
  dfs1(1);
  dfs2(1, 1);
  build(1, 1, sz);
  while (m--) {
    ll opt, s, t;
    scanf("%lld %lld %lld", &opt, &s, &t);
    if (opt == 1) {
      ll a, b;
      scanf("%lld %lld", &a, &b);
      fu++;
      lim[fu] = Line(-a, b + a * deep[s], fu);
      ll l = lca(s, t);
      Alice(s, l, lim[fu]);
      fu++;
      lim[fu] = Line(a, lim[fu - 1].b - 2 * a * deep[l], fu);
      Alice(t, l, lim[fu]);
    } else {
      ans = inf;
      for (; belong[s] != belong[t]; s = fa[belong[s]][0]) {
        if (deep[belong[s]] < deep[belong[t]])
          std::swap(s, t);
        query(1, pl[belong[s]], pl[s]);
      }
      if (deep[s] > deep[t])
        std::swap(s, t);
      query(1, pl[s], pl[t]);
      printf("%lld\n", ans);
    }
  }
}
