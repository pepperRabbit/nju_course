#include <iostream>
#include <algorithm>
using namespace std;

/*
题目：A*B

题目描述：

输入A*B。

输出A*B=C。

注意：A、B、C都是非负整数。A和B的十进制长度不超过5000。

示例：

输入：

1*1

输出：

1*1=1



输入：

1111111111111111111111111111111111*111111111111111111111111111111111111111

输出：

1111111111111111111111111111111111*111111111111111111111111111111111111111=123456790123456790123456790123456777777654320987654320987654320987654321*/

int res[10001] = { 0 };

int main() {
	string s;
	string a, b;
	cin >> s;
	int pos = s.find('*');
	a = s.substr(0, pos);
	b = s.substr(pos + 1);
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int len_a = a.length();
	int len_b = b.length();
	int len = len_a + len_b;
	for (int i = 0; i < len_b; i++) {
		for (int j = 0; j < len_a; j++) {
			res[i + j] += (b[i] - '0') * (a[j] - '0');
		}
	}
	bool flag = false;
	for (int i = 0; i < len; i++) {
		res[i + 1] += res[i] / 10;
		res[i] %= 10;
	}
	cout << s << "=";
	for (int i = len; i >= 0; i--) {
		if (flag) {
			cout << res[i];
		}
		else if (res[i] != 0) {
			cout << res[i];
			flag = true;
		}
	}
	if (!flag) cout << 0;
	return 0;
}