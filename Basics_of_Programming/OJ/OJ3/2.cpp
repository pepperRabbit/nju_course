#include <iostream>
using namespace std;

/*��Ŀ���׳�1

��Ŀ������дһ��������n�Ľ׳ˡ�
���룺����һ��������n����1<=n<=10��
��������һ������������ʾn�Ľ׳ˡ�*/

int main() {
	int n;
	cin >> n;
	int res = 1;
	for (int i = 1; i <= n; i++) {
		res *= i;
	}
	cout << res << endl;
	return 0;
}