#include <iostream>
using namespace std;

/*题目：调整序列中的数字0

题目描述：

输入n个整数，组成一个序列，你需要将这个序列中所有的0移动到序列的末尾，同时保持非零元素的相对顺序。

输入共两行，第一行n表示这个序列有多少个整数，第二行代表这个数字序列。

你需要输出调整后的序列。

例：

输入：

5

0 1 0 3 12

输出：

1 3 12 0 0*/

int main() {
	int n;
	cin >> n;
	int i = 0, j = n - 1;
	int* num;
	num = (int*)malloc(sizeof(int) * n);
	for (int k = 0; k < n; k++) {
		int a;
		cin >> a;
		if (a == 0) {
			num[j] = 0;
			j--;
		}
		else {
			num[i] = a;
			i++;
		}
	}
	for (int k = 0; k < n; k++) {
		cout << num[k];
		if (k != n - 1) cout << " ";
	}
	cout << endl;
	free(num);
	return 0;
}