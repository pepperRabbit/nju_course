#include <iostream>
using namespace std;

/*
��Ŀ�����˻�

��Ŀ������

�������һ������Ϊn���������� ��Ҫ�������������ҳ�����������ɵ����˻���Ȼ�����������˻���

��һ������n��3<=n<=1000������ʾ���еĳ��ȡ��ڶ�������������У������е�����Ԫ�ط�Χ[-1000,1000]��

ʾ����

���룺

3

1 2 3

�����

6*/

int main() {
	int n;
	cin >> n;
	long long max1 = 0xffffffffffffffff, max2 = 0xfffffffffffffffe, max3 = 0xfffffffffffffffd;
	long long min1 = 0x7ffffffffffffffe, min2 = 0x7fffffffffffffff;
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		if (num > max1) {
			max3 = max2;
			max2 = max1;
			max1 = num;
		}
		else if (num > max2) {
			max3 = max2;
			max2 = num;
		}
		else if (num > max3) max3 = num;
		if (num < min1) {
			min2 = min1;
			min1 = num;
		}
		else if (num < min2) min2 = num;
	}
	cout << max(max1 * max2 * max3, max1 * min1 * min2) << endl;
	return 0;
}