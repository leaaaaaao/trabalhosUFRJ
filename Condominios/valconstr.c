/**
 * O programa, proposto pela professora de computação, tem como objetivo
 * gerenciar os condomínios de uma construtora, guardando informações
 * sobre os condomínios em si, bem como os blocos pertencentes a cada condominio.
 * O programa deve possibilitar que o usuário crie, consulte, edite ou apague condomínios
 * e blocos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _ENDERECO {
    int CEP;
    char UF[3];
    char cidade[30];
    char bairro[30];
    char rua[30];
    int numero;
} Endereco;

typedef struct _BLOCO {
    int *aptos;
    int nbloco, qtdapto, andares;
} Bloco;

typedef struct _CONDOMINIO {
    char nome [30];
    Endereco endereco;
    Bloco *blocos;
    struct _CONDOMINIO *next;
} Condominio;

void print_menu(void);
void fixStr (char *string);
void criarCondominio (Condominio **lista);
Endereco lerEndereco (void);

int main (void)
{
    int cod;
    Condominio *head = NULL;

    while (1)
    {
        print_menu();    
        while(!scanf("%d", &cod))
        {
            while (getchar() != '\n');
            printf("ERRO: Insira apenas numeros\n>");
        }
        switch(cod)
        {
            case 1:
                criarCondominio(&head);
                break;

            default:
                return 0;
                break;
        }
    }
}

void print_menu(void)
{
    puts("O que deseja fazer?");
    puts("1. Criar condominio");

}

void fixStr (char *string)
{
    int i;
    for (i = 0; string[i] != '\n'; i++);
    string[i] = '\0';
}

void criarCondominio (Condominio **lista)
{
    if (*lista == NULL)
    {
        Endereco enderecoNovo;
        *lista = malloc(sizeof(Condominio));
        if (!lista)
        {
            puts("[ERRO: Nao foi possivel criar o condominio]");
            return;
        }
        printf("Insira o nome do novo condominio:\n>");
        getchar();
        fgets((*lista)->nome, 30, stdin);
        fixStr((*lista)->nome);

        enderecoNovo = lerEndereco();
        (*lista)->endereco = enderecoNovo;
        
        /* Inicia a lista de blocos como vazia, e o ponteiro pro próximo como NULL, já que não há próximo elemento. */
        (*lista)->blocos = NULL;
        (*lista)->next = NULL;
    }
}

Endereco lerEndereco (void)
{
    Endereco ans;
    puts("-----ENDERECO-----");
    printf("CEP:\n>");
    while(!scanf("%d", &ans.CEP))
    {
        while (getchar() != '\n');
        printf("ERRO: Insira apenas numeros\n>");
    }

    printf("UF:\n>");
    getchar();
    scanf("%s", ans.UF);
    
    printf("Cidade:\n>");
    getchar();
    fgets(ans.cidade, 30, stdin);
    fixStr(ans.cidade);

    printf("Bairro:\n>");
    getchar();
    fgets(ans.bairro, 30, stdin);
    fixStr(ans.bairro);
    
    printf("Rua:\n>");
    getchar();
    fgets(ans.rua, 30, stdin);
    fixStr(ans.rua);

    printf("Numero:\n>");
    while(!scanf("%d", &ans.numero))
    {
        while (getchar() != '\n');
        printf("ERRO: Insira apenas numeros\n>");
    }

    return ans;
}