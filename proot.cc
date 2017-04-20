#include <cstdio>
#define ll long long
int n;
ll pow(ll a, ll b, ll n) {
  ll ans = 1;
  for (; b; b >>= 1, a = (a * a) % n)
    if (b & 1) ans = (ans * a) % n;
  return ans;
}
bool check(int i) {
  for (int j = 2; j * j < n; j++)
    if ((n - 1) % j == 0)
      if (pow(i, (n - 1) / j, n) == 1 || pow(i, j, n) == 1) return false;
  return true;
}
int proot() {
  for (int i = 2;; i++)
    if (pow(i, n - 1, n) == 1 && check(i)) return i;
}
int main() {
  scanf("%d", &n);
  printf("%d", proot());
}
