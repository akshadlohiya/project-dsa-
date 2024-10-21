#include <stdio.h>
#include <string.h>
#include "fvcs.h"
#include <dirent.h>

int main(char *argv[], int argc) {
	if(strcmp(argv[1], "fvcs") == 0) 
		ftp();
	else {
		printf("Wrong input\n");
		return 1;
	}
	if(strcmp(argv[2], "commit")) {
		commit();
	}
	else if(strcmp(argv[2], "add") == 0) {
		add();
	}
	else if(strcmp(argv[2], "history") == 0) {
		history();
	}
	else {
		return 2;
	}
	return 0;
}
