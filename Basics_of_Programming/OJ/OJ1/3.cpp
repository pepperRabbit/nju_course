#include <iostream>
#include <math.h>
using namespace std;

/*��Ŀ���ж�������

��Ŀ������

����������������ʾ�����ߵĳ��ȣ��ж����ܷ񹹳�һ�������Σ����ܣ����Yes�����������No��

ÿ���߳��ȷ�Χ��int���ڣ����κ����㲻����������*/ 

int main() {
	int a, b, c;
	cin >> a >> b >> c;
	if (a + b > c && fabs(a - b) < c) cout << "Yes" << endl;
	else cout << "No" << endl;
	return 0;
}
