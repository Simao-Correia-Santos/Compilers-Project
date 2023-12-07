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
	struct node *node;
	struct params_list *parameters;
	struct params_list *variables;
};

struct symbols_list {
	struct function *function;
	struct params_list *variable;
	struct symbols_list *next;
};

void insert_putchar_getchar(struct node *node);
void check_program(struct node *program);
void check_func_definition(struct node *node);
void check_func_declaration(struct node *node);
void check_declaration(struct node *node, int is_global, struct function *function);
void check_parameter_declarator(struct node *no, struct function *function);
void check_fuction_body(struct node *no, struct function *function);
void check_statement(struct node *statement, struct function *function);
void check_expr_comma(struct node *expr_comma_node, struct function *func);
void check_expression(struct node *expression, struct function *func);

void get_comparison_annotation(char *tipo, struct node *node, struct node *params_list);
void get_annotation(struct symbols_list *symbol, struct node *node);
void get_expression_type(struct node *expression, char *son_1_type, char *son_2_type);
void conflict_types_func_var(char *type, struct node *func_definition, struct params_list *var);
int wrong_number_of_arguments(struct node *node, int num);
int is_int_short_char(char *type_1, char *type_2);
void operator_conflict_I(struct node *node);
void operator_conflict_II(struct node *expression, struct node *son_1, struct node *son_2);
void operator_conflict_III(struct node *expression, struct node *son_1, struct node *son_2);
void operator_conflic_IV(struct node *expression, struct node *son_1, struct node *son_2);
void conflicts_call(struct node *call);

struct symbols_list *insert_function_symbol(struct symbols_list *symbol_table, char *identifier, char *type);
struct symbols_list *search_function_symbol(struct symbols_list *table, char *identifier);
struct params_list *search_variable_symbol(struct symbols_list *table, char *identifier);
struct symbols_list *insert_variable_symbol(struct symbols_list *table, char *identifier, char *type);
struct params_list *search_local_variable(struct function *function, char *identifier);
struct params_list *insert_local_variable(struct function *function, char *type, char *identifier, struct node *node);
struct params_list *search_parameters_list(struct function *function, char *identifier);

void show_symbol_table();
void show_symbol_table_functions();

#endif
