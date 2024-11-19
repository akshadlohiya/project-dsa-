#include <stdio.h>
#include <string.h>
#include "fvcs.h"
#include <dirent.h>
// ./akshad fvcs repo create == argv[0] = ./akshad, argv[1] = fvcs, argv[2] = repo, argv[3] = create
int main(int argc, char *argv[]) {
	char name[1024];
	unsigned int id;
	int i;
	if(strcmp(argv[1], "fvcs") != 0) {
		printf("Wrong input\n");
		return 1;
	}
	if(strcmp(argv[2] , "repo") == 0) {
		if(strcmp(argv[3], "create") == 0) {
			printf("please enter the name of repo\n");
			scanf("%s", name);
			id = create_repo(name);
			printf("If you want to store your ip localy on your press 1 or press any other key for write your id\n");
			scanf("%d", &i);
			if(i == 1) { //asking user if he wants to store id no file in his repo
				FILE *file = fopen("id.txt", "wb");
				fwrite(&id, sizeof(int), 1, file);
				fclose(file);
			}
			printf("your directory id is %u\n", id); //if in both case print the id
		}
		else if(strcmp(argv[3], "delete") == 0) {
			printf("Please Enter you id for repo deletion\n");
			scanf("%u", &id); 
			delete_repo(id);
			printf("Your repo has been deleted\n");
		}
		else {
			printf("incomplete argument\n");
			return 2;
		}
		
	}
	if(strcmp(argv[2], "commit") == 0) {
	}
	else if(strcmp(argv[2], "add") == 0) {
	}
	else if(strcmp(argv[2], "history") == 0) {
	}
	else {
		return 2;
	}
	return 0;
}
