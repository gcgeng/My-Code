#include <algorithm>
#include <cctype>
#include <cstdio>
#define ll long long
const int maxn = 1e5 + 1e2;
inline ll read() {
  ll x = 0, f = 1;
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
struct node {
  ll P, R, G, D;
  ll x, y;
  int id;
  node() {}
  void init() {
    D = read();
    P = read();
    R = read();
    G = read();
    x = G;
    y = -P + R - D * G - G;
  }
  bool operator<(const node b) const { return this->D < b.D; }
} a[maxn], tmp[maxn];
ll f[maxn];
struct point {
  ll x, y;
  point(ll a = 0, ll b = 0) : x(a), y(b) {}
};
point operator-(point a, point b) { return point(a.x - b.x, a.y - b.y); }
double cross(point a, point b) { return (double)a.x * b.y - (double)a.y * b.x; }
int N, D;
point p[maxn], st[maxn];
ll line(ll x, point &p) { return p.x * x + p.y; }
bool cmp(int i, int j) {
  return a[i].x == a[j].x ? a[i].y + f[a[i].id] < a[j].y + f[a[j].id]
                          : a[i].x < a[j].x;
}
void solve(int l, int r) {
  if (l == r) {
    f[l] = std::max(f[l - 1], f[l]);
    return;
  }
  int mid = (l + r) >> 1;
  solve(l, mid);
  int n = 0, top = 0;
  for (int i = l; i <= mid; i++)
    if (f[a[i].id] >= a[i].P) p[++n] = point(a[i].x, a[i].y + f[a[i].id]);
  for (int i = 1; i <= n; i++) {
    while (top > 1 && cross(st[top] - st[top - 1], p[i] - st[top - 1]) >= 0)
      top--;
    st[++top] = p[i];
  }
  int j = 1;
  for (int i = mid + 1; i <= r; i++) {
    while (j < top && line(a[i].D, st[j + 1]) > line(a[i].D, st[j])) j++;
    if (j <= top) f[i] = std::max(f[i], line(a[i].D, st[j]));
  }
  solve(mid + 1, r);
  int p = l, q = mid + 1;
  for (int i = l; i <= r; i++) {
    if (q > r || (p <= mid && cmp(p, q)))
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
  int kase = 0;
  while (scanf("%d %lld %d", &N, &f[0], &D) != EOF) {
    if (N == 0 && f[0] == 0 && D == 0) return 0;
    for (int i = 1; i <= N; i++) a[i].init();
    a[++N].D = D + 1;
    std::sort(a + 1, a + 1 + N);
    for (int i = 1; i <= N; i++) f[i] = 0, a[i].id = i;
    solve(1, N);
    printf("Case %d: %lld\n", ++kase, f[N]);
  }
}
