#include <iostream>
#include <cmath>
using namespace std;

/*��Ŀ���������

��Ŀ������

��дһ�����򣬼���һԪ���η���ax^2+bx+c=0�Ľ��������������ո�ʽ��ӡ����Ļ�ϣ����������λС����

 

���룺a,b,c ��Ϊ���� ��cin >> a >> b >> c;����֤a������0��

�����

��������������ͬ��ʵ���⣬����������������ֵС�Ľ��ڵ�һ���������

x1=3.00

x2=4.00

 

������ֻ��һ��ʵ���⣬�������

x1=x2=2.00

�������޽⣬�������

no results

��ʾ1��������λС���ķ���������

#include <iomanip>

����

double a = 3.14159;

cout << fixed << setprecision(2) << a << endl;

����

��ʾ2��cmathͷ�ļ��е�sqrt()�������Զ�����/��������ֵ���п���������*/

int main() {
	double a, b, c;
	cin >> a >> b >> c;
	double test = b * b - 4 * a * c;
	if (test == 0) {
		double res = -b / (2 * a);
		printf("x1=x2=%.2lf", res);
	}
	else if (test < 0) cout << "no results";
	else {
		double x1 = (-b - sqrt(test)) / (2 * a);
		double x2 = (-b + sqrt(test)) / (2 * a);
		printf("x1=%.2lf\nx2=%.2lf\n", x1, x2);
	}
	return 0;
}
