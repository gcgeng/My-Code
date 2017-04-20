#include <cstdio>
const int maxn = 100100;
double f[maxn], A[maxn], B[maxn], Rate[maxn];
int N;
double S, ans;
double m2a(double x, int i) { return x * (Rate[i]) / (A[i] * Rate[i] + B[i]); }
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d %lf", &N, &S);
  for (int i = 1; i <= N; i++) scanf("%lf %lf %lf", &A[i], &B[i], &Rate[i]);
  f[1] = S * (Rate[1]) / (A[1] * Rate[1] + B[1]);
  ans = S;
  // printf("%.3lf ", f[1]);
  for (int i = 2; i <= N; i++) {
    for (int j = 1; j < i; j++) {
      double x = f[j] * A[i] + (f[j] / Rate[j]) * B[i];
      if (x > ans) ans = x;
    }
    f[i] = m2a(ans, i);
    //  printf("%.3lf ", f[i]);
  }
  printf("%.3f", ans);
}
