#include "stdio.h"
#include "string.h"

#include "common/cine.h"

int main()
{
    int option;

    Sala sala;
    readSala(&sala);

    do
    {
        option = menu();

        switch (option)
        {
        case 1: 
            mostrar_sala(&sala, RESERVADO);
            break;
        case 2:
            mostrar_sala(&sala, COMPRADO);
            break;
        case 3:
            mostrar_sala(&sala, LIVRE);
            break;

        default:
            break;
        }

    } while (option != 4);

    return 0;
}
