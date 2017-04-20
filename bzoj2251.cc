#include <algorithm>
#include <cstdio>
#include <cstring>
const int maxn = 3010;
int a[maxn], sa[2][maxn], rank[2][maxn], height[maxn];
int n, p, q, k, K;
char str[maxn];
int v[maxn];
void getsa(int sa[maxn], int rank[maxn], int Sa[maxn], int Rank[maxn]) {
  for (int i = 1; i <= n; i++)
    v[rank[sa[i]]] = i;
  for (int i = n; i >= 1; i--)
    if (sa[i] > k)
      Sa[v[rank[sa[i] - k]]--] = sa[i] - k;
  for (int i = n - k + 1; i <= n; i++)
    Sa[v[rank[i]]--] = i;
  for (int i = 1; i <= n; i++)
    Rank[Sa[i]] = Rank[Sa[i - 1]] + (rank[Sa[i - 1]] != rank[Sa[i]] ||
                                     rank[Sa[i - 1] + k] != rank[Sa[i] + k]);
}
void getheight(int sa[maxn], int rank[maxn]) {
  int i, k = 0;
  for (i = 1; i <= n; height[rank[i++]] = k) {
    if (k)
      k--;
    int j = sa[rank[i] - 1];
    while (a[i + k] == a[j + k])
      k++;
  }
}
void da() {
  p = 0, q = 1, k = 1;
  for (int i = 1; i <= n; i++)
    v[a[i]]++;
  for (int i = 1; i <= 2; i++)
    v[i] += v[i - 1];
  for (int i = 1; i <= n; i++)
    sa[p][v[a[i]]--] = i;
  for (int i = 1; i <= n; i++)
    rank[p][sa[p][i]] =
        rank[p][sa[p][i - 1]] + (a[sa[p][i - 1]] != a[sa[p][i]]);
  while (k < n) {
    getsa(sa[p], rank[p], sa[q], rank[q]);
    p ^= 1;
    q ^= 1;
    k <<= 1;
  }
  getheight(sa[p], rank[p]);
}
void solve() {
  for (int i = 1; i <= n; i++) {
    for (int j = height[i] + 1; sa[p][i] + j - 1 <= n; j++) {
      int l, r;
      for (l = i; l >= 1 && height[l] >= j; l--)
        ;
      for (r = i + 1; r <= n && height[r] >= j; r++)
        ;
      if (r - l > 1)
        printf("%d\n", r - l);
    }
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d %s", &n, str + 1);
  for (int i = 1; i <= n; i++)
    a[i] = str[i] - '0';
  a[0] = 3;
  for (int i = n + 1; i < maxn; i++)
    a[i] = 3;
  da();
  solve();
}
