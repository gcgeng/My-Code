#include <algorithm>
#include <cstdio>
#define ll long long
const int maxn = 1 << 13;
int n;
int a[maxn];
ll po[13];
ll ans;
bool check(int k) {
  for (int i = 1; i <= (1 << (n - k)); i++)
    if (a[(i - 1) * (1 << k) + 1] + (1 << (k - 1)) !=
        a[(i - 1) * (1 << k) + (1 << (k - 1)) + 1])
      return 0;
  return 1;
}
void swap(int i, int j, int k) {
  for (int m = 1; m <= k; m++)
    std::swap(a[i + m - 1], a[j + m - 1]);
}
void dfs(int now, int num) {
  if (now && !check(now))
    return;
  if (now == n) {
    ans += po[num];
    return;
  }
  dfs(now + 1, num);
  int tmp[5], tot = 0;
  for (int i = 1; i <= (1 << (n - now)); i += 2)
    if (a[i * (1 << now) + 1] != a[(i - 1) * (1 << now) + 1] + (1 << now)) {
      if (tot == 4)
        return;
      tmp[++tot] = i;
      tmp[++tot] = i + 1;
    }
  if (!tot)
    return;
  for (int i = 1; i <= tot; i++)
    for (int j = i + 1; j <= tot; j++) {
      swap((1 << now) * (tmp[i] - 1) + 1, (1 << now) * (tmp[j] - 1) + 1,
           1 << now);
      dfs(now + 1, num + 1);
      swap((1 << now) * (tmp[i] - 1) + 1, (1 << now) * (tmp[j] - 1) + 1,
           1 << now);
    }
}
int main() {
  // freopen("input", "r", stdin);
  po[0] = 1;
  for (int i = 1; i <= 12; i++)
    po[i] = po[i - 1] * i;
  scanf("%d", &n);
  for (int i = 1; i <= 1 << n; i++)
    scanf("%d", &a[i]);
  dfs(0, 0);
  printf("%lld", ans);
}
