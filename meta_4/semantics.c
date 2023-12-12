#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantics.h"

struct symbols_list *global_symbol_table;

// Category names #defined in ast.h
char *category_names[] = names;

int semantic_errors = 0;

// Check Program
void check_program(struct node *program){
    struct node* aux;

    global_symbol_table = (struct symbols_list*)malloc(sizeof(struct symbols_list));
    global_symbol_table->function = NULL;
    global_symbol_table->variable = NULL;
    global_symbol_table->next = NULL;

    insert_putchar_getchar(program);

    for (int i = 0; (aux = getchild(program, i)) != NULL; i++){
        if (aux->category == FuncDefinition){
            check_func_definition(aux);
        }
        else if (aux->category == FuncDeclaration){
            check_func_declaration(aux);
        }
        else if (aux->category == Declaration){
            check_declaration(aux, 1, NULL);
        }
    }
}

void check_func_definition(struct node *func_definition){
    int void_parameters_flag;

    struct node *typespec_node = getchild(func_definition, 0);
    struct node *identifier_node = getchild(func_definition, 1);

    struct symbols_list *symbol = search_function_symbol(global_symbol_table, identifier_node->token);
    struct params_list *var = search_variable_symbol(global_symbol_table, identifier_node->token);

    if (symbol != NULL && symbol->function->is_defined == 1){
        printf("Line %d, column %d: Symbol %s already defined\n", identifier_node->token_line, identifier_node->token_column  , identifier_node->token);
        semantic_errors++;
        return;
    }
    if (var != NULL){
        conflict_types_func_var(category_names[typespec_node->category], getchild(func_definition, 2), var);
        return;
    }

    if ((void_parameters_flag = void_parameters(getchild(func_definition, 2))) == 1){
        return;
    }

    if (symbol != NULL){
        get_comparison_annotation(category_names[typespec_node->category], identifier_node, getchild(func_definition, 2));
        if (strcmp(identifier_node->annotation, symbol->function->node->annotation) != 0){
            printf("Line %d, column %d: Conflicting types (got %s, expected %s)\n", identifier_node->token_line, identifier_node->token_column  , identifier_node->annotation, symbol->function->node->annotation);
            return;
        }
    }

    if ((symbol == NULL && !void_parameters_flag) || symbol->function->is_defined == 0){
        if (symbol == NULL && !void_parameters_flag){
            symbol = insert_function_symbol(global_symbol_table, identifier_node->token, category_names[typespec_node->category]);
            symbol->function->node = identifier_node;
        }
        symbol->function->is_defined = 1;

        if (symbol->function->parameters != NULL){
            symbol->function->parameters = NULL;
        }
        check_parameter_declarator(getchild(func_definition, 2), symbol->function);

        if (identifier_node->annotation == NULL)
            get_annotation(symbol, identifier_node);

        check_fuction_body(getchild(func_definition, 3), symbol->function);
    }
}

void check_fuction_body(struct node *func_body, struct function *function){
    int pos = 0;
    struct node *son;

     while ((son = getchild(func_body, pos)) != NULL){
        if (son->category == Declaration){
            check_declaration(son, 0, function);
        }
        else {
            check_statement(son, function);
        }
        pos++;
     }
}

void check_func_declaration(struct node *func_declaration){
    int void_parameters_flag;
    
    struct node *typespec_node = getchild(func_declaration, 0);
    struct node *identifier_node = getchild(func_declaration, 1);

    struct symbols_list *symbol = search_function_symbol(global_symbol_table, identifier_node->token);

    if ((void_parameters_flag = void_parameters(getchild(func_declaration, 2))) == 1){
        return;
    }

    if (symbol == NULL && !void_parameters_flag){
        symbol = insert_function_symbol(global_symbol_table, identifier_node->token, category_names[typespec_node->category]);
        symbol->function->node = identifier_node;

        if (symbol->function->is_defined == 0)
            check_parameter_declarator(getchild(func_declaration, 2), symbol->function);
        
        if (identifier_node->annotation == NULL)
            get_annotation(symbol, identifier_node);
    }
    else if (symbol != NULL){
        get_comparison_annotation(category_names[typespec_node->category], identifier_node, getchild(func_declaration, 2));
        if (strcmp(identifier_node->annotation, symbol->function->node->annotation) != 0)
            printf("Line %d, column %d: Conflicting types (got %s, expected %s)\n",identifier_node->token_line, identifier_node->token_column  , identifier_node->annotation, symbol->function->node->annotation);
    }
}

void check_parameter_declarator(struct node *params_list, struct function *function){
    char aux[10];
    struct node *param_decl;
    int pos = 0;
    struct params_list *parameter_flag;

    while ((param_decl = getchild(params_list, pos)) != NULL){
        parameter_flag = NULL;
        struct node *typespec_node = getchild(param_decl, 0);
        struct node *identifier_node = getchild(param_decl, 1); //PODE SER NULL
        struct params_list *new = (struct params_list*) malloc(sizeof(struct params_list));
        new->printable = 1;
        if (identifier_node != NULL){
            new->name = identifier_node->token;
            if ((parameter_flag = search_parameters_list(function, identifier_node->token)) != NULL){
                printf("Line %d, column %d: Symbol %s already defined\n",identifier_node->token_line, identifier_node->token_column, identifier_node->token); 
                new->printable = 0;
            }
        }
        else 
            new->name = NULL;
        new->next = NULL;
        strcpy(aux, category_names[typespec_node->category]);
        aux[0] = aux[0]+32;
        new->type = strdup(aux);

        if (function->parameters == NULL){
            function->parameters = new;
        }
        else {
            struct params_list *aux = function->parameters;
            while (aux->next != NULL){
                aux = aux->next;
            }
            aux->next = new;
        }
        
        pos++;
    }
}

void check_declaration(struct node *declaration, int is_global, struct function *function){
    struct params_list *aux;
    char aux_type[10];

    struct node *typespec_node = getchild(declaration, 0);
    struct node *identifier_node = getchild(declaration, 1);
    struct node *expr_comma_node = getchild(declaration, 2);

    strcpy(aux_type, category_names[typespec_node->category]);
    aux_type[0] = aux_type[0] + 32;

    if (expr_comma_node != NULL){
        check_expr_comma(expr_comma_node, function);
        if ((strcmp(aux_type, "int") == 0 || strcmp(aux_type, "short") == 0 || strcmp(aux_type, "char") == 0) && (strcmp(expr_comma_node->type, "double") == 0))
            printf("Line %d, column %d: Conflicting types (got double, expected %s)\n",identifier_node->token_line, identifier_node->token_column, aux_type);
    }

    if (is_global && strcmp(category_names[typespec_node->category], "Void") != 0){
        if ((aux = search_variable_symbol(global_symbol_table, identifier_node->token)) == NULL)
            insert_variable_symbol(global_symbol_table, identifier_node->token, category_names[typespec_node->category]);
        else if(strcmp(aux->type, aux_type) != 0 && strcmp(aux->type, "double") == 0)
            printf("Line %d, column %d: Conflicting types (got %s, expected %s)\n",identifier_node->token_line, identifier_node->token_column  , aux_type, aux->type);
    }
    else if (!is_global && strcmp(category_names[typespec_node->category], "Void") != 0){
        if (search_parameters_list(function, identifier_node->token) == NULL && search_local_variable(function, identifier_node->token) == NULL)
            insert_local_variable(function, category_names[typespec_node->category], identifier_node->token, identifier_node);
        else
            printf("Line %d, column %d: Symbol %s already defined\n", identifier_node->token_line, identifier_node->token_column  , identifier_node->token);
    }
    
    if(strcmp(category_names[typespec_node->category], "Void") == 0){ 
        printf("Line %d, column %d: Invalid use of void type in declaration\n",identifier_node->token_line, identifier_node->token_column  );
    }
}

void check_statement(struct node *statement, struct function *function){
    int statListPos = 0;
    struct node *sonStatList;
    struct node *body_if;
    struct node *body_else;
    struct node *body_while;
    struct node *expr_comma_node;

    switch(statement->category){
        case StatList:
            while((sonStatList = getchild(statement, statListPos)) != NULL){
                check_statement(sonStatList, function);
                statListPos++;
            }
            break;

        case If:
            body_if = getchild(statement, 0);
            check_expr_comma(body_if, function);

            if (body_if->annotation != NULL)
                printf("Line %d, column %d: Conflicting types (got %s, expected int)\n",body_if->token_line, body_if->token_column, body_if->annotation);

            else if (strcmp(body_if->type, "undef") == 0 || strcmp(body_if->type, "void") == 0 || strcmp(body_if->type, "double") == 0){
                if(getchild(body_if, 1) != NULL)
                    printf("Line %d, column %ld: Conflicting types (got %s, expected int)\n",body_if->token_line, getchild(body_if,0)->token_column + strlen(getchild(body_if,0)->token), body_if->type);
                else{
                    printf("Line %d, column %d: Conflicting types (got %s, expected int)\n",body_if->token_line, body_if->token_column, body_if->type);
                }
            }

            body_if = getchild(statement, 1);
            if (body_if != NULL){
                if (body_if->category == StatList || body_if->category == If || body_if->category == While || body_if->category == Return){
                    check_statement(body_if, function);
                }
                else {
                    check_expr_comma(body_if, function);
                }
            }

            body_else = getchild(statement, 2);
            if (body_else != NULL){
                if (body_else->category == StatList || body_else->category == If || body_else->category == While || body_else->category == Return){
                    check_statement(body_else, function);
                }
                else{
                    check_expr_comma(body_else, function);
                }
            }
            break;


        case While:
            body_while = getchild(statement, 0);
            check_expr_comma(body_while, function);

            if(body_while->annotation != NULL)
                printf("Line %d, column %d: Conflicting types (got %s, expected int)\n", body_while->token_line, body_while->token_column, body_while->annotation);

            else if (strcmp(body_while->type, "undef") == 0 || strcmp(body_while->type, "void") == 0 || strcmp(body_while->type, "double") == 0)
                printf("Line %d, column %d: Conflicting types (got %s, expected int)\n", body_while->token_line, body_while->token_column  , body_while->type);

            body_while = getchild(statement, 1);
            if(body_while != NULL){
                if (body_while->category == StatList || body_while->category == If || body_while->category == While || body_while->category == Return){
                    check_statement(body_while, function);
                }
                else{
                    check_expr_comma(body_while, function);
                }
            }
            break;

        case Return:
            expr_comma_node = getchild(statement, 0);
            if(expr_comma_node->category != Null){
                check_expr_comma(expr_comma_node, function);
                if (expr_comma_node->annotation != NULL)
                    printf("Line %d, column %d: Conflicting types (got %s, expected %s)\n", expr_comma_node->token_line, expr_comma_node->token_column, expr_comma_node->annotation, function->type);
                else if (strcmp(function->type, "void") == 0 && strcmp(expr_comma_node->type, "void") != 0)
                    printf("Line %d, column %d: Conflicting types (got %s, expected void)\n", expr_comma_node->token_line, expr_comma_node->token_column, expr_comma_node->type);
                else if (strcmp(expr_comma_node->type, "double") == 0 && strcmp(function->type, "double") != 0)
                    printf("Line %d, column %d: Conflicting types (got double, expected %s)\n", expr_comma_node->token_line, expr_comma_node->token_column, function->type);
            }
            else if (strcmp(function->type, "void") != 0){
                    printf("Line %d, column %d: Conflicting types (got void, expected %s)\n", statement->token_line, statement->token_column  , function->type);
            } 
            break;

        default:
            check_expr_comma(statement, function);
            break;
    }
}

void check_expr_comma(struct node *expr_comma_node, struct function *func){
    struct node *son_1;
    struct node *son_2;

    if (expr_comma_node->category != Comma){
        check_expression(expr_comma_node, func);
    }
    else {
        son_1 = getchild(expr_comma_node, 0);
        son_2 = getchild(expr_comma_node, 1);
        check_expr_comma(son_1, func);
        check_expr_comma(son_2, func);

        if (son_1->annotation != NULL && son_2->annotation != NULL){
            expr_comma_node->type = "undef";
            printf("Line %d, column %d: Operator , cannot be applied to types %s, %s\n", expr_comma_node->token_line, expr_comma_node->token_column, son_1->annotation, son_2->annotation);
            return;
        }

        else if (son_2->annotation != NULL){
            expr_comma_node->type = "undef";
            printf("Line %d, column %d: Operator , cannot be applied to types %s, %s\n", expr_comma_node->token_line, expr_comma_node->token_column, son_1->type, son_2->annotation);
            return;
        }
        else if (son_1->annotation != NULL){
            expr_comma_node->type = strdup(son_2->type);
            printf("Line %d, column %d: Operator , cannot be applied to types %s, %s\n",expr_comma_node->token_line, expr_comma_node->token_column, son_1->annotation, son_2->type);
            return;
        }
        else if (strcmp(son_2->type, "undef") == 0){
            expr_comma_node->type = "undef";
            printf("Line %d, column %d: Operator , cannot be applied to types %s, %s\n",expr_comma_node->token_line, expr_comma_node->token_column, son_1->type, son_2->type);
            return;
        }
        else if (strcmp(son_1->type, "undef") == 0)
            printf("Line %d, column %d: Operator , cannot be applied to types %s, %s\n",expr_comma_node->token_line, expr_comma_node->token_column, son_1->type, son_2->type);
       
        expr_comma_node->type = strdup(son_2->type);
    }
}

void check_expression(struct node *expression, struct function *func){  
    struct symbols_list *symbol;
    struct params_list *aux_list;
    struct params_list *aux_list_2;
    struct node *son;
    struct node *son_2;
    int pos = 1;

    switch(expression->category){
        case Decimal:
            expression->type = "double";
            break;
        
        case Natural:
        case Chrlit:
            expression->type = "int";
            break;
        
        case Identifier:
            if (func != NULL){
                aux_list = search_local_variable(func, expression->token);
                if (aux_list != NULL){
                    expression->type = strdup(aux_list->type);
                    return;
                }
                else {
                    aux_list = search_parameters_list(func, expression->token);
                    if (aux_list != NULL){
                        expression->type = strdup(aux_list->type);
                        return;
                    }
                    else if ((aux_list_2 = search_variable_symbol(global_symbol_table, expression->token)) != NULL){
                        expression->type = strdup(aux_list_2->type);
                        return;
                    }
                }
            }
            symbol = search_function_symbol(global_symbol_table, expression->token);
            if (symbol != NULL){
                aux_list = symbol->function->parameters;
                get_annotation(symbol, expression);
                expression->type = symbol->function->type;
            }
            else {
                expression->type = "undef";
                printf("Line %d, column %d: Unknown symbol %s\n", expression->token_line, expression->token_column  , expression->token);
            }
            break;

        case Plus:
        case Minus:
            son = getchild(expression, 0);
            check_expression(son, func);
            expression->type = strdup(son->type);
            operator_conflict_I(expression, son);
            break;

        case Or:
        case And:
        case Mod:
        case BitWiseAnd:
        case BitWiseOr:
        case BitWiseXor:
            son = getchild(expression, 0);
            son_2 = getchild(expression, 1);
            check_expression(son, func);
            check_expression(son_2, func);
            expression->type = "int";
            operator_conflict_II(expression, son, son_2);
            break;

        case Add:
        case Sub:
        case Mul:
        case Div:
            son = getchild(expression, 0);
            son_2 = getchild(expression, 1);
            check_expression(son, func);
            check_expression(son_2, func);
            get_expression_type(expression, son, son_2);
            operator_conflict_III(expression, son, son_2);
            break;

        case Eq:
        case Ne:
        case Lt:
        case Gt:
        case Le:
        case Ge:
            son = getchild(expression, 0);
            son_2 = getchild(expression, 1);
            check_expression(son, func);
            check_expression(son_2, func);
            expression->type = "int";
            operator_conflict_IV(expression, son, son_2);
            break;

        case Not:
            son = getchild(expression, 0);
            check_expression(son, func);
            expression->type = "int";
            operator_conflict_V(son, expression);
            break;

        case Store:
            son = getchild(expression, 0);
            son_2 = getchild(expression, 1);
            check_expression(son, func);
            check_expression(son_2, func);
            expression->type = strdup(son->type);
            if (strcmp(category_names[son->category], "Identifier") != 0)
                printf("Line %d, column %d: Lvalue required\n", expression->token_line, son->token_column);
            else {
                operator_conflic_VI(expression, son, son_2);
            }
            break;
        
        case Call:
            son = getchild(expression, 0);
            check_expression(son, func);
            expression->type = strdup(son->type);
            while ((son_2 = getchild(expression, pos)) != NULL){
                check_expression(son_2, func);
                pos += 1;
            }
            if (wrong_number_of_arguments(expression, pos-1) == 0){
                conflicts_call(expression);
            }
            break;
        
        default:
            break;
    }
}



int void_parameters(struct node *params_list){
    struct node *param_decl;
    int pos = 0;

    while ((param_decl = getchild(params_list, pos)) != NULL){
        struct node *typespec_node = getchild(param_decl, 0);
        
        if (pos == 0 && getchild(params_list, pos+1) != NULL && strcmp(category_names[typespec_node->category], "Void") == 0){
            printf("Line %d, column %d: Invalid use of void type in declaration\n", typespec_node->token_line, typespec_node->token_column);
            return 1;
        }
        else if (strcmp(category_names[typespec_node->category], "Void") == 0 && pos != 0){
            printf("Line %d, column %d: Invalid use of void type in declaration\n", typespec_node->token_line, typespec_node->token_column);
            return 1;
        }
        else if (pos == 0 && strcmp(category_names[typespec_node->category], "Void") == 0 && getchild(param_decl, 1) != NULL){
            printf("Line %d, column %d: Invalid use of void type in declaration\n", typespec_node->token_line, typespec_node->token_column);
            return 1;
        }
        pos += 1;
    }
    return 0;
}

void get_comparison_annotation(char *tipo, struct node *node, struct node *params_list){
    struct node *aux_node;
    char buffer[128] = "";
    char aux[10];
    int pos = 0;
    
    strcpy(aux, tipo);
    aux[0] = aux[0] + 32;

    strcat(buffer, aux);
    strcat(buffer, "(");

    while((aux_node = getchild(params_list, pos)) != NULL){
        strcpy(aux, category_names[getchild(aux_node, 0)->category]);
        aux[0] = aux[0] + 32;
        strcat(buffer, aux);
        if (getchild(params_list, pos+1) != NULL)
            strcat(buffer, ",");
        pos += 1;
    }
    strcat(buffer, ")");
    node->annotation = strdup(buffer);
}

void get_annotation(struct symbols_list *symbol, struct node *node){
    char buffer[128] = "";
    struct params_list *aux_list = symbol->function->parameters;

    strcat(buffer, symbol->function->type);
    strcat(buffer, "(");
    while (aux_list != NULL){
        strcat(buffer, aux_list->type);
        if (aux_list->next != NULL)
            strcat(buffer, ",");
        aux_list = aux_list->next;
    }
    strcat(buffer, ")");
    node->annotation = strdup(buffer);
}

void get_expression_type(struct node *expression, struct node *son_1, struct node *son_2){
    if (son_1->annotation != NULL || son_2->annotation != NULL){
        expression->type = "undef";
        return;
    }
    else if (strcmp(son_1->type, "undef") == 0 || strcmp(son_2->type, "undef") == 0 || strcmp(son_1->type, "void") == 0 || strcmp(son_2->type, "void") == 0)
        expression->type = "undef";
    else if (strcmp(son_1->type, "double") == 0 || strcmp(son_2->type, "double") == 0)
        expression->type = "double";
    else if (strcmp(son_1->type, "int") == 0 || strcmp(son_2->type, "int") == 0)
        expression->type = "int";
    else if (strcmp(son_1->type, "short") == 0 || strcmp(son_2->type, "short") == 0)
        expression->type = "short";
    else if (strcmp(son_1->type, "char") == 0 || strcmp(son_2->type, "char") == 0)
        expression->type = "char";
}

void conflict_types_func_var(char *type, struct node *param_list, struct params_list *var){
    char aux_type[10];
    struct node *param_declarator;
    int pos = 0;

    strcpy(aux_type, type);
    aux_type[0] = aux_type[0] + 32;
    printf("Line %d, column %d: Conflicting types (got %s(", param_list->token_line, param_list->token_column  , aux_type);

    while ((param_declarator = getchild(param_list, pos)) != NULL){
        if (pos |= 0)
            printf(",");
        strcpy(aux_type, category_names[getchild(param_declarator, 0)->category]);
        aux_type[0] = aux_type[0] + 32;
        printf("%s", aux_type);
        pos += 1;
    }
    printf("), expected %s)\n", var->type);
}

int wrong_number_of_arguments(struct node *node, int got){
    int required = 0;
    int pos = 0;

    struct symbols_list *symbol = search_function_symbol(global_symbol_table, getchild(node, 0)->token);
    if (symbol != NULL){
        struct params_list *aux = symbol->function->parameters;
        while (aux != NULL){
            required += 1;
            aux = aux->next;
        }
        if (required == 1 && strcmp(symbol->function->parameters->type, "void") == 0)
            required = 0;
        if (got != required){
            printf("Line %d, column %d: Wrong number of arguments to function %s (got %d, required %d)\n",getchild(node, 0)->token_line, getchild(node, 0)->token_column  ,  symbol->function->name, got, required);
            return 1;
        }
    }
    else {
        while(getchild(node, pos+1) != NULL)
            pos += 1;
        return 1;
    }
    return 0;
}

void operator_conflict_I(struct node *node, struct node *son){
    char *operator = (char*)malloc(sizeof(char));
    switch (node->category){
        case Minus:
            operator = "-";
            break;
        case Plus:
            operator = "+";
            break;
        default:
            break;
    }
    if (strcmp(node->type, "void") == 0 || strcmp(node->type, "undef") == 0){
        if (son->annotation != NULL)
            printf("Line %d, column %d: Operator %s cannot be applied to type %s\n", node->token_line, node->token_column, operator, son->annotation);
        else 
            printf("Line %d, column %d: Operator %s cannot be applied to type %s\n", node->token_line, node->token_column, operator, node->type);
    }
}

void operator_conflict_II(struct node *expression, struct node *son_1, struct node *son_2){
    char *operator = (char*)malloc(sizeof(char)*2);

    switch (expression->category){
        case BitWiseAnd:
            operator = "&";
            break;
        case BitWiseOr:
            operator = "|";
            break;
        case BitWiseXor:
            operator = "^";
            break;
        case Or:
            operator = "||";
            break;
        case And:
            operator = "&&";
            break;
        case Mod:
            operator = "%";
            break;
        default:
            break;
    }

    if (son_1->annotation != NULL && son_2->annotation != NULL)
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->token_line, expression->token_column, operator, son_1->annotation, son_2->annotation);
    else if (son_1->annotation != NULL)
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->token_line, expression->token_column, operator, son_1->annotation, son_2->type);
    else if (son_2->annotation != NULL)
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->token_line, expression->token_column, operator, son_1->type, son_2->annotation);

    else if (strcmp(son_1->type, "undef") == 0 || strcmp(son_2->type, "undef") == 0 || strcmp(son_1->type, "void") == 0 || strcmp(son_2->type, "void") == 0 || strcmp(son_1->type, "double") == 0 || strcmp(son_2->type, "double") == 0){ 
        printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->token_line, expression->token_column, operator, son_1->type, son_2->type);
    }     
}

void operator_conflict_III(struct node *expression, struct node *son_1, struct node *son_2){
    char *operator = (char*)malloc(sizeof(char));

    switch(expression->category){
        case Add:
            operator = "+";
            break;
        case Sub:
            operator = "-";
            break;
        case Mul:
            operator = "*";
            break;
        case Div:
            operator = "/";
            break;
        default:
            break;
    }
    if (strcmp(expression->type, "undef") == 0){
       if (son_1->annotation != NULL && son_2->annotation != NULL)
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->token_line, expression->token_column, operator, son_1->annotation, son_2->annotation);
        else if (son_1->annotation != NULL)
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->token_line, expression->token_column, operator, son_1->annotation, son_2->type);
        else if (son_2->annotation != NULL)
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->token_line, expression->token_column, operator, son_1->type, son_2->annotation);
        else
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->token_line, expression->token_column, operator, son_1->type, son_2->type);
    }
}

void operator_conflict_IV(struct node *expression, struct node *son_1, struct node *son_2){
    char *operator = (char*)malloc(sizeof(char)*2);

    switch(expression->category){
        case Eq:
            operator = "==";
            break;
        case Ne:
            operator = "!=";
            break;
        case Lt:
            operator = "<";
            break;
        case Gt:
            operator = ">";
            break;
        case Le:
            operator = "<=";
            break;
        case Ge:
            operator = ">=";
            break;
        default:
            break;
    }
    if ((strcmp(son_1->type, "undef") != 0 || strcmp(son_2->type, "undef") != 0) && (strcmp(son_1->type, "undef") == 0 || strcmp(son_1->type, "void") == 0 || strcmp(son_2->type, "undef") == 0 || strcmp(son_2->type, "void") == 0)){
        if (son_1->annotation != NULL && son_2->annotation != NULL)
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->token_line, expression->token_column, operator, son_1->annotation, son_2->annotation);
        else if (son_1->annotation != NULL)
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->token_line, expression->token_column, operator, son_1->annotation, son_2->type);
        else if (son_2->annotation != NULL)
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->token_line, expression->token_column, operator, son_1->type, son_2->annotation);
        else
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->token_line, expression->token_column, operator, son_1->type, son_2->type);
    }
}

void operator_conflict_V(struct node *node, struct node *expr){
    if (node->annotation != NULL)
    {
        printf("Line %d, column %d: Operator ! cannot be applied to type %s\n", expr->token_line, expr->token_column, node->annotation);
    }
    else if (strcmp(node->type, "int") != 0 && strcmp(node->type, "char") != 0 && strcmp(node->type, "short") != 0){
        if (node->annotation == NULL)
            printf("Line %d, column %d: Operator ! cannot be applied to type %s\n", expr->token_line, expr->token_column, node->type);
        else
            printf("Line %d, column %d: Operator ! cannot be applied to type %s\n", expr->token_line, expr->token_column, node->annotation);
    }
}

void operator_conflic_VI(struct node *expression, struct node *son_1, struct node *son_2){
    int flag = 0;
    if ((strcmp(son_2->type, "double") == 0 && strcmp(son_1->type, "double") != 0)){
        printf("Line %d, column %d: Operator = cannot be applied to types ", expression->token_line, expression->token_column);
        flag = 1;
    }
    else if (strcmp(son_1->type, "undef") == 0 || strcmp(son_1->type, "void") == 0 || strcmp(son_2->type, "undef") == 0 || strcmp(son_2->type, "void") == 0){
        printf("Line %d, column %d: Operator = cannot be applied to types ", expression->token_line, expression->token_column); 
        flag = 1;
    }

    if (flag && (son_1->annotation != NULL || strcmp(son_1->type, "undef") == 0))
        expression->type = "undef";

    if (flag && son_1->annotation != NULL && son_2->annotation != NULL)
        printf("%s, %s\n", son_1->annotation, son_2->annotation);
    else if (flag && son_1->annotation != NULL)
        printf("%s, %s\n", son_1->annotation, son_2->type);
    else if (flag && son_2->annotation != NULL)
        printf("%s, %s\n", son_1->type, son_2->annotation);
    else if (flag)
        printf("%s, %s\n", son_1->type, son_2->type);
}

void conflicts_call(struct node *call){
    struct params_list *params = search_function_symbol(global_symbol_table, getchild(call, 0)->token)->function->parameters;
    struct node *aux;
    int pos = 1;

    while ((aux = getchild(call, pos)) != NULL){
        if (strcmp(aux->type, "undef") == 0 || strcmp(aux->type, "void") == 0 || (strcmp(aux->type, "double") == 0 && strcmp(params->type, "double") != 0)){
            if (aux->annotation == NULL){
                printf("Line %d, column %d: Conflicting types (got %s, expected %s)\n", aux->token_line, aux->token_column , aux->type, params->type);
            }
            else 
                printf("Line %d, column %d: Conflicting types (got %s, expected %s)\n", aux->token_line, aux->token_column  , aux->annotation, params->type);
        }
        pos += 1;
        params = params->next;
    }
}




// Insert putchar and getchar function´
void insert_putchar_getchar(struct node *node){
    struct symbols_list *putchar = insert_function_symbol(global_symbol_table, "putchar", "Int");
    putchar->function->parameters = (struct params_list *) malloc(sizeof(struct params_list));
    putchar->function->parameters->type = "int";
    putchar->function->parameters->name = NULL;
    putchar->function->parameters->next = NULL;

    struct symbols_list *getchar = insert_function_symbol(global_symbol_table, "getchar", "Int");
    getchar->function->parameters = (struct params_list *) malloc(sizeof(struct params_list));
    getchar->function->parameters->type = "void";
    getchar->function->parameters->name = NULL;
    getchar->function->parameters->next = NULL;
}   

// Insert a new function symbol in the list, unless it is already there
struct symbols_list *insert_function_symbol(struct symbols_list *table, char *identifier, char *type) {
    char aux_type[10];
    strcpy(aux_type, type);
    aux_type[0] = aux_type[0] + 32;

    struct symbols_list *new = (struct symbols_list *) malloc(sizeof(struct symbols_list));
    new->variable = NULL;
    new->function = (struct function*) malloc(sizeof(struct function));
    new->function->name = strdup(identifier);
    new->function->is_defined = 0;
    new->function->type = strdup(aux_type);
    new->function->parameters = NULL;
    new->function->variables = NULL;
    new->next = NULL;

    struct symbols_list *symbol = table;
    while(symbol != NULL) {
        if(symbol->next == NULL) {
            symbol->next = new;    /* insert new symbol at the tail of the list */
            break;
        } else if(symbol->function != NULL && strcmp(symbol->function->name, identifier) == 0) {
            free(new);
            return NULL;           /* return NULL if symbol is already inserted */
        }
        symbol = symbol->next;
    }
    return symbol->next;
}

// Look up a function symbol by its identifier
struct symbols_list *search_function_symbol(struct symbols_list *table, char *identifier) {
    struct symbols_list *symbol = table->next;
    while (symbol != NULL){
        if(symbol->function != NULL && strcmp(symbol->function->name, identifier) == 0)
            return symbol;
        symbol = symbol->next;
    }
    return NULL;
}

//Look up a variable symbol by its identifier
struct params_list *search_variable_symbol(struct symbols_list *table, char *identifier){
    struct symbols_list *symbol = table->next;
    while (symbol != NULL){
        if(symbol->variable != NULL && strcmp(symbol->variable->name, identifier) == 0)
            return symbol->variable;
        symbol = symbol->next;
    }
    return NULL;
}

// Insert a new variable symbol in the list, unless it is already there
struct symbols_list *insert_variable_symbol(struct symbols_list *table, char *identifier, char *type) {
    char aux_type[10];

    strcpy(aux_type, type);
    aux_type[0] = aux_type[0] + 32;
    
    struct symbols_list *new = (struct symbols_list *) malloc(sizeof(struct symbols_list));
    new->function = NULL;
    new->variable = (struct params_list*) malloc(sizeof(struct params_list));
    new->variable->name = strdup(identifier);
    new->variable->type = strdup(aux_type);
    new->variable->next = NULL;
    new->next = NULL;

    struct symbols_list *symbol = table;
    while(symbol != NULL) {
        if(symbol->next == NULL) {
            symbol->next = new;    /* insert new symbol at the tail of the list */
            break;
        } else if(symbol->variable != NULL && strcmp(symbol->variable->name, identifier) == 0) {
            free(new);
            return NULL;           /* return NULL if symbol is already inserted */
        }
        symbol = symbol->next;
    }
    return new;
}

// Look up a variable symbol by its identifier inside a function
struct params_list *search_local_variable(struct function *function, char *identifier){
    struct params_list *aux = function->variables;
    while (aux != NULL){
        if(strcmp(aux->name, identifier) == 0)
            return aux;
        aux = aux->next;
    }
    return NULL;
}

// Insert e new local variable in the list, unless it is already there
struct params_list *insert_local_variable(struct function *function, char *type, char *identifier, struct node *node){
    char aux_type[10];

    strcpy(aux_type, type);
    aux_type[0] = aux_type[0] + 32;


    struct params_list *new = (struct params_list *) malloc(sizeof(struct params_list));
    new->name= strdup(identifier);
    new->type = strdup(aux_type);
    new->next = NULL;

    struct function *aux_function = function;

    if (aux_function->variables == NULL){
            function->variables = new;
    }
    else {
        if(strcmp(aux_function->variables->name, identifier) == 0) {
            printf("Line %d column %d: Symbol %s already defined\n", node->token_line, node->token_column  , identifier);
            free(new);
            return NULL;
        } 
        struct params_list *aux_list = aux_function->variables;
        while (aux_list->next != NULL){
            aux_list = aux_list->next;
        }
        aux_list->next = new;
    }
    return new;
}

// Look up a parameter symbol by its identifier inside a function
struct params_list *search_parameters_list(struct function *function, char *identifier){
    struct params_list *aux = function->parameters;

    while (aux != NULL && strcmp(aux->type, "void") != 0){
        if (strcmp(aux->name, identifier) == 0){
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

// Show Global Tabel
void show_symbol_table(){
    struct symbols_list *aux = global_symbol_table;

    printf("===== Global Symbol Table =====\n");
    while ((aux = aux->next) != NULL){
        if (aux->function != NULL){
            struct params_list *aux_list = aux->function->parameters;
            printf("%s\t%s(", aux->function->name, aux->function->type);
            while (aux_list != NULL){
                printf("%s", aux_list->type);
                if (aux_list->next != NULL){
                    printf(",");
                }
                aux_list = aux_list->next;
            }
            printf(")\n");
        }
        else 
            printf("%s\t%s\n", aux->variable->name, aux->variable->type);
    }
    printf("\n");
    show_symbol_table_functions();
}

// Show Function Table
void show_symbol_table_functions(){
    struct symbols_list *aux = global_symbol_table;
    while((aux = aux->next) != NULL){
        if(aux->function != NULL && aux->function->is_defined){
            printf("===== Function %s Symbol Table =====\n", aux->function->name);
            printf("return\t%s\n",aux->function->type);
            while(aux->function->parameters != NULL){
                if (strcmp(aux->function->parameters->type, "void") != 0 && (aux->function->parameters->printable))
                    printf("%s\t%s\tparam\n", aux->function->parameters->name, aux->function->parameters->type);
                aux->function->parameters = aux->function->parameters->next;
            }
            while(aux->function->variables != NULL){
                if (strcmp(aux->function->variables->type, "void") != 0)
                    printf("%s\t%s\n", aux->function->variables->name, aux->function->variables->type);
                aux->function->variables = aux->function->variables->next;
            }
            printf("\n");
        }
    }
}
