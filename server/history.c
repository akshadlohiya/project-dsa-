#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fvcs.h"

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
	history(num);
	return 0;
}

void history(int i) {
	int index;
	FILE *fp = fopen("history.txt", "r");
	if(!fp) {
		printf("Cannot open the file\n");
		return;
	}
	fscanf(fp, "%d", &index);
	fclose(fp);
	if(i > index) {
		printf("Invalid input\n");
		return;
	}
	char name[1024], c;
	snprintf(name, sizeof(name), "his%i.txt", i);
	fp = fopen(name, "r");
	if(!fp) {
		printf("Cannot open the file\n");
		return;
	}
	while((c = getc(fp)) != EOF) {
		printf("%c", c);
	}
	return;
}
