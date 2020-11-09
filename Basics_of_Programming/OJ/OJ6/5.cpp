#include <iostream>
#include <string>
using namespace std;

/*题目：A+B

题目描述：

输入A+B。

输出A+B=C。

注意：A、B、C都是非负整数。

示例：

输入：

1+1

输出：

1+1=2

 

输入：

1111111111111111111111111111111111+111111111111111111111111111111111111111

输出：

1111111111111111111111111111111111+111111111111111111111111111111111111111=111112222222222222222222222222222222222*/

int main() {
	string s, a, b, ret;
	cin >> s;
	bool flag = false;
	int pos = s.find('+');
	a = s.substr(0, pos);
	b = s.substr(pos + 1);
	if (a.length() != b.length()) {
		if (a.length() < b.length()) swap(a, b);
		int len = a.length() - b.length();
		for (int i = 0; i < len; i++) {
			string temp = "0";
			b = temp.append(b);
		}
	}
	for (int i = 0; i < b.length(); i++) {
		int res = 0;
		if (flag) res = 1;
		res += b[b.length() - 1 - i] + a[a.length() - 1 - i] - 2 * 0x30;
		if (res >= 10) {
			flag = true;
			res -= 10;
		}
		else flag = false;
		string r = to_string(res);
		ret = r.append(ret);
	}
	if (flag) {
		string temp = "1";
		ret = temp.append(ret);
	}
	cout << s << "=" << ret;
	return 0;
}