#include <iostream>
#include <cstdio>
using namespace std;

/*
��Ŀ�������㷨�Ľ�����������

��Ŀ������

������ͨ�����������е�Ԫ��ʵ�ֵģ���ͬ�������㷨��Ӧ�Ų�ͬ�Ľ����������С�����ʵ��ð�������ѡ�����򣬲�����������н���Ԫ�ؽ���ʱ����ӡ�����Ϣ�Լ�����������顣



���룺�������ݣ���һ��Ϊ�����㷨�����ͣ�����SELECT��BUBBLE���֣��ڶ���Ϊ������Ԫ�ص�������������100����������Ϊ�����и�Ԫ�أ�����int��Χ�ڣ���



�����ÿ��Ԫ�ؽ���ʱ������У���һ��ΪԪ�ؽ����������Ϣ������Ԫ�ص�ֵ�����±꣬��ʽ��ʾ�����ڶ���Ϊ���ν���������顣





������



���룺



SELECT

10

1 5 4 9 -5 -2 6 8 0 20



�����



swap: 1 at loc0 and -5 at loc4

-5 5 4 9 1 -2 6 8 0 20

swap: 5 at loc1 and -2 at loc5

-5 -2 4 9 1 5 6 8 0 20

swap: 4 at loc2 and 0 at loc8

-5 -2 0 9 1 5 6 8 4 20

swap: 9 at loc3 and 1 at loc4

-5 -2 0 1 9 5 6 8 4 20

swap: 9 at loc4 and 4 at loc8

-5 -2 0 1 4 5 6 8 9 20



���룺



BUBBLE

10

1 5 4 9 -5 -2 6 8 0 20



�����



swap: 5 at loc1 and 4 at loc2

1 4 5 9 -5 -2 6 8 0 20

swap: 9 at loc3 and -5 at loc4

1 4 5 -5 9 -2 6 8 0 20

swap: 9 at loc4 and -2 at loc5

1 4 5 -5 -2 9 6 8 0 20

swap: 9 at loc5 and 6 at loc6

1 4 5 -5 -2 6 9 8 0 20

swap: 9 at loc6 and 8 at loc7

1 4 5 -5 -2 6 8 9 0 20

swap: 9 at loc7 and 0 at loc8

1 4 5 -5 -2 6 8 0 9 20

swap: 5 at loc2 and -5 at loc3

1 4 -5 5 -2 6 8 0 9 20

swap: 5 at loc3 and -2 at loc4

1 4 -5 -2 5 6 8 0 9 20

swap: 8 at loc6 and 0 at loc7

1 4 -5 -2 5 6 0 8 9 20

swap: 4 at loc1 and -5 at loc2

1 -5 4 -2 5 6 0 8 9 20

swap: 4 at loc2 and -2 at loc3

1 -5 -2 4 5 6 0 8 9 20

swap: 6 at loc5 and 0 at loc6

1 -5 -2 4 5 0 6 8 9 20

swap: 1 at loc0 and -5 at loc1

-5 1 -2 4 5 0 6 8 9 20

swap: 1 at loc1 and -2 at loc2

-5 -2 1 4 5 0 6 8 9 20

swap: 5 at loc4 and 0 at loc5

-5 -2 1 4 0 5 6 8 9 20

swap: 4 at loc3 and 0 at loc4

-5 -2 1 0 4 5 6 8 9 20

swap: 1 at loc2 and 0 at loc3

-5 -2 0 1 4 5 6 8 9 20*/

void print_n(int n[], int len) {
	for (int i = 0; i < len; i++) {
		cout << n[i];
		if (i < len - 1) cout << " ";
	}
	cout << endl;
}

void bubble_sort(int n[], int len) {
	for (int i = 0; i < len - 1; i++) {
		bool is_changed = false;
		for (int j = 0; j < len - 1 - i; j++) {
			if (n[j] > n[j + 1]) {
				printf("swap: %d at loc%d and %d at loc%d\n", n[j], j, n[j + 1], j + 1);
				swap(n[j], n[j + 1]);
				print_n(n, len);
				is_changed = true;
			}
		}
		if (!is_changed) return;
	}
}

void select_sort(int n[], int len) {
	for (int i = 0; i < len - 1; i++) {
		int pos = i;
		for (int j = i + 1; j < len; j++) {
			if (n[j] < n[pos]) pos = j;
		}
		if (pos != i) {
			printf("swap: %d at loc%d and %d at loc%d\n", n[i], i, n[pos], pos);
			swap(n[i], n[pos]);
			print_n(n, len);
		}
	}
}

int main() {
	int n, num[101] = { 0 };
	string s;
	cin >> s;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num[i];
	}
	if (s == "BUBBLE") {
		bubble_sort(num, n);
	}
	else if (s == "SELECT") {
		select_sort(num, n);
	}
	return 0;
}