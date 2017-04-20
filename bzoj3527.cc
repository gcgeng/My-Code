#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#define pi acos(-1)
const int maxn = 262200 + 10;
typedef std::complex<double> E;
E f[maxn], g[maxn], _f[maxn], e1[maxn], e2[maxn];
int R[maxn], q[maxn];
int n, m, L;
void fft(E *a, int f) {
  for (int i = 0; i < n; i++)
    if (i < R[i]) std::swap(a[i], a[R[i]]);
  for (int i = 1; i < n; i <<= 1) {
    E wn(cos(pi / i), f * sin(pi / i));
    for (int j = 0; j < n; j += (i << 1)) {
      E w(1, 0);
      for (int k = 0; k < i; k++, w *= wn) {
        E x = a[j + k], y = a[j + k + i] * w;
        a[j + k] = x + y;
        a[j + k + i] = x - y;
      }
    }
  }
  if (f == -1)
    for (int i = 0; i < n; i++) a[i] /= n;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d", &n);
  n--;
  for (int i = 0; i <= n; i++) {
    double x;
    scanf("%lf", &x);
    f[i] = x;
    _f[n - i] = x;
  }
  for (int i = 1; i <= n; i++) g[i] = 1.0 / i / i;
  m = 2 * n;
  for (n = 1; n <= m; n <<= 1, L++)
    ;
  for (int i = 0; i < n; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
  fft(f, 1);
  fft(g, 1);
  fft(_f, 1);
  for (int i = 0; i < n; i++) e1[i] = f[i] * g[i];
  for (int i = 0; i < n; i++) e2[i] = _f[i] * g[i];
  fft(e1, -1);
  fft(e2, -1);
  for (int i = 0; i <= (m / 2); i++)
    printf("%.3lf\n", e1[i].real() - e2[m / 2 - i].real());
  return 0;
}
