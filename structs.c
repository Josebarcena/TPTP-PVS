#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "structs.h"

void Add_Variable(Variable **head,const char *name, const char *type) {
    Variable *new_var = (Variable *)malloc(sizeof(Variable));
    if (!new_var) {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }
    new_var->name = strdup(name);
    new_var->type = strdup(type);
    new_var->next = NULL;
    new_var->prev = NULL;
    if(*head == NULL)
    {
        *head = new_var;
        return;    
    }
    Variable *temp = *head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_var;
    new_var->prev = temp;  // Insertar al final
}