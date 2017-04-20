#include <cstdio>
#include <cstring>
#define ll long long
const int maxn = 1000005;
const int maxm = 100005;
ll phi[maxn << 1], mu[maxn << 1], p[maxm], q[maxm];
bool vis[maxm];
int prime[maxn], cnt, kase, n, m = 2000000;
void linear_shaker(int N) {
  phi[1] = mu[1] = 1;
  for (int i = 2; i <= N; i++) {
    if (!phi[i]) {
      phi[i] = i - 1;
      mu[i] = -1;
      prime[cnt++] = i;
    }
    for (int j = 0; j < cnt; j++) {
      if (prime[j] * i > N)
        break;
      if (i % prime[j] == 0) {
        phi[i * prime[j]] = phi[i] * prime[j];
        mu[i * prime[j]] = 0;
        break;
      } else {
        phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        mu[i * prime[j]] = -mu[i];
      }
    }
  }
  for (int i = 2; i <= N; i++) {
    phi[i] += phi[i - 1];
    mu[i] += mu[i - 1];
  }
}
ll get_p(int x) { return (x <= m) ? phi[x] : p[n / x]; };
ll get_q(int x) { return (x <= m) ? mu[x] : q[n / x]; };
void solve(ll x) {
  if (x <= m)
    return;
  int i, last = 1, t = n / x;
  if (vis[t])
    return;
  vis[t] = 1;
  p[t] = ((x + 1) * x) >> 1;
  q[t] = 1;
  while (last < x) {
    i = last + 1;
    last = x / (x / i);
    solve(x / i);
    p[t] -= get_p(x / i) * (last - i + 1);
    q[t] -= get_q(x / i) * (last - i + 1);
  }
}
int main() {
  //  freopen("input", "r", stdin);
  scanf("%d", &kase);
  linear_shaker(m);
  while (kase--) {
    scanf("%d", &n);
    memset(vis, 0, sizeof(vis));
    if (n <= m)
      printf("%lld %lld\n", phi[n], mu[n]);
    else {
      solve((ll)n);
      printf("%lld %lld\n", p[1], q[1]);
    }
  }
}
