#include <iostream>
using namespace std;

/*��Ŀ��Problem 1

��Ŀ������

Cͬѧ����ѧ��ʦ���콲��һ���µ�֪ʶ�㣺���Լ�����������˺ܶ�κ���ҵ��������֮���������æ���һ�´𰸶Բ��ԣ���Ϊ��ҵʵ��̫���ˣ�����дһ�������������жϡ�     

�����ʽ��

��һ������������ m n ��0 < m,n <= 1 000 000 000��

�ڶ���һ�������� d (��ʾǰ�����������������Լ��)

�����ʽ��

һ������������ 0 ���� 1��0 ��ʾ �����ԡ�, 1 ��ʾ ���ԡ���

ע�⣺

- �벻Ҫ�ж��������������������ʾ��������Ϣ��
- �ύʱ�ǵ�ȥ������ĩβ**Ϊ��ͣ�������ʱʹ�õ�**�������
  - cin.get();
  - getchar();
  - system("pause");
  - ...
- ����õ���`scanf_s(...)`����vs���е�`_s`�������ύʱ�軹ԭΪ��׼����
  - ��α���`_s`�������ο�Ⱥ�ļ���

����
����1
8 6

2

���1
 1

����2
12 6

3

���2
0*/

int gcd(int a, int b) {
	if (a % b == 0) return b;
	gcd(b, a % b);
}

int main() {
	int a, b, x;
	cin >> a >> b >> x;
	if (x == gcd(a, b)) cout << 1 << endl;
	else cout << 0 << endl;
	return 0;
}