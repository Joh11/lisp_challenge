#ifndef PRETTIFY_H
#define PRETTIFY_H

#include <stdlib.h>

#include "sexpr.h"

// This is unsafe but we don't care
// TODO make it safe
// TODO (A . (B . NIL)) -> (A B)
char *sprettify(sexpr_ptr id, char *str);

#endif
