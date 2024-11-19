#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define SIZE 128

typedef struct node {
	char *name;
	void *id;
	struct node *next, *prev;
} node;

typedef struct hashtable {
	node *block[SIZE];
} hashtable;

void ftp(char *);
void ssh(char *);
void save(hashtable *, const char *, int);
void read(hashtable *, const char *, int);
void delete_repo(unsigned int);
void init(hashtable **);
void delete_node(hashtable *, hashtable *, unsigned int);
void insert(hashtable *, char *, void *);
unsigned int hash_fun(char *);
unsigned int create_repo(char *);
unsigned int get_id(hashtable *, hashtable *, char *, unsigned int *);
char *get_name(hashtable *, unsigned int);
node *create_node(char *, void *);
node *search(hashtable *, char *);

