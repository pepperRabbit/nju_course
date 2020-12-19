#include <iostream>
#include <algorithm>
using namespace std;

/*
��Ŀ���ڶ���

��Ŀ������

������Ҫ��֤���⣺�κθ�λ���ֲ�ȫ��ͬ��3λ�����������±任����ܱ�Ϊ495����495Ϊ3λ�����ĺڶ�����

�任���裺��������һ����λ���ֲ�ȫ��ͬ��3λ������������ɸ���������3������������Ϸֱ�����һ���������һ����С�������������ȥ��С���õ�һ���µ�3λ�����ٶ��µ�3λ���ظ���������������ظ�7�Ρ�

������Ҫ���дһ��������֤һ�����Ƿ�Ϊ�ڶ��������ռ��������һ��3λ���������жϸ�λ�����Ƿ�**��ȫ��ͬ**������ȫ��ͬ��ʵʩ���ϱ任�����ÿ���任��õ���3λ����������λ����ȫ��ͬ�����"NO"��

���룺

һ��3λ������

�����

���ÿ���任��õ���3λ������һ����-���������������Ǻڶ��������"NO"

����1:

���룺

486

�����

486-396-594-495

����2:

���룺

495

�����

495

����3:

���룺

666

�����

NO*/

bool is_3same(int num) {
	if (num % 10 == (num / 10) % 10 && num % 10 == num / 100) return true;
	return false;
}

int get_pivot(int n[], int i, int j) {
	int pivot = n[i];
	while (i < j) {
		while (i < j && n[j] >= pivot) {
			j--;
		}
		if (i < j) n[i] = n[j];
		while (i < j && n[i] < pivot) {
			i++;
		}
		if (i < j) n[j] = n[i];
	}
	n[i] = pivot;
	return i;
}

void quick_sort(int n[], int low, int high) {
	if (low < high) {
		int pivot = get_pivot(n, low, high);
		quick_sort(n, low, pivot - 1);
		quick_sort(n, pivot + 1, high);
	}
}

void solve(int num) {
	if (is_3same(num)) {
		cout << "NO" << endl;
		return;
	}
	int n[3], i = 0;
	cout << num;
	while (i < 7 && num != 495) {
		n[0] = num % 10, n[1] = (num / 10) % 10, n[2] = num / 100;
		quick_sort(n, 0, 2);
		int small = n[0] * 100 + n[1] * 10 + n[2], big = n[2] * 100 + n[1] * 10 + n[0];
		num = big - small;
		cout << "-" << num;
		i++;
	}
}

int main() {
	int n;
	cin >> n;
	solve(n);
	return 0;
}