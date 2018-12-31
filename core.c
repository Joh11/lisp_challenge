#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "core.h"
#include "init.h"
#include "sexpr.h"
#include "parse.h"
#include "eval.h"
#include "prettify.h"
#include "terminate.h"

tagged_sexpr **sexprTable;
int sexprTableSize;

int quit = 0;

int mainLoop()
{
    fillSexprTable(10000);
    
    while(!quit)
    {
	// read line from stdin

	// TODO variable length
	char str[1024] = "";
	fgets(str, 1024, stdin);
	cleanStr(str);

	// tokenize
	llist *tokens = tokenize(str);
	llist *current = tokens;


	// TODO maybe collect garbage
	while(current) // while there are still some tokens
	{
	    sexpr_ptr sexpr = parseOne(&current); // parse once
	    sexpr = eval(sexpr); // eval
	    prettify(sexpr); // print the prettified result
	}

	// free the tokens
	freeLlist(tokens);

	// loop
    }

    freeSexprTable();
    
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
