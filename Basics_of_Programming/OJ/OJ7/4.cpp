#include <iostream>
using namespace std;

/*
题目：最大乘积

题目描述：

李华给出了一个长度为n的整型序列 ，要求你在序列中找出由三个数组成的最大乘积，然后输出这个最大乘积。

第一行输入n（3<=n<=1000），表示序列的长度。第二行输入这个序列，序列中的所有元素范围[-1000,1000]。

示例：

输入：

3

1 2 3

输出：

6*/

int main() {
	int n;
	cin >> n;
	long long max1 = 0xffffffffffffffff, max2 = 0xfffffffffffffffe, max3 = 0xfffffffffffffffd;
	long long min1 = 0x7ffffffffffffffe, min2 = 0x7fffffffffffffff;
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		if (num > max1) {
			max3 = max2;
			max2 = max1;
			max1 = num;
		}
		else if (num > max2) {
			max3 = max2;
			max2 = num;
		}
		else if (num > max3) max3 = num;
		if (num < min1) {
			min2 = min1;
			min1 = num;
		}
		else if (num < min2) min2 = num;
	}
	cout << max(max1 * max2 * max3, max1 * min1 * min2) << endl;
	return 0;
}