#include <iostream>
using namespace std;

/*��Ŀ��n�Ľ׳˺��������

��Ŀ������

����һ������n������n!���β���������������1<=n<=100000000��

ʾ�� 1:

����: 3

���: 0

����: 3! = 6, β����û���㡣

 

ʾ�� 2:

����: 5

���: 1

����: 5! = 120, β������ 1 ����.*/

int count5(int n) {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		int j = i;
		while (j % 5 == 0) {
			cnt++;
			j /= 5;
		}
	}
	return cnt;
}

int main() {
	int n, cnt = 0;
	cin >> n;
	cout << count5(n) << endl;
	return 0;
}