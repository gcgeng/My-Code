#include <cstdio>
const int maxn = 20010;
int a[maxn], sa[2][maxn], rank[2][maxn], height[maxn];
int n, K, k, m, p, q;
int v[1000100];
void calc(int sa[maxn], int rank[maxn], int Sa[maxn], int Rank[maxn]) {
  for (int i = 1; i <= n; i++)
    v[rank[sa[i]]] = i;
  for (int i = n; i >= 1; i--)
    if (sa[i] > k)
      Sa[v[rank[sa[i] - k]]--] = sa[i] - k;
  for (int i = n - k + 1; i <= n; i++)
    Sa[v[rank[i]]--] = i;
  for (int i = 1; i <= n; i++)
    Rank[Sa[i]] = Rank[Sa[i - 1]] + (rank[Sa[i]] != rank[Sa[i - 1]] ||
                                     rank[Sa[i] + k] != rank[Sa[i - 1] + k]);
}
void calh(int sa[maxn], int rank[maxn]) {
  int i, j, k = 0;
  for (i = 1; i <= n; height[rank[i++]] = k)
    for (k ? k-- : 0, j = sa[rank[i] - 1]; a[i + k] == a[j + k]; k++)
      ;
  return;
}
void da() {
  m = 1000010, p = 0, q = 1, k = 1;
  for (int i = 1; i <= n; i++)
    v[a[i]]++;
  for (int i = 1; i <= m; i++)
    v[i] += v[i - 1];
  for (int i = 1; i <= n; i++)
    sa[p][v[a[i]]--] = i;
  for (int i = 1; i <= n; i++)
    rank[p][sa[p][i]] =
        rank[p][sa[p][i - 1]] + (a[sa[p][i - 1]] != a[sa[p][i]]);
  while (k < n) {
    calc(sa[p], rank[p], sa[q], rank[q]);
    p ^= 1;
    q ^= 1;
    k <<= 1;
  }
  calh(sa[p], rank[p]);
}
bool check(int x) {
  int l = 1, r = 1;
  for (int i = 2; i <= n + 1; i++)
    if (height[i] >= x)
      r++;
    else if (r - l + 1 >= K)
      return true;
    else {
      l = i;
      r = i;
      continue;
    }
  return false;
}
void solve() {
  int l = 0, r = n;
  while (r - l > 1) {
    int mid = (l + r) >> 1;
    if (check(mid))
      l = mid;
    else
      r = mid;
  }
  printf("%d\n", check(r) ? r : l);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d %d", &n, &K);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  da();
  solve();
}
