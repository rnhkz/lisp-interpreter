#include <stdio.h>
#include <stdlib.h>

/* If we are compiling on Windows. compile these functions */
#ifdef _WIN32
#include <string.h>

static char input[2048];

/* Fake readline function */
char* realine(char* prompt)
{
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char* cpy = malloc(strlen(buffer)+1);
	strcpy(cpy, buffer);
	cpy[strlen(cpy)-1] = '\0';
	return cpy;
}

/* Fale add_history function */
void add_history(char* unused) {}

/* Otherwise include the editlines headers */
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char** argv)
{
	/* Print Version and Exit Information */
	puts("Lispy Version 0.0.0.0.1");
	puts("Press Ctrl+c to Exit\n");
	
	/* Input loop */
	while (1) {
		/* Now in either case, readline will be correctly defined. */
		char* input = readline("lispy> ");

		printf("No you're a %s\n", input);
		free(input);
	}

	return 0;
}
