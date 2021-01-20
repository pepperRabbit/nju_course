#include <iostream>
using namespace std;

/*
��Ŀ����������

��Ŀ������

����a��b��������ÿ�������еĽ�����ѧ�š��ɼ���Ҫ�����������ϲ�����ѧ���������С�
���룺
��һ�У�a��b��������Ԫ�ص�����N��M,�ÿո������ ������N����a������ Ȼ��M����b������ ÿ��������ѧ�źͳɼ���������ɡ�ѧ�źͳɼ���Ϊ���ͣ�0<N��M<100��

�����
����ѧ���������е����ݡ�

ע�⣺
����Ҫ�ڳ�����ʵ�����º�����





typedef struct node {  //node�Ķ���
	int sid;  //ѧ��
	int score; //����
	struct node *next;
} node;

node *creat_link(int n);  //��������ڵ�ĸ����������������������ͷ�ڵ㡣

node *merge_link(node *a, node *b); //�������������ͷ�ڵ㣬���غϲ������ź���������ͷ�ڵ㡣

void print_link(node *a); //��ӡ����Ľڵ���Ϣ

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	node *a = creat_link(n);
	node *b = creat_link(m);
	node *c= merge_link(a, b);
	print_link(c);
	return 0;
}



����1��
���룺

2 3

5 100

6 89

3 82

4 95

2 10

�����

2 10

3 82

4 95

5 100

6 89

����2��
���룺

1 1

2 45

1 50

�����

1 50

2 45*/

struct node {
	int id;
	int grade;
	node* next;

	node() {
		id = 0;
		grade = 0;
		next = NULL;
	}
};

node* creat_link(int n) {
	node* head = new node();
	for (int i = 0; i < n; i++) {
		node* p = new node();
		cin >> p->id >> p->grade;
		if (head->next) {
			p->next = head->next;
			head->next = p;
		}
		else {
			head->next = p;
		}
	}
	return head;
}

void select_sort(node* a) {
	node* start = a->next;
	while (start != NULL) {
		node* small = start;
		node* p = start->next;
		while (p != NULL) {
			if (p->id < small->id) small = p;
			p = p->next;
		}
		p = start;
		start = start->next;
		int tid = p->id, tg = p->grade;
		p->id = small->id;
		p->grade = small->grade;
		small->id = tid;
		small->grade = tg;
	}
}

node* merge_link(node* a, node* b) {
	node* p = a;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = b->next;
	select_sort(a);
	return a;
}

void print_link(node* a) {
	node* p = a->next;
	while (p != NULL) {
		cout << p->id << " " << p->grade << endl;
		p = p->next;
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	node* a = creat_link(n);
	node* b = creat_link(m);
	node* c = merge_link(a, b);
	print_link(c);
	return 0;
}