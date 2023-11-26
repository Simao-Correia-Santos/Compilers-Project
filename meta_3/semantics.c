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
            check_declaration(aux);
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
    }

    for (pos_parameter_list = 2; getchild(func_definition, pos_parameter_list)->category != FuncBody; pos_parameter_list++){
        check_parameter_declarator(getchild(func_definition, pos_parameter_list), symbol->function->parameters);
    }
    check_fuction_body(getchild(func_definition, pos_parameter_list), symbol->function->variables);
}

void check_func_declaration(struct node *no){}

void check_declaration(struct node *no){}

void check_parameter_declarator(struct node* no, struct params_list *parameters_list){}

void check_fuction_body(struct node* no, struct params_list *variaveis_locais_list){}

// Insert a new symbol in the list, unless it is already there
struct symbols_list *insert_function_symbol(struct symbols_list *table, char *identifier, char *type, struct node *node) {
    struct symbols_list *new = (struct symbols_list *) malloc(sizeof(struct symbols_list));
    new->variable = NULL;
    new->function = (struct function*) malloc(sizeof(struct function));
    new->function->is_defined = 1;
    new->function->name = strdup(identifier);
    new->function->type = type;
    new->function->parameters = (struct params_list*) malloc(sizeof(struct params_list));
    new->function->parameters->next = NULL;
    new->function->variables = (struct params_list*) malloc(sizeof(struct params_list));
    new->function->variables->next = NULL;
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

