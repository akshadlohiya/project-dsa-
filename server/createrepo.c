#include <stdio.h>
#include "fvcs.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

unsigned int count = 0;

int main() {
	char name[1024];
	printf("please Enter the name of repo:\n"); // Entering the name of repo
	scanf("%s", name);
	int id = create_repo(name); // calling the repo_create function to create repo on the server
	printf("%d\n", id);
	return 0;
}

unsigned int create_repo(char *name) {
	unsigned int id;
	char command[1024];
	snprintf(command, sizeof(command), "mkdir %s", name);
	int i = system(command);
	if(i == -1) {
		printf("Unsuccesful to run the command\n");
	}
	hashtable *hname_id = NULL, *hid_name = NULL;
	init(&hname_id); //initialize the hash map
	init(&hid_name);
	readp(hname_id, "hname_id.txt", count); // read the file to get old hashmap
	readp(hid_name, "hid_name.txt", count);
	id = get_id(hname_id, hid_name, name, &count); // create a node(repo) in hashmap
	save(hname_id, "hname_id.txt", count); // save them in file on server
	save(hid_name, "hid_name.txt", count);
	snprintf(command, sizeof(command), "cd ./%s", name);
	i = system(command);
	if(i == -1) {
		printf("Unsuccesful to run the command\n");
	}
	FILE *fp = fopen("history.txt", "w");
	if(!fp) {
		printf("file cannot open\n");
		return 0;
	}
	fprintf(fp, "%d", 0);
	printf("Welcome Developer Please Support us by giving 5$\n"); //timepass
	return id; // return the id of repo
}
