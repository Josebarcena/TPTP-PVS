#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "structs.h"

void Add_Variable(Variable **head,const char *name, const char *type) {
    Variable *temp = *head;
    
    while (temp) {
        if (strcmp(temp->name, name) == 0 && strcmp(temp->type, type) == 0) {
            return;
        }
        temp = temp->next;
    }

    Variable *new_var = (Variable *)malloc(sizeof(Variable));
    if (!new_var) {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }

    new_var->name = strdup(name);
    new_var->type = strdup(type);
    new_var->next = NULL;
    new_var->prev = NULL;

    if (*head == NULL) {
        *head = new_var;
        return;
    }

    temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_var;
    new_var->prev = temp;
}

void Free_Variables(Variable *head) {
    Variable *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp->name);
        free(temp->type);
        free(temp);
    }
}

int VariableExistsInGroups(TypeGroup *head, const char *varName) {
    TypeGroup *tg = head;
    while (tg) {
        char *namesCopy = strdup(tg->names);
        namesCopy = strtok(namesCopy, ",");
        while (namesCopy != NULL) {
            if (strcmp(namesCopy, varName) == 0) {
                return 1;
            }
        namesCopy = strtok(NULL, ",");
    }
        tg = tg->next;
    }
    return 0;
}
