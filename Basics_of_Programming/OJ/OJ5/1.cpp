#include <iostream>
using namespace std;

/*��Ŀ��Сĸţ

��Ŀ������

��һͷСĸţ�� �ӳ�������ĸ���ͷ��ʼÿ����һͷĸţ�� ���˹��ɣ���n���ж���ͷĸţ? ����һ������n��1<=n<=50����

ʾ��1��

���룺1

�����1

 

ʾ��2��

���룺4

�����2*/

int count_cow(int n) {
	if (n <= 0) return 0;
	else if (n > 0 && n < 4) return 1;
	else return count_cow(n - 1) + count_cow(n - 3);
}

int main() {
	int n;
	cin >> n;
	cout << count_cow(n) << endl;
	return 0;
}