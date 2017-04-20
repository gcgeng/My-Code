#include <algorithm>
#include <cmath>
#include <cstdio>
const int maxn = 10100;
int N, M, pre1[maxn], pre2[maxn], a[maxn], belong[maxn], block, blockm,
    last[1000010];
void reset(int x) {
  int l = (x - 1) * block + 1, r = std::min(x * block, N);
  for (int i = l; i <= r; i++) pre2[i] = pre1[i];
  std::sort(pre2 + l, pre2 + r + 1);
}
void change(int x, int v) {
  for (int i = 1; i <= N; i++) last[a[i]] = 0;
  a[x] = v;
  for (int i = 1; i <= N; i++) {
    int t = pre1[i];
    pre1[i] = last[a[i]];
    if (t != pre1[i]) reset(belong[i]);
    last[a[i]] = i;
  }
}
int find(int i, int x) {
  int l = block * (i - 1) + 1, r = std::min(block * i, N);
  int fir = l;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (pre2[mid] < x)
      l = mid + 1;
    else
      r = mid - 1;
  }
  return l - fir;
}
int ask(int l, int r) {
  int ans = 0;
  if (belong[l] == belong[r]) {
    for (int i = l; i <= r; i++) ans += pre1[i] < l;
    return ans;
  }
  for (int i = l; i <= block * belong[l]; i++) ans += pre1[i] < l;
  for (int i = block * (belong[r] - 1) + 1; i <= r; i++) ans += pre1[i] < l;
  for (int i = belong[l] + 1; i < belong[r]; i++) ans += find(i, l);
  return ans;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d %d", &N, &M);
  block = sqrt(N) + 1;
  blockm = N / block;
  if (N % block) blockm++;
  for (int i = 1; i <= N; i++) {
    scanf("%d", &a[i]);
    belong[i] = ((i - 1) / block) + 1;
  }
  for (int i = 1; i <= N; i++) {
    pre1[i] = last[a[i]];
    last[a[i]] = i;
  }
  for (int i = 1; i <= blockm; i++) reset(i);
  while (M--) {
    char opt[5];
    int x, y;
    scanf("%s %d %d", opt, &x, &y);
    if (opt[0] == 'Q') {
      printf("%d\n", ask(x, y));
    } else {
      change(x, y);
    }
  }
  return 0;
}
