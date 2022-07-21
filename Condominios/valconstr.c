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
#include <time.h>

/* Estruturas */
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
    int nblocos;
    Bloco *blocos;
    struct _CONDOMINIO *next;
} Condominio;

/* Protótipos */
void menuPrincipal(void);
void getStr (char *string);
Endereco lerEndereco (void);
Condominio lerCondominio (void);
int strCompareUpper(char *str1, char *str2);
void inserirCondominio (Condominio *lista, Condominio novoCond);
void inserirNoInicio (Condominio **lista, Condominio novoCond);
void mostrarCondominio (Condominio atual);
void listarCondominios (Condominio *lista);
void deletarCondominio (Condominio **lista, char *nomedel);

/*-------------------------------------------------------------------------------------------------------------------*/
int main (void)
{
    int cod;
    Condominio *head = NULL, *iterador, condos;
    FILE *fp_save;
    char nomedel[30];


    if ((fp_save = fopen("save", "rb")) != NULL)
    {
        fread(condos.nome, sizeof(char) * 30, 1, fp_save);
        if (!feof(fp_save))
        {
            fread(&condos.endereco, sizeof(Endereco), 1, fp_save);
            fread(&condos.nblocos, sizeof(int), 1, fp_save);
            /* FALTA LER OS BLOCOS */
            condos.blocos = NULL;
            condos.next = NULL;
            inserirNoInicio(&head, condos);
        }
        while (fread(condos.nome, sizeof(char) * 30, 1, fp_save) == 1)
        {
            fread(&(condos.endereco), sizeof(Endereco), 1, fp_save);
            fread(&(condos.nblocos), sizeof(int), 1, fp_save);
                /* FALTA LER OS BLOCOS */
            condos.blocos = NULL;
            condos.next = NULL;
            inserirCondominio(head, condos);
        }
        fclose(fp_save);
    }


    while (1)
    {
        menuPrincipal();    
        while(!scanf("%d", &cod))
        {
            while (getchar() != '\n');
            printf("ERRO: Insira apenas numeros\n>");
        }
        while (getchar() != '\n');

        switch(cod)
        {
            case 1:
                condos = lerCondominio();
                if (head == NULL || (strCompareUpper(head->nome, condos.nome) > 0))
                    inserirNoInicio(&head, condos);
                else
                    inserirCondominio(head, condos);
                break;
            case 2:
                listarCondominios(head);
                break;
            case 3:
                puts("Insira o nome do condominio a deletar:");
                getStr(nomedel);
                deletarCondominio(&head, nomedel);
                break;
            case 4:
                
                break;
            case 5:
                
                break;
            case 6:
                if ((fp_save = fopen ("save", "wb")) == NULL)
                {
                    puts("Erro ao salvar :(");
                    return 1;
                }

                iterador = head;
                
                while (iterador != NULL)
                {
                    fwrite(&(iterador->nome), sizeof(char) * 30, 1, fp_save);
                    fwrite(&(iterador->endereco), sizeof(Endereco), 1, fp_save);
                    fwrite(&(iterador->nblocos), sizeof(int), 1, fp_save);
                    /* FALTA ESCREVER OS BLOCOS EM SI */
                    iterador = iterador->next;
                }
                puts("Encerrando...");
                return 0;
            default:
                return 0;
                break;
        }
    }
}

void menuPrincipal(void)
{
    puts("O que deseja fazer?");
    puts("1. Criar condominio");
    puts("2. Listar condominios");
    puts("3. Deletar condominio");
    puts("4. Editar condominio");
    puts("5. Filtrar condominios");
    puts("6. Salvar e sair");
}

void getStr (char *string)
{
    int len;

    fgets(string, 30, stdin);
    len = strlen(string);
    string[len - 1] = '\0';
}

Endereco lerEndereco (void)
{
    Endereco ans;
    puts("-----ENDERECO-----");

    printf("UF:\n>");
    scanf("%s", ans.UF);
    while (getchar() != '\n');
    
    printf("Cidade:\n>");
    getStr(ans.cidade);
    
    printf("CEP:\n>");
    while(!scanf("%d", &ans.CEP))
    {
        while (getchar() != '\n');
        printf("ERRO: Insira apenas numeros\n>");
    }
    while (getchar() != '\n');

    printf("Bairro:\n>");
    getStr(ans.bairro);
    
    printf("Rua:\n>");
    getStr(ans.rua);

    printf("Numero:\n>");
    while(!scanf("%d", &ans.numero))
    {
        while (getchar() != '\n');
        printf("ERRO: Insira apenas numeros\n>");
    }
    while (getchar() != '\n');

    return ans;
}

Condominio lerCondominio (void)
{
    Condominio ans;

    printf("Insira o nome do condominio\n>");
    getStr(ans.nome);

    ans.endereco = lerEndereco();
    ans.blocos = NULL;
    ans.next = NULL;
    ans.nblocos = 0;
    return ans;
}

int strCompareUpper(char *str1, char *str2)
{
    int i, ch1, ch2;
    for(i = 0; str1[i] != '\0' && str2[i] != '\0'; i++)
    {
        if (str1[i] >= 'a' && str1[i] <='z')
            ch1 = str1[i] - 32;
        else 
            ch1 = str1[i];
            
        if (str2[i] >= 'a' && str2[i] <='z')
            ch2 = str2[i] - 32;
        else
            ch2 = str2[i];

        if (!(ch1 - ch2))
            continue;
        else 
            return ch1 - ch2;
    }
    if (str1[i] == str2[i])
        return 0;

    if (str1[i] == '\0')
        return -1;
    else
        return 1;
}

void inserirNoInicio (Condominio **lista, Condominio novoCond)
{
    Condominio *temp;

    temp = *lista;
    if ((*lista = malloc(sizeof(Condominio))) == NULL)
    {
        puts("Erro: nao foi possivel criar o condominio\n");
        return;
    }
    **lista = novoCond;
    (*lista)->next = temp;
}

void inserirCondominio (Condominio *lista, Condominio novoCond)
{
    Condominio *temp, *iterator;
    
    iterator = lista;

    if (!strCompareUpper(iterator->nome, novoCond.nome))
    {
        puts("Erro: ja existe um condominio com esse nome\n");
        return;
    }
    while (iterator->next != NULL && strCompareUpper(iterator->next->nome, novoCond.nome) < 0)
    {
        iterator = iterator->next;
    }
    temp = iterator->next;
    
    if (iterator->next != NULL && !strCompareUpper(iterator->next->nome, novoCond.nome))
    {
        puts("Erro: ja existe um condominio com esse nome\n");
        return;
    }
    
    if ((iterator->next = malloc(sizeof(Condominio))) == NULL)
    {
        puts("Erro: nao foi possivel criar o condominio");
        iterator->next = temp;
        return;
    }
    
    *(iterator->next) = novoCond;
    iterator->next->next = temp;
}

void mostrarCondominio (Condominio atual)
{
    puts("________________________________");
    printf("Nome: %s\n", atual.nome);
    printf("Endereco:\nUF: %s\nCidade: %s\nCEP: %d\n\n", atual.endereco.UF, atual.endereco.cidade, atual.endereco.CEP);
}

void listarCondominios (Condominio *lista)
{
    Condominio *iterator;

    iterator = lista;
    
    if (iterator == NULL)
    {
        puts("Nao ha condominios para mostrar.\n");
        return;
    }
    while(iterator != NULL)
    {
        mostrarCondominio(*iterator);
        iterator = iterator->next;
    }
}

void deletarCondominio (Condominio **lista, char *nomedel)
{
    Condominio *iterator, *temp;

    if (*lista == NULL)
    {
        puts("Nao ha condominios para deletar\n");
        return;
    }

    if (!strCompareUpper((*lista)->nome, nomedel))
    {
        temp = (*lista)->next;
        free(*lista);
        *lista = temp;
        puts("Condominio deletado!!\n");
        return;
    }
    
    iterator = *lista;

    while (iterator->next != NULL)
    {
        if (!strCompareUpper(iterator->next->nome, nomedel))
        {
            temp = iterator->next->next;
            free(iterator->next);
            iterator->next = temp;
            puts("Condominio deletado!!\n");
            return;
        }
        iterator = iterator->next;
    }

    puts("Nao existe um condominio com esse nome.\n");
}