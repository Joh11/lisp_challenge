#include <stdlib.h>
#include <string.h>

#include "sexpr.h"

tagged_sexpr **sexprTable;
int sexprTableSize;

int quit = 0;

int mainLoop()
{
    return 0;
}

int newAtom(sexpr_ptr id, const char* str)
{
    if(sexprTable[id] != NULL)
	return 0;

    sexprTable[id] = (tagged_sexpr *)malloc(sizeof(tagged_sexpr));
    sexprTable[id]->type = ATOM;
    sexprTable[id]->value.atom_ = malloc(sizeof(char) * (strlen(str) + 1)); // care \0 is not counted
    strcpy(sexprTable[id]->value.atom_, str);

    return 1;
}

int newPair(sexpr_ptr id, sexpr_ptr fst, sexpr_ptr snd)
{
    if(sexprTable[id] || !sexprTable[fst] || !sexprTable[snd])
	// If id is not free, or fst / snd is unbound
	return 0;

    sexprTable[id] = (tagged_sexpr *)malloc(sizeof(tagged_sexpr));
    sexprTable[id]->type = PAIR;
    sexprTable[id]->value.pair_.fst = fst;
    sexprTable[id]->value.pair_.snd = snd;

    return 1;
}

sexpr_ptr getFirstFree()
{
    // TODO maybe something smarter, not in linear time
    for(int i = 0 ; i < sexprTableSize ; i++)
    {
	if(sexprTable[i] == NULL)
	    return i;
    }

    return -1;
}
