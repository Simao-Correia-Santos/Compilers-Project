#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantics.h"

int semantic_errors = 0;
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

    for (int i = 0; (aux = getchild(program, i)) != NULL; i++){
        if (aux->category == FuncDefinition){
            check_func_definition(aux);
        }
        else if (aux->category == FuncDeclaration){
            check_func_declaration(aux);
        }
        else if (aux->category == Declaration){
            check_declaration(aux, 1);
        }
    }
}

void check_func_definition(struct node *func_definition){
    int pos_parameter_list;
    struct symbols_list *symbol;

    struct node *typespec_node = getchild(func_definition, 0);
    struct node *identifier_node = getchild(func_definition, 1);

    if (search_function_symbol(global_symbol_table, identifier_node->token) == NULL){
        symbol = insert_function_symbol(global_symbol_table, identifier_node->token, category_names[typespec_node->category], func_definition);
        symbol->function->is_defined = 1;

        for (pos_parameter_list = 2; getchild(func_definition, pos_parameter_list)->category != FuncBody; pos_parameter_list++){
            check_parameter_declarator(getchild(func_definition, pos_parameter_list), symbol->function->parameters);
        }
        check_fuction_body(getchild(func_definition, pos_parameter_list), symbol->function->variables);
    }
}

void check_fuction_body(struct node* no, struct params_list *variaveis_locais_list){}

void check_func_declaration(struct node *func_declaration){
    int pos_parameter_list;
    struct symbols_list *symbol;

    struct node *typespec_node = getchild(func_declaration, 0);
    struct node *identifier_node = getchild(func_declaration, 1);

    if (search_function_symbol(global_symbol_table, identifier_node->token) == NULL){
        symbol = insert_function_symbol(global_symbol_table, identifier_node->token, category_names[typespec_node->category], func_declaration);

        if (symbol->function->is_defined == 0){
            for (pos_parameter_list = 2; getchild(func_declaration, pos_parameter_list)->category != FuncBody; pos_parameter_list++){
                check_parameter_declarator(getchild(func_declaration, pos_parameter_list), symbol->function->parameters);
            }
        }
    }
}

void check_parameter_declarator(struct node* node, struct params_list *parameters_list){
    struct params_list *new = (struct params_list*) malloc(sizeof(struct params_list));

    struct node *typespec_node = getchild(node, 0);
    struct node *identifier_node = getchild(node, 1); //Pode ser NULL

    new->name = identifier_node->token;
    new->type= category_names[typespec_node->category];
    new->next = NULL;

    if (parameters_list == NULL){
        parameters_list = new;
    }
    else {
        while (parameters_list->next != NULL){
            parameters_list = parameters_list->next;
        }
        parameters_list->next = new;
    }
}

void check_declaration(struct node *declaration, int is_global){
    
}

// Insert a new symbol in the list, unless it is already there
struct symbols_list *insert_function_symbol(struct symbols_list *table, char *identifier, char *type, struct node *node) {
    struct symbols_list *new = (struct symbols_list *) malloc(sizeof(struct symbols_list));
    new->variable = NULL;
    new->function = (struct function*) malloc(sizeof(struct function));
    new->function->name = strdup(identifier);
    new->function->is_defined = 0;
    new->function->type = type;
    new->function->parameters = NULL;
    new->function->variables = NULL;
    new->next = NULL;

    struct symbols_list *symbol = table;
    while(symbol != NULL) {
        if(symbol->next == NULL) {
            symbol->next = new;    /* insert new symbol at the tail of the list */
            break;
        } else if(strcmp(symbol->next->function->name, identifier) == 0) {
            free(new);
            return NULL;           /* return NULL if symbol is already inserted */
        }
        symbol = symbol->next;
    }
    return new;
}

// Look up a symbol by its identifier
struct symbols_list *search_function_symbol(struct symbols_list *table, char *identifier) {
    struct symbols_list *symbol = table;
    for(symbol->function = table->next->function; symbol != NULL; symbol = symbol->next)
        if(symbol->function != NULL && strcmp(symbol->function->name, identifier) == 0)
            return symbol;
    return NULL;
}

