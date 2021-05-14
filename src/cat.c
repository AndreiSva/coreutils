#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool extra_flushyness = false;
short arg_start = 1;
int main(int argc, char** argv) {
	if (argc == 1) {
readfromstdin:
		;
		char* string = malloc(1000);
		size_t i = 1000;
		while (getline(&string, &i, stdin)) {
			printf("%s", string);
		}
		return 0;
	}

	if (argv[1][0] == '-') {
		switch (argv[1][1]) {
			case 'h':
				printf("Andrei CAT\n\
	-v | displays version information\n\
	-h | displays this help section\n\
	-u | flush stdout after every character for extra flushyness\n");
				return 0;
			case 'v':
				printf("Andrei's cat v1.0\n");
				return 0;
			case 'u':
				extra_flushyness = true;
				arg_start = 2;
				break;
			default:
				goto readfromstdin;
				break;
			}
		}

	for (int i = arg_start; i < argc; i++) {
		FILE* input_file = NULL;
		unsigned char chunk[5000];
		size_t bytesRead = 0;
		input_file = fopen(argv[i], "r");
		if (input_file != NULL) {
			while ((bytesRead = fread(chunk, 1, sizeof(chunk), input_file))) {
				for (int char_index = 0; char_index < bytesRead; char_index++) {
					putc(chunk[char_index], stdout);
					if (extra_flushyness == true) {
						fflush(stdout);
					}
				}		
			}
			fclose(input_file);	
		} else {
			puts("cat: error reading file");
			return 1;
		}
	}
}
