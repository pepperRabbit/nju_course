#include <iostream>
#include <cmath>
using namespace std;

/*题目：水仙花数

题目描述：编写一个程序，求所有水仙花数（水仙花数是这样的三位数，它们等于它们的各位数字的立方和）。例如：153 = 1^3+5^3+3^3。

输入：无

输出：将所有的水仙花数按从小到大的顺序输出在一行内，之间用空格隔开，如：

xxx xxx xxx*/

bool count(int x) {
	int res = 0, i = x;
	while (i != 0) {
		res += (int)pow((i % 10), 3);
		i /= 10;
	}
	if (res == x) return true;
	else return false;
}

int main() {
	for (int i = 100; i < 1000; i++) {
		if (count(i)) cout << i << " ";
	}
	return 0;
}