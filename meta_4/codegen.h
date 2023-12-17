#ifndef _CODEGEN_H
#define _CODEGEN_H

#include "ast.h"

void codegen_program(struct node *program);
void codegen_func_definition(struct node *node);
void codegen_func_declaration(struct node *node);
void codegen_declaration(struct node *node, int is_global, struct function *func);
void codegen_parameter_declarator(struct node *no, struct function *func);
void codegen_fuction_body(struct node *no, struct function *func);
void codegen_statement(struct node *statement, struct function *func);
void codegen_expr_comma(struct node *expr_comma_node, struct function *func);
int codegen_expression(struct node *expression, struct function *func);

int codegen_store(struct node *expression, struct function *func);


#endif