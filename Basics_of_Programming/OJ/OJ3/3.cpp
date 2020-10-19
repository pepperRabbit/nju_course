#include <iostream>
using namespace std;

/*题目：阶乘2

题目描述：写一个程序，求n的阶乘，并将最后的结果模1e9+7。
输入：输入一个正整数n。（1<=n<=1000）
输出：输出一个正整数，表示模1e9+7之后n的阶乘。
举例：
输入10
输出结果为（10!）%(1e9+7)，也就是3628800。
输入100
输出结果为（100!）%(1e9+7)，也就是437918130。
提示：(a+b)%n == （a%n + b%n）%n*/

int main() {
	int n;
	cin >> n;
	long long int res = 1;
	const int mod = 1e9 + 7;
	for (int i = 1; i <= n; i++) {
		res = ((res % mod) * (i % mod)) % mod;
	}
	cout << res << endl;
	return 0;
}