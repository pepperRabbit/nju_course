#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
using namespace std;

/*
题目：数据结构

题目描述：

有N张编号为1~n的牌，按顺序从1~n排成一列。现在有四种操作，分别如下：
1 X Y  将编号为X的牌插在编号为Y的牌的左边
2 X Y  将编号为X的牌插在编号为Y的牌的右边
3 X Y  将编号为X的牌和编号为Y的牌交换位置
4      将下标为i的牌和下标为n-i+1的牌交换位置,i从1取到n/2。（下标就是牌所在的位置）
在M次操作之后，求下标为奇数的牌的编号之和。
输入：

有多组数据
每组数据第一行n和m， n,m<=100000
输出：

对于每一组数据，
输出一行，"Case x: y"，x表示是第x组，y表示的是第x组数据的奇数下标和为y。


样例输入：

6 4
1 1 4
2 3 5
3 1 6
4
6 3
1 1 4
2 3 5
3 1 6
100000 1
4
4 1
3 3 4
样例输出：

Case 1: 12
Case 2: 9
Case 3: 2500050000
Case 4: 5*/

struct card {
	int val;
	int pos;

	card() {
		val = -1;
		pos = -1;
	}
};

int main() {
	int n, m, time = 1;
	while (scanf("%d %d", &n, &m) != EOF) {
		card* cards = new card[n];
		card* p[100000];
		for (int i = 0; i < n; i++) {
			p[i] = &cards[i];
			cards[i].val = i + 1;
			cards[i].pos = i;
		}
		for (int i = 0; i < m; i++) {
			int sel, x, y;
			cin >> sel;
			if (sel == 4) {
				for (int j = 0; j < n / 2; j++) {
					swap(p[j]->pos, p[n - 1 - j]->pos);
					swap(p[j], p[n - 1 - j]);
				}
			}
			else {
				cin >> x >> y;
				int x_pos = cards[x - 1].pos, y_pos = cards[y - 1].pos;
				card* tmp = p[x_pos];
				switch (sel) {
				case 1:
					if (x_pos < y_pos) {
						tmp->pos = y_pos - 1;
						for (int i = x_pos + 1; i < y_pos; i++) {
							p[i - 1] = p[i];
							p[i - 1]->pos--;
						}
						p[y_pos - 1] = tmp;
					}
					else if (x_pos > y_pos) {
						tmp->pos = y_pos;
						for (int i = x_pos - 1; i >= y_pos; i--) {
							p[i + 1] = p[i];
							p[i + 1]->pos++;
						}
						p[y_pos] = tmp;
					}
					break;
				case 2:
					if (x_pos < y_pos) {
						tmp->pos = y_pos;
						for (int i = x_pos; i < y_pos; i++) {
							p[i] = p[i + 1];
							p[i]->pos--;
						}
						p[y_pos] = tmp;
					}
					else if (x_pos > y_pos) {
						tmp->pos = y_pos + 1;
						for (int i = x_pos; i > y_pos + 1; i--) {
							p[i] = p[i - 1];
							p[i]->pos++;
						}
						p[y_pos + 1] = tmp;
					}
					break;
				case 3:
					swap(p[x_pos], p[y_pos]);
					swap(cards[x - 1].pos, cards[y - 1].pos);
;					break;
				}
			}
		}
		long long res = 0;
		for (int i = 0; i < n; i += 2) {
			res += p[i]->val;
		}
		printf("Case %d: %lld\n", time, res);
		time++;
	}
	return 0;
}