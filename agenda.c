#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 30

typedef struct contato {
    int codigo;
    int ativo;
    char nome [100];
    char email [100];
    char celular [20];
} Contato;

Contato contato;

void adicionarContato ();
void consultarContato();
void excluirContato ();
void editarContato ();
int sair();
void clrscr();
int proximoId();

void main() {
    int opcao;

    do {        
        printf("\n\n\t\tMENU");
        printf("\n1 - Cadastrar");
        printf("\n2 - Listar");
        printf("\n3 - Editar");
        printf("\n4 - Excluir");
        printf("\n5 - Sair");
        printf("\nOpção: ");

        scanf("%d", &opcao);
        fflush(stdin);
        clrscr();
        switch (opcao) {
            case 1:
                printf("\nDigite um nome: ");
                scanf("%s", contato.nome);
                printf("\nDigite um telefone: ");
                scanf("%s", contato.celular);
                printf("\nDigite um email: ");
                scanf("%s", contato.email);
                adicionarContato(contato.nome, contato.celular, contato.email);
                getchar();
                clrscr();
                break;
            case 2:
                clrscr();
                consultarContato();
                getchar();
                fflush(stdin);
                break;
            case 3:
                clrscr();
                editarContato();
                getchar();
                fflush(stdin);
                break;
            case 4:
                clrscr();
                excluirContato();
                getchar();
                fflush(stdin);
                break;
            case 5:
                clrscr();
                sair();
                break;
            default:
                printf("opção inválida!");
                break;
        }
    } while (opcao != 5);
}

void adicionarContato(char nome[BUFFER_SIZE],char tel[BUFFER_SIZE],char email[BUFFER_SIZE]){
    int id = proximoId();
    FILE *arquivo = fopen("agenda.txt","a");
        
    fprintf(arquivo, "%d %d %s %s %s\n", id, 1, nome, tel, email);
    fclose(arquivo);
}

void consultarContato(){
    FILE *arquivo = fopen("agenda.txt","r");
    int codigo;
    int ativo;
    char nome[BUFFER_SIZE];
    char email[BUFFER_SIZE];
    char tel[BUFFER_SIZE];
    while (1)
    {
        fscanf(arquivo, "%d %d %s %s %s", &codigo, &ativo, nome, email, tel);
        if( feof(arquivo) )
            break;

        printf("Id: %d Nome: %s - Tel: %s Email: %s \n", codigo, nome, email, tel);
    }
    fclose(arquivo);
}

int sair(){
    clrscr();
    printf("--------------------------------------------------------\n");
    printf("--------------------FINALIZANDO PROGRAMA----------------\n");
    printf("--------------------------------------------------------\n\n");
    getchar();
    return 0;
}

void excluirContato (){
    FILE *arquivo = fopen("agenda.txt","r");
    FILE *copia = fopen("copia.txt","a");
    int opcao;
    int codigo;
    int ativo;
    char nome[BUFFER_SIZE];
    char email[BUFFER_SIZE];
    char tel[BUFFER_SIZE];
    printf("\n\n\t\tEscolha o contato a ser excluído pelo seu id\n");
    printf("\n");
    consultarContato();

    printf("\nOpção: ");
    scanf("%d", &opcao);

    while (!feof(arquivo))
    {
        fscanf(arquivo, "%d %d %s %s %s", &codigo, &ativo, nome, email, tel);
        if(codigo != opcao) {
            fprintf(copia, "%d %d %s %s %s\n", codigo, ativo, nome, email, tel);
        }
    }
    fclose(arquivo);
    fclose(copia);
    remove("agenda.txt");
    rename("copia.txt", "agenda.txt");
}

void editarContato (){
    FILE *arquivo = fopen("agenda.txt","r");
    FILE *copia = fopen("copia.txt","a");
    int opcao;
    int codigo;
    int ativo;
    char nome[BUFFER_SIZE];
    char email[BUFFER_SIZE];
    char tel[BUFFER_SIZE];
    printf("\n\n\t\tEscolha o contato a ser editado pelo seu id\n");
    printf("\n");
    consultarContato();

    printf("\nOpção: ");
    scanf("%d", &opcao);

    while (!feof(arquivo))
    {
        fscanf(arquivo, "%d %d %s %s %s", &codigo, &ativo, nome, email, tel);

        if(codigo == opcao) {
            printf("\nDigite o novo nome: ");
            scanf("%s", nome);
            printf("\nDigite o novo telefone: ");
            scanf("%s", tel);
            printf("\nDigite o novo email: ");
            scanf("%s", email);
            fprintf(copia, "%d %d %s %s %s\n", codigo, ativo, nome, email, tel);
            break;
        }
        else {
            fprintf(copia, "%d %d %s %s %s\n", codigo, ativo, nome, email, tel);
        }
    }
    fclose(arquivo);
    fclose(copia);
    remove("agenda.txt");
    rename("copia.txt", "agenda.txt");
}

int proximoId(){
    FILE *arquivo = fopen("agenda.txt","r");
    char c, letra = '\n';
    int vezes = 1;
    while(fread (&c, sizeof(char), 1, arquivo)) {
        if(c == letra) {
            vezes++;
        }
    }
    fclose(arquivo);
    return vezes;
}
/**< LIMPA A TELA */

void clrscr()
{
    system("@cls||clear");
}