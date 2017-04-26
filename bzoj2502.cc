#include <cstdio>
#include <algorithm>
const int maxn = 100+10;
const int maxm = maxn*maxn;
struct edge{
	int to, next, cap, cost;
	edge(int a, int b, int c, int d):to(a), next(b), cap(c), cost(d){}
	edge(){}
}e[maxn<<1];
int dist[maxn], fi[maxn], head[maxn];
int n, m, cnt;
void add_edge(int from, int to, int cap, int cost) {
	e[++cnt] = edge(to, head[from], cap, cost);
	head[from] = cnt;
}
void add(int from, int to, int cap, int cost) {
	add_edge(from, to, cap, cost);
	add_edge(to, from, 0, -cost);
}
int main() {
	scanf("%d", &n);
	int s = 0, t = n + 1, v = t + 1;
	for(int i = 1; i <= n; i++) {

