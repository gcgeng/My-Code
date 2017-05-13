#include <cstring>
#include <cstdio>
char str[10];
int main() {
  scanf("%s", str);
  int tmp = 0, ans = 0;
  for(int i = 0; i < strlen(str); i++) {
    if(str[i] == 'B') ans += tmp;
    else tmp++;
  }
  printf("%d %d",strlen(str), ans);
  return 0;
}
