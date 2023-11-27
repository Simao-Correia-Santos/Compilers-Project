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
            check_declaration(aux, 1, NULL);
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
            check_statement();
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
    struct node *param_decl;
    int pos = 0;

    while ((param_decl = getchild(params_list, pos)) != NULL){
        struct node *typespec_node = getchild(param_decl, 0);
        struct node *identifier_node = getchild(param_decl, 1); //PODE SER NULL
        
        if (typespec_node->category != Void){
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
        }
        pos++;
    }
}

void check_declaration(struct node *declaration, int is_global, struct function *function){
    struct node *typespec_node = getchild(declaration, 0);
    struct node *identifier_node = getchild(declaration, 1);

    if (is_global && search_variable_symbol(global_symbol_table, identifier_node->token) == NULL){
        insert_variable_symbol(global_symbol_table, identifier_node->token, category_names[typespec_node->category]);
    }
    else if (!is_global && search_local_variable(function, identifier_node->token) == NULL){
        insert_local_variable(function, identifier_node->token, category_names[typespec_node->category]);
    }
}

void check_statement(){}

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

// Look up a variable symbol by its identifier inside a function
struct function *search_local_variable(struct function *function, char *identifier){
    struct params_list *aux = function->variables;
    while (aux != NULL){
        if(strcmp(aux->name, identifier) == 0)
            return function;
        aux = aux->next;
    }
    return NULL;
}

// Insert e new local variable in the list, unless it is already there
struct params_list *insert_local_variable(struct function *function, char *type, char *identifier){
    struct params_list *new = (struct params_list *) malloc(sizeof(struct params_list));
    new->name= strdup(identifier);
    new->type = strdup(type);
    new->next = NULL;

    struct function *aux_function = function;

    if (aux_function->variables == NULL){
            function->variables = new;
    }
    else {
        if(strcmp(aux_function->variables->name, identifier) == 0) {
            free(new);
            return NULL;
        } 
        while (aux_function->variables->next != NULL){
            aux_function->variables = aux_function->variables->next;
        }
        aux_function->variables->next = new;
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
    printf("\n");
    show_symbol_table_functions();
}

void show_symbol_table_functions(){
    struct symbols_list *aux = global_symbol_table;
    while((aux = aux->next) != NULL){
        if(aux->function != NULL && aux->function->is_defined){
            printf("===== Function %s Symbol Table =====\n", aux->function->name);
            printf("Return  %s\n",aux->function->type);
            while(aux->function->parameters != NULL){
                printf("%s  %s param\n", aux->function->parameters->name, aux->function->parameters->type);
                aux->function->parameters = aux->function->parameters->next;
            }
            while(aux->function->variables != NULL){
                printf("%s  %s\n", aux->function->variables->type, aux->function->variables->name);
                aux->function->variables = aux->function->variables->next;
            }
            printf("\n");
        }
    }
}