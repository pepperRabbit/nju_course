#include <iostream>
using namespace std;

/* leetcode 42 
��Ŀ������ˮ

��Ŀ������

����n���Ǹ�������ʾÿ�����Ϊ1�����ӵĸ߶�ͼ�����㰴�����е����ӣ�����֮���ܽӶ�����ˮ��
��һ������n(0<=n<=3,000)��֮������n�����ӵĸ߶ȡ�




ʾ����
���룺
12
0 1 0 2 1 0 1 3 2 1 2 1
�����
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
