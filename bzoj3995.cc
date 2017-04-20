#include <algorithm>
#include <cstdio>
#include <cstring>
const int maxn = 60110;
int l[maxn][2], r[maxn][2], u[maxn], d[maxn];
int N, M;
struct seg {
  int a[5];
  int l, r;
} t[maxn << 2];
void up(int &a, int b) { a = std::min(a, b); }
void update(int a[5], int l[5], int r[5], int se, int de) {
  memset(a, 0x3f, sizeof(t[0].a));

  up(a[0], l[0] + r[0] + se);
  up(a[1], l[0] + r[1] + se);
  up(a[0], l[0] + r[2] + de);
  up(a[0], l[0] + r[3] + de);
  up(a[1], l[0] + r[3] + se);
  up(a[1], l[0] + r[4] + de);

  up(a[0], l[1] + r[0] + de);
  up(a[1], l[1] + r[1] + de);
  up(a[1], l[1] + r[3] + de);

  up(a[2], l[2] + r[0] + se);
  up(a[4], l[2] + r[1] + se);
  up(a[2], l[2] + r[2] + de);
  up(a[4], l[2] + r[3] + se);
  up(a[2], l[2] + r[3] + de);
  up(a[4], l[2] + r[4] + de);

  up(a[2], l[3] + r[0] + se);
  up(a[0], l[3] + r[0] + de);
  up(a[4], l[3] + r[1] + se);
  up(a[1], l[3] + r[1] + de);
  up(a[2], l[3] + r[2] + de);
  up(a[4], l[3] + r[3] + se);
  up(a[3], l[3] + r[3] + de);
  up(a[4], l[3] + r[4] + de);

  up(a[2], l[4] + r[0] + de);
  up(a[4], l[4] + r[1] + de);
  up(a[4], l[4] + r[3] + de);
}
void build(int k, int l, int r) {
  t[k].l = l, t[k].r = r;
  if (l == r) {
    t[k].a[0] = d[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(k << 1, l, mid);
  build(k << 1 | 1, mid + 1, r);
  int se = std::min(::r[mid][0], ::r[mid][1]), de = ::r[mid][0] + ::r[mid][1];
  update(t[k].a, t[k << 1].a, t[k << 1 | 1].a, se, de);
}
void query(int k, int x, int y, int res[5]) {
  int l = t[k].l, r = t[k].r, mid = (l + r) >> 1;
  if (x <= l && r <= y) {
    memcpy(res, t[k].a, sizeof(t[k].a));
    return;
  }
  int se = std::min(::r[mid][0], ::r[mid][1]), de = ::r[mid][0] + ::r[mid][1];
  int r1[5], r2[5];
  if (x <= mid) {
    if (y > mid) {
      query(k << 1, x, y, r1);
      query(k << 1 | 1, x, y, r2);
      update(res, r1, r2, se, de);
    } else
      query(k << 1, x, y, res);
  } else
    query(k << 1 | 1, x, y, res);
}
void change(int k, int x, int y) {
  int l = t[k].l, r = t[k].r, mid = (l + r) >> 1;
  if (x <= l && r <= y) {
    if (l == r) {
      t[k].a[0] = d[l];
      return;
    } else {
      int se = std::min(::r[mid][0], ::r[mid][1]),
          de = ::r[mid][0] + ::r[mid][1];
      update(t[k].a, t[k << 1].a, t[k << 1 | 1].a, se, de);
    }
  } else {
    int se = std::min(::r[mid][0], ::r[mid][1]), de = ::r[mid][0] + ::r[mid][1];
    if (x <= mid)
      change(k << 1, x, y);
    if (y > mid)
      change(k << 1 | 1, x, y);
    update(t[k].a, t[k << 1].a, t[k << 1 | 1].a, se, de);
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d %d", &N, &M);
  for (int i = 1; i < N; i++) {
    int x;
    scanf("%d", &x);
    r[i][0] = l[i + 1][0] = x;
  }
  for (int i = 1; i < N; i++) {
    int x;
    scanf("%d", &x);
    r[i][1] = l[i + 1][1] = x;
  }
  for (int i = 1; i <= N; i++) {
    int x;
    scanf("%d", &x);
    u[i] = d[i] = x;
  }
  build(1, 1, N);
  while (M--) {
    char ch[5];
    scanf("%s", ch);
    if (ch[0] == 'Q') {
      int A[5], x, y;
      scanf("%d %d", &x, &y);
      query(1, x, y, A);
      printf("%d\n", A[0]);
    } else {
      int x0, y0, x1, y1, v;
      scanf("%d %d %d %d %d", &x0, &y0, &x1, &y1, &v);
      x0--, x1--;
      if (x0 == x1) {
        if (y0 > y1)
          std::swap(y0, y1);
        r[y0][x0] = l[y1][x0] = v;
        change(1, y0, y1);
      } else {
        u[y0] = d[y0] = v;
        change(1, y0, y1);
      }
    }
  }
}
