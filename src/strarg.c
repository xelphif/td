#include "strarg.h"

#include <stdlib.h>
#include <errno.h>

// only returns when input is a valid array index
// if input is invalid, returns -1
int strarg(const char *s)
{
    errno = 0;

    int val = (int)strtol(s, (char **)NULL, 10);

    // check if value is out of range or if
    // the input was invalid
    if (errno == ERANGE || errno == EINVAL)
        return -1;

    return val;
}
