#include <stdio.h>
#include <string.h>
#include "fvcs.h"
#include <dirent.h>

int main(char *argv[], int argc) {
	if(strcmp(argv[1], fvcs) == 0) 
		ftp();
	else {
		printf("Wrong input\n");
		return;
	}
}
