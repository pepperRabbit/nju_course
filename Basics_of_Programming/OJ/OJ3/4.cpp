#include <iostream>
using namespace std;

/*题目：九九乘法表

题目描述：写一个程序，输出九九乘法表。 本题无输入，直接输出九九乘法表。 输出格式如下。
1*1=1 
2*1=2 2*2=4 
3*1=3 3*2=6 3*3=9 
.....
...
... 
9*1=9 9*2=18..... 9*9=81*/

int main() {
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j <= i; j++) {
			cout << i << "*" << j << "=" << i * j;
			if (j != i) cout << " ";
		}
		cout << endl;
	}
	return 0;
}