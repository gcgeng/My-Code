#include <algorithm>
#include <cstdio>
#include <cstring>
const int maxn = 1005 * 1005;
int sa[2][maxn], rank[2][maxn], p, q, k, height[maxn], v[maxn];
int str[maxn], vis[maxn];
int n, m, cnt, sigma, atsigma, wtf[maxn];
void getsa(int sa[maxn], int rank[maxn], int Sa[maxn], int Rank[maxn]) {
  for (int i = 1; i <= cnt; i++)
    v[rank[sa[i]]] = i;
  for (int i = cnt; i >= 1; i--)
    if (sa[i] > k)
      Sa[v[rank[sa[i] - k]]--] = sa[i] - k;
  for (int i = cnt - k + 1; i <= cnt; i++)
    Sa[v[rank[i]]--] = i;
  for (int i = 1; i <= cnt; i++)
    Rank[Sa[i]] = Rank[Sa[i - 1]] + (rank[Sa[i - 1]] != rank[Sa[i]] ||
                                     rank[Sa[i - 1] + k] != rank[Sa[i] + k]);
}
void getheight(int sa[maxn], int rank[maxn]) {
  int i, k = 0;
  for (i = 1; i <= cnt; height[rank[i++]] = k) {
    if (k)
      k--;
    for (int j = sa[rank[i] - 1]; str[i + k] == str[j + k]; k++)
      ;
  }
}
void da() {
  p = 0, q = 1, k = 1;
  for (int i = 1; i <= cnt; i++)
    v[str[i]]++;
  for (int i = 1; i <= sigma; i++)
    v[i] += v[i - 1];
  for (int i = 1; i <= cnt; i++)
    sa[p][v[str[i]]--] = i;
  for (int i = 1; i <= cnt; i++)
    rank[p][sa[p][i]] =
        rank[p][sa[p][i - 1]] + (str[sa[p][i - 1]] != str[sa[p][i]]);
  while (k < cnt) {
    getsa(sa[p], rank[p], sa[q], rank[q]);
    p ^= 1;
    q ^= 1;
    k <<= 1;
  }
  getheight(sa[p], rank[p]);
}
bool check(int x) {
  for (int i = 1; i <= n; i++)
    vis[i] = 0;
  int sta[maxn];
  int num = 0, top = 0;
  for (int i = 2; i <= cnt - 1; i++) {
    if (height[i] >= x) {
      if (!vis[wtf[sa[p][i - 1]]])
        vis[wtf[sa[p][i - 1]]] = 1, num++, sta[++top] = wtf[sa[p][i - 1]];
      if (!vis[wtf[sa[p][i]]])
        vis[wtf[sa[p][i]]] = 1, num++, sta[++top] = wtf[sa[p][i]];
      if (num == n)
        return true;
    } else if (num) {
      num = 0;
      while (top)
        vis[sta[top--]] = 0;
    }
  }
  return false;
}
int main() {
  //  freopen("input", "r", stdin);
  scanf("%d", &n);
  int l = 0, r = 0x3f3f3f, ans;
  memset(wtf, -1, sizeof(wtf));
  for (int i = 1; i <= n; i++) {
    scanf("%d", &m);
    int x, y;
    r = std::min(r, m - 1);
    for (int j = 1; j <= m; j++) {
      scanf("%d", &x);
      if (j != 1)
        str[++cnt] = x - y, wtf[cnt] = i, atsigma = std::min(atsigma, x - y);
      y = x;
    }
    str[++cnt] = 1000;
  }
  for (int i = 1; i <= cnt; i++)
    str[i] -= atsigma - 1, sigma = std::max(sigma, str[i] + 1);
  da();
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (check(mid)) {
      ans = mid;
      l = mid + 1;
    } else
      r = mid - 1;
  }
  printf("%d\n", ans + 1);
}
