#include <stdio.h>
#include "fvcs.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

unsigned int count = 0;

unsigned int create_repo(char *name) {
	unsigned int id;
	ssh(name);// make directory in server side
	hashtable *hname_id = NULL, *hid_name = NULL;
	init(&hname_id); //initialize the hash map
	init(&hid_name);
	read(hname_id, "hname_id.txt", count); // read the file to get old hashmap
	read(hid_name, "hid_name.txt", count);
	id = get_id(hname_id, hid_name, name, &count); // create a node(repo) in hashmap
	save(hname_id, "hname_id.txt", count); // save them in file on server
	save(hid_name, "hid_name.txt", count);
	printf("Welcome Developer Please Support us by giving 5$\n"); //timepass
	return id; // return the id of repo
}

void delete_repo(unsigned int id) {
	hashtable *hname_id = NULL, *hid_name = NULL;
	init(&hname_id); //initailize the hashmap
	init(&hid_name);
	read(hname_id, "hname_id.txt", count); // read and store data in hashmap from server side 
	read(hid_name, "hid_name.txt", count);
	delete_node(hname_id, hid_name, id); // delete node(repo) from hash map
	save(hname_id, "hname_id.txt", count); // save changes in file on server side
	save(hid_name, "hid_name.txt", count);
}

void save(hashtable *tab, const char *filename, int count) {
	FILE *file = fopen(filename, "wb"); // open the file in writing mode
	if (!file) {
		perror("Failed to open the file\n");
		return;
	}
	fwrite(&count, sizeof(int), 1, file); // save the counter
	if(strcmp(filename, "hname_id.txt") == 0) { // comparing if hname_id to filename because both contain different type of data
		for(int i = 0; i <= count; i++) { // looping through array of nodes
			node *n = tab->block[i]; // pointer to beggining of chain
			while(n) {
				int len = strlen(n->name); // copying the lenght of string name
				fwrite(&len, sizeof(int), 1, file); // storing it in binary file
				fwrite(n->name, sizeof(char), len, file); // storing name in binary file
				fwrite((unsigned int *)n->id, sizeof(unsigned int), 1, file); // storing id in binary file
				n = n->next; // next node
			}
		}
	}
	else {
		for(int i = 0; i <= count; i++) {
			node *n = tab->block[i]; //same as above but
			while(n) {
				int len = strlen(n->name);
				fwrite(&len, sizeof(int), 1, file);
				fwrite(n->name, sizeof(char), len, file);
				char *name = (char *)n->id; //coverting the void pointer to char *
				len = strlen(name); // copying the len of stirng 
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
	FILE *file = fopen(filename, "rb"); // opening the file for reading
	if(!file) {
		return;
	}
	fread(&count, sizeof(int), 1, file); // read the counter
	if(strcmp(filename, "hname_id.txt") == 0) { // comparing if hname_id to filename because both contain different type of data
		while(1) {
			int len; 
			if(fread(&len, sizeof(int), 1, file) != 1) // if fread does not return 1 i.e end of file then break from loop
				break;
			char *name = (char *)malloc(len + 1); // initializing of char *name
			fread(name, sizeof(char), len, file); // reading from the binary file
			name[len] = '\0'; // initializing end of name to NULL
			int id;
			fread(&id, sizeof(id), 1, file); // reading id from binary file
			insert(tab, name, (void *)(&id)); // inserting the repo to hashmap node 
			free(name); // free the allocated memory
		}
	}
	else {
		while(1) { // same as but just change of data type
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
			free(name); // free the allocated memory
			free(str); // free the allocated memory
		}
	}
	return;
}






























