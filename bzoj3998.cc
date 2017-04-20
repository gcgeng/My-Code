#include <cstdio>
#include <cstring>
const int maxn = 5e5 + 1e2;
const int maxm = maxn << 1;
int N, T, k;
char str[maxn];
struct Suffix_Automaton {
  int rt, last, trans[maxm][26], fa[maxm], sz, len[maxm], cnt[maxm];
  int v[maxn], q[maxm], sum[maxm];
  void init() {
    sz = 0;
    rt = last = ++sz;
  }
  void insert(int x) {
    int p = last, np = last = ++sz;
    len[np] = len[p] + 1;
    cnt[np] = 1;
    while (!trans[p][x] && p) {
      trans[p][x] = np;
      p = fa[p];
    }
    if (!p) {
      fa[np] = 1;
    } else {
      int q = trans[p][x];
      if (len[q] == len[p] + 1) {
        fa[np] = q;
      } else {
        int nq = ++sz;
        len[nq] = len[p] + 1;
        memcpy(trans[nq], trans[q], sizeof(trans[q]));
        fa[nq] = fa[q];
        fa[q] = fa[np] = nq;
        while (trans[p][x] == q) {
          trans[p][x] = nq;
          p = fa[p];
        }
      }
    }
    return;
  }
  void pre() {
    for (int i = 1; i <= sz; i++)
      v[len[i]]++;
    for (int i = 1; i <= ::N; i++)
      v[i] += v[i - 1];
    for (int i = sz; i; i--)
      q[v[len[i]]--] = i;
    for (int i = sz; i; i--) {
      int t = q[i];
      if (T == 1)
        cnt[fa[t]] += cnt[t];
      else
        cnt[t] = 1;
    }
    cnt[1] = 0;
    for (int i = sz; i; i--) {
      int t = q[i];
      sum[t] = cnt[t];
      for (int j = 0; j < 26; j++)
        sum[t] += sum[trans[t][j]];
    }
  }
  void dfs(int x, int k) {
    if (k <= cnt[x])
      return;
    k -= cnt[x];
    for (int i = 0; i < 26; i++)
      if (int t = trans[x][i]) {
        if (k <= sum[t]) {
          putchar(i + 'a');
          dfs(t, k);
          return;
        }
        k -= sum[t];
      }
  }
} sam;
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%s", str + 1);
  N = strlen(str + 1);
  scanf("%d %d", &T, &k);
  sam.init();
  for (int i = 1; i <= N; i++) {
    sam.insert(str[i] - 'a');
  }
  sam.pre();
  if (k > sam.sum[1])
    printf("-1\n");
  else
    sam.dfs(1, k);
  return 0;
}
