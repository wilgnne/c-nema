#include "stdio.h"
#include "string.h"

#include "common/cine.h"

void saveSala(Sala *sala) {
    FILE *f = fopen("database.bin", "wb");
    fwrite(sala, sizeof(Sala), 1, f);
    fclose(f);
}

void readSala(Sala *sala) {
    FILE *f = fopen("database.bin", "rb");

    if (f == NULL) {
        printf("DATABASE NOT FOUND\n\n");
        clearSala(sala);
        strcpy(sala->nome, "Sala 01");
        saveSala(sala);
        f = fopen("database.bin", "rb");
    }

    fread(sala, sizeof(Sala), 1, f);
    fclose(f);
}


void header()
{
    system("@cls||clear");
    printf("\n");
    printf("       _..._                                                                 .-'''-.                          \n");
    printf("    .-'_..._''.                                                             '   _    \\                        \n");
    printf("  .' .'      '.\\ .--.    _..._           __.....__       __  __   ___     /   /` '.   \\                       \n");
    printf(" / .'            |__|  .'     '.     .-''         '.    |  |/  `.'   `.  .   |     \\  '                       \n");
    printf(". '              .--. .   .-.   .   /     .-''''-.  `.  |   .-.  .-.   ' |   '      |  '                      \n");
    printf("| |              |  | |  '   '  |  /     /________\\   \\ |  |  |  |  |  | \\    \\     / /     ____     _____    \n");
    printf("| |              |  | |  |   |  |  |                  | |  |  |  |  |  |  `.   ` ..' /     `.   \\  .'    /    \n");
    printf(". '              |  | |  |   |  |  \\    .-------------' |  |  |  |  |  |     '-...-'`        `.  `'    .'     \n");
    printf(" \\ '.          . |  | |  |   |  |   \\    '-.____...---. |  |  |  |  |  |                       '.    .'       \n");
    printf("  '. `._____.-'/ |__| |  |   |  |    `.             .'  |__|  |__|  |__|                       .'     `.      \n");
    printf("    `-.______ /       |  |   |  |      `''-...... -'                                         .'  .'`.   `.    \n");
    printf("             `        |  |   |  |                                                          .'   /    `.   `.  \n");
    printf("                      '--'   '--'                                                         '----'       '----' \n");
    printf("\n");
}

int decode_option(char *input)
{
    if (strcmp(input, "1\n") == 0)
        return 1;
    if (strcmp(input, "2\n") == 0)
        return 2;
    if (strcmp(input, "3\n") == 0)
        return 3;
    if (strcmp(input, "4\n") == 0)
        return 4;
    return -1;
}

int menu()
{
    char option[20];
    int decoded_option;

    do
    {
        header();
        printf("1 - Reservar\n");
        printf("2 - Comprar\n");
        printf("3 - Cancelar\n");
        printf("4 - Sair\n");

        fgets(option, 20, stdin);

        decoded_option = decode_option(option);
    } while (!(decoded_option > 0 && decoded_option < 5));

    return decoded_option;
}

int decode_poltrona(char *input, int *row, int *col)
{
    if (input[0] >= 'A' && input[0] <= ('A' + ROWS))
    {
        if (input[1] >= '1' && input[1] <= ('1' + COLS))
        {
            *row = input[0] - 'A';
            *col = input[1] - '1';
            return 1;
        }
        return 0;
    }
    return 0;
}

int reservar_poltrona(Poltrona *poltrona, Status tipo_de_reserva)
{
    if (tipo_de_reserva == LIVRE)
    {
        poltrona->status = tipo_de_reserva;
        return 1;
    }
    else if (poltrona->status == 0)
    {
        printf("Nome: ");
        fgets(poltrona->name, 50, stdin);
        poltrona->status = tipo_de_reserva;
        return 1;
    }
    
    return 0;
}

int mostrar_sala(Sala *sala, Status tipo_de_reserva)
{
    char input[20];
    int rows, cols;

    readSala(sala);
    system("@cls||clear");
    printf("----%s---\n\n", sala->nome);

    for (int i = ROWS - 1; i >= 0; i--)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (j == 2 || j == COLS - 2)
                printf("  ");

            if (sala->poltronas[i][j].status == LIVRE)
                printf("\033[0;32m");
            if (sala->poltronas[i][j].status == RESERVADO)
                printf("\033[0;33m");
            if (sala->poltronas[i][j].status == COMPRADO)
                printf("\033[0;31m");

            printf("%c%d ", 'A' + i, j + 1);

            printf("\033[0m");
        }
        if (i == 1)
            printf("\n");
        printf("\n");
    }

    printf("\n\n-----TELA-----\n");
    printf("Entre com o codigo da poltrona, ou um valor invalido para sair:\n");

    fflush(stdin);
    fgets(input, 20, stdin);

    if (decode_poltrona(input, &rows, &cols))
    {
        if (reservar_poltrona(&sala->poltronas[rows][cols], tipo_de_reserva))
        {
            if (tipo_de_reserva == LIVRE)
                printf("Liberado com Sucesso\n");
            else if (tipo_de_reserva == RESERVADO)
                printf("Reservado com Sucesso\n");
            else if (tipo_de_reserva == COMPRADO)
                printf("Comprado com Sucesso\n");
            
            saveSala(sala);
            getchar();
        }
        else
        {
            printf("Poltrona reservada\n");
            getchar();
        }
    }
    else
    {
        printf("Sair");
    }
}

int clearSala(Sala *sala)
{
    memset(sala, 0, sizeof(Sala));
}
