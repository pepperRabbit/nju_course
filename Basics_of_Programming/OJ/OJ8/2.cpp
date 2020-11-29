#include <iostream>
using namespace std;

/*
题目：超大型斐波那契数

题目描述：

描述：
给定A,B,N，计算fib(A^B)%N。fib表示斐波那契函数。例如fib(0)=0,fib(1)=1,fib(2)=1,fib(3)=2.....。

输入：
输入三个整数A,B,N(0 <= A,B < 2^64，1<=N<=1000)。A和B不会同时等于0。

输出：
输出一个整数，表示fib(A^B)%N。

样例1：
输入：

1 1 2

输出：

1

样例2：
输入：

2 3 1000

输出：

21

样例3：
输入：

18446744073709551615 18446744073709551615 1000

输出：

250*/

unsigned long long fib[2000] = { 0 };

int main() {
	unsigned long long a, b, n, t = 1;
	cin >> a >> b >> n;
	if (n == 1) {
		cout << 0 << endl;
		return 0;
	}
	fib[0] = 1, fib[1] = 1, fib[2] = 2;
	fib[2] %= n;
	int i;
	for (i = 3; fib[i - 1] != 1 || fib[i - 2] != 1; i++) {
		fib[i] = (fib[i - 1] + fib[i - 2]) % n;
	}
	i -= 2;
	a %= i;
	while (b > 0) {
		if (b % 2) {
			b--;
			t = (t * a) % i;
		}
		else {
			b /= 2;
			a = (a * a) % i;
		}
	}
	cout << fib[t - 1] << endl;
	return 0;
}