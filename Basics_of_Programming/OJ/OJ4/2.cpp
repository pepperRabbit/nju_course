#include <iostream>
#include <cmath>
using namespace std;

/*��Ŀ������

��Ŀ��������дһ�������жϸ��������Ƿ�Ϊ������������ָֻ����������2,3,5������������Ϊ�������ӡtrue�������ӡfalse��

���룺����һ������n(1<=n<=10000000)

��������true����false��true��ʾ�ǳ�����false��ʾ���ǳ�����

ʾ����

���룺6 �����true

���룺14 �����false*/

void judge(int x) {
	if (x == 1) {
		cout << "false" << endl;
		return;
	}
	while (x % 2 == 0) {
		x /= 2;
	}
	while (x % 3 == 0) {
		x /= 3;
	}
	while (x % 5 == 0) {
		x /= 5;
	}
	if (x == 1) cout << "true" << endl;
	else cout << "false" << endl;
}

int main() {
	int x;
	cin >> x;
	judge(x);
	return 0;
}