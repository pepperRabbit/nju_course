#include <iostream>
#include <algorithm>
using namespace std;

/*
题目：黑洞数

题目描述：

我们需要验证命题：任何各位数字不全相同的3位正整数经以下变换后均能变为495，称495为3位整数的黑洞数。

变换步骤：对于任意一个各位数字不全相同的3位正整数，将组成该正整数的3个数字重新组合分别生成一个最大数和一个最小数，用最大数减去最小数得到一个新的3位数；再对新的3位数重复上述操作，最多重复7次。

现在需要你编写一个程序，验证一个数是否为黑洞数。接收键盘输入的一个3位正整数，判断各位数字是否**不全相同**，若不全相同则实施以上变换，输出每步变换后得到的3位整数；若各位数字全相同，输出"NO"。

输入：

一个3位正整数

输出：

输出每步变换后得到的3位整数（一个‘-’隔开）；若不是黑洞数，输出"NO"

样例1:

输入：

486

输出：

486-396-594-495

样例2:

输入：

495

输出：

495

样例3:

输入：

666

输出：

NO*/

bool is_3same(int num) {
	if (num % 10 == (num / 10) % 10 && num % 10 == num / 100) return true;
	return false;
}

int get_pivot(int n[], int i, int j) {
	int pivot = n[i];
	while (i < j) {
		while (i < j && n[j] >= pivot) {
			j--;
		}
		if (i < j) n[i] = n[j];
		while (i < j && n[i] < pivot) {
			i++;
		}
		if (i < j) n[j] = n[i];
	}
	n[i] = pivot;
	return i;
}

void quick_sort(int n[], int low, int high) {
	if (low < high) {
		int pivot = get_pivot(n, low, high);
		quick_sort(n, low, pivot - 1);
		quick_sort(n, pivot + 1, high);
	}
}

void solve(int num) {
	if (is_3same(num)) {
		cout << "NO" << endl;
		return;
	}
	int n[3], i = 0;
	cout << num;
	while (i < 7 && num != 495) {
		n[0] = num % 10, n[1] = (num / 10) % 10, n[2] = num / 100;
		quick_sort(n, 0, 2);
		int small = n[0] * 100 + n[1] * 10 + n[2], big = n[2] * 100 + n[1] * 10 + n[0];
		num = big - small;
		cout << "-" << num;
		i++;
	}
}

int main() {
	int n;
	cin >> n;
	solve(n);
	return 0;
}