#include <iostream>
using namespace std;

/*��Ŀ��Max Number

��Ŀ������

����3��������������е����ֵ��

ע�����ⲻ����ʹ��STL�Ŀ⺯��max��*/

int main() {
	int a, b, c;
	int max;
	cin >> a >> b >> c;
	if (a > b) max = a;
	else max = b;
	if (c > max) max = c;
	cout << max << endl;
	return 0;
}