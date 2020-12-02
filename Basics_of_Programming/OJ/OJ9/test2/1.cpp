#include <iostream>
#include <cmath>
using namespace std;

/*
��Ŀ��Problem 1 �׺���

��Ŀ������

��Ŀ����
����������n������d(n)Ϊn����������֮�͡���d(a)=b����d(b)=a��a��b����������Ԫ�飨a,b)Ϊ�׺����ԡ�

����d(220)=1+2+4+5+10+11+20+22+44+55+110=284��d(284)=1+2+4+71+142=220������220��284Ϊ��Ϊ�׺�����(220,284)Ϊ�׺����ԡ� ��N���������׺�����(a,b),(1<=a,b<=n)�ĺ�K��

 

����
һ������N��2 �� N �� 10^3��

���
�����һ������K.

��������
1000
�������
504*/

int solve(int x) {
	int res = 0;
	for (int i = 1; i < x / 2 + 1; i++) {
		if (x % i == 0) {
			res += i;
		}
	}
	return res;
}

int main() {
	int n, res = 0;
	cin >> n;
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (solve(i) == j && solve(j) == i) {
				//cout << i << " " << j << endl;
				res = res + i + j;
			}
		}
	}
	cout << res << endl;
	return 0;
}
