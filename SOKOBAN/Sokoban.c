/** Trabalho final da disciplina de Computação I.
 * O programa é o jogo sokoban completo na linguagem c,
 * com cinco níveis, contendo todas as mecânicas do jogo original, 
 * além de ser portável entre sistemas operacionais diferentes ou máquinas mais antigas.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "render.h"

#ifdef _WIN32
#include <conio.h>
#endif

/* Prototipos */
#ifdef __linux__
char getinput(void);
#endif
void menuPrincipal (void);
int start (int numfase);
Caixa *getCaixa (int yUnk, int xUnk);
int move (int dx, int dy);
int ganhou (void);

/* Globais */
Caixa *caixas = NULL;

int alt, larg;

int fase1 [11][19] = {
                    {0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {2, 2, 2, 0, 2, 0, 2, 2, 0, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2},
                    {2, 0, 0, 0, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 0, 0, 1, 1, 2},
                    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2},
                    {2, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 0, 2, 2, 0, 0, 1, 1, 2},
                    {0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                    {0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}
                    };
                    
                    
int fase2 [10][14] = {
                    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0},
                    {2, 1, 1, 0, 0, 2, 0, 0, 0, 0, 0, 2, 2, 2},
                    {2, 1, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2},
                    {2, 1, 1, 0, 0, 2, 0, 2, 2, 2, 2, 0, 0, 2},
                    {2, 1, 1, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2},
                    {2, 1, 1, 0, 0, 2, 0, 2, 0, 0, 0, 0, 2, 2},
                    {2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 0, 0, 2},
                    {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
                    {0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
                    {0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
                    };


int fase3 [10][17] = {
                    {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 2, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 0, 0},
                    {2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 0, 2, 2, 2},
                    {2, 1, 1, 1, 1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2},
                    {2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
                    {2, 1, 1, 1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                    {2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0}
                    };

int fase4 [14][19] = {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 1, 2},
                    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 1, 1, 1, 2},
                    {2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2},
                    {2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 1, 2},
                    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 1, 2},
                    {2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2},
                    {2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
                    {2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0},
                    {2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
                    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0},
                    {2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
                    {2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0},
                    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}
                    };
int fase5[13][17] = {
                    {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 2, 2, 2, 2},
                    {0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 2, 0, 0, 2},
                    {0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2},
                    {2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 2},
                    {2, 1, 1, 1, 1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2},
                    {2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0},
                    {2, 1, 1, 1, 1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 0},
                    {2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 2, 2, 0, 2, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0}
                    };

int jogavel [20][20];

int main (void)
{
    int faseEscolhida, nxt = 1;

    while (1)
    {
        #ifdef _WIN32
        system("cls");
        #endif

        #ifdef __linux__
        system("clear");
        #endif
        menuPrincipal();
        do
        {
            #ifdef _WIN32
            faseEscolhida = tolower(getch());
            #endif

            #ifdef __linux__
            faseEscolhida = getinput();
            #endif

            #ifdef _WIN32
            system("cls");
            #endif

            #ifdef __linux__
            system("clear");
            #endif

            menuPrincipal();

            if (faseEscolhida == 'q') return 0;
            
            if (faseEscolhida == 'h')
            {
                puts ("W para andar para cima");
                puts ("A para andar para a esquerda");
                puts ("S para andar para baixo");
                puts ("D para andar para a direita");

                puts ("Q para sair da fase (durante o jogo) ou sair do jogo (no menu principal)");
                puts ("R para reiniciar a fase");
                puts ("H para esse menu :D");
            }
        }
        while (faseEscolhida < '0' || faseEscolhida > '5');
        nxt = faseEscolhida - '0';

        while ((nxt = start(nxt))); 
    }
    return 0;
}

void menuPrincipal (void)
{
    puts("----------SOKOBAN----------\n");
    puts("Selecione a fase: (1-5)");
    printf("1 ");
    printf("2 ");
    printf("3 ");
    printf("4 ");
    printf("5 ");
    puts("\n");
    puts("H para ajuda");
}


/** Retorna a próxima fase que você quer jogar, ou seja, numfase se você apertar R de reset, 
 * numfase + 1 se vc passar pra próxima ou 0 se vc quiser voltar ao menu, porque vai dar false na condição da main
 * */
int start (int numfase)
{
    char key;
    int win = 0;

    switch (numfase)
    {
    case 1:
        initfase1();
        alt = 11;
        larg = 19;
        break;
    case 2:
        initfase2();
        alt = 10;
        larg = 14;
        break;
    case 3:
        initfase3();
        alt = 10;
        larg = 17;
        break;
    case 4:
        initfase4();
        alt = 14;
        larg= 19;
        break;
    case 5:
        initfase5();
        alt = 13;
        larg = 17;
        break;
    default:
        break;
    }

    do
    {
        #ifdef _WIN32
        system("cls");
        #endif

        #ifdef __linux__
        system("clear");
        #endif
    
        printFaseAtual(alt, larg);

        #ifdef _WIN32
        key = tolower(getch());
        #endif

        #ifdef __linux__
        key = getinput();
        #endif

        switch (key)
        {
        case 'w':
            win = move(0, -1);

            break;
        case 'a':
            win = move(-1, 0);
            
            break;
        case 's':
            win = move(0, 1);
            
            break;
        case 'd':
            win = move(1, 0);
            
            break;
        default:
            break;
        }
    }
    while (key != 'q' && key != 'r' && !win);

    if (win)
    {
        if (numfase < 5) puts("Proxima fase - N");

        puts("Voltar ao Menu - M");
        puts("Sair - Q");
        
        do
        {
            #ifdef _WIN32
            key = tolower(getch());
            #endif

            #ifdef __linux__
            key = getinput();
            #endif

            switch (key)
            {
            case 'n':
                return numfase + 1;

                break;
            case 'm':
                return 0;
                
                break;
            case 'q':
                exit(0);
            
                break;
            default:
                break;
            }
        }
        while (key != 'n' && key != 'm' && key != 'q');
    }
    if (key == 'q')
        return 0;
    if (key == 'r')
    {
        return numfase;
    }
    return 0;
}

Caixa *getCaixa (int yUnk, int xUnk)
{
    Caixa *search;

    search = caixas;

    while (search != NULL)
    {
        if (search->coordy == yUnk && search ->coordx == xUnk)
            return search;

        search = search->next;
    }
    return caixas;
}

/* Retorna true se esse movimento te fez ganhar o jogo */
int move(int dx, int dy)
{
    Caixa *aux;    

    if (temCaixa(player.coordy + dy, player.coordx + dx))
    {
        if (temCaixa(player.coordy + 2*dy, player.coordx + 2*dx) ||   jogavel[player.coordy + 2*dy][player.coordx + 2*dx] == PAREDE )
        {
            return 0;
        } 
        else 
        {
            aux = getCaixa(player.coordy + dy, player.coordx + dx);
            aux->coordy += dy;
            aux->coordx += dx;
    
            player.coordy += dy;
            player.coordx += dx;

            if (!(aux->onplace) && jogavel [aux->coordy][aux->coordx] == OBJETIVO)
            {
                aux->onplace = 1;
                if (ganhou())
                {
                    #ifdef _WIN32
                    system("cls");
                    #endif

                    #ifdef __linux__
                    system("clear");
                    #endif

                    printFaseAtual(alt, larg);
                    return 1;
                }
            }
            else if ((aux->onplace) && jogavel [aux->coordy][aux->coordx] != OBJETIVO)
                aux->onplace = 0;
            return 0;
        }
    } 
    else 
    {
        if (jogavel[player.coordy + dy][player.coordx + dx] == CHAO ||  jogavel[player.coordy + dy][player.coordx + dx] == OBJETIVO)
        {
            player.coordy += dy;
            player.coordx += dx;
            return 0;
        }
    }
    return 0;
}

int ganhou (void)
{
    Caixa *check = caixas;

    while (check != NULL)
    {
        if (!(check->onplace))
            return 0;
        check = check->next;
    }
    return 1;
}

#ifdef __linux__
char getinput(void)
{
    char ans = 'a';
    system("/bin/stty raw");
    
    ans = tolower(getc(stdin));

    system("/bin/stty cooked");

    return ans;
}
#endif

/* RENDER */

void createCaixa (int newcoordy, int newcoordx)
{
    Caixa *iterator = caixas;
    if (caixas == NULL)
    {
        if ((caixas = malloc(sizeof(Caixa))) == NULL)
        {
            puts ("Erro ao criar entidade.....\n");
            exit(1);
        }
        caixas->coordy = newcoordy;
        caixas->coordx = newcoordx;
        caixas->onplace = 0;
        caixas->next = NULL;
    }
    else
    {
        while (iterator->next != NULL)
            iterator = iterator->next;
        
        if ((iterator->next = malloc(sizeof(Caixa))) == NULL)
        {
            puts ("Erro ao criar entidade.....\n");
            exit(1);
        }
        iterator->next->coordy = newcoordy;
        iterator->next->coordx = newcoordx;
        iterator->next->onplace = 0;
        iterator->next->next = NULL;
    }
}

void clearCaixas (void)
{
    Caixa *temp;

    while (caixas != NULL)
    {
        temp = caixas->next;
        free (caixas);
        caixas = temp;
    }
}

void clearMap (void)
{
    int x, y;
    clearCaixas();

    for (y = 0; y < 20; y++)
    {
        for (x = 0; x < 20; x++)
        {
            jogavel[y][x] = 0;
        }
    }
}

int temCaixa (int yUnk, int xUnk)
{
    Caixa *search;
    
    search = caixas;

    while (search != NULL)
    {
        if (search->coordy == yUnk && search ->coordx == xUnk)
            return 1;

        search = search->next;
    }

    return 0;
}

void printFaseAtual (int dimY, int dimX)
{
    int y, x;
    Caixa *aux;

    for (y = 0; y < dimY; y++)
    {
        for (x = 0; x < dimX; x++)
        {
            if (temCaixa (y, x))
            {
                aux = getCaixa(y, x);
                if (aux->onplace)
                    printf("\033[1;32m()\033[m");
                else
                    printf("()");
            }
            else if(player.coordy == y && player.coordx == x)
            {
                printf("::");
            }
            else
            {
                switch (jogavel[y][x])
                {
                case PAREDE:
                    printf("\033[1;31m||\033[m");
                    break;
                case OBJETIVO:
                    printf("\033[1;36m[]\033[m");
                    break;
                case CHAO:
                    printf("  ");
                    break;
                default:
                    break;
                }
            }
        }
        printf("\n");
    }
}

void initfase1 (void)
{
    int y, x;
    clearMap();
    player.coordy = 8;
    player.coordx = 11;    

    createCaixa(7, 2);
    createCaixa(7, 5);
    createCaixa(2, 5);
    createCaixa(4, 5);
    createCaixa(3, 7);
    createCaixa(4, 7);

    for (y = 0; y < 11; y++)
    {
        for (x = 0; x < 19; x++)
        {
            jogavel[y][x] = fase1[y][x];
        }
    }
}

void initfase2 (void)
{
    int y, x;
    clearMap();
    player.coordy = 4;
    player.coordx = 7;

    createCaixa(2, 7);
    createCaixa(2, 10);
    createCaixa(3, 6);
    createCaixa(5, 10);
    createCaixa(6, 9);
    createCaixa(6, 11);
    createCaixa(7, 4);
    createCaixa(7, 7);
    createCaixa(7, 9);
    createCaixa(7, 11);

    for (y = 0; y < 10; y++)
    {
        for (x = 0; x < 14; x++)
        {
            jogavel[y][x] = fase2[y][x];
        }
    }
}

void initfase3 (void)
{
    int y, x;
    clearMap();   
    player.coordy = 1;
    player.coordx = 14;

    createCaixa(2, 10);
    createCaixa(2, 12);
    createCaixa(3, 10);
    createCaixa(3, 13);
    createCaixa(4, 10);
    createCaixa(4, 12);
    createCaixa(5, 10);
    createCaixa(6, 10);
    createCaixa(6, 13);
    createCaixa(7, 9);
    createCaixa(7, 12);



    for (y = 0; y < 10; y++)
    {
        for (x = 0; x < 17; x++)
        {
            jogavel[y][x] = fase3[y][x];
        }
    }
}

void initfase4 (void) {
    
    int y, x;
    clearMap();

    player.coordy = 11;
    player.coordx = 10;

    createCaixa(3, 8);
    createCaixa(3, 10);
    createCaixa(4, 2);
    createCaixa(4, 3);
    createCaixa(4, 4);
    createCaixa(4, 6);
    createCaixa(4, 9);
    createCaixa(5, 3);
    createCaixa(5, 9);
    createCaixa(6, 2);
    createCaixa(6, 3);
    createCaixa(6, 6);
    createCaixa(6, 8);
    createCaixa(6, 10);
    createCaixa(7, 3);
    createCaixa(10, 6);
    createCaixa(11, 3);
    createCaixa(11, 4);
    createCaixa(11, 6);
    createCaixa(11, 7);
    
    for(y = 0; y < 14; y++) 
    {
        for(x = 0; x < 19; x++) 
        {
            jogavel[y][x] = fase4[y][x];
        }
    }
}

void initfase5 (void){
    int y, x;
    clearMap();
    
    player.coordy = 7;
    player.coordx = 14;

    createCaixa(2, 11);
    createCaixa(3, 14);
    createCaixa(5, 10);
    createCaixa(5, 13);
    createCaixa(6, 9);
    createCaixa(6, 11);
    createCaixa(6, 12);
    createCaixa(7, 9);
    createCaixa(7, 12);
    createCaixa(8, 11);
    createCaixa(9, 10);
    createCaixa(9, 12);

    for(y = 0; y < 13; y++) 
    {
        for(x = 0; x < 17; x++) 
        {
            jogavel[y][x] = fase5[y][x];
        }
    }
    
}