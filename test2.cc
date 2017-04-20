#include <algorithm>
#include <cstdio>
#include <cstring>
const int maxn = 15;
int n, k, x;
int bit[maxn], a[maxn];
void add(int x, int val) {
  for (int i = x; i <= n; i += i & (-i))
    bit[i] += val;
}
int query(int pos) {
  int ret = 0;
  for (int i = pos; i; i -= i & (-i))
    ret += bit[i];
  return ret;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d%d%d", &n, &k, &x);
  int cnt = 0;
  for (int i = 1; i <= n; i++)
    a[i] = i;
  do {
    memset(bit, 0, sizeof(bit));
    int tmp = 0;
    for (int i = 1; i <= n; i++) {
      tmp += query(a[i]);
      add(a[i], 1);
    }
    tmp = (((n - 1) * n) >> 1) - tmp;
    if (tmp == x)
      cnt++;
    if (cnt == k)
      break;
  } while (std::next_permutation(a + 1, a + n + 1));
  for (int i = 1; i <= n; i++)
    printf("%d ", a[i]);
  return 0;
}
