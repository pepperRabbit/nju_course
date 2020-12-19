#include <iostream>
#include <string.h>
using namespace std;

/*
题目：从入门到精通

题目描述：

描述：

小明有很多字符串（只包含英文字母），但是他没法快速找出，现在他有一项任务，会有人不停的询问他某个字符串是否存在，如果存在小明要回答Yes，同时给出有关该字符串的三个值：①所有字符全部转换为小写字母的字符串；②所有字符全部转换为大写字母的字符串；③所有字符的ASCII码之和。如果不存在，小明要回答No。

输入：

首先输入一个整数N(1<=N<=1000)，表示字符串的数量。接着输入N个字符串，每个字符串长度不超过1000。然后输入一个Q（1<=Q<=1000），表示查询的次数。最后输入Q个查询，每个查询输入一个字符串。

输出：

对于每个查询，输出Yes或者No。如果输出Yes，后面要跟三行字符串。具体格式看示例

示例：

输入：

1

htHt

2

hqhq

htHt

输出：

No

Yes

htht

HTHT

408



备注：请写一个程序，先对所有字符串进行排序，再使用二分查找字符串是否存在。*/

int qsort(char* s[], int low, int high) {
	char* pivot = new char[1001];
	strcpy(pivot, s[low]);
	while (low < high) {
		while (high > low && strcmp(s[high], pivot) > -1) {
			high--;
		}
		if (high > low) s[low] = s[high];
		while (high > low && strcmp(s[low], pivot) < 0) {
			low++;
		}
		if (high > low) s[high] = s[low];
	}
	s[low] = pivot;
	return low;
}

void quick_sort(char* s[], int low, int high) {
	if (low < high) {
		int pivot = qsort(s, low, high);
		quick_sort(s, low, pivot - 1);
		quick_sort(s, pivot + 1, high);
	}
}

bool b_search(char* str[], char* s, int low, int high) {
	while (low <= high) {
		int mid = (low + high)/2;
		if (strcmp(s, str[mid]) == 0) return true;
		else if (strcmp(s, str[mid]) < 0) high = mid - 1;
		else low = mid + 1;
	}
	return false;
}

void to_low(char* s) {
	int len = strlen(s);
	for (int i = 0; i < len; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 0x20;
	}
}

void to_up(char* s) {
	int len = strlen(s);
	for (int i = 0; i < len; i++) {
		if (s[i] >= 'a' && s[i] <= 'z') s[i] -= 0x20;
	}
}

int main() {
	char* strs[1001];
	int n, q;
	cin >> n;
	for (int i = 0; i < n; i++) {
		char* s = new char[1001];
		cin >> s;
		strs[i] = s;
	}
	quick_sort(strs, 0, n - 1);
	cin >> q;
	for (int i = 0; i < q; i++) {
		char s[1001];
		cin >> s;
		if (b_search(strs, s, 0, n - 1)) {
			int res = 0;
			int len = strlen(s);
			for (int i = 0; i < len; i++) {
				res += s[i];
			}
			cout << "Yes" << endl;
			//cout << _strlwr(s) << endl;
			//cout << _strupr(s) << endl;
			to_low(s);
			cout << s << endl;
			to_up(s);
			cout << s << endl;
			cout << res << endl;
		}
		else {
			cout << "No" << endl;
		}
	}
	return 0;
}