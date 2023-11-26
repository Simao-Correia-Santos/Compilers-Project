#ifndef _SEMANTICS_H
#define _SEMANTICS_H
#include "ast.h"

struct params_list {
	char *name;
	char *type;
	struct node *node;
	struct params_list *next;
};

struct function {
	int is_defined;
	char *name;
	char *type;
	struct params_list *parameters;
	struct params_list *variables;
};

struct symbols_list {
	struct function *function;
	struct params_list *variable;
	struct symbols_list *next;
};

void check_program(struct node *program);
void check_func_definition(struct node *node);
void check_func_declaration(struct node *node);
void check_declaration(struct node *node);
void check_parameter_declarator(struct node *no, struct params_list *parameters_list);
void check_fuction_body(struct node *no, struct params_list *variaveis_locais_list);

struct symbols_list *insert_function_symbol(struct symbols_list *symbol_table, char *identifier, char *type, struct node *node);
struct symbols_list *search_function_symbol(struct symbols_list *table, char *identifier);


#endif
