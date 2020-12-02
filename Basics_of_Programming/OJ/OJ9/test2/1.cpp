#include <iostream>
#include <cmath>
using namespace std;

/*
题目：Problem 1 亲和数

题目描述：

题目描述
对于正整数n，定义d(n)为n所有真因数之和。设d(a)=b，若d(b)=a且a≠b，则称无序二元组（a,b)为亲和数对。

例如d(220)=1+2+4+5+10+11+20+22+44+55+110=284，d(284)=1+2+4+71+142=220，所以220和284为互为亲和数，(220,284)为亲和数对。 求N以内所有亲和数对(a,b),(1<=a,b<=n)的和K。

 

输入
一个整数N。2 ≤ N ≤ 10^3。

输出
输出：一个整数K.

样例输入
1000
样例输出
504*/

int solve(int x) {
	int res = 0;
	for (int i = 1; i < x / 2 + 1; i++) {
		if (x % i == 0) {
			res += i;
		}
	}
	return res;
}

int main() {
	int n, res = 0;
	cin >> n;
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (solve(i) == j && solve(j) == i) {
				//cout << i << " " << j << endl;
				res = res + i + j;
			}
		}
	}
	cout << res << endl;
	return 0;
}
