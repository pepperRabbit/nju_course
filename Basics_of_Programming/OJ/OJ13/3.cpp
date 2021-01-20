#include <iostream>
using namespace std;

/*
��Ŀ����ʿն��

��Ŀ������

�����������һ����n��ͷ�Ķ�������ϣ����һЩ��ʿ������ɱ�������������е�ͷ����������m����ʿ���Թ�Ӷ��һ������ֵΪx����ʿ���Կ�������һ��ֱ��������x��ͷ������Ҫ֧��x����ҡ���ι�Ӷ��ʿ���ܿ����������е�ͷ������Ҫ֧���Ľ�����٣�ע�⣬һ����ʿֻ�ܿ�һ��ͷ���Ҳ��ܱ���Ӷ���Σ���������ٵĻ��ѣ�����޽⣬�����Loowater is doomed!".

���룺

��������ݰ�������������������һ��������"0 0"��Ҳ����˵������"0 0"ʱ���������ÿ�����������ĵ�һ�а�������1��20000֮�����������ʾ����ͷ��n���Լ���������ʿ������m��
��������n���У�ÿ�ж�����һ����������������ͷ��ֱ������λ�����ס�
��������m���У�ÿ�ж�����һ����������ָ��¬������ʿ�ĸ߶ȣ�Ҳ��������Ϊ��λ��
�����

����ÿ�����԰�������һ�������������ɱ�����������ͽ�����������ʿ�ǲ�����ɱ�����������һ�� "Loowater is doomed!"��
����������

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
���������

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