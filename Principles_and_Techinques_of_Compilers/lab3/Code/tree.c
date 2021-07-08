#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node* create(bool flag, int type, char name[], char val[], int line)
{
	node* n = (node*)malloc(sizeof(node));
	n->flag = flag;
	n->type = type;
	n->line = line;
	strcpy(n->name, name);
        strcpy(n->val, val);
	n->child=NULL;
	n->sibling=NULL;
	return n;
}

void addChild(int num, node* root, node* childs[])
{	
	//if(root==NULL) printf("error root null!!!\n");
	//if(root) printf("root:%s\n",root->name);
	node* t;
	int cnt = 0;
	for(int i=0; i<num; i++){
		//printf("%d\n",i);
		//if(childs[i]) printf("c:%s\n", childs[i]->name);
		//if(childs[i]==NULL) printf("c null\n");
		if(childs[i]==NULL) continue;
		if(cnt==0){
			root->child = childs[i];
			t = root->child;
		}
		else{
			t->sibling = childs[i];
			t = t->sibling;
		}
		cnt++;
		//if(t==NULL) printf("t null!\n");
		//if(t==NULL && num-i>1) return;
	}
}

/*void addChild(node* root, node* child)
{
	if(root){
		root->child = child;
	}
}

void addSibling(node* root, node* sib)
{
	node* t = root;
	if(root){
		while(t->sibling!=NULL){
			t = t->sibling;
		}
		t->sibling = sib;
	}
}

void addChild2(node* root, node* c1, node* c2)
{
	if(root){
		root->child = c1;
		root->child->sibling = c2;
	}
}

void addChild3(node* root, node* c1, node* c2, node* c3)
{
	//if(root)
}*/

void print(node* root, int height)
{
	if(!root) return;
	for(int i=0; i<height; i++){
		printf("  ");
	}
	printf("%s",root->name);
	if(root->flag){
		if(strcmp("INT",root->name)==0) printf(": %d\n", atoi(root->val));
		else if(strcmp("FLOAT",root->name)==0) printf(": %f\n", atof(root->val));
		else if(strcmp("TYPE",root->name)==0) printf(": %s\n", root->val);
		else if(strcmp("ID",root->name)==0) printf(": %s\n", root->val);
		else printf("\n");
	}
	else printf(" (%d)\n",root->line);
	node* t = root->child;
	while(t!=NULL){
		print(t, height+1);
		t = t->sibling;
	}
}
