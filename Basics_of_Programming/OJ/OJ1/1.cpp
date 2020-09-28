#include <iostream>
using namespace std;

/*
题目：华氏温度转换为摄氏温度

题目描述：

编写一个程序，将华氏温度转换为摄氏温度，转换公式为c=5/9*(f-32)。其中，c为摄氏温度，f为华氏温度。打印结果保留整数。

输入一个华氏温度，用小数表示。

输出一个摄氏温度，强制转换为整数输出。*/

int main() {
	double c, f;
	cin >> f;
	c = (f - 32) * 5 / 9;
	int res = (int)c;
	cout << res << endl;
	return 0;
}
