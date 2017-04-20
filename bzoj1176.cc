#include <algorithm>
#include <cstdio>
const int maxn = 2002005;
struct node {
  int x, y, z, pos, tag, ans;
  node() {}
  node(int a, int b, int c, int d, int e, int g)
      : x(a), y(b), z(c), pos(d), tag(e), ans(g) {}
} a[maxn], tmp[maxn];
int n, s, m, foo, cur;
int bit[maxn], tim[maxn];
bool cmp1(node a, node b) { return a.x != b.x ? a.x < b.x : a.y < b.y; }
bool cmp2(node a, node b) { return a.pos < b.pos; }
inline int lowbit(int i) { return i & -i; }
void add(int x, int p) {
  for (; x <= n; x += lowbit(x))
    if (tim[x] == cur)
      bit[x] += p;
    else
      tim[x] = cur, bit[x] = p;
}
int ask(int x) {
  int ret = 0;
  for (; x; x -= lowbit(x))
    if (tim[x] == cur) ret += bit[x];
  return ret;
}
void solve(int l, int r) {
  if (l == r) return;
  int mid = (l + r) >> 1;
  int p = l, q = mid + 1;
  for (int i = l; i <= r; i++)
    if (a[i].pos <= mid)
      tmp[p++] = a[i];
    else
      tmp[q++] = a[i];
  for (int i = l; i <= r; i++) a[i] = tmp[i];
  solve(l, mid);
  int j = l;
  cur++;
  for (int i = mid + 1; i <= r; i++) {
    while (j <= mid && a[j].x <= a[i].x) {
      if (a[j].tag == 1) add(a[j].y, a[j].z);
      ++j;
    }
    if (a[i].tag == 2) a[i].ans += ask(a[i].y);
  }
  solve(mid + 1, r);
  p = l;
  q = mid + 1;
  for (int i = l; i <= r; i++)
    if ((a[p].x < a[q].x || q > r) && p <= mid)
      tmp[i] = a[p++];
    else
      tmp[i] = a[q++];
  for (int i = l; i <= r; i++) a[i] = tmp[i];
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d", &n);
  while (1) {
    scanf("%d", &foo);
    if (foo == 3) break;
    if (foo == 1) {
      int a, b, c;
      scanf("%d %d %d", &a, &b, &c);
      m++;
      ::a[m] = node(a, b, c, m, 1, 0);
    } else {
      int a, b, c, d;
      scanf("%d %d %d %d", &a, &b, &c, &d);
      m++;
      ::a[m] = node(a - 1, d, 0, m, 2, 0);
      m++;
      ::a[m] = node(c, b - 1, 0, m, 2, 0);
      m++;
      ::a[m] = node(a - 1, b - 1, 0, m, 2, 0);
      m++;
      ::a[m] = node(c, d, 0, m, 2, 0);
    }
  }
  std::sort(a + 1, a + m + 1, cmp1);
  solve(1, m);
  std::sort(a + 1, a + m + 1, cmp2);
  for (int i = 1; i <= m; i++) {
    if (a[i].tag == 1) continue;
    int ans = 0;
    ans -= a[i++].ans;
    ans -= a[i++].ans;
    ans += a[i++].ans;
    ans += a[i].ans;
    printf("%d\n", ans);
  }
  return 0;
}
