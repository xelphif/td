#ifndef SERIALIZE_H
#define SERIALIZE_H

// forward declaring structs used in files
#include "array.h"

#define FILENAME "TODO.json"

int serialize(char *filename, array_t *array);
int deserialize(char *filename, array_t *array);

#endif
