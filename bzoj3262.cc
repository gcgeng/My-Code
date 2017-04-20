#include <algorithm>
#include <cctype>
#include <cstdio>
const int maxn = 100100;
const int maxk = maxn << 1;
struct flower {
  int x, y, z, cnt, ans;
  flower() {
    cnt = 0;
    ans = 0;
  }
} a[maxn], aa[maxn], tmp[maxn];
bool cmp1(flower a, flower b) {
  return a.x == b.x ? (a.y == b.y ? a.z < b.z : a.y < b.y) : a.x < b.x;
}
bool cmp2(flower a, flower b) { return a.y == b.y ? a.z < b.z : a.y < b.y; }
bool equal(flower a, flower b) {
  return a.x == b.x && a.y == b.y && a.z == b.z;
}
int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
int n, k, m, cur;
int bit[maxk], tim[maxk], ans[maxk];
void add(int i, int v) {
  for (; i <= k; i += i & -i) {
    if (tim[i] == cur)
      bit[i] += v;
    else
      tim[i] = cur, bit[i] = v;
  }
}
int query(int i) {
  int ret = 0;
  for (; i; i -= i & -i)
    if (tim[i] == cur) ret += bit[i];
  return ret;
}
void solve(int l, int r) {
  if (l == r) return;
  int mid = (l + r) >> 1;
  solve(l, mid);
  solve(mid + 1, r);
  int j = l;
  cur++;
  for (int i = mid + 1; i <= r; i++) {
    while (j <= mid && a[j].y <= a[i].y) add(a[j].z, a[j].cnt), j++;
    a[i].ans += query(a[i].z);
  }
  int p = l, q = mid + 1;
  for (int i = l; i <= r; i++) {
    if ((p <= mid) && (q > r || cmp2(a[p], a[q])))
      tmp[i] = a[p++];
    else
      tmp[i] = a[q++];
  }
  for (int i = l; i <= r; i++) a[i] = tmp[i];
  return;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  n = read();
  k = read();
  for (int i = 1; i <= n; i++)
    aa[i].x = read(), aa[i].y = read(), aa[i].z = read();
  std::sort(aa + 1, aa + 1 + n, cmp1);
  a[++m] = aa[1];
  a[1].cnt = 1;
  for (int i = 2; i <= n; i++) {
    if (!equal(a[m], aa[i]))
      a[++m] = aa[i], a[m].cnt = 1;
    else
      a[m].cnt++;
  }
  solve(1, m);
  for (int i = 1; i <= m; i++) ans[a[i].ans + a[i].cnt - 1] += a[i].cnt;
  for (int i = 0; i < n; i++) printf("%d\n", ans[i]);
  return 0;
}
