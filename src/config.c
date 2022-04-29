#include "config.h"
#include "array.h"

#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <toml.h>
#include <unistd.h>

struct config *conf;

static struct config config_defaults = {
    .filename = ".todo.json",

    .symbols = {" ", "x"},

    .menu_marker = ">",

    .pad_x = 0,
    .pad_y = 0,

    .center = false,
};

static array_t *str_p;

static const char *get_user_home_dir(void)
{
    const struct passwd *passwd = getpwuid(getuid());
    if (passwd == NULL)
        return NULL;
    return passwd->pw_dir;
}

int extract_conf(void)
{
    conf = malloc(sizeof(struct config));
    memcpy(conf, &config_defaults, sizeof(struct config));

    // const char *xdg_config_home = getenv("XDG_CONFIG_HOME");
    const char *user_home_dir = get_user_home_dir();

    char *config_dir;

    // TODO: proper config search... no hardcoded path
    if (user_home_dir)
        config_dir = strcat((char *)user_home_dir, "/.config/nctd/config.toml");

    FILE *fp = fopen(config_dir, "r");
    if (!fp) {
        return 1;
    }

    char errbuf[200];

    toml_table_t *tconf = toml_parse_file(fp, errbuf, sizeof(errbuf));
    fclose(fp);

    if (!tconf) {
        return 1;
    }

    str_p = init_array();
    toml_datum_t datum;

    datum = toml_string_in(tconf, "filename");
    if (datum.ok) {
        conf->filename = datum.u.s;
        a_push(str_p, datum.u.s);
    }

    toml_table_t *tmenu = toml_table_in(tconf, "menu");
    if (tmenu) {
        datum = toml_string_in(tmenu, "finished_symbol");
        if (datum.ok) {
            conf->symbols[1] = datum.u.s;
            a_push(str_p, datum.u.s);
        }
        datum = toml_string_in(tmenu, "unfinished_symbol");
        if (datum.ok) {
            conf->symbols[0] = datum.u.s;
            a_push(str_p, datum.u.s);
        }
        datum = toml_string_in(tmenu, "menu_marker");
        if (datum.ok) {
            conf->menu_marker = datum.u.s;
            a_push(str_p, datum.u.s);
        }
        datum = toml_int_in(tmenu, "pad");
        if (datum.ok) {
            conf->pad_x = conf->pad_y = datum.u.i;
        }
        datum = toml_int_in(tmenu, "pad_x");
        if (datum.ok) {
            conf->pad_x = datum.u.i;
        }
        datum = toml_int_in(tmenu, "pad_y");
        if (datum.ok) {
            conf->pad_y = datum.u.i;
        }
        datum = toml_bool_in(tmenu, "center");
        if (datum.ok) {
            conf->center = datum.u.b;
        }
    }

    toml_free(tconf);

    return 0;
}

int free_conf(void)
{
    if (str_p)
        a_destroy(str_p);
    free(conf);

    return 0;
}
