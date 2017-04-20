#include <cstdio>
const int maxm = 102;
int A[maxm][maxm], B[maxm][1], C[maxm][1];
int N, M, x, S, a[maxm];
int main() {
  scanf("%d %d %d %d", &N, &M, &x, &S);
  for (int i = 1; i <= S; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i <= S; i++) {
    for (int j = 1; j <= S; j++) {
      int tmp = (i * j) % M;
      A[tmp][i] = 1;
    }
  }
  for (int i = 1; i <= M; i++) {
    for (int j = 1; j <= M; j++)
      printf("%d ", A[i][j]);
    printf("\n");
  }
  return 0;
}
