#include <cstdio>
#include <cstring>
#include <queue>
#define mod 10007
const int maxn = 6010;
int a[maxn][27], f[101][maxn], point[maxn];
int n, m, sz = 1;
char s[101];
bool leaf[maxn];
void insert(char s[101]) {
  int now = 1, c;
  for (int i = 0; i < strlen(s); i++) {
    c = s[i] - 'A' + 1;
    if (a[now][c])
      now = a[now][c];
    else
      now = a[now][c] = ++sz;
  }
  leaf[now] = 1;
}
void ac() {
  std::queue<int> q;
  q.push(1);
  point[1] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 1; i <= 26; i++) {
      if (!a[u][i])
        continue;
      int k = point[u];
      while (!a[k][i])
        k = point[k];
      point[a[u][i]] = a[k][i];
      if (leaf[a[k][i]])
        leaf[a[u][i]] = 1;
      q.push(a[u][i]);
    }
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= 26; i++)
    a[0][i] = 1;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    insert(s);
  }
  ac();
  f[0][1] = 1;
  for (int x = 1; x <= m; x++)
    for (int i = 1; i <= sz; i++) {
      if (leaf[i] || !f[x - 1][i])
        continue;
      for (int j = 1; j <= 26; j++) {
        int k = i;
        while (!a[k][j])
          k = point[k];
        f[x][a[k][j]] = (f[x][a[k][j]] + f[x - 1][i]) % mod;
      }
    }
  int ans1 = 0, ans2 = 1;
  for (int i = 1; i <= m; i++)
    ans2 = (ans2 * 26) % mod;
  for (int i = 1; i <= sz; i++) {
    if (!leaf[i])
      ans1 = (ans1 + f[m][i]) % mod;
  }
  // printf("%d %d\n", ans2, ans1);
  printf("%d\n", (ans2 - ans1 + mod) % mod);
  return 0;
}
