#include <iostream>
using namespace std;

/*题目：斐波那契

题目描述：编写一个程序，输入一个非负整数n，输出斐波那契数列（Fibonacci）数列的第n项。斐波那契数列的定义如下：

F(0) = 0， F(1) = 1
F(n) = F(n-1)+F(n-2) while n>1

斐波那契数列由0和1开始，之后的斐波那契数就是由之前的两数相加而得出。

输入：输入一个整数n(0<=n<=1000)。

输出：输出一个整数。

注意：斐波那契数列中的0是第0项；答案需要取模1e9+7，如计算结果为1000000008，请输出1。

示例：

输入：0 输出：0

输入：20 输出：6765

输入：657 输出：778917214*/

int main() {
	int n;
	cin >> n;
	if (n == 0) {
		cout << 0 << endl;
		return 0;
	}
	if (n == 1) {
		cout << 1 << endl;
		return 0;
	}
	long long a = 0, b = 1, temp = 0, mod = 1e9 + 7;
	for (int i = 2; i <= n; i++) {
		temp = (a + b) % mod;
		a = b;
		b = temp;
	}
	cout << b << endl;
	return 0;
}