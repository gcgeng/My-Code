#include <cstdio>
#include <algorithm>
int n, m;
const int maxn = 10010;
struct seg{
	int l, r, sum1, sum2, tag;
}t1[2][maxn<<2];
void pushdown(seg *t, int k) {
	if(t[k].tag == -1) return;
	int l = t[k].l, r = t[k].r, mid = (l + r) >> 1;
	if(t[k<<1].tag != -1 && (r-l) >= 2) pushdown(t, k<<1);
	if(t[k<<1|1].tag != -1 && (r-l) >= 2) pushdown(t, k<<1|1);
	if(t[k].tag == 1) {
		t[k<<1].sum2 = (mid - l + 1) - t[k<<1].sum1;
		t[k<<1|1].sum2 = (r - mid) - t[k<<1|1].sum1;
	}
	if(t[k].tag == 0) {
		t[k<<1].sum1 = t[k<<1|1].sum2 = 0;
	}
	t[k<<1].tag = t[k<<1|1].tag = t[k].tag;
	t[k].tag = -1;
}
void update(seg *t, int k) {
	t[k].sum1 = t[k<<1].sum1 + t[k<<1|1].sum1;
	t[k].sum2 = t[k<<1].sum2 + t[k<<1|1].sum2;
}
void build(int k, int l, int r) {
	t1[0][k].l = l, t1[0][k].r = r, t1[0][k].tag = -1;
	if(l == r) {
		t1[0][k].sum1 = 1;
		t1[0][k].sum2 = 0;
		return;
	}
	int mid = (l+r) >> 1;
	build(k << 1, l, mid);
	build(k << 1|1, mid+1, r);
	update(t1[0], k);
}
void modify(seg *t, int k, int x, int y, int v) {
	pushdown(t, k);
	int l = t[k].l, r = t[k].r;
	if(x <= l && r <= y) {
		if(v == 1) {
			t[k].sum2 = (r-l+1)-t[k].sum1;
		}
		else {
			t[k].sum2 = t[k].sum1 = 0;
		}
	        t[k].tag = v;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) modify(t, k<<1, x, y, v);
	if(y > mid) modify(t, k<<1|1, x, y, v);
	update(t, k);
}
int query(seg *t, int k, int x, int y) {
	pushdown(t, k);
	int l = t[k].l, r = t[k].r, mid = (l + r) >> 1;
	if(x <= l && r <= y) return t[k].sum2;
	int tmp = 0;
	if(x <= mid) tmp += query(t, k << 1, x, y);
	if(y > mid) tmp += query(t, k << 1|1, x, y);
	return tmp;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("input", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	n++;
	build(1, 1, n);
	int ans2 = 0;
	while(m--) {
		int k, x, y;
		scanf("%d %d %d", &k, &x, &y);
		x++;
		y++;
		if(k == 0) {
			printf("%d ", query(t1[0], 1, x, y));
			ans2 += query(t1[0], 1, x, y);
			modify(t1[0], 1, x, y, 0);
		}
		else {
			modify(t1[0], 1, x, y, 1);
		}
		printf("%d %d\n", t1[0][1].sum1, t1[0][1].sum2);
	}
	printf("%d\n%d\n", query(t1[0], 1, 1, n), ans2);
	return 0;
}
