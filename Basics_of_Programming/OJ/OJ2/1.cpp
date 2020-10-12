#include <iostream>
using namespace std;

/*题目：闰年判断

题目描述：

编写一个程序，判断某年是不是闰年。

输入：输入一个整数，表示年份。

输出：如果是闰年，输出“YES”，如果不是，输出“NO”。

闰年：1、公历年份是4的倍数的，且不是100的倍数。2、公历年份是400的倍数。满足其中一个条件就是闰年。*/

int main() {
	int year;
	cin >> year;
	if (year % 4 == 0 && year % 100 || year % 400 == 0) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}