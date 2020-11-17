#include <iostream>
using namespace std;

/*题目：同构字符串

题目描述：

输入两个字符串 s 和 t，判断它们是否是同构的。

如果 s 中的字符可以被替换得到 t ，那么这两个字符串是同构的。

所有出现的字符都必须用另一个字符替换，同时保留字符的顺序。两个字符不能映射到同一个字符上，但字符可以映射自己本身。

示例 1:

输入: egg add 输出: true

示例 2:

输入: foo bar 输出: false

示例 3:

输入: paper title 输出: true

说明: 你可以假设 s 和 t 具有相同的长度。
*/

int main() {
	int count_s[26] = { 0 };
	int count_t[26] = { 0 };
	string s, t;
	cin >> s >> t;
	for (int i = 0; i < s.length(); i++) {
		count_s[s[i] - 'a']++;
		count_t[t[i] - 'a']++;
	}
	for (int i = 0; i < 26; i++) {
		if (count_s[i] > 0) {
			for (int j = 0; j < 26; j++) {
				if (count_s[i]==count_t[j]) {
					count_t[j] = 0;
					break;
				}
				else if (j == 25) {
					cout << "false" << endl;
					return 0;
				}
			}
		}
	}
	cout << "true" << endl;
	return 0;
}