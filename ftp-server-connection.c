#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fvcs.h"

void ftp(char *name) {
	name[strcspn(name, "\n")] = 0;
	char command[256];
	snprintf(command, sizeof(command), "./fileupload.exp %s", name);
	int res = system(command);
	if(res == -1)
		perror("Error executing sytem command");
	return;
}

void ssh(char *name) {
	name[strcspn(name, "\n")] = 0;
	char command[256];
	snprintf(command, sizeof(command), "./sshrepo.exp %s", name);
	int res = system(command);
	if(res == -1)
		perror("Error executing sytem command");
} 
