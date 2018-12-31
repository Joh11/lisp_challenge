#include <stdlib.h>
#include <string.h>

#include "parse.h"
#include "core.h"

void cleanStr(char *str)
{
    char *temp = malloc(sizeof(char) * (strlen(str) + 1));

    size_t j = 0;
    for(size_t i = 0 ; i < strlen(str) ; ++i)
    {
	char c = str[i];
	// uppercasify	
	if(c >= 97 && c <= 122)
	    c -= 32;

	if(strchr("().-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", c))
	{
	    temp[j] = c;
	    j++;
	}
    }
    temp[j] = '\0';

    strcpy(str, temp);

    free(temp);
}

llist *tokenize(const char* str)
{
    llist root = {NULL, NULL};
    llist *current = &root;

    size_t j = 0;
    for(size_t i = 0 ; i < strlen(str) ; i++)
    {
	char c = str[i];
	if(strchr("().", c)) // 1 char tokens
	{
	    if(j != i) // If a token must be processed first
	    {
		current->next = malloc(sizeof(llist));
		current = current->next;
		current->str = malloc((1 + i - j) * sizeof(char));
		strncpy(current->str, str + j, i - j);
		current->str[i - j] = '\0';
	    }
	    
	    current->next = malloc(sizeof(llist));
	    current = current->next;
	    current->str = malloc(2 * sizeof(char));
	    current->str[0] = c;
	    current->str[1] = '\0';

	    j = i + 1; // forward the second cursor
	}
    }

    if(j != strlen(str)) // We may have to make the last token by ourselves here
    {
	current->next = malloc(sizeof(llist));
	current = current->next;
	current->str = malloc((1 + strlen(str) - j) * sizeof(char));
	strncpy(current->str, str + j, strlen(str) - j);
	current->str[strlen(str) - j] = '\0';
    }

    return root.next;
}

void freeLlist(llist *ll)
{
    if(ll)
    {
	if(ll->str) free(ll->str);
	freeLlist(ll->next);
	free(ll);
    }
}

sexpr_ptr parseOne(llist **ll)
{
    if(!ll || !*ll)
	return -1;

    const char *str = (*ll)->str;
    token_type ttype = getTokenType(str);

    switch(ttype)
    {
    case DOT:
    case RPAR:
	// TODO Big error incoming
	return -1;
	break;

    case MISC:
	// TODO simplify if number
	(*ll) = (*ll)->next;

	if(strcmp(str, "NIL") == 0)
	    return 0;
	if(strcmp(str, "T") == 0)
	    return 1;
	sexpr_ptr ptr = getFirstFree();
	newAtom(ptr, str);
	return ptr;
	break;

    case LPAR:
	(*ll) = (*ll)->next; // Consume the "("

	if(!*ll) // TODO ERROR
	    return -1;
	
	if(strcmp((*ll)->str, ")") == 0) // If this is the empty list, return NIL
	{
	    (*ll) = (*ll)->next; // Consume the ")"
	    return 0; // because sexprTable[0] = ATOM["NIL"]
	}

	return recParseList(ll);
	break;
    }

    return -1; // TODO It should never arrive here
}

sexpr_ptr recParseList(llist **ll)
{
// Goal : to turn A B . C) into (A . (B . C))

    // First recurse once, to get the first sexpr
    // We're guaranteed that this one exists
    sexpr_ptr fst = parseOne(ll);

    if(!*ll) // if token stream empty : TODO error
	return -1;

    if(strcmp((*ll)->str, ")") == 0) // If we've reach the end of the list
    {
	(*ll) = (*ll)->next; // Consume the ")"
	sexpr_ptr ptr = getFirstFree();
	newPair(ptr, fst, 0);
	return ptr;
    }

    if(strcmp((*ll)->str, ".") == 0)
    {
	(*ll) = (*ll)->next; // Consume the "."
	
	if(!*ll) // TODO error
	    return -1;

	sexpr_ptr snd = parseOne(ll);

	if(!*ll || strcmp((*ll)->str, ")") != 0)
	    return -1; // TODO error

	(*ll) = (*ll)->next; // Consume the ")"

	sexpr_ptr ptr = getFirstFree();
	newPair(ptr, fst, snd);
	return ptr;
    }

    // Otherwise, parse the end of the list
    sexpr_ptr snd = recParseList(ll);
    sexpr_ptr ptr = getFirstFree();
    newPair(ptr, fst, snd);
    return ptr;
}

token_type getTokenType(const char* str)
{
    if(strcmp(str, "(") == 0)
	return LPAR;
    if(strcmp(str, ")") == 0)
	return RPAR;
    if(strcmp(str, ".") == 0)
	return DOT;

    return MISC;
}
