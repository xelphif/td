/*
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "node.h"

char check_true[4]  = "[x]";
char check_false[4] = "[ ]";

node_t *init_node(char *task, size_t len, int check) {
    node_t *node = malloc(sizeof(node_t) + len * sizeof(char));

    node->next = NULL;
    node->prev = NULL;
    node->check = check;
    strncpy(node->task, task, len);

    return node;
}

void push_node(node_t **head_ref, node_t *node) {
    if (*head_ref == NULL) {
        *head_ref = node;
        return;
    }

    node_t *curr = *head_ref;
    while (curr->next != NULL)
        curr = curr->next;

    curr->next = node;
    node->prev = curr;

    return;
}

void delete_node(node_t **head_ref, node_t *node) {
    if (*head_ref == NULL || node == NULL)
        return;
    if (*head_ref == node)
        *head_ref = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
    if (node->prev != NULL)
        node->prev->next = node->next;

    free(node);

    return;
}

void check_node(node_t *node) {
    if (node == NULL)
        return;

    node->check ^= 1;

    return;
}

char *checks(int check) {
    return check ? check_true : check_false;
}

node_t *find_node(node_t *head, int index) {
    node_t *curr = head;
    for (int i = 0; i < index; i++) {
        if (curr->next == NULL)
            return NULL;

        curr = curr->next;
    }

    return curr;
}

void free_list(node_t *head) {
    while (head != NULL)
        delete_node(&head, head);

    return;
}


// IO

node_t *load_list(char *filename, int *n_nodes) {
    FILE *fp = fopen(filename, "r");

    if (!fp)
        return NULL;

    node_t *head = NULL;
    char *buf = NULL;
    size_t n = 0;
    size_t len;

    int check, i = 0;

    for (i = 0; (len = getline(&buf, &n, fp)) != -1; i++) {
        sscanf(buf, "%d:%[^\n]", &check, buf);
        push_node(&head, init_node(buf, len, check));
    }

    if (n_nodes != NULL)
        *n_nodes = i;

    free(buf);
    fclose(fp);

    return head;
}

void dump_list(node_t *head, char *filename) {
    if (head == NULL) {
        remove(filename);
        return;
    }

    FILE *fp = fopen(filename, "w");

    node_t *curr = head;
    while (curr != NULL) {
        fprintf(fp, "%d:%s\n", curr->check, curr->task);
        curr = curr->next;
    }

    fclose(fp);

    return;
}

void print_list(node_t *head) {
    node_t *curr = head;

    for (int i = 0; curr != NULL; i++) {
        printf("%i. %s %s\n", i, checks(curr->check), curr->task);
        curr = curr->next;
    }
}
*/
