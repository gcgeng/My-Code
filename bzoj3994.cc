#include <algorithm>
#include <cctype>
#include <cstdio>
#define ll long long
const int maxn = 50000 + 10;
int prime[maxn], tot;
int mu[maxn], sigma[maxn], summu[maxn];
ll sumsigma[maxn];
bool check[maxn];
int read() {
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
void shake() {
  int minPrimeCnt[maxn];
  mu[1] = 1, sigma[1] = 1;
  for (int i = 2; i < maxn; i++) {
    if (!check[i]) {
      prime[tot++] = i;
      mu[i] = -1;
      sigma[i] = 2;
      minPrimeCnt[i] = 1;
    }
    for (int j = 0; j < tot; j++) {
      int x = i * prime[j];
      if (x >= maxn)
        break;
      check[x] = 1;
      if (i % prime[j] == 0) {
        mu[x] = 0;
        minPrimeCnt[x] = minPrimeCnt[i] + 1;
        sigma[x] = sigma[i] / (minPrimeCnt[i] + 1) * (minPrimeCnt[x] + 1);
        break;
      } else {
        mu[x] = -mu[i];
        sigma[x] = sigma[i] << 1;
        minPrimeCnt[x] = 1;
      }
    }
  }
  summu[0] = 0;
  for (int i = 1; i < maxn; i++)
    summu[i] = summu[i - 1] + mu[i];
  for (int i = 1; i < maxn; i++)
    sumsigma[i] = sumsigma[i - 1] + sigma[i];
}
ll F(int n, int m) {
  if (n > m)
    std::swap(n, m);
  ll ans = 0;
  for (int i = 1, last = 1; i <= n; i = last + 1) {
    last = std::min(n / (n / i), m / (m / i));
    ans += (summu[last] - summu[i - 1]) * sumsigma[n / i] * sumsigma[m / i];
  }
  return ans;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  shake();
  int kase = read();
  while (kase--) {
    int n = read(), m = read();
    printf("%lld\n", F(n, m));
  }
  return 0;
}
