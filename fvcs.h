#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

typedef struct node {
	DIR *dir;
	lists *fl, *bl;
} node;
typedef  node* p;
typedef struct lists {
	node *forw, *back;
	lists *next, *prev;
} lists;
