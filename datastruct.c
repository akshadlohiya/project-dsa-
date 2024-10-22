#include <stdio.h>
#include "fvcs.h"
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>

void init(p *st) {
	node *r = *st;
	r = NULL;
}

node *insert_node(p *st, char *dir) {
	node *nn, *r = *st;
	lists *l;
	nn = (node *)malloc(sizeof(node));
	l = (lists *)malloc(sizeof(lists));
	if(nn) {
		nn->dir = opendir(dir);
		if(!dir) {
			perror("opendir");
			return;
		}
		nn->fl = l;
		nn->bl = NULL;
		nn->fl->forw = NULL;
		nn->fl->back = NULL;
		nn->fl->next = NULL;
		nn->fl->prev = NULL;
	}
	if(!r) {
		r = nn;
	}
	else {
		while(r->l->forw)
			r = r->l->forw;
		r->fl->forw = nn;
		nn->bl = r->fl
		r->fl->back = r;
		r = r->fl->forw;
	}
	return r;
}
