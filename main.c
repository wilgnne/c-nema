#include "stdio.h"

void t1(char t[]) {
    printf(" t    : %p\n", t);
    printf("&t    : %p\n", &t);    
}

int main()
{
    char texto[] = "Ola";

    printf(" texto: %p\n", texto);
    printf("&texto: %p\n\n", &texto);   

    t1(texto);
    return 0;
}
