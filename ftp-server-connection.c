#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fvcs.h"

void ftp(char *name) {
	name[strcspn(name, "\n")] = 0; // copy the name  of repo and remove any newline from it 
	char command[256];
	snprintf(command, sizeof(command), "./fileupload.exp %s", name); // concate "./fileupload.exp" with name and store it in command
	int res = system(command); // run this on client side
	if(res == -1)
		perror("Error executing sytem command");
	return;
}

void ssh(char *name) {
	name[strcspn(name, "\n")] = 0; // copy the name  of repo and remove any newline from it
	char command[256];
	snprintf(command, sizeof(command), "./sshrepo.exp %s", name); // concate "./fileupload.exp" with name and store it in command
	int res = system(command); // run this on client side
	if(res == -1)
		perror("Error executing sytem command");
} 
