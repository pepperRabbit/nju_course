#include <iostream>
#include <cmath>
using namespace std;

/*题目：丑数

题目描述：编写一个程序，判断给定的数是否为丑数。丑数是指只包含质因数2,3,5的正整数。若为丑数则打印true，否则打印false。

输入：输入一个整数n(1<=n<=10000000)

输出：输出true或者false，true表示是丑数，false表示不是丑数。

示例：

输入：6 输出：true

输入：14 输出：false*/

void judge(int x) {
	if (x == 1) {
		cout << "false" << endl;
		return;
	}
	while (x % 2 == 0) {
		x /= 2;
	}
	while (x % 3 == 0) {
		x /= 3;
	}
	while (x % 5 == 0) {
		x /= 5;
	}
	if (x == 1) cout << "true" << endl;
	else cout << "false" << endl;
}

int main() {
	int x;
	cin >> x;
	judge(x);
	return 0;
}