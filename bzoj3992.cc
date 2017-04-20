#include <cstdio>
#include <cstring>
#define mod 1004535809
#define ll long long
const int maxm = 102;
struct Matrix {
  ll a[maxm][maxm];
  int n, m;
  Matrix(int i = 0, int j = 0) : n(i), m(j) { memset(a, 0, sizeof(a)); }
};
Matrix operator*(Matrix A, Matrix B) {
  Matrix C = Matrix(A.n, B.m);
  for (int i = 0; i < A.n; i++) {
    for (int j = 0; j < B.m; j++) {
      for (int k = 0; k < A.m; k++) {
        C.a[i][j] = (C.a[i][j] + (A.a[i][k] * B.a[k][j]) % mod) % mod;
      }
    }
  }
  return C;
}
Matrix pow(Matrix A, int n) {
  Matrix ans = Matrix(A.n, A.n);
  for (int i = 0; i < ans.n; i++)
    ans.a[i][i] = 1;
  while (n) {
    if (n & 1)
      ans = ans * A;
    n >>= 1;
    A = A * A;
  }
  return ans;
}
Matrix A, B, C;
int N, M, x, S, a[maxm];
int main() {
  freopen("sdoi2015_sequence.in", "r", stdin);
  freopen("sdoi2015_sequence.out", "w", stdout);
  scanf("%d %d %d %d", &N, &M, &x, &S);
  for (int i = 1; i <= S; i++) {
    scanf("%d", &a[i]);
    a[i] %= M;
  }
  A = Matrix(M, M), B = Matrix(M, 1), C = Matrix(M, 1);
  for (int i = 0; i < M; i++) {
    for (int j = 1; j <= S; j++) {
      int tmp = (i * a[j]) % M;
      A.a[tmp][i]++;
    }
  }
  for (int i = 1; i <= S; i++)
    B.a[a[i]][0]++;
  C = pow(A, N - 1);
  /*for (int i = 0; i < C.n; i++) {
    for (int j = 0; j < C.m; j++)
      printf("%lld ", B.a[i][j]);
    printf("\n");
  }*/
  C = C * B;
  printf("%lld\n", C.a[x % M][0] % mod);
  return 0;
}
