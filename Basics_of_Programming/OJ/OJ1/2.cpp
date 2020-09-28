#include <iostream>
using namespace std;

/*题目：Max Number

题目描述：

输入3个整数，输出其中的最大值。

注：本题不允许使用STL的库函数max。*/

int main() {
	int a, b, c;
	int max;
	cin >> a >> b >> c;
	if (a > b) max = a;
	else max = b;
	if (c > max) max = c;
	cout << max << endl;
	return 0;
}