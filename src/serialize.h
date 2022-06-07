#pragma once

#include "array.h"

int file_delete(void);
int serialize(struct array *array);
int deserialize(struct array *array);
