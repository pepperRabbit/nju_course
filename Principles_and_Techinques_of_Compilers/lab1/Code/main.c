#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

extern FILE* yyin;

node* root = NULL;
bool error = false;

int main(int argc, char** argv){
	if(argc <= 1) return 1;
	FILE *f = fopen(argv[1], "r");
	if(!f) {
		perror(argv[1]);
		return 1;
	}
	yyrestart(f);
	yyparse();
	if(!error){
		print(root, 0);
	}
	return 0;
}
