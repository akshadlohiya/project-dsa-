#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "fvcs.h"

void storeFile(const char *filename) {
	FILE *fp = fopen(filename, "r"); // open the file filename in read mode 
	if(!fp) {
		printf("Cannot open the file\n");
		return;
	}
	char c, a[1024];
	int i = 1, j = 0;
	FILE *h = fopen("history.txt", "r"); // open the the file history.txt in read mode
	if(!h) {
		printf("Cannot open the file\n");
		fclose(fp);
		return;
	}
	if(fscanf(h, "%d", &j) != 1) { // scan the digit stored in the file history.txt
		printf("Not a valid format\n");
		fclose(h);
		fclose(fp);
	}
	fclose(h);
	snprintf(a, sizeof(a), "his%d.txt", j); // concate it with this
	h = fopen(a, "w"); // open the file a in write mode
	if(!h) {
		printf("Cannot open the file\n");
		fclose(fp);
		return;
	}
	fprintf(h, "in the file %s:\n%d>", filename, i); // the whole file
	while((c = getc(fp)) != EOF) {
		putc(c, h);
		if(c == '\n') {
			i++;
			fprintf(h, "%d>", i);
		}
	}
	fclose(fp);
	fclose(h);
}

void compare(const char *file1, const char *file2) {
	FILE *fp1 = fopen(file1, "r"), *fp2 = fopen(file2, "r"); // open both the file in read mode 
	int i = 1, j = 1, r1, r2;
	if(!fp1 || !fp2) {
		if(fp1)
			fclose(fp1);
		if(fp2)
			fclose(fp2);
		return;
	}
	char a[1024], b[1024];
	FILE *h = fopen("history.txt", "r"); // same as above
	if(!h) {
		printf("Cannot open the file\n");
		fclose(fp1);
		fclose(fp2);
		return;
	}
	char c[1024];
	int index;
	if(fscanf(h, "%d", &index) != 1) {
		printf("Not a valid format\n");
		fclose(h);
		fclose(fp1);
		fclose(fp2);
	}
	fclose(h);
	snprintf(c, sizeof(c), "his%d.txt", index); 
	h = fopen(c, "w");
	if(!h) {
		printf("Cannot open the file\n");
		fclose(fp1);
		fclose(fp2);
		return;
	}
	while(1) {
		r1 = !feof(fp1) && readline(a, sizeof(a), fp1);
		r2 = !feof(fp2) && readline(b, sizeof(b), fp2);
		if(r1 && r2) {
			if(strcmp(a, b) != 0) {
				fprintf(h, "The difference in the lines are:\n"); // it there difference between the line then print it
				fprintf(h, "in %s file : %d -> %s\n", file1, i, a);
				fprintf(h, "in %s file : %d -> %s\n", file2, j, b);
			}
			i++;
			j++;
		}
		else if(r1) {
			fprintf(h, "Added in file %s are :\n", file1); // if one file end the print the changes of it
			fprintf(h, "%d -> %s\n", i, a);
			i++;
			while(!feof(fp1) && readline(a, sizeof(a), fp1)) {
				fprintf(h, "%d -> %s\n", i, a);
				i++;
			}
			break;
		}
		else if(r2) {
			fprintf(h, "Removed in file %s are :\n", file2);
			fprintf(h, "%d -> %s\n", j, b);
			j++;
			while(!feof(fp1) && readline(b, sizeof(b), fp2)) {
				fprintf(h, "%d -> %s\n", j, b);
				j++;
			}
			break;
		}
		else {
			break;
		}
	}
	fclose(fp1);
	fclose(fp2);
	fclose(h);
	return;
}

int readline(char *a, int size, FILE *fp) { // this function readline in a txt file
	int i = 0;
	char c;
	while(i < size - 1) {
		c = getc(fp);
		if(c == EOF || c == '\n')
			break;
		a[i++] = c;
	}
	a[i++] = '\n'; 
	a[i] = '\0';
	return 1;
}
void save(hashtable *tab, const char *filename, int count) {
	FILE *file = fopen(filename, "wb"); // open the file in writing mode
	if (!file) {
		perror("Failed to open the file\n");
		return;
	}
	fwrite(&count, sizeof(int), 1, file); // save the counter
	if(strcmp(filename, "hname_id.txt") == 0) { // comparing if hname_id to filename because both contain different type of data
		for(int i = 0; i <= count; i++) { // looping through array of nodes
			node *n = tab->block[i]; // pointer to beggining of chain
			while(n) {
				int len = strlen(n->name); // copying the lenght of string name
				fwrite(&len, sizeof(int), 1, file); // storing it in binary file
				fwrite(n->name, sizeof(char), len, file); // storing name in binary file
				fwrite((unsigned int *)n->id, sizeof(unsigned int), 1, file); // storing id in binary file
				n = n->next; // next node
			}
		}
	}
	else {
		for(int i = 0; i <= count; i++) {
			node *n = tab->block[i]; //same as above but
			while(n) {
				int len = strlen(n->name);
				fwrite(&len, sizeof(int), 1, file);
				fwrite(n->name, sizeof(char), len, file);
				char *name = (char *)n->id; //coverting the void pointer to char *
				len = strlen(name); // copying the len of stirng 
				fwrite(&len, sizeof(int), 1, file); 
				fwrite(name, sizeof(char), len, file);
				n = n->next;
			}
		}
	}
	fclose(file);
	return;
}

void readp(hashtable *tab, const char *filename, int count) {
	FILE *file = fopen(filename, "rb"); // opening the file for reading
	if(!file) {
		return;
	}
	fread(&count, sizeof(int), 1, file); // read the counter
	if(strcmp(filename, "hname_id.txt") == 0) { // comparing if hname_id to filename because both contain different type of data
		while(1) {
			int len; 
			if(fread(&len, sizeof(int), 1, file) != 1) // if fread does not return 1 i.e end of file then break from loop
				break;
			char *name = (char *)malloc(len + 1); // initializing of char *name
			fread(name, sizeof(char), len, file); // reading from the binary file
			name[len] = '\0'; // initializing end of name to NULL
			int id;
			fread(&id, sizeof(id), 1, file); // reading id from binary file
			insert(tab, name, (void *)(&id)); // inserting the repo to hashmap node 
			free(name); // free the allocated memory
		}
	}
	else {
		while(1) { // same as but just change of data type
			int len;
			if(fread(&len, sizeof(int), 1, file) != 1)
				break;
			char *str = (char *)malloc(len + 1);
			fread(str, sizeof(char), len, file);
			str[len] = '\0';
			fread(&len, sizeof(int), 1, file);
			char *name = (char *)malloc(len + 1);
			fread(name, sizeof(char), len, file);
			name[len] = '\0';
			insert(tab, str, (void *)name);
			free(name); // free the allocated memory
			free(str); // free the allocated memory
		}
	}
	return;
}

void delete_fol(char *name) {
	char command[1024];
	snprintf(command, sizeof(command), "rm -r %s", name);
	int i = system(command);
	if(i == -1) {
		printf("cannot execute system command\n");
		return;
	}
	return;
}
