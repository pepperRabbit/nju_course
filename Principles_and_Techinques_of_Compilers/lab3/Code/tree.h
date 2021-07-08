#ifndef NODE
#define NODE
#include <stdbool.h>

typedef struct node
{	
	bool flag;	//true: terminal
	int type;
	char name[32];
	char val[32];
	int line;
	struct node* sibling;
	struct node* child;
} node;

node* create(bool flag, int type, char name[], char val[], int line);
/*void addChild(node* root, node* child);
void addSibling(node* root, node* sib);
void addChild2(node* root, node* c1, node* c2);
void addChild3(node* root, node* c1, node* c2, node* c3);*/
void addChild(int num, node* root, node* childs[]);
void print(node* root, int height);

#endif
