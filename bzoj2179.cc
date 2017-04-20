#include <algorithm>
#include <cmath>
#include <cstdio>
#define maxn 131072
#define ll long long
const ll P = 479 << 21 ^ 1;
const ll G = 3;
ll n, m, L;
char ch[maxn];
ll R[maxn], c[maxn];
ll a[maxn], b[maxn];
ll w[2][maxn], s[2];
ll pow(ll a, ll b) {
  ll ans = 1;
  while (b) {
    if (b & 1) ans = ((ll)ans * a) % P;
    a = ((ll)a * a) % P;
    b >>= 1;
  }
  return ans;
}
ll inv(ll x) { return pow(x, P - 2); }
void ntt(ll *a, ll f) {
  for (ll i = 0; i < n; i++)
    if (i < R[i]) std::swap(a[i], a[R[i]]);
  for (ll i = 1; i < n; i <<= 1) {
    for (ll j = 0, l = n / (i << 1); j < n; j += (i << 1))
      for (ll k = 0, t = 0; k < i; k++, t += l) {
        ll x = a[j + k], y = (1ll * w[f][t] * a[j + k + i]) % P;
        a[j + k] = (x + y) % P;
        a[j + k + i] = (x - y + P) % P;
      }
    if (f)
      for (ll i = 0; i < n; i++) (a[i] *= inv(n)) %= P;
  }
}
void init() {
  s[0] = pow(G, (P - 1) / n);
  s[1] = inv(s[0]);
  for (ll i = 0; i < n; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
  for (ll i = 0; i < n; i++)
    for (ll j = 0; j < 2; j++) w[j][i] = i ? w[j][i - 1] * s[j] % P : 1;
}
int main() {
  scanf("%lld", &n);
  n--;
  scanf("%s", ch);
  for (ll i = 0; i <= n; i++) a[i] = ch[n - i] - '0';
  scanf("%s", ch);
  for (ll i = 0; i <= n; i++) b[i] = ch[n - i] - '0';
  m = 2 * n;
  for (n = 1; n <= m; n <<= 1) L++;
  init();
  ntt(a, 0);
  ntt(b, 0);
  for (ll i = 0; i <= n; i++) a[i] *= b[i];
  ntt(a, 1);
  for (ll i = 0; i <= m; i++) c[i] = a[i];
  for (ll i = 0; i <= m; i++)
    if (c[i] >= 10) {
      c[i + 1] += c[i] / 10, c[i] %= 10;
      if (i == m) m++;
    }
  for (ll i = m; i >= 0; i--) printf("%lld", c[i]);
  return 0;
}
