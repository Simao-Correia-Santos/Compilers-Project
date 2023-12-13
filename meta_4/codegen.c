#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantics.h"
#include "codegen.h"

int temporary;

extern struct symbol_list *symbol_table;

void codegen_program(struct node *program){
  struct node* aux;

  printf("declare i32 @putchar(i32)\n");
  printf("declare i32 @getchar()\n");

  for (int i = 0; (aux = getchild(program, i)) != NULL; i++){
    if (aux->category == FuncDefinition)
      codegen_func_definition(aux);
    else if (aux->category == FuncDeclaration)
      codegen_func_declaration(aux);
    else if (aux->category == Declaration)
      codegen_declaration(aux);
  }
}

void codegen_func_definition(struct node *func_definition){
  struct node *typespec_node = getchild(func_definition, 0);
  struct node *identifier_node = getchild(func_definition, 1);

  if (typespec_node->category == Int || typespec_node->category == Short || typespec_node->category == Char)
    printf("define i32 ");
  else if (typespec_node->category == Double)
    printf("define double ");

  printf("@%s", identifier_node->token);

  codegen_parameter_declarator(getchild(func_definition, 2));
  codegen_fuction_body(getchild(func_definition, 3)); 
}

void codegen_func_declaration(struct node *func_declaration){}

void codegen_declaration(struct node *declaration){}

void codegen_parameter_declarator(struct node *parameter){}

void codegen_fuction_body(struct node *func_body){}

void codegen_statement(struct node *statement){}

void codegen_expr_comma(struct node *expr_comma){}

void codegen_expression(struct node *expression){}
