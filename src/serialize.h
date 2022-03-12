#ifndef SERIALIZE_H
#define SERIALIZE_H

// forward declaring structs used in files
typedef struct json_object json_object;
typedef struct array array_t;
typedef struct item item_t;

json_object *init_json_object (item_t *item);
int serialize (char *filename, array_t *array);
int deserialize (char *filename, array_t *array);

#endif
