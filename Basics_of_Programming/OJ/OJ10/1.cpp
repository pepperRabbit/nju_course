#include <iostream>
using namespace std;

/*

输入：

i am supermind taichi master paul ma

输出：

64

样例2：

输入：

just now a friend asked me teacher ma what happened

输出：

84

样例3：

输入：

traditional kongfu has melt power

输出：

64*/

int main() {
	char s[10001];
	int c = 0, len = 0, cnt = 0;
	while ((c = getchar()) != EOF) {
		s[len++] = c;
	}
	for (int i = 0; i < len; i++) {
		if (s[i] == ' ') cnt++;
		//else if (s[i] == '\n');
		else if (s[i] <= 0x6F) cnt += (s[i] - 0x61) % 3 + 1;
		else if (s[i] <= 0x73) cnt += s[i] - 0x6f;
		else if (s[i] <= 0x76) cnt += s[i] - 0x73;
		else if (s[i] <= 0x7a) cnt += s[i] - 0x76;
	}
	cout << cnt << endl;
	return 0;
}