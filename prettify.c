#include <string.h>

#include "prettify.h"
#include "core.h"

char *sprettify(sexpr_ptr id, char *str)
{
    // If the corresponding sexpr does not exist then ""
    if(sexprTable[id] == NULL)
	return strcpy(str, "");

    switch(sexprTable[id]->type)
    {
    case ATOM:
	strcpy(str, sexprTable[id]->value.atom_);
	return str + strlen(sexprTable[id]->value.atom_);
	break;
    case PAIR:
	str[0] = '(';
	str++;
	str = sprettify(sexprTable[id]->value.pair_.fst, str);
	
	strcpy(str, " . "); str +=3;

	str = sprettify(sexprTable[id]->value.pair_.snd, str);
	str[0] = ')'; str++;
	return str;
	break;
    case LAMBDA:
	// TODO maybe something better
	strcpy(str, "#LAMBDA");
	return str + strlen("#LAMBDA");
	break;

    default: // Just to suppress warning, should never be reached
	return str;
    }
}
