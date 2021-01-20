#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
using namespace std;

/*
��Ŀ�����ݽṹ

��Ŀ������

��N�ű��Ϊ1~n���ƣ���˳���1~n�ų�һ�С����������ֲ������ֱ����£�
1 X Y  �����ΪX���Ʋ��ڱ��ΪY���Ƶ����
2 X Y  �����ΪX���Ʋ��ڱ��ΪY���Ƶ��ұ�
3 X Y  �����ΪX���ƺͱ��ΪY���ƽ���λ��
4      ���±�Ϊi���ƺ��±�Ϊn-i+1���ƽ���λ��,i��1ȡ��n/2�����±���������ڵ�λ�ã�
��M�β���֮�����±�Ϊ�������Ƶı��֮�͡�
���룺

�ж�������
ÿ�����ݵ�һ��n��m�� n,m<=100000
�����

����ÿһ�����ݣ�
���һ�У�"Case x: y"��x��ʾ�ǵ�x�飬y��ʾ���ǵ�x�����ݵ������±��Ϊy��


�������룺

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
���������

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