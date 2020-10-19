#include <iostream>
using namespace std;

/*��Ŀ���׳�2

��Ŀ������дһ��������n�Ľ׳ˣ��������Ľ��ģ1e9+7��
���룺����һ��������n����1<=n<=1000��
��������һ������������ʾģ1e9+7֮��n�Ľ׳ˡ�
������
����10
������Ϊ��10!��%(1e9+7)��Ҳ����3628800��
����100
������Ϊ��100!��%(1e9+7)��Ҳ����437918130��
��ʾ��(a+b)%n == ��a%n + b%n��%n*/

int main() {
	int n;
	cin >> n;
	long long int res = 1;
	const int mod = 1e9 + 7;
	for (int i = 1; i <= n; i++) {
		res = ((res % mod) * (i % mod)) % mod;
	}
	cout << res << endl;
	return 0;
}