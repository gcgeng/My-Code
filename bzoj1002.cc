#include <cstdio>
int mod = 10;
struct data {
  int a[50], len;
} f[3];
int n;
inline int min(int a, int b) { return a < b ? a : b; }
data mul(data a, int k) {
  for (int i = 1; i <= a.len; i++)
    a.a[i] *= k;
  for (int i = 1; i <= a.len; i++) {
    a.a[i + 1] += a.a[i] / mod;
    a.a[i] %= mod;
  }
  while (a.a[a.len + 1]) {
    a.len++;
    a.a[a.len + 1] += a.a[a.len] / mod;
    a.a[a.len] %= mod;
  }
  return a;
}
data sub(data a, const data &b) {
  a.a[1] += 2;
  for (int i = 1; i <= min(a.len, b.len); i++) {
    a.a[i] -= b.a[i];
    if (a.a[i] < 0) {
      a.a[i] += 10;
      a.a[i + 1]--;
    }
  }
  while (a.a[a.len] == 0)
    a.len--;
  return a;
}
void print(const data &a) {
  for (int i = a.len; i >= 1; i--)
    printf("%d", a.a[i]);
}
int main() {
  f[0].len = f[1].len = 1;
  f[0].a[1] = 1;
  f[1].a[1] = 5;
  scanf("%d", &n);
  int p = 1, pp = 0, now = 2;
  for (int i = 3; i <= n; i++) {
    data x = mul(f[p], 3);
    f[now] = sub(x, f[pp]);
    (++now) %= 3;
    (++p) %= 3;
    (++pp) %= 3;
  }
  print(f[(now + 2) % 3]);
}
