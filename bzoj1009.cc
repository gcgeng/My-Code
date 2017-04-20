#include <cstdio>
const int maxn = 25;
int p[maxn], a[maxn][maxn], b[maxn][maxn];
int n, m, mod;
char ch[maxn];
void mul(int a[maxn][maxn], int b[maxn][maxn], int ans[maxn][maxn]) {
  int tmp[maxn][maxn];
  for (int i = 0; i < m; i++)
    for (int j = 0; j < m; j++) {
      tmp[i][j] = 0;
      for (int k = 0; k < m; k++)
        tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j]) % mod;
    }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++)
      ans[i][j] = tmp[i][j];
  }
}
int main() {
  // freopen("input", "r", stdin);
  scanf("%d %d %d", &n, &m, &mod);
  scanf("%s", ch + 1);
  int j = 0;
  for (int i = 2; i <= m; i++) {
    while (j > 0 && ch[j + 1] != ch[i])
      j = p[j];
    if (ch[j + 1] == ch[i])
      j++;
    p[i] = j;
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j <= 9; j++) {
      int t = i;
      while (t > 0 && ch[t + 1] - '0' != j)
        t = p[t];
      if (ch[t + 1] - '0' == j)
        t++;
      if (t != m)
        b[t][i] = (b[t][i] + 1) % mod;
    }
  }
  for (int i = 0; i < m; i++)
    a[i][i] = 1;
  while (n) {
    if (n & 1)
      mul(a, b, a);
    mul(b, b, b);
    n >>= 1;
  }
  int sum = 0;
  for (int i = 0; i < m; i++)
    sum = (sum + a[i][0]) % mod;
  printf("%d\n", sum);
  return 0;
}
