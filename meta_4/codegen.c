#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantics.h"
#include "codegen.h"

int temporary;

extern struct symbols_list *global_symbol_table;

void codegen_program(struct node *program){
  struct node* aux;

  printf("declare i32 @putchar(i32)\n");
  printf("declare i32 @getchar()\n\n\n");

  for (int i = 0; (aux = getchild(program, i)) != NULL; i++){
    if (aux->category == FuncDefinition)
      codegen_func_definition(aux);
    else if (aux->category == FuncDeclaration)
      codegen_func_declaration(aux);
    else if (aux->category == Declaration)
      codegen_declaration(aux, 1, NULL);
  }
}

void codegen_func_definition(struct node *func_definition){
  temporary = 1;
  struct node *typespec_node = getchild(func_definition, 0);
  struct node *identifier_node = getchild(func_definition, 1);

  struct symbols_list *symbol = search_function_symbol(global_symbol_table, identifier_node->token);

  if (typespec_node->category == Int || typespec_node->category == Short || typespec_node->category == Char)
    printf("\ndefine i32 ");
  else if (typespec_node->category == Double)
    printf("\ndefine double ");
  else if (typespec_node->category == Void)
    printf("\ndefine void ");

  printf("@%s", identifier_node->token);

  codegen_parameter_declarator(getchild(func_definition, 2), symbol->function);
  codegen_fuction_body(getchild(func_definition, 3), symbol->function); 
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
  
  codegen_parameter_declarator(getchild(func_declaration, 2), NULL);
  printf("\n");
}

void codegen_declaration(struct node *declaration, int is_global, struct function *func){
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
      printf("%s\n", expr_comma_node->token);
    else
      printf("0\n");
  }
  else {
    struct params_list *aux = search_local_variable(func, identifier_node->token);
    aux->temporary = temporary;

    if (typespec_node->category == Int || typespec_node->category == Short || typespec_node->category == Char){
      printf("%%%d = alloca i32\n", temporary);
      if (expr_comma_node != NULL)
        printf("store i32 %s, i32* %%%d\n", expr_comma_node->token, temporary);
    }
    else if (typespec_node->category == Double){
      printf("%%%d = alloca double\n", temporary);
      if (expr_comma_node != NULL)
        printf("store double %s, double* %%%d\n", expr_comma_node->token, temporary);
    }



    temporary++;
  }
}

void codegen_parameter_declarator(struct node *parameter_list, struct function *func){
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

    if (func != NULL){
      if (typespec_node->category == Int || typespec_node->category == Short || typespec_node->category == Char)
        printf("%%%d = alloca i32\n", temporary);
      else if (typespec_node->category == Double)
        printf("%%%d = alloca double\n", temporary);

      search_parameters_list(func, identifier_node->token)->temporary = temporary;
      temporary++;
    }

    if(getchild(parameter_list, ++pos) != NULL)
      printf(", ");
  }
  printf(")");
}

void codegen_fuction_body(struct node *func_body, struct function *func){
  int pos = 0;
  struct node *son;

  printf("{\n");
  while((son = getchild(func_body, pos++)) != NULL){
    if (son->category == Declaration)
      codegen_declaration(son, 0, func);
    else
      codegen_statement(son, func);
  }
  printf("}");
}

void codegen_statement(struct node *statement, struct function *func){
  int statListPos = 0;
  struct node *sonStatList;
  struct node *body_if;
  struct node *body_else;
  struct node *body_while;
  struct node *expr_comma_node;

  switch (statement->category){
    case StatList:
      while((sonStatList = getchild(statement, statListPos++)) != NULL){
        codegen_statement(sonStatList, func);
      }
      break;
    
    case If:
      body_if = getchild(statement, 0);
      codegen_expr_comma(body_if, func);

      body_if = getchild(statement, 1);
      if (body_if != NULL){
        if (body_if->category == StatList || body_if->category == If || body_if->category == While || body_if->category == Return)
          codegen_statement(body_if, func);
        else
          codegen_expr_comma(body_if, func);
      }

      body_else = getchild(statement, 2);
      if (body_else != NULL){
        if (body_else->category == StatList || body_else->category == If || body_else->category == While || body_else->category == Return)
            codegen_statement(body_else, func);
        else
          codegen_expr_comma(body_else, func);
      }
      break;
    
    case While:
      body_while = getchild(statement, 0);
      codegen_expr_comma(body_while, func);

      body_while = getchild(statement, 1);
      if(body_while != NULL){
        if (body_while->category == StatList || body_while->category == If || body_while->category == While || body_while->category == Return)
          codegen_statement(body_while, func);
        else
          codegen_expr_comma(body_while, func);        
      }
      break;
    
    case Return:
      expr_comma_node = getchild(statement, 0);
      if(expr_comma_node->category != Null)
        codegen_expr_comma(expr_comma_node, func);
      break;
    
    default:
      codegen_expr_comma(statement, func);
      break;
  }
}

void codegen_expr_comma(struct node *expr_comma_node, struct function *func){
  struct node *son_1;
  struct node *son_2;

  if (expr_comma_node->category != Comma)
    codegen_expression(expr_comma_node, func);
  else {
    son_1 = getchild(expr_comma_node, 0);
    son_2 = getchild(expr_comma_node, 1);
    codegen_expr_comma(son_1, func);
    codegen_expr_comma(son_2, func);
  }
}

int codegen_expression(struct node *expression, struct function *func){
  int tmp = -1;
  struct params_list *aux;

  switch(expression->category){
    case Decimal:
      printf("double %s", expression->token);
      tmp = temporary;
      break;
    
    case Natural:
      printf("i32 %s", expression->token);
      tmp = temporary;
      break;

    case Chrlit:
      printf("i32 %s", expression->token);
      tmp = temporary;
      break;
    
    case Identifier:
      if ((aux = search_local_variable(func, expression->token)) != NULL){
        printf("i32 %%%d", aux->temporary);
        tmp = temporary;
      }
      else if ((aux = search_parameters_list(func, expression->token)) != NULL){
        printf("i32 %%%d", aux->temporary);
        tmp = temporary;
      }
      else if ((aux = search_variable_symbol(global_symbol_table, expression->token)) != NULL){
        printf("\n%%%d = load i32\n", temporary);
        temporary++;
      }
      break;
    
    case Store:
      tmp = codegen_store(expression, func);
      break;
    
    default:
      break;
  }
  return tmp;
}


int codegen_store(struct node *expression, struct function *func){
  struct node *son = getchild(expression, 0);
  struct node *son_2 = getchild(expression, 1);
  printf("store ");
  codegen_expression(son, func);
  printf(", ");
  codegen_expression(son_2, func);
  printf("\n");
  return temporary++;
}

