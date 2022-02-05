#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "node.h"


void print_usage() {
    printf("Usage: [options] [arguments]\n");
}

int main(int argc, char *argv[]) {
    node_t *head = load_list(FILENAME);

    int opt = 0, mod = 0;
    static struct option long_options[] = {
        { "add",    required_argument,  0,  'a'},
        { "delete", required_argument,  0,  'd'},
        { "check",  required_argument,  0,  'c'},
        {0, 0, 0, 0}
    };

    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "a:d:c:",
                    long_options, &option_index )) != -1) {
        switch (opt) {
            case 'a' :
                push_node(&head, init_node(optarg, strlen(optarg), 0));
                mod = 1;
                break;
            case 'd' :
                delete_node(&head, find_node(head, atoi(optarg)));
                mod = 1;
                break;
            case 'c' :
                check_node(find_node(head, atoi(optarg)));
                mod = 1;
                break;
            default :
                print_usage();
                break;
        }
    }

    if (mod == 1)
        dump_list(head, FILENAME);

    print_list(printf, head);
    free_list(head);

    return 0;
}
