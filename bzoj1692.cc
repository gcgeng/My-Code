#include <algorithm>
#include <cstdio>
const int maxn = 3000010 << 1;
int n, p, q, pp, qq, k;
int v[maxn], a[maxn], sa[2][maxn], rank[2][maxn];
inline void getsa(int sa[maxn], int rank[maxn], int Sa[maxn], int Rank[maxn]) {
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
inline void da() {
  p = 0, q = 1, k = 1;
  for (int i = 1; i <= n; i++)
    v[a[i]]++;
  for (int i = 1; i <= 26; i++)
    v[i] += v[i - 1];
  for (int i = 1; i <= n; i++)
    sa[p][v[a[i]]--] = i;
  for (int i = 1; i <= n; i++)
    rank[p][sa[p][i]] =
        rank[p][sa[p][i - 1]] + (a[sa[p][i]] != a[sa[p][i - 1]]);
  while (k < n) {
    getsa(sa[p], rank[p], sa[q], rank[q]);
    p ^= 1;
    q ^= 1;
    k <<= 1;
  }
}
inline void solve() {
  int l = 1, r = n >> 1, cnt = 0;
  while (l != r) {
    pp = a[l], qq = a[r];
    if (pp != qq) {
      if (pp < qq) {
        printf("%c", pp + 'A' - 1);
        l++;
      } else {
        printf("%c", qq + 'A' - 1);
        r--;
      }
      cnt++;
    } else {
      int r1 = rank[p][l], r2 = rank[p][n - r + 1];
      if (r1 < r2) {
        printf("%c", pp + 'A' - 1);
        l++;
      } else {
        printf("%c", qq + 'A' - 1);
        r--;
      }
      cnt++;
    }
    if (cnt == 80) {
      printf("\n");
      cnt = 0;
    }
  }
  printf("%c", a[l] + 'A' - 1);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    char ch = getchar();
    while (ch < 'A' || ch > 'Z')
      ch = getchar();
    a[i] = ch - 'A' + 1;
    a[n * 2 - i + 1] = a[i];
  }
  n <<= 1;
  da();
  solve();
}
