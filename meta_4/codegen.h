#ifndef _CODEGEN_H
#define _CODEGEN_H

#include "ast.h"

void codegen_program(struct node *program);
void codegen_func_definition(struct node *node);
void codegen_func_declaration(struct node *node);
void codegen_declaration(struct node *node, int is_global);
void codegen_parameter_declarator(struct node *no);
void codegen_fuction_body(struct node *no);
void codegen_statement(struct node *statement);
void codegen_expr_comma(struct node *expr_comma_node);
int codegen_expression(struct node *expression);

int codegen_decimal(struct node *expression);
int codegen_natural(struct node *expression);
int codegen_chrlit(struct node *expression);
int codegen_identifier(struct node *expression);
int codegen_plus(struct node *expression);
int codegen_minus(struct node *expression);
int codegen_or(struct node *expression);
int codegen_and(struct node *expression);
int codegen_mod(struct node *expression);
int codegen_bitwiseand(struct node *expression);
int codegen_bitwiseor(struct node *expression);
int codegen_bitwisexor(struct node *expression);
int codegen_add(struct node *expression);
int codegen_sub(struct node *expression);
int codegen_mul(struct node *expression);
int codegen_div(struct node *expression);
int codegen_eq(struct node *expression);
int codegen_ne(struct node *expression);
int codegen_lt(struct node *expression);
int codegen_gt(struct node *expression);
int codegen_le(struct node *expression);
int codegen_ge(struct node *expression);
int codegen_not(struct node *expression);
int codegen_store(struct node *expression);
int codegen_call(struct node *expression);

#endif