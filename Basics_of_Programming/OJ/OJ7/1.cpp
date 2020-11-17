#include <iostream>
#include <vector>
using namespace std;

/*
* leetcode 467
��Ŀ�������ַ�����Ψһ�����ַ���

��Ŀ������

���ַ��� s �����ǡ�abcdefghijklmnopqrstuvwxyz�������޻����ַ��������� s �������������ģ�"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".

��������������һ���ַ��� p ������Ҫ�����ҳ� s ���ж��ٸ�Ψһ�� p �ķǿ��Ӵ��������ǵ�����������ַ��� p ������Ҫ����ַ��� s �� p �Ĳ�ͬ�ķǿ��Ӵ�����Ŀ��

ע��: p ����Сд��Ӣ����ĸ��ɣ�p �Ĵ�С���ܳ��� 10000��

ʾ�� 1:

����: a ���: 1 ����: �ַ��� S ��ֻ��һ��"a"���ַ���

ʾ�� 2:

����: cac ���: 2 ����: �ַ��� S �е��ַ�����cac��ֻ�������Ӵ���a������c����.

ʾ�� 3:

����: zab ���: 6 ����: ���ַ��� S ���������Ӵ���z������a������b������za������ab������zab����.*/

int solve(string p) {
	int len = 1, res = 0;
	vector<int> cnt(26, 0);
	for (int i = 0; i < p.length(); i++) {
		if (i > 0 && (p[i] - p[i - 1] == 1 || p[i - 1] - p[i] == 25)) {
			len++;
		}
		else len = 1;
		cnt[p[i] - 'a'] = len > cnt[p[i] - 'a'] ? len : cnt[p[i] - 'a'];
	}
	for (int i = 0; i < 26; i++) {
		res += cnt[i];
	}
	return res;
}

int main() {
	string s;
	cin >> s;
	cout << solve(s) << endl;
	return 0;
}