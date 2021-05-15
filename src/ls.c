#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

char* target;
int files_read = 0;

bool list_all;
bool color;
int main(int argc, char** argv) {
	char* folders[1000];
	if (argc == 1 || argv[argc - 1][0] == '-') {
		target = ".";
	} else {
		target = argv[argc - 1];
	}

	for (int i = 0; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
				case 'a':
					list_all = true;
					break;
				case 'c':
					color = true;
					break;
			}
		}
	}

	DIR* directory;
	struct dirent* dir;
	directory = opendir(target);
	
	if (directory) {
		while ((dir = readdir(directory)) != NULL) {
			folders[files_read] = dir->d_name;
			files_read++;
		}
	}
	
	for (char c = 34; c < 127; c++) {
		for (int i = 0; i < files_read; i++) {
			if (folders[i][0] == c) {
				if (!list_all) {
					if (folders[i][0] == '.') {
							continue;
					}
				}

				if (color) {
					struct stat sb;
					if (!strcmp(folders[i], ".") || !strcmp(folders[i], "..")) {
						printf("\033[0;34m");
					} else if (stat(folders[i], &sb) == 0 && sb.st_mode & S_IFDIR) {
						printf("\033[1m\033[34m");
					} else if (stat(folders[i], &sb) == 0 && sb.st_mode & S_IXUSR) {
						printf("\033[1m\033[32m");
					}
				}

				printf("%s  \033[0m", folders[i]);
			}
		}
	}
	printf("\n");
	closedir(directory);
}
