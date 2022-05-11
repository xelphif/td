#pragma once

#include "array.h"

extern char *filename;

int serialize(array_t *array);
int deserialize(array_t *array);
