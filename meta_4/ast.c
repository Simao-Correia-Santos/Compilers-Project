#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"

// Category names #defined in ast.h
char *category_name[] = names;

// Create a node of a given category with a given lexical symbol
struct node *newnode(enum category category, char *token) {
    struct node *new = malloc(sizeof(struct node));
    new->category = category;
    new->brother = NULL;
    new->type = NULL;
    new->annotation = NULL;
    new->token = token;
    new->children = malloc(sizeof(struct node_list));
    new->children->node = NULL;
    new->children->next = NULL;
    return new;
}

// Append a node to the list of children of the parent node
void addchild(struct node *parent, struct node *child) {
    if (parent == NULL || child == NULL) return;

    struct node_list *new = malloc(sizeof(struct node_list));
    new->node = child;
    new->next = NULL;
    struct node_list *children = parent->children;
    while(children->next != NULL)
        children = children->next;
    children->next = new;

    if(child->brother != NULL){
        addchild(parent, child->brother);
    }
}

// Add a brother
void addBrother(struct node *irmao_velho, struct node *irmao_novo){
    if (irmao_novo == NULL || irmao_velho == NULL) return;

    struct  node *aux = irmao_velho;
    while (aux->brother != NULL){
        aux = aux->brother;
    }
    aux->brother = irmao_novo;
}

// Adiciona filho no inicio da lista
void insert_typespec(struct node* parent, struct node* son){
    struct node_list *new = malloc(sizeof(struct node_list));
    new->node = son;
    new->next = parent->children->next;
    parent->children->next = new;
}

// Get a pointer to a specific child, numbered 0, 1, 2, ...
struct node *getchild(struct node *parent, int position) {
    struct node_list *children = parent->children;
    while((children = children->next) != NULL)
        if(position-- == 0)
            return children->node;
    return NULL;
}

// Show AST tree
void show_ast_tree(struct node *node, int point){
    for (int i = 0; i < point; i++){
        printf("..");
    }

    if (node->token == NULL && node->type == NULL)
        printf("%s\n", category_name[node->category]);
    else if (node->type != NULL && node->token != NULL && node->annotation == NULL)
            printf("%s(%s) - %s\n", category_name[node->category], node->token, node->type);
    else if (node->type != NULL && node->token != NULL && node->annotation != NULL)
            printf("%s(%s) - %s\n", category_name[node->category], node->token, node->annotation);
    else if (node->token != NULL && node->type == NULL)
            printf("%s(%s)\n", category_name[node->category], node->token);    
    else 
        printf("%s - %s\n", category_name[node->category], node->type);
        
    struct node_list *child = node->children;
    while(child->next != NULL){
        child = child->next;
        show_ast_tree(child->node, point + 1);
    }
}

// Dealocate memory
void deallocate_memory(struct node* node){
    if (node != NULL){
    struct node_list *current_child = node->children;
        while (current_child->node != NULL) {
            struct node_list *next_child = current_child;
            deallocate_memory(current_child->node);
            free(current_child);
            current_child = next_child;
        }
        if (node->token != NULL) free(node->token);
        free(node);
    }
}