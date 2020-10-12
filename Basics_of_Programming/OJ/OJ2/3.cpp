#include <iostream>
using namespace std;

/*题目：Nintendo Switch

题目描述：

编写一个程序，输入一个0到9的正整数，输出其对应的汉语拼音（小写）。

注：本题只能使用switch case语句，不能使用if else语句。*/

int main() {
	int a;
	cin >> a;
	switch (a) {
	case 1: cout << "yi" << endl; break;
	case 2: cout << "er" << endl; break;
	case 3: cout << "san" << endl; break;
	case 4: cout << "si" << endl; break;
	case 5: cout << "wu" << endl; break;
	case 6: cout << "liu" << endl; break;
	case 7: cout << "qi" << endl; break;
	case 8: cout << "ba" << endl; break;
	case 9: cout << "jiu" << endl; break;
	case 0: cout << "ling" << endl; break;
	}
	return 0;
}