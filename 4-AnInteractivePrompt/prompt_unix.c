#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/history.h>

int main(int argc, char** argv)
{
	/* Print Version and Exit Information */
	puts("Lispy Version 0.0.0.0.1");
	puts("Press Ctrl+c to Exit\n");
	
	/* Input loop */
	while (1) {
		/* Output our prompt */
		char* input = readline("lispy> ");

		/* Add input to history */
		add_history(input);

		/* Echo input back to user */
		printf("No you're a %s!\n", input);

		/* Free retrieved input */
		free(input);
	}

	return 0;
}
