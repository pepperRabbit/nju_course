#include <iostream>
using namespace std;

/* leetcode 42 
题目：接雨水

题目描述：

给定n个非负整数表示每个宽度为1的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
第一行输入n(0<=n<=3,000)，之后输入n个柱子的高度。




示例：
输入：
12
0 1 0 2 1 0 1 3 2 1 2 1
输出：
6*/

int solve(int height[], int n) {
	int res = 0, left = 0, right = n - 1;
	while (left < right) {
		int smaller = min(height[left], height[right]);
		if (smaller == height[left]) {
			left++;
			while (left < right && height[left] < smaller) {
				res += smaller - height[left];
				left++;
			}
		}
		else {
			right--;
			while (left < right && height[right] < smaller) {
				res += smaller - height[right];
				right--;
			}
		}
	}
	return res;
}

int main() {
	int n, * p;
	cin >> n;
	p = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> *(p + i);
	}
	int res = solve(p, n);
	cout << res << endl;
	return 0;
}
