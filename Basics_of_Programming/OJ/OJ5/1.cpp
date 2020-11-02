#include <iostream>
using namespace std;

/*题目：小母牛

题目描述：

若一头小母牛， 从出生起第四个年头开始每年生一头母牛， 按此规律，第n年有多少头母牛? 输入一个整数n（1<=n<=50）。

示例1：

输入：1

输出：1

 

示例2：

输入：4

输出：2*/

int count_cow(int n) {
	if (n <= 0) return 0;
	else if (n > 0 && n < 4) return 1;
	else return count_cow(n - 1) + count_cow(n - 3);
}

int main() {
	int n;
	cin >> n;
	cout << count_cow(n) << endl;
	return 0;
}