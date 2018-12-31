#ifndef CORE_H
#define CORE_H

#include "sexpr.h"

// The sexpr table
// It is a dynamically allocated table of pointers on tagged_sexpr
// Because each tagged_sexpr may be a null ptr if it is empty
extern tagged_sexpr **sexprTable;
extern int sexprTableSize;

// If the corresponding index is empty, add a new atom with the given data
// return 1 if it worked, 0 otherwise
int newAtom(int id, const char* str);

int newPair(int id, int fst, int snd);

#endif
