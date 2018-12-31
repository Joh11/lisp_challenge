#include <stdio.h>
#include <stdlib.h>

#include "terminate.h"
#include "core.h"

void freeSexprTable()
{
    int i;

    for(i = 0 ; i < sexprTableSize ; i++)
    {
	if(sexprTable[i] != NULL)
	{
	    switch(sexprTable[i]->type)
	    {
	    case ATOM:
		// First free the string, then the atom itself
		free(sexprTable[i]->value.atom_);
		free(sexprTable[i]);
		break;
	    case PAIR:
		// Do nothing : it may have already been done, or it
		// will be done later on
		break;
	    case LAMBDA:
		// TODO do something here maybe
		break;
	    }

	    sexprTable[i] = NULL;
	}
    }
}
