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
    struct symbols_list *symbol;

    struct node *typespec_node = getchild(func_definition, 0);
    struct node *identifier_node = getchild(func_definition, 1);

    if (search_function_symbol(global_symbol_table, identifier_node->token) == NULL){
        symbol = insert_function_symbol(global_symbol_table, identifier_node->token, category_names[typespec_node->category]);
        symbol->function->is_defined = 1;

        check_parameter_declarator(getchild(func_definition, 2), symbol->function);

        check_fuction_body(getchild(func_definition, 3), symbol->function->variables);
    }
}

void check_fuction_body(struct node* no, struct params_list *variaveis_locais_list){}

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

void check_parameter_declarator(struct node* node, struct function *function){
    struct node *param_decl;
    int pos = 0;

    while ((param_decl = getchild(node, pos)) != NULL){
        struct node *typespec_node = getchild(param_decl, 0);
        struct node *identifier_node = getchild(param_decl, 1); //PODE SER NULL
        
        struct params_list *new = (struct params_list*) malloc(sizeof(struct params_list));
        if (identifier_node != NULL)
            new->name = identifier_node->token;
        else 
            new->name = NULL;
        new->type= category_names[typespec_node->category];
        new->next = NULL;

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

void check_declaration(struct node *declaration, int is_global){
    struct node *typespec_node = getchild(declaration, 0);
    struct node *identifier_node = getchild(declaration, 1);

    if (search_variable_symbol(global_symbol_table, identifier_node->token) == NULL){
        insert_variable_symbol(global_symbol_table, identifier_node->token, category_names[typespec_node->category]);
    }
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

//Look up a variavle symbol by its identifier
struct symbols_list *search_variable_symbol(struct symbols_list *table, char *identifier){
    struct symbols_list *symbol = table->next;
    while (symbol != NULL){
        if(symbol->variable != NULL && strcmp(symbol->variable->name, identifier) == 0)
            return symbol;
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

// Show Global Tabel
void show_symbol_table(){
    struct symbols_list *aux = global_symbol_table;

    printf("===== GLOBAL SYMBOL TABLE =====\n");
    printf("putchar	int(int)\ngetchar	int(void)\n");
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
}