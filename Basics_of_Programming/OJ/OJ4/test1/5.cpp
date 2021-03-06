#include <iostream>
using namespace std;

/*题目：Problem 2

题目描述：

W同学十分喜欢吃串串，但是每次他只在这三样东西中进行选择：3元一串的金针菇，5元一串的鹌鹑蛋，还有7元一串的基围虾。现在假设W同学吃串花了n元钱，请你计算他的菜单中可能点了多少串金针菇，多少串鹌鹑蛋，多少串基围虾。

输入
输入：1行，一个数n，表示一共花费了n元(0<=n<=1000)

输出
输出：1行，如果不能得出有效的组合方案，输出-1；否则，分别输出金针菇、鹌鹑蛋、基围虾的串数，输出结果为最小字典序的那一种方案。

最小字典序解释，如果存在多种结果为i,j,k的方案可以输出，优先选择输出i最小的，如果有多的相同i的方案，在其中优先选择j最小的输出；如果依旧有多的相同j的方案，在剩余的方案中选出k最小的进行输出。
注意：

请不要有多余的输入或输出（例如提示、调试信息）

提交时记得去除程序末尾为暂停程序而临时使用的输入语句

cin.get();

getchar();

system("pause");

...

如果用到了scanf_s(...)这类vs特有的_s函数，提交时需还原为标准函数

如何避免_s函数？参考群文件。

样例输入1
67
样例输出1
0 5 6
样例输入2
4
样例输出2
-1*/

int main() {
	int x;
	cin >> x;
	for (int i = 0; i <= x / 3; i++) {
		for (int j = 0; j <= x / 5; j++) {
			for (int k = 0; k <= x / 7; k++) {
				if (i * 3 + j * 5 + k * 7 == x) {
					cout << i << " " << j << " " << k << " " << endl;
					return 0;
				}
				else if (i * 3 + j * 5 + k * 7 > x) break;
			}
		}
	}
	cout << -1 << endl;
	return 0;
}