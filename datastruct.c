#include <stdio.h>
#include <string.h>
#include "fvcs.h"
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>

void delete_node(hashtable *hname_id, hashtable *hid_name, unsigned int id) {
	char *name = get_name(hid_name, id);
	node *n = search(hname_id, name);
	if(!n)
		return;
	n->prev->next = n->next;
	n->next->prev = n->prev;
	free(n);
	char str[32];
	snprintf(str, sizeof(str), "%d", id);
	n = search(hid_name, str);
	n->prev->next = n->next;
	n->next->prev = n->prev;
	free(n);
	return;
}

unsigned int hash_fun(char *name) {
	unsigned int num;
	while(*name) {
		num = (num * 28) + *name++;
	}
	return num % SIZE;
}

void init(hashtable *tab) {
	tab = (hashtable *)malloc(sizeof(hashtable));
	for(int i = 0; i < SIZE; i++)
		tab->block[i] = NULL;
	return;
}

node *create_node(char *name, unsigned int id) {
	node *n = (node *)malloc(sizeof(node));
	n->name = strdup(name);
	n->id = id;
	n->next = NULL;
	n->prev = NULL;
	return n;
}

void insert(hashtable *tab, char *name, unsigned int id) {
	unsigned int i = hash_fun(name);
	node *n = create_node(name, id);
	n->next = tab->block[i];
	tab->block[i]->prev = n;
	tab->block[i] = n;
	return;
}

unsigned int get_id(hashtable *hname_id, hashtable *hid_name, char *name) {
	node *n = search(hname_id, name);
	if(n)
		return n->id;
	int id = count++;
	insert(hname_id, name, id);
	char str[32];
	snprintf(str, sizeof(str), "%d", id);
	insert(hid_name, str, (int)strdup(name));
	return id;
}

char *get_name(hashtable *hid_name, unsigned int id) {
	char str[32];
	snprintf(str, sizeof(str), "%d", id);
	node *n = search(hid_name, str);
	return n ? (const char *)n->id : NULL;
}

node *search(hashtable *tab, char *name) {
	unsigned int i = hash_fun(name);
	node *n = tab->block[i];
	while(n) {
		if(strcmp(n->name, name) == 0)
			return n;
		n = n->next;
	}
	return NULL;
}










