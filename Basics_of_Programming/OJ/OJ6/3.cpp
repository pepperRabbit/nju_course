#include <iostream>
using namespace std;

/*题目：爬楼梯

题目描述：

假设你正在爬楼梯，需要n阶才能到达楼顶。每次可以爬1或2个台阶，问一共有多少种不同的方法可以爬到楼顶？（n是一个正整数且1=<n<=1000）

示例：

输入： 2

输出： 2

解释： 有两种方法可以爬到楼顶。1阶+1阶 || 2阶。

输入： 3

输出： 3

解释： 有三种方法可以爬到楼顶。1阶+1阶+1阶 || 1阶+2阶 || 2阶+1阶*/

/*int solve(int n) {
	if (n < 0) return 0;
	if (n == 0) return 1;
	return solve(n - 1) + solve(n - 2);
}*/

int main() {
	int n;
	cin >> n;
	int cnt[1001] = { 0 };
	cnt[1] = 1;
	cnt[2] = 2;
	if(n <= 2 && n >= 0){
		cout << cnt[n] << endl;
	}
	else {
		for (int i = 3; i <= n; i++) {
			cnt[i] = cnt[i - 1] + cnt[i - 2];
		}
		cout << cnt[n] << endl;
	}
	return 0;
}