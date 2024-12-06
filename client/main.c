#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ./akshad fvcs repo create == argv[0] = ./akshad, argv[1] = fvcs, argv[2] = repo, argv[3] = create
int main(int argc, char *argv[]) {
	unsigned int id;
	int i;
	if(strcmp(argv[1], "fvcs") != 0) {
		printf("Wrong input\n");
		return 1;
	}
	if(strcmp(argv[2] , "repo") == 0) {
		if(strcmp(argv[3], "create") == 0) {
			system("./createrepo.exp > output.txt");
			FILE *fp = fopen("output.txt", "r");
			char idc[1024];
			fscanf(fp, "%s", idc);
			id = atoi(idc);
			printf("If you want to store your ip localy on your press 1 or press any other key for write your id\n");
			scanf("%d", &i);
			if(i == 1) { //asking user if he wants to store id no file in his repo
				FILE *file = fopen("id.txt", "w");
				fwrite(&id, sizeof(int), 1, file);
				fclose(file);
			}
			printf("your directory id is %u\n", id); //if in both case print the id
		}
		else if(strcmp(argv[3], "delete") == 0) {
			system("./deleterepo.exp");
		}
		else {
			printf("incomplete argument\n");
			return 2;
		}
		
	}
	if(strcmp(argv[2], "commit") == 0) {
		system("./commit.exp");
	
	}
	else if(strcmp(argv[2], "history") == 0) {
		system("./history.exp");
	}
	else if(strcmp(argv[2], "rollback") == 0) {
		system("./rollback.exp");
	}
	else {
		return 2;
	}
	return 0;
}
