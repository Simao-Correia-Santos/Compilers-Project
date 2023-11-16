#ifndef _AST_H
#define _AST_H

enum category {Program, Declaration, FuncDeclaration, FuncDefinition, ParamList, FuncBody, ParamDeclaration, StatList, Or, And, Eq, Ne, Lt, Gt, Le, Ge, Add, Sub, Mul, Div, Mod, Not, Minus, Plus, Store, Comma, Call, BitWiseAnd, BitWiseXor, BitWiseOr, Null, Char, Chrlit, Identifier, Int, Short, Natural, Double, Decimal, Void, If, While, Return, Error};

struct node {
    int children_count;
    enum category category;
    char *token;
    struct node *brother;
    struct node_list *children;
};

struct node_list {
    struct node *node;
    struct node_list *next;
};

struct node *newnode(enum category category, char *token);

void addchild(struct node *parent, struct node *child);

void addBrother(struct node *irmao_velho, struct node *irmao_novo);

void insert_typespec(struct node *parent, struct node *son);

void deallocate_memory(struct node* node);

void show_ast_tree(struct node *node, int underline);

void get_category_name(int pos, char *category_buffer);

#endif