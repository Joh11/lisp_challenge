#ifndef CORE_H
#define CORE_H

#include "sexpr.h"

// The sexpr table
// It is a dynamically allocated table of pointers on tagged_sexpr
// Because each tagged_sexpr may be a null ptr if it is empty
extern tagged_sexpr **sexprTable;
extern int sexprTableSize;

// Can be =1 by the evaluator when it reaches an (exit) command
extern int quit;


// The main loop
int mainLoop();


// If the corresponding index is empty, add a new atom with the given data
// return 1 if it worked, 0 otherwise
int newAtom(sexpr_ptr id, const char* str);

int newPair(sexpr_ptr id, sexpr_ptr fst, sexpr_ptr snd);

// Return -1 if the sexpr table is full
sexpr_ptr getFirstFree();

#endif
