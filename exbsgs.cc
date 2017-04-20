#include <cmath>
#include <cstdio>
#include <map>
#define ll long long
int a, c, m;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll qpow(ll a, ll b, ll p) {
  ll ans = 1;
  for (; b; b >>= 1, a = (a * a) % p)
    if (b & 1) ans = (ans * a) % p;
  return ans;
}
ll exbsgs(int a, int c, int m) {
  a %= m, c %= m;
  if (a == 0) return c > 1 ? -1 : c == 0 && m > 1;
  int delta = 0;
  ll t = 1;
  for (int g = gcd(a, m); g != 1; g = gcd(a, m)) {
    if (c % g) return -1;
    m /= g, c /= g, t = t * a / g % m;
    ++delta;
    if (c == t) return delta;
  }
  std::map<int, int> hash;
  int M = int(sqrt(1.0 * m) + 1);
  ll tmp = c;
  for (int i = 0; i != M; i++) {
    hash[tmp] = i;
    tmp = tmp * a % m;
  }
  tmp = qpow(a, M, m);
  ll now = t;
  for (int i = 1; i <= m + 1; i++) {
    now = now * tmp % m;
    if (hash.count(now)) return i * M - hash[now] + delta;
  }
  return -1;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  while (scanf("%d %d %d", &m, &a, &c) != EOF) {
    ll ans = exbsgs(a, c, m);
    if (ans != -1)
      printf("%lld\n", ans);
    else
      printf("no solution\n");
  }
  return 0;
}
