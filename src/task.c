#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task.h"

task_t *init_task(char *text, size_t len, int finished) {
    task_t *task = malloc(sizeof(task_t));
    task->text = malloc(sizeof(char) * len);

    task->finished = finished;
    task->deleted  = 0;
    strncpy(task->text, text, len);

    return task;
}

task_t **list_add(task_t **tasks, task_t *task, size_t *used, size_t *size) {
    if (*used == *size) {
        *size *= 2;
        tasks = realloc(tasks, *size * sizeof(task_t));
    }

    tasks[(*used)++] = task;
    return tasks;
}

void delete_task(task_t *task) {
    task->deleted = 1;
}

void finish_task(task_t *task) {
    task->finished ^= 1;
}

char *finish_s(int finished) {
    return finished ? done_s : n_done_s;
}

// IO

task_t **load_list(char *filename, size_t *n_tasks, size_t *size) {
    FILE *fp = fopen(filename, "r");

    if (!fp)
        return NULL;

    task_t **tasks = malloc(sizeof(task_t) * *size);

    char *buf = NULL;
    size_t n = 0;
    size_t len;

    int finished;

    while ((len = getline(&buf, &n, fp)) != -1) {
        sscanf(buf, "%d:%[^\n]", &finished, buf);
        list_add(tasks, init_task(buf, len, finished), n_tasks, size);
    }

    free(buf);
    fclose(fp);

    return tasks;
}

void dump_list(char *filename, task_t **tasks, size_t used) {
    if (tasks == NULL) {
        remove(filename);
        return;
    }

    FILE *fp = fopen(filename, "w");

    for (int i = 0; i < used; i++) {
        if (tasks[i]->deleted)
            continue;
        fprintf(fp, "%d:%s\n", tasks[i]->finished, tasks[i]->text);
    }

    fclose(fp);

    return;
}

void free_list(task_t **tasks, size_t used) {
    for (int i = 0; i < used; i++)
        free(tasks[i]->text);
    free(tasks);

    return;
}

void print_list(task_t **tasks, size_t used) {
    int display = 0;
    for (int i = 0; i < used; i++) {
        if (tasks[i]->deleted)
            continue;
        printf("%d. %s %s\n", display, finish_s(tasks[i]->finished), tasks[i]->text);
        display++;
    }

    return;
}
