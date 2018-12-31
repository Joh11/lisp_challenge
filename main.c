#include <stdio.h>
#include <stdlib.h>

#include "init.h"
#include "terminate.h"
#include "prettify.h"
#include "parse.h"

int main(int argc, char *argv[])
{
    /*
    printf("Init phase : \n");

    fillSexprTable(10000);


    newPair(300, 0, 1);
    char temp[100] = "";
    sprettify(300, temp);
    printf("Prettify test : %s\n", temp);
    
    char str[] = "( + 2 43 e3zhue32ueu SQSQS . ezhd . NIL)";
    printf("cleanStr test : %s", str);
    cleanStr(str);
    printf("%s\n", str);
    
    llist *ll = tokenize(str);
    llist *ll2 = ll;
    while(ll2)
    {
	printf("%s / ", ll2->str);
	ll2 = ll2->next;
    }
    freeLlist(ll);

    printf("Terminating phase : \n");
    
    freeSexprTable();
    */
    return mainLoop();
}
