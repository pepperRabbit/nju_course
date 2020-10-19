#include <iostream>
#include <cmath>
using namespace std;

/*��Ŀ���������

��Ŀ������дһ���������1~n֮�������ĺ͡�
���룺����һ��������n��1<=n<=500000��
��������һ������������ʾ1~n֮�������ĺ͡�*/

bool is_prime(int x) {
	for (int i = 2; i <= (int)sqrt((double)x); i++) {
		if (x % i == 0) return false;
	}
	return true;
}

int main() {
	int n;
	cin >> n;
	long int res = 0;
	for (int i = 2; i <= n; i++) {
		if (is_prime(i)) res += i;
	}
	cout << res << endl;
	return 0;
}