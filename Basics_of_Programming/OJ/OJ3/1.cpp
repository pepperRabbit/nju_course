#include <iostream>
#include <cmath>
using namespace std;

/*题目：素数求和

题目描述：写一个程序，求出1~n之间素数的和。
输入：输入一个正整数n，1<=n<=500000。
输出：输出一个正整数，表示1~n之间素数的和。*/

bool is_prime(int x) {
	for (int i = 2; i <= (int)sqrt((double)x); i++) {
		if (x % i == 0) return false;
	}
	return true;
}

int main() {
	int n;
	cin >> n;
	long int res = 0;
	for (int i = 2; i <= n; i++) {
		if (is_prime(i)) res += i;
	}
	cout << res << endl;
	return 0;
}