#include <iostream>
using namespace std;

/*
题目：骑士斩龙

题目描述：

你的王国里有一条有n个头的恶龙，你希望雇一些骑士来把它杀死（即砍掉所有的头）。村里有m个骑士可以雇佣，一个能力值为x的骑士可以砍掉恶龙一个直径不超过x的头，且需要支付x个金币。如何雇佣骑士才能砍掉恶龙所有的头，且需要支付的金币最少？注意，一个骑士只能砍一个头（且不能被雇佣两次）。输出最少的花费，如果无解，输出“Loowater is doomed!".

输入：

输入的内容包含多个测试用例，最后一个输入是"0 0"，也就是说当输入"0 0"时程序结束。每个测试用例的第一行包含两个1到20000之间的整数，表示龙的头数n，以及王国中骑士的数量m。
接下来的n行中，每行都包含一个整数，并给出龙头的直径，单位是厘米。
接下来的m行中，每行都包含一个整数，并指定卢瓦特骑士的高度，也是以厘米为单位。
输出：

对于每个测试案例，在一行内输出国王击杀巨龙所需的最低金币数。如果骑士们不可能杀死龙，则输出一行 "Loowater is doomed!"。
输入样例：

2 3
5
4
7
8
4
2 1
5
5
10
0 0
输出样例：

11
Loowater is doomed!*/

int get_pivot(int i, int j, int n[]) {
	int pivot = n[i];
	while (i < j) {
		while (i < j && n[j] >= pivot) {
			j--;
		}
		n[i] = n[j];
		while (i < j && n[i] < pivot) {
			i++;
		}
		n[j] = n[i];
	}
	n[i] = pivot;
	return i;
}

void quick_sort(int left, int right, int n[]) {
	if (left < right) {
		int pivot = get_pivot(left, right, n);
		quick_sort(left, pivot - 1, n);
		quick_sort(pivot + 1, right, n);
	}
}

int main() {
	int n, m;
	while (true) {
		cin >> n >> m;
		if (!n && !m) break;
		int* dragons = (int*)malloc(sizeof(int) * n);
		int* knights = (int*)malloc(sizeof(int) * m);
		for (int i = 0; i < n; i++) {
			cin >> dragons[i];
		}
		for (int i = 0; i < m; i++) {
			cin >> knights[i];
		}
		quick_sort(0, n - 1, dragons);
		quick_sort(0, m - 1, knights);
		int res = 0, d = 0, k = 0;
		while (d < n) {
			if (k == m) break;
			while (k < m) {
				if (knights[k] >= dragons[d]) {
					res += knights[k];
					k++;
					d++;
					break;
				}
				k++;
			}
			if (k == m && d < n) {
				cout << "Loowater is doomed!" << endl;
			}
		}
		if (d == n) cout << res << endl;
	}
	return 0;
}