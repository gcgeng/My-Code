#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cassert>
namespace Solve{
	int n, k;
	int read() {
		int x = 0, f = 1;
		char ch = getchar();
		while(!isdigit(ch)) {
			if(ch == '-') f = -1;
			ch = getchar();
		}
		while(isdigit(ch)) {
			x = x * 10 + ch - '0';
			ch = getchar();
		}
		return x * f;
	}
	void solve() {
		n = read(), k = read();
		int tmpa = n/2, tmpb = n - tmpa;
		int Maxk = tmpa * tmpb;
		int tmp = Maxk - k;
		assert(k <= Maxk);
		for(int i = 1; i <= tmp/tmpa; i++) putchar('B');
		for(int i = 1; i <= tmpa - tmp%tmpa; i++) putchar('A');
		putchar('B');
		for(int i = 1; i <= tmp % tmpa; i++) putchar('A');
		for(int i = 1; i <= tmpb - tmp/tmpa -1; i++) putchar('B');
		printf("\n");
	}
}
int main() {
	Solve::solve();
	return 0;
}
