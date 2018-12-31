#ifndef SEXPR_H
#define SEXPR_H

// Basically everything sexpr is :
// an atom A (formed of A-Z, 0-9, and -)
// a pair (sexpr1 . sexpr2)
// a lambda

// Every atom is stored in a big table, so that they can be quickly
// garbage collected if necessary

typedef int sexpr_ptr;

// The actual data in an atom :
// a dynamically allocated string, ending in \0 ofc
typedef char* atom;

// A pair : the ids of two sexpr in the sexpr table
typedef struct
{
    sexpr_ptr fst, snd;
} pair;

typedef enum
{
    ATOM, PAIR, LAMBDA
} sexpr_type;

typedef union sexpr_union_t
{
    atom atom_;
    pair pair_;
    void *lambda; // TODO void* for now because I have no clue how to implement it yet
    
} sexpr_union;

typedef struct
{
    sexpr_type type;
    sexpr_union value;

} tagged_sexpr;


// To keep it clear :

// A tagged_sexpr will be used internally in the sexpr table, it is the
// type that owns the dynamically allocated resources (i.e. inside
// atoms)

// A sexpr_ptr is a weak ptr, used everywhere else in the code

#endif
