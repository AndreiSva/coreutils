#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>

struct stat st = {0};

bool verbose = false;

int main(int argc, char** argv) {
	if (argc == 1) {
		puts("error: not enough arguments");
		return 1;
	} else {
		for (int arg = 0;arg < argc; arg++) {
			if (argv[arg][0] == '-') {
				switch (argv[arg][1]) {
					case 'h':
				printf("Andrei's mkdir\n\
	-v | displays version information\n\
	-h | displays this help section\n\
	-V | verbose mode\n");
						return 0;
					case 'v':
						printf("Andrei's mkdir v1.0\n");
						return 0;
					case 'V':
						verbose = true;
						break;
				}
			}
		}
	}
	if (stat(argv[argc - 1], &st) == -1) {
		mkdir(argv[argc - 1], 0700);
	} else {
		puts("error: directory already exists");
		return 1;
	}

	if (verbose) {
		printf("created directory %s\n", argv[argc - 1]);
	}
}
