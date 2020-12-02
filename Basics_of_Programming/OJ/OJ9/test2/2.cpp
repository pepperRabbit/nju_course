#include <iostream>
using namespace std;

/*
题目：Problem 2 虚假的字符串

题目描述：

一位同学学到现在，非常希望能用程序处理一段话，但这门课还没有讲到字符串的处理，直接把hello world这样的句子写进代码里是在练死劲，没有什么用，只得伤心地吐槽了一句“讲得真慢”。

这时，另一位同学啪就站起来了，说：“我有一个绝妙的主意！”，掏出笔纸唰唰唰写着什么，很快啊，方案就设计好了：

用数字-1，代表一句话的结束，之后的内容将被忽略掉；
用数字0-9，代表字符0-9；
用数字10，代表空格；
用数字11-36，代表小写字母a-z；
如此下来，使用一个int数组，就可以利用以上规则，将对应的一句话打印出来了！

请你实现函数：

void my_cout_str(int data[]) ：根据以上规则，输出int数组data所代表的一串字符，并在这一串字符后面紧跟着输出一个点"."。
并在main函数中合适的位置调用它，完成功能。

注意事项：

不要改变以上my_cout_str函数的定义，例如增加其他参数。
所有输出均在my_cout_str函数内进行。
如果你的开发环境对数组大小为变量有限制，可直接定义一个较大的数组（输入的数据量上限）来完成功能。
输入描述：

第一行：一个正整数n，代表接下来数据的个数，不超过100。
第二行：n个整数([-1,36])，代表int数组的内容。
输出描述：

第一行：对应的一句话。
Samples:

input:

11
18 15 22 22 25 10 2 0 2 0 -1
output:

hello 2020.
input:

10
24 11 19 32 15 -1 33 34 -1 36
output:

naive.*/

void my_cout_str(int data[],int len) {
	for (int i = 0; i < len; i++) {
		if (data[i] == -1) {
			cout << "." << endl;
			return;
		}
		else if (data[i] >= 0 && data[i] <= 9) {
			cout << data[i];
		}
		else if (data[i] == 10) {
			cout << " ";
		}
		else if (data[i] >= 11 && data[i] <= 36) {
			char c = 'a' + data[i] - 11;
			cout << c;
		}
	}
}

int main() {
	int n, data[101] = { 0 };
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> data[i];
	}
	my_cout_str(data, n);
	return 0;
}
