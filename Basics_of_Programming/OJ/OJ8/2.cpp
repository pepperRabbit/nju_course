#include <iostream>
using namespace std;

/*
��Ŀ��������쳲�������

��Ŀ������

������
����A,B,N������fib(A^B)%N��fib��ʾ쳲���������������fib(0)=0,fib(1)=1,fib(2)=1,fib(3)=2.....��

���룺
������������A,B,N(0 <= A,B < 2^64��1<=N<=1000)��A��B����ͬʱ����0��

�����
���һ����������ʾfib(A^B)%N��

����1��
���룺

1 1 2

�����

1

����2��
���룺

2 3 1000

�����

21

����3��
���룺

18446744073709551615 18446744073709551615 1000

�����

250*/

unsigned long long fib[2000] = { 0 };

int main() {
	unsigned long long a, b, n, t = 1;
	cin >> a >> b >> n;
	if (n == 1) {
		cout << 0 << endl;
		return 0;
	}
	fib[0] = 1, fib[1] = 1, fib[2] = 2;
	fib[2] %= n;
	int i;
	for (i = 3; fib[i - 1] != 1 || fib[i - 2] != 1; i++) {
		fib[i] = (fib[i - 1] + fib[i - 2]) % n;
	}
	i -= 2;
	a %= i;
	while (b > 0) {
		if (b % 2) {
			b--;
			t = (t * a) % i;
		}
		else {
			b /= 2;
			a = (a * a) % i;
		}
	}
	cout << fib[t - 1] << endl;
	return 0;
}