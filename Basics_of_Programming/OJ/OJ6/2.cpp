#include <iostream>
#include <math.h>
using namespace std;

/*��Ŀ���ߵ�������λ

��Ŀ������

����һ���޷���32λ����������ߵ��������λ���Ӧ���޷���������

ʾ����

����: 43261596

���: 964176192

����: ����Ķ����ƴ� 00000010100101000001111010011100 ��ʾ�޷������� 43261596����˷��� 964176192��������Ʊ�ʾ��ʽΪ 00111001011110000010100101000000��

���룺4294967293

�����3221225471

���ͣ�����Ķ����ƴ� 11111111111111111111111111111101 ��ʾ�޷������� 4294967293����˷��� 3221225471 ������Ʊ�ʾ��ʽΪ 10111111111111111111111111111111 ��*/

int main() {
	unsigned num, res = 0;
	cin >> num;
	int binary[32] = { 0 };
	int i = 31;
	while (num != 0) {
		binary[i--] = num % 2;
		num /= 2;
	}
	for (int j = 0; j < 32; j++) {
		res += (int)pow((double)2, (double)(j)) * binary[j];
	}
	cout << res << endl;
	return 0;
}