/**
 * O objetivo do programa é criar uma interface para acompanhar registros de 
 * vendas com os seguintes campos: codigo_vendedor, nome_vendedor,
 * valor_da_venda, mes.
 * 
 * A interface precisa ter as seguintes funcionalidades, listadas no enunciado:
 * 
 * 1- Criar um arquivo de dados
 * 2- Incluir um determinado registro no arquivo
 * 3- Excluir um registro do arquivo
 * 4- Alterar o valor de uma venda no arquivo
 * 5- Imprimir os registros na saída padrão
 * 6- Excluir o arquivo de dados
 * 7- Finalizar o programa
 * 
 * Os registros devem estar ordenados por código e mês, e nao deve haver
 * mais de um registro com as mesmas informações nesses dois campos. 
 * 
 * Quaisquer outros detalhes do funcionamento vieram da minha interpretação :)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _VENDA {
    int cod_vendedor;
    char nome_vendedor[50];
    float valor_venda;
    int mes;
    struct _VENDA *next;
} Venda;

void printMenu (void);
void getStr (char *string);
Venda lerVenda (void);
int checkVenda (Venda *p);
void incluirRegistro (Venda **lista);
void mostrarRegistro (Venda registro);
void imprimirRegistros (Venda *lista);
void excluirVendedor (Venda **lista);
void alterarVenda (Venda **lista);

int main (void)
{
    int cod;
    char nomeArq[50];
    FILE *fsave;
    Venda *vendas = NULL, *iterador;

    printf("Insira o nome do arquivo de onde deseja carregar os dados (0 para nao carregar):\n>");
    getStr(nomeArq);

    if (strcmp(nomeArq, "0"))
    {
        if ((fsave = fopen(nomeArq, "rb")) == NULL)
        {
            puts("Nao foi possivel abrir o arquivo");
            return 1;
        }
        else
        {
            if(!feof(fsave))
            {
                vendas = malloc (sizeof(Venda));
                if(!checkVenda(vendas))
                {
                    puts("Erro ao carregar arquivo\n");
                    return 1;
                }
                fread(&(vendas->cod_vendedor), sizeof(int), 1, fsave);
                fread(vendas->nome_vendedor, 50 * sizeof(char), 1, fsave);
                fread(&(vendas->valor_venda), sizeof(float), 1, fsave);
                fread(&(vendas->mes), sizeof(int), 1, fsave);
            }
            vendas->next = malloc(sizeof(Venda));
            if(!checkVenda(vendas->next))
            {
                puts("Erro ao carregar arquivo\n");
                return 1;
            }
            iterador = vendas;
            while(!feof(fsave))
            {
                fread(&(iterador->next->cod_vendedor), sizeof(int), 1, fsave);
                if (feof(fsave)) break;
                fread(iterador->next->nome_vendedor, 50 * sizeof(char), 1, fsave);
                fread(&(iterador->next->valor_venda), sizeof(float), 1, fsave);
                fread(&(vendas->next->mes), sizeof(int), 1, fsave);

                iterador->next->next = malloc(sizeof(Venda));
                if(!checkVenda(iterador->next->next))
                {
                    puts("Erro no carregamento dos dados...\n");
                    return 1;
                }
                iterador = iterador->next;
            }
            free(iterador->next);
            iterador->next = NULL;
        }
        fclose(fsave);
    }
    

    while (1)
    {
        printMenu();
        scanf("%d", &cod);

        switch (cod)
        {
            case 1:
                printf("Insira o nome do arquivo a criar:\n>");
                getStr(nomeArq);

                if ((fsave = fopen(nomeArq, "w")) == NULL)
                    puts("Nao foi possivel criar o arquivo\n");
                else
                    puts("Arquivo criado com sucesso!\n");

                fclose(fsave);
                break;
            case 2:
                incluirRegistro(&vendas);
                break;
            case 3:
                excluirVendedor(&vendas);
                break;
            case 4:
                alterarVenda(&vendas);
                break;
            case 5:
                imprimirRegistros(vendas);
                break;
            case 6:
                printf("Insira o nome do arquivo a deletar:\n>");
                getStr(nomeArq);
                if ((fsave = fopen(nomeArq, "r")) != NULL)
                {
                    fclose(fsave);
                    if(!remove(nomeArq))
                        puts("Deletado com sucesso\n");
                    else
                        puts("Nao foi possivel deletar o arquivo\n");
                }
                else
                    puts("Nao existe um arquivo com esse nome\n");
                break;
            case 7:
                printf("Digite o nome do arquivo onde deseja salvar:\n>");
                getStr(nomeArq);

                fsave = fopen(nomeArq, "wb");
                if (fsave == NULL)
                {
                    puts("Erro ao abrir o arquivo para salvar");
                    return 1;
                }

                iterador = vendas;
                
                while (iterador != NULL)
                {
                    fwrite(&(iterador->cod_vendedor), sizeof(int), 1, fsave);
                    fwrite(iterador->nome_vendedor, 50 * sizeof(char), 1, fsave);
                    fwrite(&(iterador->valor_venda), sizeof(float), 1, fsave);
                    fwrite(&(iterador->mes), sizeof(int), 1, fsave);
                    iterador = iterador->next;
                }
                puts("Salvo\nEncerrando...\n");
                return 0;

            default:
                puts("Comando invalido. Insira um numero de 1 a 7\n");
                break;
        }
    }
    return 0;
}

void printMenu (void)
{
    puts("O que deseja fazer?");
    puts("1. Criar o arquivo de dados");
    puts("2. Incluir um registro no arquivo");
    puts("3. Excluir um vendedor do arquivo");
    puts("4. Alterar o valor de uma venda no arquivo");
    puts("5. Imprimir os registros");
    puts("6. Excluir o arquivo de dados");
    puts("7. sair");
    printf(">");
}

void getStr (char *string)
{
    int len;

    fflush(stdin);
    fgets(string, 50, stdin);
    len = strlen(string);
    string[len - 1] = '\0';
}

Venda lerVenda (void)
{
    Venda atual;

    printf("Insira o codigo do vendedor:\n>");
    while (!scanf("%d", &atual.cod_vendedor))
    {
        while (getchar() != '\n');
        puts("Erro: insira apenas numeros");
    }

    printf("Insira o nome do vendedor:\n>");
    getStr(atual.nome_vendedor);

    printf("Insira o valor da venda:\n>");
    while (!scanf("%f", &atual.valor_venda))
    {
        while (getchar() != '\n');
        puts("Erro: insira apenas numeros");
    }

    printf("Insira o mes da venda:\n>");
    while (!scanf("%d", &atual.mes))
    {
        while (getchar() != '\n');
        puts("Erro: insira apenas numeros");
    }
    return atual;
}

int checkVenda (Venda *p)
{
    if (p == NULL)
        return 0;
    else
        return 1;
}

void incluirRegistro (Venda **lista)
{
    Venda novoRegistro, *temp, *iterator;

    novoRegistro = lerVenda();

    if (*lista == NULL)
    {
        *lista = malloc(sizeof(Venda));
        if (!checkVenda(*lista))
        {
            puts("Erro: nao foi possivel inserir o registro\n");
            return;
        }

        **lista = novoRegistro;
        (*lista)->next = NULL;
        
        puts("Registro inserido com sucesso!!\n");
        return;
    }
    else if ((*lista)->mes > novoRegistro.mes || ((*lista)->mes == novoRegistro.mes && (*lista)->cod_vendedor > novoRegistro.cod_vendedor))
    {
        temp = *lista;
        *lista = malloc(sizeof(Venda));

        if (!checkVenda(*lista))
        {
            puts("Erro: nao foi possivel inserir o registro\n");
            return;
        }

        **lista = novoRegistro;
        (*lista)->next = temp;
        
        puts("Registro inserido com sucesso!!\n");
        return;
    }
    else
    {
        iterator = *lista;
        while (iterator->next != NULL && novoRegistro.mes > iterator->next->mes)
        {
            iterator = iterator->next;
        }
        while (iterator->next != NULL && novoRegistro.cod_vendedor > iterator->next->cod_vendedor)
        {
            iterator = iterator->next;
        }

        if (iterator->next != NULL && novoRegistro.cod_vendedor == iterator->next->cod_vendedor && novoRegistro.mes == iterator->next->mes)
        {
            puts("Erro: ja existe uma venda com esse codigo de vendedor nesse mes.\n");
            return;
        }

        temp = iterator->next;
        iterator->next = malloc(sizeof(Venda));

        if (!checkVenda(iterator->next))
        {
            puts("Erro: nao foi possivel inserir o registro\n");
            iterator->next = temp;
            return;
        }

        *(iterator->next) = novoRegistro;
        iterator->next->next = temp;
        
        puts("Registro inserido com sucesso!!\n");
        return;
    }
}

void mostrarRegistro (Venda registro)
{
    puts("-----------------------------------");
    printf("Codigo do vendedor: %d\n", registro.cod_vendedor);
    printf("Nome do vendedor: %s\n", registro.nome_vendedor);
    printf("Valor da venda: %.2f\n", registro.valor_venda);
    printf("Mes da venda: %d\n\n", registro.mes);
}

void imprimirRegistros (Venda *lista)
{
    Venda *iterator;
    iterator = lista;

    if (iterator == NULL)
    {
        puts("Nao ha registros.\n");
    }
    while (iterator != NULL)
    {
        mostrarRegistro(*iterator);
        iterator = iterator->next;
    }
}

void excluirVendedor (Venda **lista)
{
    Venda *iterator, *temp;
    int codigo;

    printf("Insira o codigo do vendedor a ser excluido:\n>");
    while (!scanf("%d", &codigo))
    {
        while (getchar() != '\n');
        puts("Erro: insira apenas numeros");
    }

    if (*lista == NULL)
    {
        puts("A lista esta vazia");
        return;
    }

    while((*lista)->cod_vendedor == codigo)
    {
        temp = (*lista)->next;
        free(*lista);
        *lista = temp;
        if (*lista == NULL) 
            return;
    }

    iterator = *lista;
    while (iterator->next != NULL)
    {
        if (iterator->next->cod_vendedor == codigo)
        {
            temp = iterator->next->next;
            free(iterator->next);
            iterator->next = temp;
        }
    }
}

void alterarVenda (Venda **lista)
{
    Venda *iterator;
    int codigoAlt, mesAlt;

    printf("Insira o codigo do vendedor que realizou a venda a ser alterada:\n>");
    while(!scanf("%d", &codigoAlt))
    {
        while (getchar() != '\n');
        puts("Erro: insira apenas numeros");
    }

    printf("Insira o mes da venda a ser alterada:\n>");
    while(!scanf("%d", &mesAlt))
    {
        while (getchar() != '\n');
        puts("Erro: insira apenas numeros");
    }

    iterator = *lista;
    while (iterator != NULL)
    {
        if (iterator->cod_vendedor == codigoAlt && iterator->mes == mesAlt)
        {
            printf("Insira o novo valor:\n>");
            
            while (!scanf("%f", &(iterator->valor_venda)))
            {
                while (getchar() != '\n');
                puts("Erro: insira apenas numeros");
            }
            puts("Valor alterado com sucesso!\n");
            return;
        }
        else
            iterator = iterator->next;
    }
    puts("Erro: venda nao encontrada\n");
}