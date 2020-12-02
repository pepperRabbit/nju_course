#include <iostream>
#include <string.h>
using namespace std;

/*
��Ŀ����ת�ַ����еĵ���

��Ŀ������

����һ��Ӣ�ľ���(�ַ���)������Ҫ��ת�ַ�����ÿ�����ʵ��ַ�˳��ͬʱ�Ա����ո�͵��ʵĳ�ʼ
˳�����ַ����У�ÿ�������ɵ����ո�ָ��������ַ����в������κζ���Ŀո��ַ������Ȳ���
��1000��
������
���룺
Let's take online judge contest.
�����
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