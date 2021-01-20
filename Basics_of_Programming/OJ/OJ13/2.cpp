#include <iostream>
#include <list>
#include <string>
using namespace std;

/*
题目：Beiju Beiju

题目描述：

描述：
You’re typing a long text with a broken keyboard. Well it’s not so badly broken. The only problem with the keyboard is that sometimes the “home” key or the “end” key gets automatically pressed (internally). You’re not aware of this issue, since you’re focusing on the text and did not even turn on the monitor! After you finished typing, you can see a text on the screen (if you turn on the monitor). In Chinese, we can call it Beiju. Your task is to find the Beiju text.

输入：
There are several test cases. Each test case is a single line containing at least one and at most 100,000 letters, underscores and two special characters ‘[’ and ‘]’. ‘[’ means the “Home” key is pressed internally, and ‘]’ means the “End” key is pressed internally. The input is terminated by end-of-file (EOF).

输出：
For each case, print the Beiju text on the screen.

样例1：
输入：

This_is_a_[Beiju]_text

[[]][][]Happy_Birthday_to_Tsinghua_University

输出：

BeijuThis_is_a__text

Happy_Birthday_to_Tsinghua_University*/

int main() {
	string s; while (cin >> s) {
		list<char>l;
		auto it = l.begin();
		for (auto i : s) {
			if (i == '[')  it = l.begin();
			else if (i == ']')  it = l.end();
			else it = l.insert(it, i), it++;
		}
		for (auto it : l) cout << it;
		cout << endl;
	}
	return 0;
}

/* 5/8???
struct node {
	char c;
	node* next;
	node() {
		c = '\0';
		next = NULL;
	}
};

void print_link(node* head) {
	node* p = head->next;
	while (p) {
		cout << p->c;
		p = p->next;
	}
	cout << endl;
}

int main() {
	string s;
	while (getline(cin, s)) {
		node* head = new node(), * tail = head, * p = tail;
		int len = s.length();
		bool flag = true;
		for (int i = 0; i < len; i++) {
			if (s[i] == '[') {
				p = head;
				flag = false;
			}
			else if (s[i] == ']') {
				p = tail;
				flag = true;
			}
			else {
				node* tmp = new node();
				tmp->c = s[i];
				tmp->next = p->next;
				p->next = tmp;
				if (flag) {
					tail = tail->next;
					p = tail;
				}
				else {
					p = p->next;
				}
			}
		}
		print_link(head);
	}
	return 0;
}*/
