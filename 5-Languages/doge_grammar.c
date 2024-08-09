#include <stdio.h>
#include <stdlib.h>
#include "../mpc.h"

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
	/* Create some parsers. */
	mpc_parser_t* Adjective = mpc_new("adjective");
	mpc_parser_t* Noun      = mpc_new("noun");
	mpc_parser_t* Phrase    = mpc_new("phrase");
	mpc_parser_t* Doge      = mpc_new("doge");

	/* Define them with the following Language */
	mpca_lang(MPCA_LANG_DEFAULT,
		"																\
			adjective	: \"wow\" | \"many\"					\
							|  \"so\" | \"such\";				\
			noun			: \"lisp\" | \"language\"			\
							| \"book\" | \"build\" | \"c\";	\
			phrase		: <adjective> <noun>;				\
			doge			: <phrase>*;							\
		",
		Adjective, Noun, Phrase, Doge);

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
		} else {
         /* Otherwise Print the Error */
         mpc_err_print(r.error);
         mpc_err_delete(r.error);
      }
	
		free(input);
	}
	mpc_cleanup(4, Adjective, Noun, Phrase, Doge);
	return 0;
}
