#include <algorithm>
#include <cstdio>
#include <cstring>
#define ll long long
const int maxm = 50000;
const int P = 1004535809;
const int G = 3;
int R[maxm], L, ind[maxm];
int N, M, x, Sb, n;
ll s[2], w[2][maxm], g;
ll qpow(ll a, ll b, ll p) {
  ll ans = 1;
  for (; b; b >>= 1, a = (a * a) % p)
    if (b & 1) ans = (ans * a) % p;
  return ans;
}
ll inv(ll x, ll p) { return qpow(x, p - 2, p); }
void ntt(ll* a, int f) {
  for (int i = 0; i < n; i++)
    if (i < R[i]) std::swap(a[i], a[R[i]]);
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0, l = n / (i << 1); j < n; j += (i << 1)) {
      for (int k = 0, t = 0; k < i; k++, t += l) {
        ll x = a[j + k], y = (1ll * w[f][t] * a[j + k + i]) % P;
        a[j + k] = (x + y) % P;
        a[j + k + i] = (x - y + P) % P;
      }
    }
  }
  if (f)
    for (int i = 0; i < n; i++) (a[i] *= inv(n, P)) %= P;
}
struct Poly {
  ll a[maxm];
  Poly() { memset(a, 0, sizeof(a)); }
  Poly(int x) {
    memset(a, 0, sizeof(a));
    a[0] = x;
  }
  ll& operator[](int i) { return a[i]; }
  Poly operator*(const Poly& b) {
    ll A[maxm], B[maxm];
    Poly C;
    memcpy(A, this->a, sizeof(this->a));
    memcpy(B, b.a, sizeof(b.a));
    ntt(A, 0);
    ntt(B, 0);
    for (int i = 0; i < n; i++) A[i] = (A[i] * B[i] * 1ll) % P;
    ntt(A, 1);
    for (int i = n - 1; i >= M - 1; i--) (A[i - M + 1] += A[i]) %= P, A[i] = 0;
    memcpy(C.a, A, sizeof(A));
    return C;
  }
} a;
Poly qqpow(Poly a, int n) {
  Poly ans(1);
  for (; n; n >>= 1, a = a * a)
    if (n & 1) ans = ans * a;
  return ans;
}
bool check(int x, int M) {
  for (int i = 2; i * i < M; i++)
    if ((M - 1) % i == 0)
      if (qpow(x, (M - 1) / i, M) == 1 || qpow(x, i, M) == 1) return false;
  return true;
}
int getroot(int x) {
  for (int g = 2;; g++)
    if (qpow(g, x - 1, x) == 1 && check(g, x)) return g;
}
void init() {
  s[0] = qpow(G, (ll)((P - 1) / n), P);
  s[1] = inv(s[0], P);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < 2; j++) w[j][i] = i ? w[j][i - 1] * s[j] % P : 1;
  for (int i = 0; i < n; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d %d %d %d", &N, &M, &x, &Sb);
  g = getroot(M);
  for (n = 1; n < (M + M - 2); n <<= 1) L++;
  for (int i = 0, xx = 1; i < M - 1; i++, (xx *= g) %= M) ind[xx] = i;
  // ind[0] = 1;
  for (int i = 0; i < Sb; i++) {
    int x;
    scanf("%d", &x);
    if (x != 0) a[ind[x]] = 1;
  }
  init();
  Poly ans = qqpow(a, N);
  printf("%lld\n", ans[ind[x]]);
}
