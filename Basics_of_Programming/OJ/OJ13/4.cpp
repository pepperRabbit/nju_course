#include <iostream>
using namespace std;

/*
��Ŀ��������ʵ�ּ��ϲ���

��Ŀ������

��������Ǹ�����������int��Χ�ڣ��������ǵĽ����������Ͳ��

ע�⣺1. ���ݣ����������õ����������С����ϵȣ���ʹ�������ʾ��2. ����ķǸ����������п������ظ�Ԫ�أ��������в������ظ�Ԫ�أ�3. ����������������ʱ���밴����˳�����

�������ʾ����

���룺��һ�������������ֱ���������������е�Ԫ�ظ�����֮������Ϊ��Ӧ���������С�

10 10
3 11 22 33 73 64 41 11 53 68
47 44 62 57 37 59 23 41 29 78

�����������ֱ���������������Ͳ��ע��ǰ������������Ӧ������͵��ַ�����

Intersection: 41
Union: 3 11 22 23 29 33 37 41 44 47 53 57 59 62 64 68 73 78
Difference: 3 11 22 33 53 64 68 73*/

struct node {
	int val;
	node* next;

	node() {
		val = 0;
		next = nullptr;
	}
};

node* create(int n, int num[]) {
	node* head = new node(), * tail = head;
	for (int i = 0; i < n; i++) {
		node* p = new node();
		p->val = num[i];
		tail->next = p;
		tail = tail->next;
	}
	return head;
}

void print(node* head) {
	node* p = head->next;
	while (p) {
		cout << p->val << " ";
		p = p->next;
	}
	cout << endl;
}

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

node* intersection(node* list1, node* list2) {
	node* head = new node(), * p1 = list1->next, * p2 = list2->next, * tail = head;
	while (p1 && p2) {
		if (p1->val == p2->val) {
			node* p = new node();
			p->val = p1->val;
			tail->next = p;
			tail = tail->next;
			p1 = p1->next;
			p2 = p2->next;
		}
		else if (p1->val < p2->val) {
			p1 = p1->next;
		}
		else {
			p2 = p2->next;
		}
	}
	tail->next = NULL;
	return head;
}

node* my_union(node* list1, node* list2) {
	node* head = new node(), * p1 = list1->next, * p2 = list2->next, * tail = head;
	int last = 0xffffffff;
	while (p1 || p2) {
		if (!p1) {
			if (p2->val != last) {
				last = p2->val;
				node* tmp = new node();
				tmp->val = last;
				tail->next = tmp;
				tail = tail->next;
			}
			p2 = p2->next;
		}
		else if (!p2) {
			if (p1->val != last) {
				last = p1->val;
				node* tmp = new node();
				tmp->val = last;
				tail->next = tmp;
				tail = tail->next;
			}
			p1 = p1->next;
		}
		else {
			if (p1->val < p2->val) {
				if (p1->val != last) {
					last = p1->val;
					node* tmp = new node();
					tmp->val = last;
					tail->next = tmp;
					tail = tail->next;
				}
				p1 = p1->next;
			}
			else if (p2->val < p1->val) {
				if (p2->val != last) {
					last = p2->val;
					node* tmp = new node();
					tmp->val = last;
					tail->next = tmp;
					tail = tail->next;
				}
				p2 = p2->next;
			}
			else {
				if (p1->val != last) {
					last = p1->val;
					node* tmp = new node();
					tmp->val = last;
					tail->next = tmp;
					tail = tail->next;
				}
				p1 = p1->next;
				p2 = p2->next;
			}
		}
	}
	tail->next = NULL;
	return head;
}

/*
10 5
12 12 12 10 10 1 2 3 4 5
1 2 3 4 5
*/
node* difference(node* list1, node* list2) {
	int last = 0xffffffff;
	node* p1 = list1->next, * p2 = list2->next, * head = new node(), * tail = head;
	while (p1) {
		if (!p2) {
			//cout << "p2 is null" << endl;
			while (p1) {
				//cout << p1->val << " " << last << endl;
				if (p1->val != last) {
					last = p1->val;
					tail->next = p1;
					tail = tail->next;
				}
				p1 = p1->next;
			}
			break;
		}
		//cout << p1->val << " " << p2->val << endl;
		if (p1->val != last) {
			last = p1->val;
			if (last != p2->val) {
				tail->next = p1;
				tail = tail->next;
			}
			else p2 = p2->next;
		}
		p1 = p1->next;
	}
	tail->next = NULL;
	return head;
}

int main() {
	int m, n;
	cin >> m >> n;
	int* num1 = (int*)malloc(sizeof(int) * m);
	int* num2 = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < m; i++) {
		cin >> num1[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> num2[i];
	}
	quick_sort(0, m - 1, num1);
	quick_sort(0, n - 1, num2);
	node* list1 = create(m, num1);
	node* list2 = create(n, num2);
	node* inter = intersection(list1, list2);
	cout << "Intersection: ";
	print(inter);
	node* myunion = my_union(list1, list2);
	cout << "Union: ";
	print(myunion);
	node* diff = difference(list1, inter);
	cout << "Difference: ";
	print(diff);
	return 0;
}