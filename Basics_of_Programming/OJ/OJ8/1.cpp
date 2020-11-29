#include <iostream>
#include <math.h>
#include <sstream>
using namespace std;

/*
题目：01

题目描述：

描述：
输入十进制数n，输出1-n的自然数中各数位只包含0和1的数的个数（即形式是二进制数的个数）。

输入：
n(1?≤?n?≤?10^20).

输出：
输出1-n的自然数中各数位只包含0和1的数的个数

样例1：
输入：

20

输出：

3

样例2：
输入：

99

输出：

3

样例3：
输入：

101

输出：

5*/

/*void binary(unsigned long long m, unsigned long long n,int &count) {
	if (m > n) return;
	else count++;
	cout << m << endl;
	binary(m * 10, n, count);
	binary(m * 10 + 1, n, count);
}

int main() {
	string s;
	cin >> s;
	int len = s.length(), ans = 0;
	if (s[0] != '1') ans = (int)pow(2, len) - 1;
	else {
		ans = (int)pow(2, len - 1) - 1;
		stringstream toull;
		s = s.substr(1);
		toull << s;
		unsigned long long t = 0, i = 0;
		toull >> t;
		int count = 1;
		binary(1, t, count);
		ans += count;
	}
	cout << ans << endl;
	return 0;
}*/

int compare(string a, string b) {
	int len1 = a.length(), len2 = b.length();
	if (len1 > len2) return 1;
	else if (len1 < len2) return 0;
	for (int i = 0; i < len1; i++) {
		if (a[i] > b[i]) return 1;
		else if (a[i] < b[i]) return 0;
	}
	return 0;
}

void solve(string original, string new_s, int& count) {
	if (compare(new_s, original)) return;
	count++;
	string n1 = new_s, n2 = new_s;
	n1 = n1.append("0"), n2 = n2.append("1");
	solve(original, n1, count);
	solve(original, n2, count);
}

int main() {
	string s;
	cin >> s;
	int count = 0;
	solve(s, "1", count);
	cout << count << endl;
	return 0;
}
