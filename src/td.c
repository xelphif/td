#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "task.h"


void print_usage() {
    printf("Usage: [options] [arguments]\n");
}

int main(int argc, char *argv[]) {
    size_t used = 0, init_size = INIT_SIZE;

    task_t **tasks = load_list(FILENAME, &used, &init_size);

    int opt = 0, mod = 0;
    size_t len;

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
                len = strlen(optarg) + 1;
                // push_node(&head, init_node(optarg, strlen(optarg), 0));
                list_add(tasks, init_task(optarg, len, 0), &used, &init_size);
                mod = 1;
                break;
            case 'd' :
                delete_task(tasks[atoi(optarg)]);
                mod = 1;
                break;
            case 'c' :
                finish_task(tasks[atoi(optarg)]);
                mod = 1;
                break;
            default :
                print_usage();
                break;
        }
    }

    if (mod == 1)
        dump_list(FILENAME, tasks, used);

    print_list(tasks, used);
    free_list(tasks, used);

    return 0;
}
