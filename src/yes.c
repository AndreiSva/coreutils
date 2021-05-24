#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

char* str;
int main(int argc, char** argv) {
	if (argc == 1) {
		str = "y";
	} else {
		str = argv[argc - 1];
	}

	while (true) {
		puts(str);
	}
}
