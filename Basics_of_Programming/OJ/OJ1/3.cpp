#include <iostream>
#include <math.h>
using namespace std;

/*题目：判断三角形

题目描述：

输入三个整数，表示三条边的长度，判断其能否构成一个三角形，若能，输出Yes，若不能输出No。

每条边长度范围在int以内，且任何运算不会产生溢出。*/ 

int main() {
	int a, b, c;
	cin >> a >> b >> c;
	if (a + b > c && fabs(a - b) < c) cout << "Yes" << endl;
	else cout << "No" << endl;
	return 0;
}
