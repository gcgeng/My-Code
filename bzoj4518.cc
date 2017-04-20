#include <algorithm>
#include <cctype>
#include <cstdio>
#define ll long long
const ll inf = 99999999999;
const int maxn = 60010;
// const int maxm = 30010;
ll f[2][maxn];
int n, m, now = 1;
ll s[maxn];
ll sq(ll x) { return x * x; };
ll read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
inline double calck(int i, int j) {
  if (s[j] - s[i] == 0)
    return inf;
  return (f[now ^ 1][j] - f[now ^ 1][i] + sq(s[j]) - sq(s[i])) /
         ((s[j] - s[i]) * 2);
}
int que[maxn], head, size, tail;
int main() {
  /*  freopen("menci_journey.in", "r", stdin);
    freopen("menci_journey.out", "w", stdout); */
  n = read();
  m = read();
  for (int i = 1; i <= n; i++)
    s[i] = read();
  for (int i = 1; i <= n; i++)
    s[i] += s[i - 1];
  for (int i = 1; i <= n; i++)
    f[0][i] = inf;
  for (int i = 1; i <= m; i++) {
    head = tail = 0;
    size = 1;
    for (int j = 1; j <= n; j++) {
      while (size >= 2) {
        int a = que[head];
        int b = que[head + 1];
        if (calck(a, b) < s[j]) {
          head++;
          size--;
          if (size < 2)
            break;
        } else
          break;
      }
      int k = que[head];
      f[now][j] = f[now ^ 1][k] + sq(s[j] - s[k]);
      if (size >= 2) {
        int x = que[tail];
        int y = que[tail - 1];
        while (calck(y, x) > calck(x, j)) {
          tail--;
          size--;
          if (size < 2)
            break;
          x = que[tail];
          y = que[tail - 1];
        }
      }
      que[++tail] = j;
      size++;
    }
    now ^= 1;
  }
  // printf("%lld\n", f[now ^ 1][n]);
  ll ans = m * f[now ^ 1][n] - s[n] * s[n];
  printf("%lld\n", ans);
}
