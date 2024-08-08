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
#include <editline/history.h>
#endif

int number_of_nodes(mpc_ast_t* t)
{
	if (t->children_num == 0) { return 1; }
	if (t->children_num >= 1) {
		int total = 1;
		for (int i = 0; i < t->children_num; i++) {
			total = total + number_of_nodes(t->children[i]);
		}
		return total;
	}
	return 0;
}

/* Use operator string to see which operation to perform */
long eval_op(long x, char* op, long y)
{
   if (strcmp(op, "+") == 0) { return x + y; }
   if (strcmp(op, "-") == 0) { return x - y; }
   if (strcmp(op, "*") == 0) { return x * y; }
   if (strcmp(op, "/") == 0) { return x / y; }
   return 0;
}


long eval (mpc_ast_t* t)
{
	/* If tagged as number return it directly */
	if (strstr(t->tag, "number")) {
		return atoi(t->contents);
	}
	
	/* The operator is always second child */
	char* op = t->children[1]->contents;
	
	/* We store the third child in 'x' */
	long x = eval(t->children[2]);

	int i = 3;
	while (strstr(t->children[i]->tag, "expr")) {
		x = eval_op(x, op, eval(t->children[i]));
		i++;
	}
	return x;
}

int main(int argc, char** argv)
{
	/* Create Some Parsers */
	mpc_parser_t* Adjetive = mpc_or(4,
		mpc_sym("wow"), mpc_sym("many"),
		mpc_sym("so"), mpc_sym("such")
	);

	mpc_parser_t* Noun = mpc_or(5,
      mpc_sym("lisp"), mpc_sym("language"),
      mpc_sym("book"), mpc_sym("build"),
		mpc_sym("c")
   );	

	mpc_parser_t* Phrase = mpc_and(2, mpcf_strfold,
		Adjetive, Noun, free);

	mpc_parser_t* Doge = mpc_many(mpcf_strfold, Phrase);

	/* Define them with the following Language */
//	mpca_lang(MPCA_LANG_DEFAULT,
//		"															\
//			adjetive	: \"wow\" | \"many\"					\
//						|  \"so\" | \"such\";				\
//			noun		: \"lisp\" | \"language\"			\
/						| \"book\" | \"build\" | \"c\";	\
/			phrase	: <adjetive> <noun>;					\
/			doge		: <phrase>*;							\
		",
//		Adjetive, Noun, Phrase, Doge);

	puts("Lispy Version 0.0.0.0.3");
	puts("Press Ctrl+c to Exit\n");
	
	/* Input loop */
	while (1) {
		char *input = readline("doge_lisp> ");
		add_history(input);
		mpc_result_t r;

		if (mpc_parse("<stdin>", input, Doge, &r)) {		
			long result = eval(r.output);
			printf("%li\n", result);
			mpc_ast_delete(r.output);
		}		
		else {
         /* Otherwise Print the Error */
         mpc_err_print(r.error);
         mpc_err_delete(r.error);
      }
	
		free(input);
	}
	mpc_cleanup(4, Adjetive, Noun, Phrase, Doge);
	return 0;
}
