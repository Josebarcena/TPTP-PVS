#include <stdio.h>
#include <limits.h> 
#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Variable{
    char *name;
    char *type;
    struct Variable *next;
    struct Variable *prev;
} Variable;
    
typedef struct TypeGroup {
    char names[1024];
    char type[50];
    struct TypeGroup *next;
} TypeGroup;

typedef struct {
    int numThread;
    char file[PATH_MAX];
} ThreadArgs;

void Add_Variable(Variable **head,const char *name, const char *type);
void Free_Variables(Variable *head);
int VariableExistsInGroups(TypeGroup *head, const char *varName);
#endif
