#ifndef _SEMANTICS_H
#define _SEMANTICS_H
#include "ast.h"

struct params_list {
	char *name;
	char *type;
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
void check_declaration(struct node *node, int is_global, struct function *function);
void check_parameter_declarator(struct node *no, struct function *function);
void check_fuction_body(struct node *no, struct function *function);
void check_statement();

struct symbols_list *insert_function_symbol(struct symbols_list *symbol_table, char *identifier, char *type);
struct symbols_list *search_function_symbol(struct symbols_list *table, char *identifier);
struct symbols_list *search_variable_symbol(struct symbols_list *table, char *identifier);
struct symbols_list *insert_variable_symbol(struct symbols_list *table, char *identifier, char *type);
struct function *search_local_variable(struct function *function, char *identifier);
struct params_list *insert_local_variable(struct function *function, char *type, char *identifier);
void show_symbol_table();
void show_symbol_table_functions();

#endif
