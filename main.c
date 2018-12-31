#include <stdio.h>
#include <stdlib.h>

#include "init.h"
#include "terminate.h"
#include "prettify.h"

int main(int argc, char *argv[])
{
    printf("Init phase : \n");

    fillSexprTable(10000);

    newPair(300, 0, 1);
    char temp[100];
    sprettify(300, temp);
    printf("Prettify test : %s\n", temp);

    printf("Terminating phase : \n");

    freeSexprTable();
    
    return 0;
}
