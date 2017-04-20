#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
const int maxn = 200010;
using std::set;
using std::string;
#define ll long long
set<int> d[maxn];
set<int>::iterator it;
int n, K, tot = 1, head[maxn], sum[maxn];
struct edge {
  int to, next;
} e[maxn * 6];
string str[maxn];
struct Suffix_Automaton {
  int trans[maxn][26], len[maxn], sz;
  int fa[maxn], last, root;
  void init() {
    tot = 0;
    last = root = ++sz;
  }
  void add(int c, int id) {
    int p = last, np = last = ++sz;
    len[np] = len[p] + 1;
    d[np].insert(id);
    while (p && !trans[p][c])
      trans[p][c] = np, p = fa[p];
    if (!p)
      fa[np] = root;
    else {
      int q = trans[p][c];
      if (len[q] == len[p] + 1)
        fa[np] = q;
      else {
        int nq = ++sz;
        len[nq] = len[p] + 1;
        fa[nq] = fa[q];
        for (int i = 0; i < 26; i++)
          trans[nq][i] = trans[q][i];
        fa[q] = fa[np] = nq;
        while (trans[p][c] == q)
          trans[p][c] = nq, p = fa[p];
      }
    }
  }
  void print() {
    for (int i = 1; i <= sz; i++) {
      std::cout << fa[i] << ' ';
    }
    std::cout << std::endl;
    for (int i = 1; i <= sz; i++)
      printf("%d ", sum[i]);
    printf("\n");
  }
} sam;
void dfs(int x) {
  for (int i = head[x]; i; i = e[i].next) {
    int v = e[i].to;
    dfs(v);
    for (it = d[v].begin(); it != d[v].end(); it++)
      d[x].insert(*it);
  }
  sum[x] = d[x].size();
}
void add_edge(int from, int to) {
  e[++tot].to = to;
  e[tot].next = head[from];
  head[from] = tot;
}
int main() {
  scanf("%d %d", &n, &K);
  sam.init();
  for (int i = 1; i <= n; i++) {
    std::cin >> str[i];
    int len = str[i].length();
    for (int j = 0; j < len; j++)
      sam.add(str[i][j] - 'a', i);
    sam.last = sam.root;
  }
  for (int i = 1; i <= sam.sz; i++)
    if (sam.fa[i])
      add_edge(sam.fa[i], i);
  dfs(sam.root);
  // sam.print();
  if (K > n) {
    for (int i = 1; i <= n; i++)
      printf("0 ");
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    ll ans = 0;
    int now = sam.root, len = str[i].length();
    for (int j = 0; j < len; j++) {
      now = sam.trans[now][str[i][j] - 'a'];
      while (sum[now] < K)
        now = sam.fa[now];
      ans += sam.len[now];
    }
    printf("%lld ", ans);
  }
  return 0;
}
