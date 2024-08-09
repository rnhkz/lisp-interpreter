#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

/* If the program is being ran in Windows, compile these functions */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* Fake readline function */
char *readline(char *prompt)
{
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char *cpy = malloc(strlen(buffer)+1);
	strcpy(cpy, buffer);
	cpy[strlen(cpy)-1] = '\0';
	return cpy;
}

/* Fake add_history function */
void add_history(char *unised) {}

/* If not Windows, include the editline headers */
#else
#include <editline/readline.h>
#ifndef __APPLE__
#include <editline/history.h>
#endif
#endif

int main(int argc, char** argv)
{
	/* Create Some Parsers */
	mpc_parser_t* Adjective = mpc_or(4,
		mpc_sym("wow"), mpc_sym("many"),
		mpc_sym("so"), mpc_sym("such")
	);

	mpc_parser_t* Noun = mpc_or(5,
      mpc_sym("lisp"), mpc_sym("language"),
      mpc_sym("book"), mpc_sym("build"),
		mpc_sym("c")
   );	

	mpc_parser_t* Phrase = mpc_and(2, mpcf_strfold,
		Adjective, Noun, free);

	mpc_parser_t* Doge = mpc_many(mpcf_strfold, Phrase);


	puts("Lispy Version 0.0.0.0.3");
	puts("Press Ctrl+c to Exit\n");
	
	/* Input loop */
	while (1) {
		char *input = readline("doge_lisp> ");
		add_history(input);
		mpc_result_t r;

		if (mpc_parse("<stdin>", input, Doge, &r)) {		
			/* On Success Print the AST */
  			mpc_ast_print(r.output);
  			mpc_ast_delete(r.output);
		}		
		else {
         /* Otherwise Print the Error */
         mpc_err_print(r.error);
         mpc_err_delete(r.error);
      }
	
		free(input);
	}
	mpc_cleanup(4, Adjective, Noun, Phrase, Doge);
	return 0;
}
