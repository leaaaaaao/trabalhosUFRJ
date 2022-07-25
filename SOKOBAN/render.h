/* Structs */
typedef struct _CAIXA
{
    int coordy, coordx, onplace;
    struct _CAIXA *next;
} Caixa;

struct jogador {
    int coordy, coordx;
} player;

/* Macros */
#define CHAO 0
#define OBJETIVO 1
#define PAREDE 2
#define JOGADOR 5
#define CAIXA 6

/* Protótipos */
void createCaixa (int newcoordy, int newcoordx);
void clearCaixas (void);
void clearMap (void);
int temCaixa (int yUnk, int xUnk);
void printFaseAtual (int dimY, int dimX);
void initfase1 (void);
void initfase2 (void);
void initfase3 (void);
void initfase4 (void);
void initfase5 (void);