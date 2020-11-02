#include <iostream>
using namespace std;

/*题目：n的阶乘后零的数量

题目描述：

给定一个整数n，返回n!结果尾数中零的数量。（1<=n<=100000000）

示例 1:

输入: 3

输出: 0

解释: 3! = 6, 尾数中没有零。

 

示例 2:

输入: 5

输出: 1

解释: 5! = 120, 尾数中有 1 个零.*/

int count5(int n) {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		int j = i;
		while (j % 5 == 0) {
			cnt++;
			j /= 5;
		}
	}
	return cnt;
}

int main() {
	int n, cnt = 0;
	cin >> n;
	cout << count5(n) << endl;
	return 0;
}