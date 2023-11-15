#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"

// create a node of a given category with a given lexical symbol
struct node *newnode(enum category category, char *token) {
    struct node *new = malloc(sizeof(struct node));
    new->children_count = 0;
    new->category = category;
    new->brother = NULL;
    new->token = token;
    new->children = malloc(sizeof(struct node_list));
    new->children->node = NULL;
    new->children->next = NULL;
    return new;
}

// append a node to the list of children of the parent node
void addchild(struct node *parent, struct node *child) {
    struct node_list *new = malloc(sizeof(struct node_list));
    parent->children_count++;
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

// add a brother
void addBrother(struct node *irmao_velho, struct node *irmao_novo){
    struct  node *aux = irmao_velho;
    while (aux->brother != NULL){
        aux = aux->brother;
    }
    aux->brother = irmao_novo;
}

// show AST tree
void show_ast_tree(struct node *node, int point){
    char category_buffer[20];
    get_category_name(node->category, category_buffer);
    for (int i = 0; i < point; i++){
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
        show_ast_tree(child->node, point + 1);
    }
}

void get_category_name(int pos, char *category_buffer){
    switch (pos){
        case 0:
            strcpy(category_buffer, "Program");
            break;
        case 1:
            strcpy(category_buffer, "Declaration");
            break;
        case 2:
            strcpy(category_buffer, "FuncDeclaration");
            break;
        case 3:
            strcpy(category_buffer, "FuncDefinition");
            break;
        case 4:
            strcpy(category_buffer, "ParamList");
            break; 
        case 5:
            strcpy(category_buffer, "FuncBody");
            break;
        case 6:
            strcpy(category_buffer, "ParamDeclaration");
            break;
        case 7:
            strcpy(category_buffer, "StatList");
            break;
        case 8:
            strcpy(category_buffer, "Or");
            break;
        case 9:
            strcpy(category_buffer, "And");
            break;
        case 10:
            strcpy(category_buffer, "Eq");
            break;
        case 11:
            strcpy(category_buffer, "Ne");
            break;        
        case 12:
            strcpy(category_buffer, "Lt");
            break;        
        case 13:
            strcpy(category_buffer, "Gt");
            break;        
        case 14:
            strcpy(category_buffer, "Le");
            break;        
        case 15:
            strcpy(category_buffer, "Ge");
            break;
        case 16:
            strcpy(category_buffer, "Add");
            break;        
        case 17:
            strcpy(category_buffer, "Sub");
            break;
        case 18:
            strcpy(category_buffer, "Mul");
            break;
        case 19:
            strcpy(category_buffer, "Div");
            break;
        case 20:
            strcpy(category_buffer, "Mod");
            break;
        case 21:
            strcpy(category_buffer, "Not");
            break;
        case 22:
            strcpy(category_buffer, "Minus");
            break;
        case 23:
            strcpy(category_buffer, "Plus");
            break;
        case 24:
            strcpy(category_buffer, "Store");
            break;
        case 25:
            strcpy(category_buffer, "Comma");
            break;
        case 26:
            strcpy(category_buffer, "Call");
            break;
        case 27:
            strcpy(category_buffer, "BitWiseAnd");
            break;
        case 28:
            strcpy(category_buffer, "BitWiseXor");
            break;
        case 29:
            strcpy(category_buffer, "BitWiseOr");
            break;
        case 30:
            strcpy(category_buffer, "Null");
            break;
        case 31:
            strcpy(category_buffer, "Char");
            break;
        case 32:
            strcpy(category_buffer, "Chrlit");
            break;
        case 33:
            strcpy(category_buffer, "Identifier");
            break;
        case 34:
            strcpy(category_buffer, "Int");
            break;
        case 35:
            strcpy(category_buffer, "Short");
            break;
        case 36:
            strcpy(category_buffer, "Natural");
            break;
        case 37:
            strcpy(category_buffer, "Double");
            break;
        case 38:
            strcpy(category_buffer, "Decimal");
            break;
        case 39:
            strcpy(category_buffer, "Void");
            break;
        case 40:
            strcpy(category_buffer, "If");
            break;
        case 41:
            strcpy(category_buffer, "While");
            break;
        case 42:
            strcpy(category_buffer, "Return");
            break;
        case 43:
            strcpy(category_buffer, "Return");
            break;   
    }
}