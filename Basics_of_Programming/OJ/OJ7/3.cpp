#include <iostream>
#include <string.h>
using namespace std;

/*
��Ŀ������

��Ŀ������

����һ����λ��Ϊ0��ʮ����������a��Ȼ���׾���a����ֵ̫С�ˣ�����ֻ��ͨ��������������������λ��һ�����������������a��һĿ�ġ� ���룺 �����ÿո�ָ�������a��k��(1��a��10^18; 0��k��100).

����� �������k�ν�������ͨ��a�ܵõ��������ֵ

��������1��

1890 1

�������1��

8190

��������2��

100 0

�������2��

100

��������3��

1034 2

�������3��

3104

��������4��

8658265816482165 9

�������4��

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