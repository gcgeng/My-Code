#include <cstdio>
#define ll long long
ll n, ans;
ll phi(ll x) {
  int ans = x;
  for (int i = 2; i * i <= x; i++)
    if (x % i == 0) {
      ans = ans / i * (i - 1);
      while (x % i == 0) x /= i;
    }
  if (x > 1) ans = ans / x * (x - 1);
  return ans;
}
int main() {
  scanf("%lld", &n);
  for (int i = 1; i * i <= n; i++)
    if (n % i == 0) {
      ans += 1ll * i * phi(n / i);
      if (i * i < n) ans += 1ll * (n / i) * phi(i);
    }
  printf("%lld\n", ans);
  return 0;
}
