#include <iostream>
using namespace std;

/*��Ŀ�����������е�����0

��Ŀ������

����n�����������һ�����У�����Ҫ��������������е�0�ƶ������е�ĩβ��ͬʱ���ַ���Ԫ�ص����˳��

���빲���У���һ��n��ʾ��������ж��ٸ��������ڶ��д�������������С�

����Ҫ�������������С�

����

���룺

5

0 1 0 3 12

�����

1 3 12 0 0*/

int main() {
	int n;
	cin >> n;
	int i = 0, j = n - 1;
	int* num;
	num = (int*)malloc(sizeof(int) * n);
	for (int k = 0; k < n; k++) {
		int a;
		cin >> a;
		if (a == 0) {
			num[j] = 0;
			j--;
		}
		else {
			num[i] = a;
			i++;
		}
	}
	for (int k = 0; k < n; k++) {
		cout << num[k];
		if (k != n - 1) cout << " ";
	}
	cout << endl;
	free(num);
	return 0;
}