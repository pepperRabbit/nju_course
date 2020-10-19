#include <iostream>
#include <cstdio>
using namespace std;

/*题目：模拟测验题

题目描述：

每次考完试，司雨妍同学的班主任总喜欢连续询问若干个同学的成绩，然后说：“司雨妍，他们几位的平均成绩是多少？” 司雨妍同学总能迅速回应，响亮报出 “XX.XX分”。请你写一个C/C++程序来简单模拟这个过程。

输入格式 ： 第一个行输入一个整数n (0 < n <= 50)，代表学生的数量； 第二行输入 n 个正整数$a{i}$，代表 n 个学生的考试成绩 (0 < $a{i}$<= 100)。

输出格式 ： 成绩的平均值，一个 double 类型的数，保留小数点后两位小数。*/

int main() {
	int n;
	double res=0;
	cin >> n;
	double score;
	for (int i = 0; i < n; i++) {
		cin >> score;
		res += score;
	}
	printf("%.2lf", res / n);
	return 0;
}