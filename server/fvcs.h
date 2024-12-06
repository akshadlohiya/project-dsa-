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
void readp(hashtable *, const char *, int);
void delete_repo(unsigned int);
void init(hashtable **);
void delete_node(hashtable *, hashtable *, unsigned int);
void insert(hashtable *, char *, void *);
void storeFile(const char *);
void delete_fol(char *);
void compare(const char *, const char *);
void commit(char *);
void history(int);
void rollback(int);
unsigned int hash_fun(char *);
unsigned int create_repo(char *);
unsigned int get_id(hashtable *, hashtable *, char *, unsigned int *);
int access_file(char *, char *);
int readline(char *, int, FILE *);
char *get_name(hashtable *, unsigned int);
node *create_node(char *, void *);
node *search(hashtable *, char *);

