#include <stdio.h>
#include "fvcs.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int main() {
	printf("Please Enter you id for repo deletion\n"); // enter id to see where the repo is located
	unsigned int id;
	scanf("%u", &id); 
	delete_repo(id); // calling the delete_repo function to delete the repo from the server
	printf("Your repo has been deleted\n");
}

void delete_repo(unsigned int id) {
	unsigned int count = 0;
	hashtable *hname_id = NULL, *hid_name = NULL;
	init(&hname_id); //initailize the hashmap
	init(&hid_name);
	char *name;
	readp(hname_id, "hname_id.txt", count); // read and store data in hashmap from server side 
	readp(hid_name, "hid_name.txt", count);
	name = get_name(hid_name, id);
	printf("%s\n", name);
	delete_node(hname_id, hid_name, id); // delete node(repo) from hash map
	save(hname_id, "hname_id.txt", count); // save changes in file on server side
	save(hid_name, "hid_name.txt", count);
}
