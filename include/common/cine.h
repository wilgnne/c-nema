#define ROWS 6
#define COLS 9

typedef enum
{
    LIVRE,
    RESERVADO,
    COMPRADO
} Status;

typedef struct
{
    char name[50];
    Status status;

} Poltrona;

typedef struct
{
    char nome[50];
    Poltrona poltronas[ROWS][COLS];
} Sala;

void header();
int decode_option(char *input);
int menu();
int decode_poltrona(char *input, int *row, int *col);
int reservar_poltrona(Poltrona *poltrona, Status tipo_de_reserva);
int mostrar_sala(Sala *sala, Status tipo_de_reserva);
int clearSala(Sala *sala);

void saveSala(Sala *sala);
void readSala(Sala *sala);