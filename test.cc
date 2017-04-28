#include <cstdio>
#include <queue>
int main(int argc, char const *argv[]) {
	int a = 1, b = 2, ans = 0;
	while(b <= 4000000) {
		printf("%d ", a);
		if(!(b&1)) ans += b;
		int tmp = a;
		a = b;
		b += tmp;
	}
	printf("\n");
	printf("%d", ans);
}
