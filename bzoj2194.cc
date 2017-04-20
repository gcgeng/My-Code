#include <algorithm>
#include <complex>
#include <cstdio>
typedef std::complex<double> E;
#define pi acos(-1)
const int maxn = 262144;
E a[maxn], b[maxn];
int R[maxn];
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
  scanf("%d", &n);
  n--;
  for (int i = 0; i <= n; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    a[i] = x;
    b[n - i] = y;
  }
  m = n << 1;
  for (n = 1; n <= m; n <<= 1) L++;
  for (int i = 0; i < n; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
  fft(a, 1);
  fft(b, 1);
  for (int i = 0; i <= n; i++) a[i] *= b[i];
  fft(a, -1);
  for (int i = m >> 1; i <= m; i++) printf("%d\n", (int)(a[i].real() + 0.1));
  return 0;
}
