#ifndef CONFIG_H
#define CONFIG_H

struct config {
    char *filename;

    char *symbols[2];

    char *menu_marker;

    /* unsigned pad_x;
    unsigned pad_y; */
};

extern struct config *conf;

int extract_conf(void);
int free_conf(void);

#endif
