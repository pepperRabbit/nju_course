#include <iostream>
using namespace std;

/*��Ŀ����¥��

��Ŀ������

������������¥�ݣ���Ҫn�ײ��ܵ���¥����ÿ�ο�����1��2��̨�ף���һ���ж����ֲ�ͬ�ķ�����������¥������n��һ����������1=<n<=1000��

ʾ����

���룺 2

����� 2

���ͣ� �����ַ�����������¥����1��+1�� || 2�ס�

���룺 3

����� 3

���ͣ� �����ַ�����������¥����1��+1��+1�� || 1��+2�� || 2��+1��*/

/*int solve(int n) {
	if (n < 0) return 0;
	if (n == 0) return 1;
	return solve(n - 1) + solve(n - 2);
}*/

int main() {
	int n;
	cin >> n;
	int cnt[1001] = { 0 };
	cnt[1] = 1;
	cnt[2] = 2;
	if(n <= 2 && n >= 0){
		cout << cnt[n] << endl;
	}
	else {
		for (int i = 3; i <= n; i++) {
			cnt[i] = cnt[i - 1] + cnt[i - 2];
		}
		cout << cnt[n] << endl;
	}
	return 0;
}