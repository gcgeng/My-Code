#include <algorithm>
#include <cmath>
#include <cstdio>
const int maxn = 100100;
const double eps = 1e-9;
const double inf = 1e20;
struct day {
  double A, B, Rate, K, f, g;
  int id;
  bool operator<(const day &b) const { return K > b.K; }
} a[maxn], tmp[maxn];
int n, top;
double S, d[maxn];
int st[maxn];
double getk(int i, int j) {
  if (fabs(a[i].f - a[j].f) < eps) return inf;
  return (a[i].g - a[j].g) / (a[i].f - a[j].f);
}
bool cmp(day &a, day &b) {
  return a.f < b.f || (fabs(a.f - b.f) < eps && a.g < b.g);
}
void solve(int l, int r) {
  if (l == r) {
    d[l] = std::max(d[l], d[l - 1]);
    a[l].g = d[l] / (a[l].A * a[l].Rate + a[l].B);
    a[l].f = a[l].g * a[l].Rate;
    return;
  }
  int mid = (l + r) >> 1, p = l, q = mid + 1;
  for (int i = l; i <= r; i++) {
    if (a[i].id <= mid)
      tmp[p++] = a[i];
    else
      tmp[q++] = a[i];
  }
  for (int i = l; i <= r; i++) a[i] = tmp[i];
  solve(l, mid);
  top = 0;
  for (int i = l; i <= mid; i++) {
    while (top > 1 && getk(st[top - 1], st[top]) < getk(st[top - 1], i) + eps)
      top--;
    st[++top] = i;
  }
  int j = 1;
  for (int i = mid + 1; i <= r; i++) {
    while (j < top && getk(st[j], st[j + 1]) + eps > a[i].K) j++;
    d[a[i].id] =
        std::max(d[a[i].id], a[st[j]].f * a[i].A + a[st[j]].g * a[i].B);
  }
  solve(mid + 1, r);
  p = l;
  q = mid + 1;
  for (int i = l; i <= r; i++) {
    if (p <= mid && (q > r || cmp(a[p], a[q])))
      tmp[i] = a[p++];
    else
      tmp[i] = a[q++];
  }
  for (int i = l; i <= r; i++) a[i] = tmp[i];
}
int main() {
  /*
  freopen("cash.in", "r", stdin);
  freopen("cash.out", "w", stdout);*/
  scanf("%d %lf", &n, &d[0]);
  for (int i = 1; i <= n; i++) {
    scanf("%lf %lf %lf", &a[i].A, &a[i].B, &a[i].Rate);
    a[i].K = -(a[i].A / a[i].B);
    a[i].id = i;
  }
  std::sort(a + 1, a + 1 + n);
  solve(1, n);
  printf("%.3lf", d[n]);
}
