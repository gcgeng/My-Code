#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#define ll long long
const int maxn = 3000;
const ll mod = 1000000000000000;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
int n, m, tot, cnt;
ll d[maxn], num[maxn], prime[maxn], check[maxn], ans[maxn], l = 1;
void getprime() {
  for (int i = 2; i <= 1000; i++) {
    if (!check[i])
      prime[cnt++] = i;
    for (int j = 0; j < cnt; j++) {
      if (i * prime[j] > 1000)
        break;
      check[i * prime[j]] = 1;
      if (i % prime[j] == 0)
        break;
    }
  }
}
void solve(int a, int f) {
  for (int k = 1; k <= a; k++) {
    int x = k;
    for (int i = 0; i < cnt; i++) {
      if (x <= 1)
        break;
      while (x % prime[i] == 0) {
        num[i] += f;
        x /= prime[i];
      }
    }
  }
}
void mul(int x) {
  for (int i = 1; i <= l; i++)
    ans[i] *= x;
  for (int i = 1; i <= l; i++) {
    ans[i + 1] += ans[i] / mod;
    ans[i] %= mod;
  }
  while (ans[l + 1]) {
    l++;
    ans[l + 1] += ans[l] / mod;
    ans[l] %= mod;
  }
}
void print() {
  for (int i = l; i; i--)
    if (i == l)
      printf("%lld", ans[i]);
    else
      printf("%06lld", ans[i]);
}
data sub(data a, data b) {
  a.a[1] += 2;
  int j = 1;
  while (a.a[j] >= 10) {
    a.a[j] %= 10;
    a.a[j + 1]++;
    j++;
  }
  for (int i = 1; i <= a.len; i++) {
    a.a[i] -= b.a[i];
    if (a.a[i] < 0) {
      a.a[i] += 10;
      a.a[i + 1]--;
    }
  }
  while (a.a[a.len] == 0)
    a.len--;
  return a;
}
int main() {
  getprime();
  ans[1] = 1;
  n = read();
  if (n == 1) {
    int x = read();
    if (!x || x == -1)
      printf("1");
    else
      printf("0");
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    d[i] = read();
    if (!d[i]) {
      printf("0");
      return 0;
    }
    if (d[i] == -1)
      m++;
    else {
      d[i]--;
      tot += d[i];
    }
  }
  if (tot > n - 2) {
    printf("0");
    return 0;
  }
  solve(n - 2, 1);
  solve(n - 2 - tot, -1);
  for (int i = 1; i <= n; i++)
    solve(d[i], -1);
  for (int i = 0; i < cnt; i++)
    while (num[i]--)
      mul(prime[i]);
  for (int i = 1; i <= n - 2 - tot; i++)
    mul(m);
  print();
  return 0;
}
