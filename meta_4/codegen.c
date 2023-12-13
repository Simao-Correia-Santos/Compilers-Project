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
      codegen_declaration(aux, 0);
  }
}

void codegen_func_definition(struct node *func_definition){
  struct node *typespec_node = getchild(func_definition, 0);
  struct node *identifier_node = getchild(func_definition, 1);

  if (typespec_node->category == Int || typespec_node->category == Short || typespec_node->category == Char)
    printf("define i32 ");
  else if (typespec_node->category == Double)
    printf("define double ");
  else if (typespec_node->category == Void)
    printf("define void ");

  printf("@%s", identifier_node->token);

  codegen_parameter_declarator(getchild(func_definition, 2));
  codegen_fuction_body(getchild(func_definition, 3)); 
}

void codegen_func_declaration(struct node *func_declaration){
  struct node *typespec_node = getchild(func_declaration, 0);
  struct node *identifier_node = getchild(func_declaration, 1);

  if (typespec_node->category == Int || typespec_node->category == Short || typespec_node->category == Char)
    printf("declare i32 ");
  else if (typespec_node->category == Double)
    printf("declare double ");
  else if (typespec_node->category == Void)
    printf("declare void ");
  
  printf("@%s", identifier_node->token);
  
  codegen_parameter_declarator(getchild(func_declaration, 2));
  printf("\n");
}

void codegen_declaration(struct node *declaration, int is_global){
  struct node *typespec_node = getchild(declaration, 0);
  struct node *identifier_node = getchild(declaration, 1);
  struct node *expr_comma_node = getchild(declaration, 2);

  if (is_global){
    printf("@%s = ", identifier_node->token);

    if (typespec_node->category == Int || typespec_node->category == Short || typespec_node->category == Char)
      printf("global i32 ");
    else if (typespec_node->category == Double)
      printf("global double ");

    if (expr_comma_node != NULL)
      codegen_expr_comma(expr_comma_node);
    else
      printf("0\n");
  }
  else {

  }
}

void codegen_parameter_declarator(struct node *parameter_list){
  struct node *param_decl, *typespec_node, *identifier_node;
  int pos = 0;
  
  printf("(");
  while((param_decl = getchild(parameter_list, pos)) != NULL){
    typespec_node = getchild(param_decl, 0);
    identifier_node = getchild(param_decl, 1);

    if (typespec_node->category == Void) //Só é void quando a função não tem parametros ex: int main(void)
      break;
    
    if (typespec_node->category == Int || typespec_node->category == Short || typespec_node->category == Char)
      printf("i32 ");
    else if (typespec_node->category == Double)
      printf("double ");
    
    if (identifier_node != NULL){
      printf("%%%s", identifier_node->token);
    }

    if(getchild(parameter_list, ++pos) != NULL)
      printf(", ");
  }
  printf(")");
}

void codegen_fuction_body(struct node *func_body){
  int pos = 0;
  struct node *son;

  printf("{\n");
  while((son = getchild(func_body, pos++)) != NULL){
    if (son->category == Declaration)
      codegen_declaration(son, 1);
    else
      codegen_statement(son);
  }
  printf("}");
}

void codegen_statement(struct node *statement){
  int statListPos = 0;
  struct node *sonStatList;
  struct node *body_if;
  struct node *body_else;
  struct node *body_while;
  struct node *expr_comma_node;

  switch (statement->category){
    case StatList:
      while((sonStatList = getchild(statement, statListPos++)) != NULL){
        codegen_statement(sonStatList);
      }
      break;
    
    case If:
      body_if = getchild(statement, 0);
      codegen_expr_comma(body_if);

      body_if = getchild(statement, 1);
      if (body_if != NULL){
        if (body_if->category == StatList || body_if->category == If || body_if->category == While || body_if->category == Return)
          codegen_statement(body_if);
        else
          codegen_expr_comma(body_if);
      }

      body_else = getchild(statement, 2);
      if (body_else != NULL){
        if (body_else->category == StatList || body_else->category == If || body_else->category == While || body_else->category == Return)
            codegen_statement(body_else);
        else
          codegen_expr_comma(body_else);
      }
      break;
    
    case While:
      body_while = getchild(statement, 0);
      codegen_expr_comma(body_while);

      body_while = getchild(statement, 1);
      if(body_while != NULL){
        if (body_while->category == StatList || body_while->category == If || body_while->category == While || body_while->category == Return)
          codegen_statement(body_while);
        else
          codegen_expr_comma(body_while);        
      }
      break;
    
    case Return:
      expr_comma_node = getchild(statement, 0);
      if(expr_comma_node->category != Null)
        codegen_expr_comma(expr_comma_node);
      break;
    
    default:
      codegen_expr_comma(statement);
      break;
  }
}

void codegen_expr_comma(struct node *expr_comma_node){
  struct node *son_1;
  struct node *son_2;

  if (expr_comma_node->category != Comma)
    codegen_expression(expr_comma_node);
  else {
    son_1 = getchild(expr_comma_node, 0);
    son_2 = getchild(expr_comma_node, 1);
    codegen_expr_comma(son_1);
    codegen_expr_comma(son_2);
  }
}

void codegen_expression(struct node *expression){
  struct node *son;
  struct node *son_2;
  int pos = 1;

  switch(expression->category){
    case Decimal:
      break;
    
    case Natural:
    case Chrlit:
      break;
    
    case Identifier:
      break;
    
    case Plus:
    case Minus:
      son = getchild(expression, 0);
      codegen_expression(son);
      break;
    
    case Or:
    case And:
    case Mod:
    case BitWiseAnd:
    case BitWiseOr:
    case BitWiseXor:
      son = getchild(expression, 0);
      son_2 = getchild(expression, 1);
      codegen_expression(son);
      codegen_expression(son_2);
      break;
    
    case Add:
    case Sub:
    case Mul:
    case Div:
      son = getchild(expression, 0);
      son_2 = getchild(expression, 1);
      codegen_expression(son);
      codegen_expression(son_2);
      break;
    
    case Eq:
    case Ne:
    case Lt:
    case Gt:
    case Le:
    case Ge:
      son = getchild(expression, 0);
      son_2 = getchild(expression, 1);
      codegen_expression(son);
      codegen_expression(son_2);
      break;
    
    case Not:
      son = getchild(expression, 0);
      codegen_expression(son);
      break;
    
    case Store:
      son = getchild(expression, 0);
      son_2 = getchild(expression, 1);
      codegen_expression(son);
      codegen_expression(son_2);
      break;
    
    case Call:
      son = getchild(expression, 0);
      codegen_expression(son);
      while ((son_2 = getchild(expression, pos++)) != NULL){
        codegen_expression(son_2);
      }
      break;
    
    default:
      break;
  }
}
