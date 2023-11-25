#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantics.h"

int semantic_errors = 0;
struct symbol_list *global_symbol_table;


// Check Programa
int check_program(struct node *program){
    global_symbol_table = (struct symbol_list*)malloc(sizeof(struct symbol_list));
    global_symbol_table->next = NULL;

    struct node_list* children = program->children->next;
    while (children != NULL){
        if (children->node->category == FuncDefinition){
            check_func_definition(children->node);
        }
        else if (children->node->category == FuncDeclaration){
            check_func_declaration(children->node);
        }
        else if (children->node->category == Declaration){
            check_declaration(children->node);
        }
        children = children->next;
    }
    return semantic_errors;
}

void check_func_definition(struct node *no){}

void check_func_declaration(struct node* no){}

void check_declaration(struct node* no){}

// Insert a new symbol in the list, unless it is already there
struct symbol_list *insert_symbol(struct symbol_list *table, char *identifier, enum type type, struct node *node) {
    struct symbol_list *new = (struct symbol_list *) malloc(sizeof(struct symbol_list));
    new->identifier = strdup(identifier);
    new->type = type;
    new->node = node;
    new->next = NULL;
    struct symbol_list *symbol = table;
    while(symbol != NULL) {
        if(symbol->next == NULL) {
            symbol->next = new;    /* insert new symbol at the tail of the list */
            break;
        } else if(strcmp(symbol->next->identifier, identifier) == 0) {
            free(new);
            return NULL;           /* return NULL if symbol is already inserted */
        }
        symbol = symbol->next;
    }
    return new;
}

// Look up a symbol by its identifier
struct symbol_list *search_symbol(struct symbol_list *table, char *identifier) {
    struct symbol_list *symbol;
    for(symbol = table->next; symbol != NULL; symbol = symbol->next)
        if(strcmp(symbol->identifier, identifier) == 0)
            return symbol;
    return NULL;
}

// Show symbol table
void show_symbol_table() {
    struct symbol_list *symbol;

    printf("===== Global Symbol Table =====\n");

    for(symbol = global_symbol_table->next; symbol != NULL; symbol = symbol->next){
        printf("%s\t%s\n", symbol->identifier, type_name(symbol->type));
    }
}
