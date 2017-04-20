#include <algorithm>
#include <cmath>
#include <cstdio>
#define ll long long
const ll maxn = 100000 + 100;
const ll maxm = 400;
const ll inf = 1ll << 62;
ll n, m, s[maxn], block, blockm, belong[maxn];
ll a[maxm], b[maxm], q[maxn], R[maxm];
int left(int x) { return (x - 1) * block + 1; }
int right(int x) { return std::min(x * block, n); }
void up(ll& x, ll v) {
  if (v > x) x = v;
}
inline double getk(ll i, ll j) {
  if (i == j) return inf;
  return (double)(s[j] - s[i]) / (double)(i - j);
}  //下凸包
inline double getprev(ll i) { return getk(q[i - 1], q[i]); }
inline ll value(ll x) { return a[belong[x]] * x + b[belong[x]] + s[x]; }
void reset(ll x) {
  ll l = left(x), r = right(x), t = l;
  q[t] = l;
  for (ll i = l + 1; i <= r; q[++t] = i++)
    while (t > l && getprev(t) >= getk(q[t], i)) t--;
  R[x] = t;
}
void change(ll l, ll r, ll k, ll b) {
  if (belong[l] == belong[r]) {
    for (ll i = l; i <= r; i++) s[i] += k * i + b;
    reset(belong[l]);
    return;
  }
  for (ll i = belong[l] + 1; i < belong[r]; i++) a[i] += k, ::b[i] += b;
  for (ll i = l; i <= right(belong[l]); i++) s[i] += k * i + b;
  reset(belong[l]);
  for (ll i = left(belong[r]); i <= r; i++) s[i] += k * i + b;
  reset(belong[r]);
}
void modify(ll l, ll r, ll v) {
  change(l, r, v, v * (1 - l));
  if (r < n) change(r + 1, n, 0, v * (r - l + 1));
}
ll find(ll x) {
  ll ans = left(x);
  ll l = ans + 1, r = R[x];
  while (l <= r) {
    ll mid = (l + r) >> 1;
    if (getprev(mid) < a[x]) {
      l = (ans = mid) + 1;
    } else
      r = mid - 1;
  }
  return value(q[ans]);
}
ll query(ll l, ll r) {
  ll ans = -inf;
  if (belong[l] == belong[r]) {
    for (ll i = l; i <= r; i++) up(ans, value(i));
    return ans;
  }
  for (ll i = l; i <= right(belong[l]); i++) up(ans, value(i));
  for (ll i = left(belong[r]); i <= r; i++) up(ans, value(i));
  for (ll i = belong[l] + 1; i < belong[r]; i++) up(ans, find(i));
  return ans;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%lld %lld", &n, &m);
  block = (ll)(sqrt(n) + 0.1);
  blockm = n / block + ((n % block) ? 1 : 0);
  for (ll i = 1; i <= n; i++) scanf("%lld", &s[i]);
  for (ll i = 1; i <= n; i++) {
    belong[i] = (i - 1) / block + 1;
    s[i] += s[i - 1];
  }
  for (ll i = 1; i <= blockm; i++) reset(i);
  while (m--) {
    ll opt, x, y;
    scanf("%lld %lld %lld", &opt, &x, &y);
    if (opt)
      printf("%lld\n", query(x, y));
    else {
      ll k;
      scanf("%lld", &k);
      modify(x, y, k);
    }
    //  for (ll i = 1; i <= n; i++) printf("%lld ", value(i));
    // prllf("\n");
  }
  return 0;
}
