#include <iostream>
#include <cmath>
using namespace std;

/*��Ŀ��ˮ�ɻ���

��Ŀ��������дһ������������ˮ�ɻ�����ˮ�ɻ�������������λ�������ǵ������ǵĸ�λ���ֵ������ͣ������磺153 = 1^3+5^3+3^3��

���룺��

����������е�ˮ�ɻ�������С�����˳�������һ���ڣ�֮���ÿո�������磺

xxx xxx xxx*/

bool count(int x) {
	int res = 0, i = x;
	while (i != 0) {
		res += (int)pow((i % 10), 3);
		i /= 10;
	}
	if (res == x) return true;
	else return false;
}

int main() {
	for (int i = 100; i < 1000; i++) {
		if (count(i)) cout << i << " ";
	}
	return 0;
}