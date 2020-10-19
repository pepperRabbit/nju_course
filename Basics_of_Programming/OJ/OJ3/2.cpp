#include <iostream>
using namespace std;

/*题目：阶乘1

题目描述：写一个程序，求n的阶乘。
输入：输入一个正整数n。（1<=n<=10）
输出：输出一个正整数，表示n的阶乘。*/

int main() {
	int n;
	cin >> n;
	int res = 1;
	for (int i = 1; i <= n; i++) {
		res *= i;
	}
	cout << res << endl;
	return 0;
}