#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantics.h"

struct symbols_list *global_symbol_table;

// Category names #defined in ast.h
char *category_names[] = names;

// Check Programa
void check_program(struct node *program){
    struct node* aux;

    global_symbol_table = (struct symbols_list*)malloc(sizeof(struct symbols_list));
    global_symbol_table->function = NULL;
    global_symbol_table->variable = NULL;
    global_symbol_table->next = NULL;

    insert_putchar_getchar();

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
    struct node *typespec_node = getchild(func_definition, 0);
    struct node *identifier_node = getchild(func_definition, 1);

    struct symbols_list *symbol = search_function_symbol(global_symbol_table, identifier_node->token);
    struct params_list *var = search_variable_symbol(global_symbol_table, identifier_node->token);

    if (symbol != NULL && symbol->function->is_defined == 1){
        printf("Symbol %s already defined\n", identifier_node->token);
        return;
    }
    if (var != NULL){
        conflict_types_func_var(category_names[typespec_node->category], getchild(func_definition, 2), var);
        return;
    }

    if (symbol == NULL || symbol->function->is_defined == 0){
        if (symbol == NULL)
            symbol = insert_function_symbol(global_symbol_table, identifier_node->token, category_names[typespec_node->category]);
        symbol->function->is_defined = 1;

        if (symbol->function->parameters != NULL){
            symbol->function->parameters = NULL;
        }
        check_parameter_declarator(getchild(func_definition, 2), symbol->function);

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
    struct symbols_list *symbol;

    struct node *typespec_node = getchild(func_declaration, 0);
    struct node *identifier_node = getchild(func_declaration, 1);

    if (search_function_symbol(global_symbol_table, identifier_node->token) == NULL){
        symbol = insert_function_symbol(global_symbol_table, identifier_node->token, category_names[typespec_node->category]);

        if (symbol->function->is_defined == 0){
           check_parameter_declarator(getchild(func_declaration, 2), symbol->function);
        }
    }
}

void check_parameter_declarator(struct node *params_list, struct function *function){
    char aux[10];
    struct node *param_decl;
    int pos = 0;

    while ((param_decl = getchild(params_list, pos)) != NULL){
        struct node *typespec_node = getchild(param_decl, 0);
        struct node *identifier_node = getchild(param_decl, 1); //PODE SER NULL
        
        if (pos == 0 && getchild(params_list, pos+1) != NULL && strcmp(category_names[typespec_node->category], "Void") == 0)
            printf("Invalid use of void type in declaration\n");
        else if (strcmp(category_names[typespec_node->category], "Void") == 0 && pos != 0)
            printf("Invalid use of void type in declaration\n");

        struct params_list *new = (struct params_list*) malloc(sizeof(struct params_list));
        if (identifier_node != NULL)
            new->name = identifier_node->token;
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
    struct node *typespec_node = getchild(declaration, 0);
    struct node *identifier_node = getchild(declaration, 1);
    struct node *expr_comma_node = getchild(declaration, 2);

    if (strcmp(category_names[typespec_node->category], "Void") == 0){
        printf("Invalid use of void type in declaration\n");
    }

    else if (is_global && search_variable_symbol(global_symbol_table, identifier_node->token) == NULL){
        insert_variable_symbol(global_symbol_table, identifier_node->token, category_names[typespec_node->category]);
    }
    else if (!is_global && search_local_variable(function, identifier_node->token) == NULL){
        insert_local_variable(function, category_names[typespec_node->category], identifier_node->token);
    }

    if (expr_comma_node != NULL){
        check_expr_comma(expr_comma_node, function);
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
                check_expr_comma(sonStatList, function);
                statListPos++;
            }
            break;

        case If:
            check_expr_comma(getchild(statement, 0), function);

            body_if = getchild(statement, 1);
            if (body_if != NULL){
                if (body_if->category == StatList){
                    check_statement(body_if, function);
                }
                else {
                    check_expr_comma(body_if, function);
                }
            }

            body_else = getchild(statement, 2);
            if (body_else != NULL){
                if (body_else->category == StatList){
                    check_statement(body_else, function);
                }
                else{
                    check_expr_comma(body_else, function);
                }
            }
            break;

        case While:
            check_expr_comma(getchild(statement, 0), function);

            body_while = getchild(statement, 1);
            if(body_while != NULL){
                if (body_while->category == StatList){
                    check_statement(body_while, function);
                }
                else{
                    check_expr_comma(body_while, function);
                }
            }
            break;

        case Return:
            expr_comma_node = getchild(statement, 0);
            if(expr_comma_node != NULL)
                check_expr_comma(expr_comma_node, function);
            break;

        default:
            check_expr_comma(statement, function);
            break;
    }
}

void check_expr_comma(struct node *expr_comma_node, struct function *func){
    if (expr_comma_node->category != Comma){
        check_expression(expr_comma_node, func);
    }
    else {
        int pos = 0;
        struct node *aux;
        while ((aux = getchild(expr_comma_node, pos)) != NULL){
            check_expr_comma(aux, func);
            pos += 1;
        }
    }
}

void check_expression(struct node *expression, struct function *func){  
    struct symbols_list *symbol;
    struct params_list *aux_list;
    struct node *son;
    struct node *son_2;
    char buffer[64] = "";

    switch(expression->category){
        case Decimal:
            expression->type = "double";
            break;
        
        case Natural:
        case Chrlit:
            expression->type = "int";
            break;
        
        case Identifier:
            symbol = search_function_symbol(global_symbol_table, expression->token);

            if (symbol != NULL){
                aux_list = symbol->function->parameters;

                strcat(buffer, symbol->function->type);
                strcat(buffer, "(");
                while (aux_list != NULL){
                    strcat(buffer, aux_list->type);
                    if (aux_list->next != NULL)
                        strcat(buffer, ",");
                    aux_list = aux_list->next;
                }
                strcat(buffer, ")");
                expression->type = symbol->function->type;
                expression->annotation = strdup(buffer);
            }
            else {
                aux_list = search_variable_symbol(global_symbol_table, expression->token);
                if (aux_list != NULL)
                    expression->type = strdup(aux_list->type);
                else {
                    if (func == NULL){
                        expression->type = "undef";
                        printf("Unknown symbol %s\n", expression->token);
                    }
                    else {
                        aux_list = search_local_variable(func, expression->token);
                        if (aux_list != NULL)
                            expression->type = strdup(aux_list->type);
                        else {
                            aux_list = search_parameters_list(func, expression->token);
                            if (aux_list != NULL)
                                expression->type = strdup(aux_list->type);
                            else {
                                expression->type = "undef";
                                printf("Unknown symbol %s\n", expression->token);
                            }
                        }
                    }
                }
            }
            break;

        case Or:
        case And:
        case Eq:
        case Ne:
        case Lt:
        case Gt:
        case Le:
        case Ge:
        case Mod:
            son = getchild(expression, 0);
            son_2 = getchild(expression, 1);
            check_expression(son, func);
            check_expression(son_2, func);
            expression->type = "int";
            break;
        
        case Not:
        case Plus:
        case Minus:
            son = getchild(expression, 0);
            check_expression(son, func);
            expression->type = strdup(son->type);
            break;

        case Add:
        case Sub:
        case Mul:
        case Div:
        case BitWiseAnd:
        case BitWiseOr:
        case BitWiseXor:
            son = getchild(expression, 0);
            son_2 = getchild(expression, 1);
            check_expression(son, func);
            check_expression(son_2, func);
            get_expression_type(expression, son->type, son_2->type);
            break;

        case Store:
            son = getchild(expression, 0);
            check_expression(son, func);
            check_expression(getchild(expression, 1), func);
            expression->type = strdup(son->type);
            if (strcmp(category_names[son->category], "Identifier") != 0)
                printf("Lvalue required\n");
            break;
        
        case Call:
            int pos = 1;
            son = getchild(expression, 0);
            check_expression(son, func);
            expression->type = strdup(son->type);
            while ((son_2 = getchild(expression, pos)) != NULL){
                check_expression(son_2, func);
                pos += 1;
            }
            if (wrong_number_of_arguments(son, pos-1) == 0){
                conflict_types_call(son, expression);
            }
            break;
        
        default:
            break;
    }
}


void get_expression_type(struct node *expression, char *son_1_type, char *son_2_type){
    if (strcmp(son_1_type, "undef") == 0 || strcmp(son_2_type, "undef") == 0 || strcmp(son_1_type, "void") == 0 || strcmp(son_2_type, "void"))
        expression->type = "undef";
    else if (strcmp(son_1_type, "double") == 0 || strcmp(son_2_type, "double") == 0)
        expression->type = "double";
    else if (strcmp(son_1_type, "int") == 0 || strcmp(son_2_type, "int") == 0)
        expression->type = "int";
    else if (strcmp(son_1_type, "short") == 0 || strcmp(son_2_type, "short") == 0)
        expression->type = "short";
    else if (strcmp(son_1_type, "char") == 0 || strcmp(son_2_type, "char") == 0)
        expression->type = "char";
}

void conflict_types_func_var(char *type, struct node *param_list, struct params_list *var){
    char aux_type[10];
    struct node *param_declarator;
    int pos = 0;

    strcpy(aux_type, type);
    aux_type[0] = aux_type[0] + 32;
    printf("Conflicting types (got %s(", aux_type);

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

    struct symbols_list *symbol = search_function_symbol(global_symbol_table, node->token);
    if (symbol != NULL){
        struct params_list *aux = symbol->function->parameters;
        while (aux != NULL){
            required += 1;
            aux = aux->next;
        }
        if (required == 1 && strcmp(symbol->function->parameters->type, "void") == 0)
            required = 0;
    }
    if (got != required){
        printf("Wrong number of arguments to function %s (got %d, required %d)\n", symbol->function->name, got, required);
        return 1;
    }
    return 0;
}

void conflict_types_call(struct node *node, struct node *call){
    int pos = 1;
    struct node *aux;
    struct params_list *param_list = search_function_symbol(global_symbol_table, node->token)->function->parameters;

    while ((aux = getchild(call, pos)) != NULL){
        if(strcmp(aux->type, param_list->type) != 0 && ((strcmp(aux->type, "int") != 0 || strcmp(param_list->type, "short") != 0) && (strcmp(aux->type, "short") != 0 || strcmp(param_list->type, "int") != 0))){
            printf("Conflicting types (got %s, expected %s)\n", aux->type, param_list->type);
        }
        pos += 1;
        param_list = param_list->next;
    }
}


// Insert putchar and getchar function´
void insert_putchar_getchar(){
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
            printf("Symbol %s already defined\n", identifier);
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
            printf("Symbol %s already defined\n", identifier);
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
struct params_list *insert_local_variable(struct function *function, char *type, char *identifier){
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
            printf("Symbol %s already defined\n", identifier);
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
                if (strcmp(aux->function->parameters->type, "void") != 0)
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