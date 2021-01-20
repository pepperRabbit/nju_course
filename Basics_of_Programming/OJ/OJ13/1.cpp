#include <iostream>
using namespace std;

/*
题目：约瑟夫环

题目描述：

 

约瑟夫（Josephus）问题：有n个小孩围坐成一圈，从某个小孩开始从1开始顺时针报数，报到m的小孩从圈子离开，然后，从下一个小孩开始重新从1开始报数，每报到m，相应的小孩从圈子离开，最后一个离开圈子的小孩为胜者。

现要求每个小孩用链表中的一个结点来表示：

struct Node {

char content; //小孩的编号

Node *next; //指向下一个小孩的指针

};

最后一个小孩结点的next指向第一个小孩结点，从而形成一个环形链表，从第一个输入的节点开始报数。

 

在此问题基础上，完成如下链表的操作：

首先构筑一个约瑟夫问题中的环形链表，链表上的每个节点的content值是任一a-z字符（字符由用户输入），节点数量 n 依据用户输入，不小于6。
然后在环形链表上采用约瑟夫算法报数（m由用户合理指定），并在环形链表上卸载相应节点（最后一个节点也需要卸载）。
在进行2）的过程中，同时生成两个单向链表，其中一个链表插入每次卸载的节点，另一个链表插入一个新生成的节点（新生成节点恰好是卸载节点在字母表逆向对应的字符，即a对应z，b对应y，依次类推），其中第一个链表按照约瑟夫问题报数的卸载顺序生成（按尾部追加法，每个新卸载的节点插入链表尾部），第二个链表 即逆向对应字符链表 按照升序关系排列，（即如果已有链表节点为b->f->g，则新插入节点如果为d，则插入的节点d应该插在b、f之间，最后结果为b->d->f->g。
再分别打印两个单向链表。
最后在程序结束前释放两个单向链表。
输入：

8 3

b m g l t m x o

输出：

g m b t m o l x

c g l n n o t y // c(x)->g(t)->l(o)->n(m)->n(m)->o(l)->t(g)->y(b)*/

struct Node {
	char content;
	Node* next;
};

Node* build_list(int n, Node* &t) {
	Node* head = new Node, * tail = head;
	head->content = ' ';
	head->next = nullptr;
	for (int i = 0; i < n; i++) {
		char c;
		cin >> c;
		Node* node = new Node;
		node->next = nullptr;
		node->content = c;
		tail->next = node;
		tail = tail->next;
	}
	t = tail;
	return head;
}

void print(Node* head) {
	Node* p = head->next;
	//if (p == NULL) cout << "error";
	while (p != NULL) {
		cout << p->content << " ";
		p = p->next;
	}
	cout << endl;
}

Node* sol1(Node* h, Node* t, int n, int m) {
	Node* head = new Node, * tail = head;
	head->content = ' ';
	head->next = nullptr;
	Node* now = h->next, * pre = t;
	t->next = now;
	int i = 1;
	while (n > 1) {
		//cout << i << " " << now->content << endl;
		if (i ==m) {
			i = 0;
			Node* p = now;
			pre->next = now->next;
			//cout << pre->next->content << endl;
			now->next = nullptr;
			tail->next = p;
			tail = tail->next;
			now = pre->next;
			n--;
		}
		else {
			pre = pre->next;
			now = pre->next;
		}
		i++;
	}
	tail->next = now;
	now->next = nullptr;
	return head;
}

void select_sort(Node* a) {
	Node* start = a->next;
	while (start != nullptr) {
		Node* small = start;
		Node* p = start->next;
		while (p != nullptr) {
			if (p->content > small->content) small = p;	//small is big...
			p = p->next;
		}
		p = start;
		start = start->next;
		char tc = p->content;
		p->content = small->content;
		small->content = tc;
	}
}

void sol2(Node* h) {
	select_sort(h);
	//print(h);
	Node* p = h->next;
	while (p != nullptr) {
		p->content = 'z' - (p->content - 'a');
		p = p->next;
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	Node* tail = new Node;
	Node* head = build_list(n, tail);
	Node* ans1 = sol1(head, tail, n, m);
	print(ans1);
	sol2(ans1);
	print(ans1);
	return 0;
}
