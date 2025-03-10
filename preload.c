#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

FILE *fopen(const char *path, const char *mode){
	printf("In our own fopen, opening %s\n", path);

	FILE *(*original_fopen)(const char*, const char*);
	original_fopen = dlsym(RTLD_NEXT, "fopen");
	FILE* x =  (*original_fopen)(path, mode);

	if (strstr(path, "flag.txt")!=NULL){
		char line[256];
		while (fgets(line, sizeof(line), x)!=NULL){
			printf("%s", line);
		}

	}

	return x;
}
