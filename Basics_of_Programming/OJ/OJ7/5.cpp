#include <iostream>
using namespace std;

/*
题目：0到n-1中丢失的数字

题目描述：

输入一个长度为n的递增数组，该数组中所有数字都是唯一的，并且每个数字的范围为[0,n]。在范围[0,n]内的n+1个数字中有且只有一个数字不在该递增数组中，请输出这个数字。

第一行输入n（1<=n<=10000）,表示数组的长度。第二行输入这个数组，数组元素为整型，范围为[0,n]。

示例：

输入：

3

0 1 3

输出：

2*/

bool num[10001] = { false };

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		num[x] = true;
	}
	for (int i = 0; i <= n; i++) {
		if (num[i] == false) {
			cout << i << endl;
			return 0;
		}
	}
	return 0;
}