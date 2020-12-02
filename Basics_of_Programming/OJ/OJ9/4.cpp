#include <iostream>
#include <string.h>
using namespace std;

/*
题目：反转字符串中的单词

题目描述：

输入一个英文句子(字符串)，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始
顺序。在字符串中，每个单词由单个空格分隔，并且字符串中不会有任何额外的空格。字符串长度不超
过1000。
样例：
输入：
Let's take online judge contest.
输出：
s'teL ekat enilno egduj .tsetnoc*/

void reverse(char s[], int start, int end) {
	int len = strlen(s);
	if (start < 0 || start >= len || end < 0 || end >= len) {
		cout << "ERROR!!!" << endl;
		return;
	}
	while (start <= end) {
		swap(s[start], s[end]);
		start++;
		end--;
	}
}

void reverse_word(char s[]) {
	int len = strlen(s), start = 0;
	bool in_a_word = false;
	for (int i = 0; i < len; i++) {
		if (s[i] != ' ' && !in_a_word) {
			in_a_word = true;
			start = i;
		}
		else if (s[i] == ' ') {
			in_a_word = false;
			reverse(s, start, i - 1);
			start = i + 1;
		}
	}
	if (s[len - 1] != ' ') reverse(s, start, len - 1);
}
int main() {
	char s[1001];
	int c, i = 0;
	while ((c = getchar()) != EOF) {
		s[i++] = c;
	}
	s[i] = '\0';
	reverse_word(s);
	cout << s << endl;
	return 0;
}