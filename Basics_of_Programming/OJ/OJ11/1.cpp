#include <iostream>
#include <string.h>
using namespace std;

/*
��Ŀ�������ŵ���ͨ

��Ŀ������

������

С���кܶ��ַ�����ֻ����Ӣ����ĸ����������û�������ҳ�����������һ�����񣬻����˲�ͣ��ѯ����ĳ���ַ����Ƿ���ڣ��������С��Ҫ�ش�Yes��ͬʱ�����йظ��ַ���������ֵ���������ַ�ȫ��ת��ΪСд��ĸ���ַ������������ַ�ȫ��ת��Ϊ��д��ĸ���ַ������������ַ���ASCII��֮�͡���������ڣ�С��Ҫ�ش�No��

���룺

��������һ������N(1<=N<=1000)����ʾ�ַ�������������������N���ַ�����ÿ���ַ������Ȳ�����1000��Ȼ������һ��Q��1<=Q<=1000������ʾ��ѯ�Ĵ������������Q����ѯ��ÿ����ѯ����һ���ַ�����

�����

����ÿ����ѯ�����Yes����No��������Yes������Ҫ�������ַ����������ʽ��ʾ��

ʾ����

���룺

1

htHt

2

hqhq

htHt

�����

No

Yes

htht

HTHT

408



��ע����дһ�������ȶ������ַ�������������ʹ�ö��ֲ����ַ����Ƿ���ڡ�*/

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