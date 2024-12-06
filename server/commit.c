#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "fvcs.h"
#include <dirent.h>


int main() {
	int i, count = 0;
	unsigned int id; // upload the current directory to the server
	FILE *fp = fopen("history.txt", "r+");
	fscanf(fp, "%d", &i);
	i++;
	rewind(fp);
	fprintf(fp, "%d", i);
	fclose(fp);
	printf("Enter the id of your repo");
	scanf("%u", &id);
	hashtable *tab = NULL;
	init(&tab);
	readp(tab, "hid_name.txt", count);
	char *a;
	a = get_name(tab, id);
	if(i != 1) {
		commit(a);
	}
}

int access_file(char *name, char *old) {
	DIR *dir1 = opendir(old); // open the directory
	DIR *dir2 = opendir(name);
	int i = 1;
	if (!dir1) {
		printf("Original directory %s cannot be opened.\n", old);
		if (dir2) 
			closedir(dir2);
		return 1;
	}
	if (!dir2) {
		printf("Updated directory %s cannot be opened.\n", name);
		closedir(dir1);
		return 1;
	}
	struct dirent *entry1, *entry2;
	struct stat stat1, stat2;
	while ((entry1 = readdir(dir1)) != NULL) { // read the content of dir 1
		if (strcmp(entry1->d_name, ".") == 0 || strcmp(entry1->d_name, "..") == 0)
			continue;
		char path1[1024], path2[1024];
		snprintf(path1, sizeof(path1), "%s/%s", old, entry1->d_name);
		snprintf(path2, sizeof(path2), "%s/%s", name, entry1->d_name);
		stat(path1, &stat1);
		rewinddir(dir2);
		int found = 0;
		while ((entry2 = readdir(dir2)) != NULL) { // read the content of directory two
			if (strcmp(entry2->d_name, entry1->d_name) == 0) {
				found = 1;
				break;
			}
		}
		if (!found) { // directory or file not found then it must have been deleted
			if (S_ISDIR(stat1.st_mode)) {
				printf("Directory removed: %s\n", path1);
				i = 0;
			}
			else {
				printf("File removed: %s\n", path1);
				i = 0;
			}
		}
		else { // if found the check wheather it is directory or file if file then compare it
			snprintf(path2, sizeof(path2), "%s/%s", name, entry2->d_name);
			stat(path2, &stat2);
			if (S_ISDIR(stat1.st_mode) && S_ISDIR(stat2.st_mode)) {
				access_file(path1, path2);
				i = 0;
			}
			else if (!S_ISDIR(stat1.st_mode) && !S_ISDIR(stat2.st_mode)) {
				compare(path1, path2);
				i = 0;
			}
		}
	}
	rewinddir(dir2); // rewind it to open directory
	while ((entry2 = readdir(dir2)) != NULL) { // opposite way reading
		if (strcmp(entry2->d_name, ".") == 0 || strcmp(entry2->d_name, "..") == 0)
			continue;
		char path1[1024], path2[1024];
		snprintf(path1, sizeof(path1), "%s/%s", old, entry2->d_name);
		snprintf(path2, sizeof(path2), "%s/%s", name, entry2->d_name);
		if (stat(path1, &stat1) == -1) { // check if exited earlier or not if not then it may be added directory or file
			stat(path2, &stat2);
			if (S_ISDIR(stat2.st_mode)) {
				printf("Directory added: %s\n", path2);
				i = 0;
			}
			else {
				printf("File added: %s\n", path2);
				storeFile(path2);
				i = 0;
			}
		}
	}
	closedir(dir1);
	closedir(dir2);
	return i;
}

void commit(char *a) {
	int i;
	char name[1024], old[1024];
	FILE *fp;
	fp = fopen("history.txt", "r"); // the history.txt file in read mode
	fscanf(fp, "%d", &i);
	fclose(fp);
	snprintf(name, sizeof(name), "./%s/commit%d", a, i); 
	snprintf(old, sizeof(old), "./%s/commit%d", a, i - 1);
	if(access_file(name, old)) {
		delete_fol(name); // if access_file return 1 then remove the folder
		fp = fopen("history.txt", "r+");
		fscanf(fp, "%d", &i);
		i--;
		rewind(fp);
		fprintf(fp, "%d", i);
		fclose(fp);
	}
}



