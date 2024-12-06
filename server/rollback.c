#include <stdio.h>
#include <string.h>
#include "fvcs.h"
#include <dirent.h>

int main() {
	printf("Enter the id and number of history to access");
	unsigned int id;
	int num, count = 0;
	scanf("%u%d", &id, &num);
	hashtable *tab = NULL;
	init(&tab);
	readp(tab, "hid_name.txt", count);
	char *a;
	a = get_name(tab, id);
	char command[1024];
	snprintf(command, sizeof(command),"cd ./%s", a);
	int j = system(command);
	if(j == -1) {
		printf("cannot rum system command");
		return 1;
	}
	rollback(num);
	return 0;
}

void rollback(int i) {
	FILE *fp = fopen("history.txt", "r");
	if(!fp) {
		printf("Cannot open the file\n");
		return;
	}
	int index;
	fscanf(fp, "%d", &index);
	fclose(fp);
	if(i > index) {
		printf("Invalid input\n");
		return;
	}
	char a[1024];
	do {
		snprintf(a, sizeof(a), "commit%i", index);
		delete_fol(a);
		index--;
	} while(i < index);
	fp = fopen("history.txt", "w");
	if(!fp) {
		printf("Cannot open the file\n");
		return;
	}
	fprintf(fp, "w");
}
