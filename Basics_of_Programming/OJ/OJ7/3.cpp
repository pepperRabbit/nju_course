#include <iostream>
#include <string.h>
using namespace std;

/*
题目：交换

题目描述：

甲有一个首位不为0的十进制正整数a。然而甲觉得a的数值太小了，但甲只能通过交换正整数的相邻两位这一个操作，来达成增大a这一目的。 输入： 两个用空格分隔的数字a和k。(1≤a≤10^18; 0≤k≤100).

输出： 经过最多k次交换操作通过a能得到的最大数值

样例输入1：

1890 1

样例输出1：

8190

样例输入2：

100 0

样例输出2：

100

样例输入3：

1034 2

样例输出3：

3104

样例输入4：

8658265816482165 9

样例输出4：

8886652516482165*/

char a[20];

void solve(int start, int k, int len) {
	//cout << "start:" << start << ",k:" << k << ",len:" << len << endl;
	if (k == 0 || start >= len) return;
	int limit = len - 1, maxnum = a[start], maxi = start;
	if (start + k < len) limit = start + k;
	//cout << maxnum << endl;
	//cout << start + 1 << " " << limit << endl;
	for (int i = start + 1; i <= limit; i++) {
		//cout << a[i] << " " << maxnum << " " << (a[i] > maxnum) << endl;
		if (a[i] > maxnum) {
			maxnum = a[i];
			maxi = i;
		}
	}
	//cout << maxi << endl;
	if (maxi != start) {
		for (int i = maxi; i > start; i--) {
			swap(a[i], a[i - 1]);
		}
		k -= (maxi - start);
	}
	//cout << k << endl;
	solve(start + 1, k, len);
}

int main() {
	int k;
	cin >> a >> k;
	int len = strlen(a);
	solve(0, k, len);
	cout << a << endl;
	return 0;
}