﻿#include <iostream>
#include <map>
using namespace std;

/*��Ŀ���ҳ������г��ִ��������Ǹ���

��Ŀ������

����n������(1=<n<=1000)�����һ�����У�����Ҫ�ҳ����г��ִ��������Ǹ����������Ǳ�֤��������������г��ִ��������Ǹ������ٳ���?n/2?+1�Ρ�

���빲���У���һ��n��ʾ��������ж��ٸ��������ڶ��д�������������С�

����Ҫ��������г��ִ��������Ǹ�����

ע��?n/2?��ʾ��n����2�Ľ������ȡ��������?4/2?=2��?5/2?=2��?6/2?=3��

����

���룺

3

3 2 3

�����

3*/

int main() {
	map<int, int> res;
	int n;
	int max = -1, max_num = -1;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int num;
		std::map<int, int>::iterator it;
		cin >> num;
		it = res.find(num);
		if (it != res.end()) {
			res[num] += 1;
		}
		else {
			res[num] = 1;
		}
		if (res[num] > max) {
			max = res[num];
			max_num = num;
		}
	}
	cout << max_num << endl;
	return 0;
}
