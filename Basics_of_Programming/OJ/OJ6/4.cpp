#include <iostream>
#include <map>
using namespace std;

/*题目：找出序列中出现次数最多的那个数

题目描述：

输入n个整数(1=<n<=1000)，组成一个序列，你需要找出其中出现次数最多的那个整数。我们保证输入的整数序列中出现次数最多的那个数至少出现?n/2?+1次。

输入共两行，第一行n表示这个序列有多少个整数，第二行代表这个数字序列。

你需要输出序列中出现次数最多的那个数。

注：?n/2?表示对n除以2的结果向下取整，例如?4/2?=2，?5/2?=2，?6/2?=3。

例：

输入：

3

3 2 3

输出：

3*/

int main() {
	map<int, int> res;
	int n;
	int max = -1, max_num = -1;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int num;
		std::map<int, int>::iterator it;
		cin >> num;
		it = res.find(num);
		if (it != res.end()) {
			res[num] += 1;
		}
		else {
			res[num] = 1;
		}
		if (res[num] > max) {
			max = res[num];
			max_num = num;
		}
	}
	cout << max_num << endl;
	return 0;
}
