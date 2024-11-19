#include <stdio.h>
#include <string.h>
#include "fvcs.h"
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>

void delete_node(hashtable *hname_id, hashtable *hid_name, unsigned int id) {
	char *name = get_name(hid_name, id); // find the name of repo through id
	node *n = search(hname_id, name); // search the node which contain the name;
	if(!n) // if not found then return
		return;
	n->prev->next = n->next; // found then delete it from both hashmap
	n->next->prev = n->prev;
	free(n); // free the node
	char str[32];
	snprintf(str, sizeof(str), "%d", id);
	n = search(hid_name, str);
	n->prev->next = n->next;
	n->next->prev = n->prev;
	free(n); // free the node
	return;
}

unsigned int hash_fun(char *name) {
	unsigned int num; // finding a unique index in hashmap to store name and id 
	while(*name) {
		num = (num * 29) + *name++;
	}
	return num % SIZE; // ensuring that it does not extend beyond the SIZE
}

void init(hashtable **tab) {
	*tab = (hashtable *)malloc(sizeof(hashtable)); // allocating memory location to hashmap
	if (*tab == NULL) {
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < SIZE; i++)
		(*tab)->block[i] = NULL; //initializing each node to NULL so that no error occur
	return;
}

node *create_node(char *name, void *id) {
	node *n = (node *)malloc(sizeof(node)); // allocating memory to the node
	n->name = strdup(name); // copying name string to n->name pointer
	n->id = id; // storing void *id  to void *n->id
	n->next = NULL; // initializing both prev and next to NULL
	n->prev = NULL;
	return n; // return the node created
}

void insert(hashtable *tab, char *name, void *id) {
	unsigned int i = hash_fun(name); // find the index on the basis of the string
	node *n = create_node(name, id); // create node
	n->next = tab->block[i]; //making the n->next pointer to point tab->block[i]
	if(tab->block[i] != NULL) // if there is node in tab->block[i]
		tab->block[i]->prev = n;
	tab->block[i] = n; // store the node in tab->block[i]
	return;
}

unsigned int get_id(hashtable *hname_id, hashtable *hid_name, char *name, unsigned int *count) {
	node *n = search(hname_id, name); // search in hashmap
	if(n) { // if found then return the id 
		unsigned int *a = (unsigned int *)n->id;
		return *a;
	}
	unsigned int id = *count++; // if not then increment the counter by 1 and store name and id in both hashmap
	insert(hname_id, name, (void *)(&id));
	char str[32];
	snprintf(str, sizeof(str), "%d", id);
	insert(hid_name, str, (void *)strdup(name));
	return id; // finally return the id
}

char *get_name(hashtable *hid_name, unsigned int id) {
	char str[32];
	snprintf(str, sizeof(str), "%d", id); // convert unsigned int to char *
	node *n = search(hid_name, str); // find the name throug id
	return n ? (char *)n->id : NULL; //if found then return n->id by counverting it into char * else return NULL
}

node *search(hashtable *tab, char *name) {
	unsigned int i = hash_fun(name); // find the index 
	node *n = tab->block[i]; 
	while(n) {
		if(strcmp(n->name, name) == 0) //loop throungh index chain and check if it matches with name if match then return the node
			return n;
		n = n->next;
	}
	return NULL; // not found then return NULL
}










