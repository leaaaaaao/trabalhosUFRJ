/**
 * O programa, proposto pela professora de computação, tem como objetivo
 * gerenciar os condomínios de uma construtora, guardando informações
 * sobre os condomínios em si, bem como os blocos pertencentes a cada condominio.
 * 
 * O programa deve possibilitar que o usuário crie, consulte, edite ou apague condomínios
 * e blocos.
 * 
 * Os dados do programa devem ser salvos em um arquivo.
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
    int nbloco, qtdapto, andares;
    struct _BLOCO *next;
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
int getInt (void);
Endereco lerEndereco (void);
int strCompareUpper(char *str1, char *str2);
Condominio lerCondominio (void);
int existeCondo (Condominio *lista, char *string);
void inserirCondominio (Condominio *lista, Condominio novoCond);
void inserirNoInicio (Condominio **lista, Condominio novoCond);
void mostrarCondominio (Condominio *atual);
void listarCondominios (Condominio *lista);
void deletarCondominio (Condominio **lista, char *nomedel);
void mostrarBloco (Bloco *atual);
void listarBlocos (Condominio *condo);
Bloco lerBloco (void);
void adicionarBlocoNoInicio (Condominio *condo, Bloco *novoBloco);
void adicionarBloco (Condominio *condo);
void deletarBloco (Condominio *atual, int numdel);
void menuCondominio (void);
void visualizar (Condominio *lista, char *nome);

/*-------------------------------------------------------------------------------------------------------------------*/
int main (void)
{
    int cod;
    char nomecondo[30];
    Condominio *head = NULL, *iterador, condos;
    FILE *fp_save;
    char nomedel[30];


    if ((fp_save = fopen("save", "rb")) != NULL)        /* Carrega os dados do arquivo de save */
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
        cod = getInt();

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
                puts("Insira o nome do condominio que voce quer alterar ou ver detalhes:");
                getStr(nomecondo);
                visualizar(head, nomecondo);

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
            case 7:

                break;
            default:

                return 0;
                break;
        }
    }
}

/* Utilitários */

void menuPrincipal(void)
{
    puts("O que deseja fazer?");
    puts("1. Criar condominio");
    puts("2. Listar condominios");
    puts("3. Deletar condominio");
    puts("4. Ver/editar condominio");
    puts("5. Filtrar condominios");
    puts("6. Salvar e sair");
    puts("7. Ajuda");
}

void getStr (char *string)
{
    int len;

    fgets(string, 30, stdin);
    len = strlen(string);
    string[len - 1] = '\0';
}

int getInt (void)
{
    int x, len, nonvalid = 1, i;
    char num[20];


    while (nonvalid)
    {
        x = 0;
        fgets (num, 20, stdin);
        len = strlen(num);
        for (i = 0; i < len - 1; i++) /* Subtraí um para não contar o \n, que a fgets inclui */
        {
            if (num[i] < '0' || num[i] > '9')
            {
                puts("Erro: insira apenas numeros.\n");
                nonvalid = 1;
                break;
            }
            else 
            {
                x *= 10;
                x += num[i] - '0';
                nonvalid = 0;
            }
        }
    }
    return x;
}

Endereco lerEndereco (void)
{
    Endereco ans;
    puts("-----ENDERECO-----");

    printf("UF:\n>");
    getStr(ans.UF);
    
    printf("Cidade:\n>");
    getStr(ans.cidade);
    
    printf("CEP:\n>");
    ans.CEP = getInt();

    printf("Bairro:\n>");
    getStr(ans.bairro);
    
    printf("Rua:\n>");
    getStr(ans.rua);

    printf("Numero:\n>");
    ans.numero = getInt();

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

/* Manipulação de condominios */

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

int existeCondo (Condominio *lista, char *string)
{
    Condominio *iterator;
    iterator = lista;

    if (lista == NULL)
        return 0;
    
    while (iterator != NULL)
    {
        if (!strCompareUpper(iterator->nome, string))
            return 1;
        else
            iterator = iterator->next;
    }
    return 0;
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

    if (existeCondo(lista, novoCond.nome))
    {
        puts("Erro: ja existe um condominio com esse nome\n");
        return;
    }

    while (iterator->next != NULL && strCompareUpper(iterator->next->nome, novoCond.nome) < 0)
    {
        iterator = iterator->next;
    }
    temp = iterator->next;
    
    if ((iterator->next = malloc(sizeof(Condominio))) == NULL)
    {
        puts("Erro: nao foi possivel criar o condominio");
        iterator->next = temp;
        return;
    }
    
    *(iterator->next) = novoCond;
    iterator->next->next = temp;
}

void mostrarCondominio (Condominio *atual)
{
    puts("________________________________");
    printf("Nome: %s\n", atual->nome);
    printf("Endereco:\nUF: %s\nCidade: %s\nCEP: %d\n\n", atual->endereco.UF, atual->endereco.cidade, atual->endereco.CEP);
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
        mostrarCondominio(iterator);
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

/* Manipulação de blocos */

void mostrarBloco (Bloco *atual)
{
    printf("Bloco %d: %d andares, %d apartamentos por andar\n", atual->nbloco, atual->andares, (atual->qtdapto / atual->andares));
}

void listarBlocos (Condominio *condo)
{
    Bloco *iterator;
    
    iterator = condo->blocos;

    if (condo->blocos == NULL)
    {
        puts("Nao ha blocos nesse condominio.\n");
        return;
    }

    puts("Blocos:\n");
    
    while (iterator != NULL)
    {
        mostrarBloco(iterator);
        iterator = iterator->next;
    }
    puts("\n");
}

Bloco lerBloco (void)
{
    Bloco ans;
 
    puts("Insira o numero do bloco:");
    ans.nbloco = getInt();

    puts("Insira o numero de andares:");
    ans.andares = getInt();

    puts("Insira o numero de apartamentos por andar:");
    ans.qtdapto = getInt() * ans.andares;

    ans.next = NULL;

    return ans;
}

void adicionarBlocoNoInicio (Condominio *condo, Bloco *novoBloco)
{
    Bloco *temp;
    
    temp = condo->blocos;
    
    if ((condo->blocos = malloc(sizeof(Bloco))) == NULL)
    {
        puts("Erro ao inserir o bloco.\n");
        condo->nblocos--;
        return;
    }

    *(condo->blocos) = *novoBloco;
    condo->blocos->next = temp;
}

void adicionarBloco (Condominio *condo)
{
    Bloco novo;
    Bloco *iterator, *temp;
    condo->nblocos++;

    novo = lerBloco();
    iterator = condo->blocos;

    if (condo->blocos == NULL || novo.nbloco < condo->blocos->nbloco)
    {
        adicionarBlocoNoInicio(condo, &novo);
        return;
    }

    while (iterator->next != NULL && novo.nbloco > iterator->next->nbloco)
    {
        iterator = iterator->next;
    }
    
    temp = iterator->next;

    if ((iterator->next = malloc(sizeof(Bloco))) == NULL)
    {
        puts("Erro ao inserir o bloco.\n");
        iterator->next = temp;
        condo->nblocos--;
        return;
    }

    *(iterator->next) = novo;
    iterator->next->next = temp;
}

void deletarBloco (Condominio *atual, int numdel)
{
    Bloco *iterator, *temp;

    iterator = atual->blocos;

    if (atual->blocos == NULL)
    {
        puts("Nao ha blocos para deletar neste condominio\n");
        return;
    }

    if (atual->blocos->nbloco == numdel)
    {
        temp = atual->blocos->next;
        free(atual->blocos);
        atual->blocos = temp;
        puts("Bloco deletado com sucesso!!\n\n");
        return;
    }

    while (iterator->next != NULL && iterator->next->nbloco != numdel)
    {
        iterator = iterator->next;
    }

    if (iterator->next->nbloco == numdel)
    {
        temp = iterator->next->next;
        free(iterator->next);
        iterator->next = temp;
        puts("Bloco deletado com sucesso!!\n\n");
        return;
    }
    
    puts("Esse bloco nao existe.\n");
}

void menuCondominio (void)
{
    puts("1. Alterar o nome do condominio");
    puts("2. Adicionar bloco");
    puts("3. Remover bloco");
    puts("4. Listar blocos");
    puts("Qualquer outro numero para voltar ao menu principal.");
}

void visualizar (Condominio *lista, char *nome)
{
    Condominio * iterator = lista;
    char novoNome[30];
    int option = 1, numeroADeletar;

    if (lista == NULL)
    {
        puts("Nao ha condominios para ver/editar.\n");
        return;
    }

    while (iterator != NULL && strCompareUpper(iterator->nome, nome))
    {
        iterator = iterator->next;
    }

    if (iterator == NULL)
    {
        puts("Nao existe um condominio com esse nome.\n");
        return;
    }

    mostrarCondominio(iterator);
    listarBlocos(iterator);

    while (option > 0 && option < 5)
    {
        menuCondominio();
        option = getInt();
    
        switch (option)
        {
        case 1:
            puts("Insira o novo nome do condominio");
            getStr(novoNome);
            if (existeCondo(lista, novoNome))
                puts("Ja existe um condominio com esse nome");
            else
                strcpy(iterator->nome, novoNome);

            break;
        case 2:
            adicionarBloco(iterator);

            break;
        case 3:
            puts("Insira o numero do bloco que deseja deletar:");
            numeroADeletar = getInt();
            deletarBloco(iterator, numeroADeletar);

            break;
        case 4:
            listarBlocos(iterator);
            break;
        default:

            break;
        }
    }
}