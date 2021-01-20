#include <iostream>
using namespace std;

/*
��Ŀ��Լɪ��

��Ŀ������

 

Լɪ��Josephus�����⣺��n��С��Χ����һȦ����ĳ��С����ʼ��1��ʼ˳ʱ�뱨��������m��С����Ȧ���뿪��Ȼ�󣬴���һ��С����ʼ���´�1��ʼ������ÿ����m����Ӧ��С����Ȧ���뿪�����һ���뿪Ȧ�ӵ�С��Ϊʤ�ߡ�

��Ҫ��ÿ��С���������е�һ���������ʾ��

struct Node {

char content; //С���ı��

Node *next; //ָ����һ��С����ָ��

};

���һ��С������nextָ���һ��С����㣬�Ӷ��γ�һ�����������ӵ�һ������Ľڵ㿪ʼ������

 

�ڴ���������ϣ������������Ĳ�����

���ȹ���һ��Լɪ�������еĻ������������ϵ�ÿ���ڵ��contentֵ����һa-z�ַ����ַ����û����룩���ڵ����� n �����û����룬��С��6��
Ȼ���ڻ��������ϲ���Լɪ���㷨������m���û�����ָ���������ڻ���������ж����Ӧ�ڵ㣨���һ���ڵ�Ҳ��Ҫж�أ���
�ڽ���2���Ĺ����У�ͬʱ��������������������һ���������ÿ��ж�صĽڵ㣬��һ���������һ�������ɵĽڵ㣨�����ɽڵ�ǡ����ж�ؽڵ�����ĸ�������Ӧ���ַ�����a��Ӧz��b��Ӧy���������ƣ������е�һ��������Լɪ�����ⱨ����ж��˳�����ɣ���β��׷�ӷ���ÿ����ж�صĽڵ��������β�������ڶ������� �������Ӧ�ַ����� ���������ϵ���У����������������ڵ�Ϊb->f->g�����²���ڵ����Ϊd�������Ľڵ�dӦ�ò���b��f֮�䣬�����Ϊb->d->f->g��
�ٷֱ��ӡ������������
����ڳ������ǰ�ͷ�������������
���룺

8 3

b m g l t m x o

�����

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
