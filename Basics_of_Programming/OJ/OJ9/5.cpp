#include <iostream>
using namespace std;
int num[40][40] = { 0 };

/*
��Ŀ���������

��Ŀ������

����һ��������n(0 < n <= 33)����ӡ������ǵ�ǰn�У������n�У���i���������������ǵĵ�i�У�
ͬһ�в�ͬԪ��֮���Կո������


ʾ����
���룺
5
�����
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1*/

void print_pascal(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			if (j > 0 && j < i) {
				num[i][j] = num[i - 1][j - 1] + num[i - 1][j];
			}
			cout << num[i][j];
			if (j != i) cout << " ";
		}
		cout << endl;
	}
}

int main() {
	for (int i = 0; i < 33; i++) {
		num[i][0] = 1;
		num[i][i] = 1;
	}
	int n;
	cin >> n;
	print_pascal(n);
	return 0;
}