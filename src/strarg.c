#include "strarg.h"

#include <errno.h>
#include <stdlib.h>

// only returns when input is a valid array index
// if input is invalid, returns -1
int strarg(const char *s)
{
    errno = 0;
    char *endptr;

    int val = strtol(s, &endptr, 10);

    if (s == endptr)
        return -1;

    // check if value is out of range or if
    // the input was invalid
    if (errno != 0)
        return -1;

    return val;
}
