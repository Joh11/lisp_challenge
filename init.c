#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "init.h"

#define DIGITS_ALLOCATED 256

void fillSexprTable(int tableSize)
{
    // Check the right size
    if(tableSize < 2 + DIGITS_ALLOCATED)
    {
	printf("insufficient sexpr table size. Using %d instead of %d", 2 + DIGITS_ALLOCATED, tableSize);
	tableSize = 2 + DIGITS_ALLOCATED;
    }
    
    // Allocate a table of the right size
    sexprTable = (tagged_sexpr **)malloc(tableSize * sizeof(tagged_sexpr *));
    sexprTableSize = tableSize;

    // Fill it with NULL ptrs
    int i;
    for(i = 0 ; i < sexprTableSize ; i++)
	sexprTable[i] = NULL;

    // Add nil, t, and digits from 0 to DIGITS_ALLOCATED - 1
    newAtom(0, "NIL");
    newAtom(1, "T");

    for(i = 0 ; i < DIGITS_ALLOCATED ; i++)
    {
	char temp[50]; // 50 should be enough, TODO make something cleaner
	sprintf(temp, "%d", i);
	newAtom(i + 2, temp);
    }
}
