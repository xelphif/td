#ifndef NODE_H
#define NODE_H

#define FILENAME "TODO"

typedef struct node {
    struct node *next;
    struct node *prev;
    int check;
    char task[];
} node_t;


node_t *init_node   (char *task, size_t len, int check);
void    push_node   (node_t **head_ref, node_t *node);
void    delete_node (node_t **head_ref, node_t *node);
void    check_node  (node_t *node);
node_t *find_node   (node_t *head, int index);
void    free_list   (node_t *head);

node_t *load_list   (char *filename);
void    dump_list   (node_t *head, char *filename);
void    print_list  (int (*print)(const char *fmt, ...), node_t *head);

#endif
