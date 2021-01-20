#include <iostream>
using namespace std;

/*
题目：链表排序

题目描述：

已有a、b两个链表，每个链表中的结点包括学号、成绩。要求把两个链表合并，按学号升序排列。
输入：
第一行，a、b两个链表元素的数量N、M,用空格隔开。 接下来N行是a的数据 然后M行是b的数据 每行数据由学号和成绩两部分组成。学号和成绩均为整型，0<N，M<100。

输出：
按照学号升序排列的数据。

注意：
你需要在程序中实现如下函数：





typedef struct node {  //node的定义
	int sid;  //学号
	int score; //分数
	struct node *next;
} node;

node *creat_link(int n);  //传入链表节点的个数，生成链表并返回链表的头节点。

node *merge_link(node *a, node *b); //传入两个链表的头节点，返回合并后并且排好序的链表的头节点。

void print_link(node *a); //打印链表的节点信息

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	node *a = creat_link(n);
	node *b = creat_link(m);
	node *c= merge_link(a, b);
	print_link(c);
	return 0;
}



样例1：
输入：

2 3

5 100

6 89

3 82

4 95

2 10

输出：

2 10

3 82

4 95

5 100

6 89

样例2：
输入：

1 1

2 45

1 50

输出：

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