#include <iostream>
using namespace std;

/*
��Ŀ��������ӡ��ά����

��Ŀ������

������
����һ����ά���飬��������������ӡ��Ԫ�ء�

����
��һ�У�������������n, m(0<n, m<=100)�ֱ�����ά���������������

֮������n��m�У������ά�����е�Ԫ�ء�

���
һ�У�Ϊ��ά������Ԫ��������ӡ������У��Կո������

����1��
���룺
3 3

1 2 3

4 5 6

7 8 9

�����
1 2 3 6 9 8 7 4 5

����2��
����
4 5

1 2 3 4 5

6 7 8 9 10

1 2 3 4 5

6 7 8 9 10

�����
1 2 3 4 5 10 5 10 9 8 7 6 1 6 7 8 9 4 3 2*/

int num[101][101] = { 0 };

void print1(int m_left, int m_right, int& n_top, int n_bottom) {
	for (int i = m_left; i <= m_right; i++) {
		cout << num[n_top][i] << " ";
	}
	n_top++;
}

void print2(int m_left, int& m_right, int n_top, int n_bottom) {
	for (int i = n_top; i <= n_bottom; i++) {
		cout << num[i][m_right] << " ";
	}
	m_right--;
}

void print3(int m_left, int m_right, int n_top, int& n_bottom) {
	for (int i = m_right; i >= m_left; i--) {
		cout << num[n_bottom][i] << " ";
	}
	n_bottom--;
}

void print4(int& m_left, int m_right, int n_top, int n_bottom) {
	for (int i = n_bottom; i >= n_top; i--) {
		cout << num[i][m_left] << " ";
	}
	m_left++;
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> num[i][j];
		}
	}
	int m_left = 0, m_right = m - 1, n_top = 0, n_bottom = n - 1;
	while (m_left <= m_right && n_top <= n_bottom) {
		print1(m_left, m_right, n_top, n_bottom);
		print2(m_left, m_right, n_top, n_bottom);
		print3(m_left, m_right, n_top, n_bottom);
		print4(m_left, m_right, n_top, n_bottom);
	}
	return 0;
}