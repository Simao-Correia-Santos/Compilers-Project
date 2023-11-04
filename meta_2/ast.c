#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"

// create a node of a given category with a given lexical symbol
struct node *newnode(enum category category, char *token) {
    struct node *new = malloc(sizeof(struct node));
    new->children_num = 0;
    new->category = category;
    new->token = token;
    new->children = malloc(sizeof(struct node_list));
    new->children->node = NULL;
    new->children->next = NULL;
    return new;
}

// append a node to the list of children of the parent node
void addchild(struct node *parent, struct node *child) {
    struct node_list *new = malloc(sizeof(struct node_list));
    parent->children_num++;
    new->node = child;
    new->next = NULL;
    struct node_list *children = parent->children;
    while(children->next != NULL)
        children = children->next;
    children->next = new;
}


// show AST tree
void show_ast_tree(struct node *node, int underline){
    char category_buffer[20];
    get_category_name(node->category, category_buffer);

    for (int i = 0; i < underline; i++){
        printf("..");
    }
    if (node->token == NULL){
        printf("%s\n", category_buffer);
    }
    else{
        printf("%s(%s)\n", category_buffer, node->token);
    }
    struct node_list *child = node->children;
    while(child->next != NULL){
        child = child->next;
        show_ast_tree(child->node, underline += 1);
    }
}


void get_category_name(int pos, char *category_buffer){
    switch (pos){
    }
}