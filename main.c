#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char line[1000] ;

    FILE *f1 = fopen("date/t1/d.in", "rt") ;
    if(f1 == NULL)
    {
        puts("Fisierul nu poate fi deschis!\n") ;
        exit(1) ;
    }

    while (fgets(line, sizeof(line), f1) != NULL)
    {
    
    }
 
    FILE *f2 = fopen("out/r.out", "wt") ;
    if(f2 == NULL)
    {
        puts("Fisierul nu poate fi deschis!\n") ;
        exit(1) ;
    }

    fclose(f1) ;
    fclose(f2);

    return 0 ;
}