#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "task.h"

char   done_s[DONE_S_LEN] = "[x]";
char n_done_s[DONE_S_LEN] = "[ ]";

int used = 0, size = ARRAY_INIT_SIZE, longest = 0;

task_t *init_task(char *text, size_t len, int finished) {
    task_t *task = malloc(sizeof(task_t) + len * sizeof(char));
    /* task->text = malloc(sizeof(char) * len); */

    task->finished = finished;
    strncpy(task->text, text, len);

    if (len > longest)
        longest = len;

    return task;
}

task_t **list_add(task_t **tasks, task_t *task) {
    if (used == size) {
        size *= 2;
        tasks = realloc(tasks, size * sizeof(task_t *));
    }

    tasks[used++] = task;
    return tasks;
}

task_t **delete_task(task_t **tasks, int remove_index) {
    if (used == 0)
        return;

    free(tasks[remove_index]);

    if (remove_index + 1 < used)
        memmove(tasks + remove_index, tasks + remove_index + 1,
                sizeof(task_t *) * (used - remove_index - 1));

    used--;

    if (used < size / 2) {
        size /= 2;
        tasks = realloc(tasks, size * sizeof(task_t *));
    }

    return tasks;
}

void finish_task(task_t *task) {
    task->finished ^= 1;
}

char *finish_s(int finished) {
    return finished ? done_s : n_done_s;
}


// IO

task_t **load_list(char *filename) {
    FILE *fp = fopen(filename, "r");

    task_t **tasks = malloc(size * sizeof(task_t *));

    if (fp == NULL)
        return tasks;

    char *buf = NULL;
    size_t n = 0;
    size_t len, slen;

    int finished;
    while ((len = getline(&buf, &n, fp)) != -1) {
        slen = len - 2;
        sscanf(buf, "%d:%[^\n]", &finished, buf);
        tasks = list_add(tasks, init_task(buf, slen, finished));
        if (slen > longest)
            longest = slen;
    }

    free(buf);
    fclose(fp);

    return tasks;
}

void dump_list(char *filename, task_t **tasks) {
    FILE *fp = fopen(filename, "w");

    struct stat st;

    for (int i = 0; i < used; i++) {
        fprintf(fp, "%d:%s\n", tasks[i]->finished, tasks[i]->text);
    }

    fclose(fp);

    if (stat(filename, &st) != -1 && st.st_size == 0)
        remove(FILENAME);

    return;
}

void free_list(task_t **tasks) {
    for (int i = 0; i < used; i++) {
        /* free(tasks[i]->text); */
        free(tasks[i]);
    }

    free(tasks);

    return;
}

void print_list(task_t **tasks) {
    int display = 0;
    for (int i = 0; i < used; i++) {
        printf("%3d. %s %s\n", display, finish_s(tasks[i]->finished), tasks[i]->text);
        display++;
    }

    return;
}
