#include <cstdio>
#define init int l = t[k].l, r = t[k].r, mid = (l + r) >> 1
const int maxn = 1e5 + 1e2;
int n, m, a[maxn], lambda, q;
struct seg {
  int l, r, val, cov;
} t[maxn << 4];
struct op {
  int a, b, c;
} o[maxn];
void update(int k) { t[k].val = t[k << 1].val + t[k << 1 | 1].val; }
void build(int k, int l, int r) {
  t[k].l = l, t[k].r = r, t[k].cov = -1;
  if (l == r) {
    t[k].val = a[l] > lambda;
    return;
  }
  int mid = (l + r) >> 1;
  build(k << 1, l, mid);
  build(k << 1 | 1, mid + 1, r);
  update(k);
}
void pushdown(int k) {
  if (t[k].cov != -1) {
    t[k << 1].cov = t[k].cov;
    t[k << 1 | 1].cov = t[k].cov;
    t[k << 1].val = (t[k << 1].r - t[k << 1].l + 1) * (t[k].cov);
    t[k << 1 | 1].val = (t[k << 1 | 1].r - t[k << 1 | 1].l + 1) * (t[k].cov);
    t[k].cov = -1;
  }
  if (t[k].l < t[k].r)
    update(k);
}
int query(int k, int x, int y) {
  init;
  pushdown(k);
  if (x <= l && r <= y)
    return t[k].val;
  int ans = 0;
  if (x <= mid)
    ans += query(k << 1, x, y);
  if (y > mid)
    ans += query(k << 1 | 1, x, y);
  return ans;
}
void modify(int k, int x, int y, int val) {
  init;
  pushdown(k);
  if (x <= l && r <= y) {
    t[k].val = (r - l + 1) * val;
    t[k].cov = val;
    return;
  }
  if (x <= mid)
    modify(k << 1, x, y, val);
  if (y > mid)
    modify(k << 1 | 1, x, y, val);
  update(k);
}
bool check(int x) {
  lambda = x;
  build(1, 1, n);
  for (int i = 1; i <= m; i++) {
    int opt = o[i].a, x = o[i].b, y = o[i].c;
    int tmp = query(1, x, y);
    if (opt == 0) {
      modify(1, x, y - tmp, 0);
      modify(1, y - tmp + 1, y, 1);
    } else {
      modify(1, x, x + tmp - 1, 1);
      modify(1, x + tmp, y, 0);
    }
  }
  return !query(1, q, q);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  int l = 1, r = n;
  for (int i = 1; i <= m; i++) {
    scanf("%d %d %d", &o[i].a, &o[i].b, &o[i].c);
  }
  scanf("%d", &q);
  while (l < r) {
    int mid = (l + r) >> 1;
    if (check(mid))
      r = mid;
    else
      l = mid + 1;
  }
  printf("%d", r);
}
