#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "task.h"

task_t *init_task(char *text, size_t len, int finished) {
    task_t *task = malloc(sizeof(task_t));
    task->text = malloc(sizeof(char) * len);

    task->finished = finished;
    task->deleted  = 0;
    strncpy(task->text, text, len);

    return task;
}

info_t *init_info() {
    info_t *info = malloc(sizeof(info_t));
    info->size = INIT_SIZE;
    info->used = 0;


    return info;
}

task_t **list_add(task_t **tasks, task_t *task, info_t *info) {
    if (info->used == info->size) {
        info->size *= 2;
        tasks = realloc(tasks, info->size * sizeof(task_t));
    }

    tasks[(info->used)++] = task;
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

task_t **load_list(char *filename, info_t *info) {
    FILE *fp = fopen(filename, "r");

    task_t **tasks = calloc(sizeof(task_t), info->size);

    if (fp == NULL)
        return tasks;

    char *buf = NULL;
    size_t n = 0;
    size_t len;

    int finished;

    while ((len = getline(&buf, &n, fp)) != -1) {
        sscanf(buf, "%d:%[^\n]", &finished, buf);
        tasks = list_add(tasks, init_task(buf, len - 2, finished), info);
    }

    free(buf);
    fclose(fp);

    return tasks;
}

void dump_list(char *filename, task_t **tasks, info_t *info) {
    FILE *fp = fopen(filename, "w");

    struct stat st;

    for (int i = 0; i < info->used; i++) {
        if (tasks[i]->deleted)
            continue;
        fprintf(fp, "%d:%s\n", tasks[i]->finished, tasks[i]->text);
    }

    fclose(fp);

    if (stat(filename, &st) != -1 && st.st_size == 0)
        remove(FILENAME);

    return;
}

void free_list(task_t **tasks, info_t *info) {
    for (int i = 0; i < info->used; i++) {
        free(tasks[i]->text);
        free(tasks[i]);
    }
    free(info);
    free(tasks);

    return;
}

void print_list(task_t **tasks, info_t *info) {
    int display = 0;
    for (int i = 0; i < info->used; i++) {
        if (tasks[i]->deleted)
            continue;
        printf("%3d. %s %s\n", display, finish_s(tasks[i]->finished), tasks[i]->text);
        display++;
    }

    return;
}
