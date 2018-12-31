#ifndef PARSE_H
#define PARSE_H

#include "sexpr.h"

// linked list of char* ; just used here so defined here
typedef struct llist_t
{
    char *str;
    struct llist_t *next;
} llist;


// keep only ().-, 0-9, and change a-z -> A-Z
void cleanStr(char *str);

// return a pointer to a linked list of tokens (ptr because it may be empty)
llist *tokenize(const char* str);

void freeLlist(llist *ll);

sexpr_ptr parseOne(llist **ll);

sexpr_ptr recParseList(llist **ll);


typedef enum {LPAR, DOT, RPAR, MISC} token_type;

token_type getTokenType(const char* str);

#endif
