#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Variable{
    char *name;
    char *type;
    struct Variable *next;
    struct Variable *prev;
} Variable;


void Add_Variable(Variable **head,const char *name, const char *type);
#endif
