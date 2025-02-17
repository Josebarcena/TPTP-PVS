#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "structs.h"

void Add_Variable(Variable **head,const char *name, const char *type) {
    // Buscar si ya existe la variable con el mismo nombre y tipo
    Variable *temp = *head;
    while (temp) {
        if (strcmp(temp->name, name) == 0 && strcmp(temp->type, type) == 0) {
            return;  // Salir sin agregar la variable
        }
        temp = temp->next;
    }

    // Crear una nueva variable
    Variable *new_var = (Variable *)malloc(sizeof(Variable));
    if (!new_var) {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }

    // Asignar valores a la nueva variable
    new_var->name = strdup(name);
    new_var->type = strdup(type);
    new_var->next = NULL;
    new_var->prev = NULL;

    // Si la lista está vacía, asignar la nueva variable como cabeza
    if (*head == NULL) {
        *head = new_var;
        return;
    }

    // Insertar al final de la lista
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