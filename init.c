#include <stdio.h>
#include "fvcs.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

unsigned int count = 0;

unsigned int create_repo(char *name) {
	unsigned int id;
	ssh(name);
	hashtable *hname_id = NULL, *hid_name = NULL;
	printf("1");
	init(&hname_id);
	init(&hid_name);
	read(hname_id, "hname_id.txt", count);
	read(hid_name, "hid_name.txt", count);
	id = get_id(hname_id, hid_name, name, &count);
	save(hname_id, "hname_id.txt", count);
	save(hid_name, "hid_name.txt", count);
	printf("Welcome Developer Please Support us by giving 5$\n");
	return id;
}

void delete_repo(unsigned int id) {
	hashtable *hname_id = NULL, *hid_name = NULL;
	init(&hname_id);
	init(&hid_name);
	printf("akshad");
	read(hname_id, "hname_id.txt", count);
	read(hid_name, "hid_name.txt", count);
	delete_node(hname_id, hid_name, id);
	save(hname_id, "hname_id.txt", count);
	save(hid_name, "hid_name.txt", count);
}

void save(hashtable *tab, const char *filename, int count) {
	FILE *file = fopen(filename, "wb");
	if (!file) {
		perror("Failed to open the file\n");
		return;
	}
	printf("2");
	fwrite(&count, sizeof(int), 1, file);
	if(strcmp(filename, "hname_id.txt") == 0) {
		for(int i = 0; i <= count; i++) {
			node *n = tab->block[i];
			while(n) {
				int len = strlen(n->name);
				fwrite(&len, sizeof(int), 1, file);
				fwrite(n->name, sizeof(char), len, file);
				fwrite((unsigned int *)n->id, sizeof(unsigned int), 1, file);
				n = n->next;
			}
		}
	}
	else {
		for(int i = 0; i <= count; i++) {
			node *n = tab->block[i];
			while(n) {
				int len = strlen(n->name);
				fwrite(&len, sizeof(int), 1, file);
				fwrite(n->name, sizeof(char), len, file);
				char *name = (char *)n->id;
				len = strlen(name);
				fwrite(&len, sizeof(int), 1, file);
				fwrite(name, sizeof(char), len, file);
				n = n->next;
			}
		}
	}
	fclose(file);
	return;
}

void read(hashtable *tab, const char *filename, int count) {
	FILE *file = fopen(filename, "rb");
	printf("2");
	if(!file) {
		return;
	}
	printf("3");
	fread(&count, sizeof(int), 1, file);
	if(strcmp(filename, "hname_id.txt") == 0) {
		while(1) {
			int len;
			if(fread(&len, sizeof(int), 1, file) != 1)
				break;
			char *name = (char *)malloc(len + 1);
			fread(name, sizeof(char), len, file);
			name[len] = '\0';
			int id;
			fread(&id, sizeof(id), 1, file);
			insert(tab, name, (void *)(&id));
			free(name);
		}
	}
	else {
		while(1) {
			int len;
			if(fread(&len, sizeof(int), 1, file) != 1)
				break;
			char *str = (char *)malloc(len + 1);
			fread(str, sizeof(char), len, file);
			str[len] = '\0';
			fread(&len, sizeof(int), 1, file);
			char *name = (char *)malloc(len + 1);
			fread(name, sizeof(char), len, file);
			name[len] = '\0';
			insert(tab, str, (void *)name);
			free(name);
			free(str);
		}
	}
	return;
}






























