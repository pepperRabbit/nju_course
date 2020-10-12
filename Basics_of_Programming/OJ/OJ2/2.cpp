#include <iostream>
#include <cmath>
using namespace std;

/*题目：方程求解

题目描述：

编写一个程序，计算一元二次方程ax^2+bx+c=0的结果，并将结果按照格式打印在屏幕上，结果保留两位小数。

 

输入：a,b,c 均为整数 （cin >> a >> b >> c;）保证a不等于0。

输出：

若方程有两个不同的实数解，则将两个解分行输出（值小的解在第一行输出）：

x1=3.00

x2=4.00

 

若方程只有一个实数解，则输出：

x1=x2=2.00

若方程无解，则输出：

no results

提示1：保留两位小数的方法举例：

#include <iomanip>

……

double a = 3.14159;

cout << fixed << setprecision(2) << a << endl;

……

提示2：cmath头文件中的sqrt()函数可以对整型/浮点型数值进行开方操作。*/

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
