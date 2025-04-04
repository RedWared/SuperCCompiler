#include <stdio.h>
#include <stdlib.h>

const char *program;

void readFile(char *file){
	FILE *src = fopen(file, "r");

	if (!src) {
		printf("%s: fatal error: The input file '%s' doesn't exist.\n", program, file);
		exit(2);
	}

	fseek(src, 0, SEEK_END);
	long fileSize = ftell(src);
	rewind(src);
	char *code = (char *)malloc(fileSize);
	if (!code) {
		printf("%s: fatal error: Failure allocating memory.\n", program);
		fclose(src);
		exit(3);
	}

	int c = 1;
	while (fgets(code, fileSize, src)) {
		printf("%d: %s", c, code);
		c++;
	}

	free(code);
	fclose(src);
}

int main(int argc, char *argv[]){
	program = argv[0];

	if (argc < 2) {
		printf("%s: fatal error: no input file.\n", program);
		printf("compilation terminated.\n");
		return 1;
	}
	readFile(argv[1]);

	return 0;
}
