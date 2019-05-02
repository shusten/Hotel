#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
struct contato {
    char nome[30];
    char telefone[15];
    int numero_hospedes;
    bool disponivel;
};

struct contato temp;
int andar, apart;
struct contato reservas[30][8]; //fazendo a matriz de um hotel com 30 andares e 8 apartamentos em cada andar.

void guarda_string(char string[], int cont){
int i, j;
// printf("No guarda string ...");

switch(cont){
    case 1:
    strcpy(temp.nome, " ");
    strcpy(temp.telefone, " ");
    temp.numero_hospedes=0;
    //andar= atoi(string);
    sscanf(string, "%d", &andar);
    i=andar;
    // printf("\nandar: %d", i);
    break;

    case 2:
    //apart= atoi(string);
    sscanf(string, "%d", &apart);
    j=apart;
    // printf("\nquarto: %d", j);
    break;

    case 3:
    strcpy(temp.nome, string);
    break;

    case 4:
    strcpy(temp.telefone, string);
    break;

    case 5:
    //temp.numero_hospedes= atoi(string);
    sscanf(string, "%d", &temp.numero_hospedes);

    // printf("Salvando ... Apartamento: [%d-%d], %s, %s, %d hospedes\n", i, j, temp.nome, temp.telefone, temp.numero_hospedes);

    i=andar;
    j=apart;
    strcpy(reservas[andar][apart].nome, temp.nome);
    strcpy(reservas[andar][apart].telefone, temp.telefone);
    reservas[andar][apart].numero_hospedes=temp.numero_hospedes;
    reservas[i][j].disponivel=false;

    // printf("Salvando ... Apartamento: [%d-%d], %s, %s, %d hospedes\n", i, j, reservas[i][j].nome, reservas[i][j].telefone, reservas[i][j].numero_hospedes);

    break;
}

system("PAUSE");

}

void salvar_arquivo(){
    int i, j;
    char string[50];
    char buffer[50];
    FILE *output;
    output = fopen("arquivo.txt", "w");

    if(output){
    for(i=0;i<=29;i++){
        for(j=0;j<=7;j++){
            if(!reservas[i][j].disponivel){
            // printf("Salvando ... Apartamento: [%d-%d], %s, %s, %d hospedes\n", i, j, reservas[i][j].nome, reservas[i][j].telefone, reservas[i][j].numero_hospedes);


            strcpy(string, "&");

            sprintf(buffer, "%d", i);
            strcat(string, buffer);

            strcat(string, "#");

            sprintf(buffer, "%d", j);
            strcat(string, buffer);

            strcat(string, "#");
            strcat(string, reservas[i][j].nome);
            strcat(string, "#");
            strcat(string, reservas[i][j].telefone);
            strcat(string, "#");

            sprintf(buffer, "%d", reservas[i][j].numero_hospedes);
            strcat(string, buffer);

            strcat(string, "#");

            fputs(string, output);
        }
        }
    }
    }else{
        printf("deu erro na abertura do arquivo");
    }
    fclose(output);
}


void ler_arquivo(){
    int cont=0, size_string;
    char ch;
    char string[30];
    FILE *input;
    input = fopen("arquivo.txt", "r");
    if(input){
        ch = fgetc(input);
        while(ch!=EOF){
            // printf("%c\n", ch);
            switch(ch){
                case '&':
                    strcpy(string, " ");
                    cont=1;
                    break;

                case '#':
                    // printf("%s\n", string);
                    guarda_string(string, cont);
                    cont++;
                    strcpy(string, " ");
                    break;

                default:
                    size_string = strlen(string);
                    if(size_string < 254) {
                        string[size_string] = ch;
                        string[size_string+1] = '\0';
                    }
            }

            ch = fgetc(input);
        }
        fclose(input);
    }else{
        printf("deu erro na abertura do arquivo");
    }

}



void inicializar(){
    int i, j;

    for(i=0;i<=29;i++){
        for(j=0;j<=7;j++){

            strcpy(reservas[i][j].nome, " ");
            strcpy(reservas[i][j].telefone, " ");
            reservas[i][j].numero_hospedes=0;
            reservas[i][j].disponivel=true;
        }
    }
}

void incluir(){
    int i, j;
    printf("Qual o andar desejado?");
    scanf("%d", &i);
    printf("Qual apartamento?");
    scanf("%d", &j);
        if(reservas[i][j].disponivel){
            printf("Esta disponivel. digite suas informacoes\n");

                printf("Digite o nome do hospede: ");
                fflush(stdin);
                gets(reservas[i][j].nome);

                printf("Digite o telefone do hospede: ");
                fflush(stdin);
                gets(reservas[i][j].telefone);

                printf("Digite  a quantidade de hospedes no quarto: ");
                scanf("%d", &reservas[i][j].numero_hospedes);

                reservas[i][j].disponivel=false;

        }else{

    printf("este apartamento %d-%d esta ocupado", i, j);

    system("PAUSE");
}
}

void alterar(){
    int i, j;
    printf("Digite qual de qual apartamento deseja alterar o cadastro\n\n");
    printf("Andar: \n");
    scanf("%d", &i);
    printf("Apartamento: \n");
    scanf("%d", &j);

    if(!reservas[i][j].disponivel){

        printf("Digite o nome: \n");
        fflush(stdin);
        gets(reservas[i][j].nome);

        printf("Digite o telefone: \n");
        fflush(stdin);
        gets(reservas[i][j].telefone);

        printf("Digite o numero de hospedes: \n");
        scanf("%d", &reservas[i][j].numero_hospedes);

        printf("Reserva alterada\n");

        system("PAUSE");

    }else{

        printf("o Apartamento %d-%d nao esta ocupado", i, j);
        system("PAUSE");
    }


}

void excluir(){
    int i, j;

    printf("Digite qual apartamento deseja excluir do cadastro... \n");
    printf("Andar: \n");
    scanf("%d", &i);
    printf("Apartamento: \n");
    scanf("%d", &j);

    if(!reservas[i][j].disponivel){

    strcpy(reservas[i][j].nome, " ");
    strcpy(reservas[i][j].telefone, " ");
    reservas[i][j].numero_hospedes=0;
    reservas[i][j].disponivel=true;

    printf("Cadastro Excluido...\n");
    system("PAUSE");

}else{

    printf("Este apartamento esta vago...");

    system("PAUSE");
}
}

void consultar(){
    int i, j, opcao;
    printf("1 - visualizar todos os apartamentos\n");
    printf("2 - visualizar um apartamento especifico\n\n");
    printf("Digite qual sua opcao: ");
    scanf("%d", &opcao);

    switch(opcao){
        case 1:
        for(i=0;i<=29;i++){
            for(j=0;j<=7;j++){
                if(!reservas[i][j].disponivel){
printf("Apartamento: [%d-%d], %s, %s, %d hospedes\n", i, j, reservas[i][j].nome, reservas[i][j].telefone, reservas[i][j].numero_hospedes);
                }else{
printf("Apartamento: [%d-%d] esta disponivel\n", i, j);
                }
            }
        }
        system("PAUSE");
        break;

        case 2:
            printf("Digite qual o apartamento voce quer visualizar\n");
                printf("andar\n");
                    scanf("%d", &i);
                        printf("Apartamento\n");
                            scanf("%d", &j);
                            if(!reservas[i][j].disponivel){
printf("Apartamento: [%d-%d], %s, %s, %d hospedes\n", i, j, reservas[i][j].nome, reservas[i][j].telefone, reservas[i][j].numero_hospedes);
        }else{

            printf("Apartamento disponivel\n");

        break;
    }
        default:
            printf("opcao invalida");
            break;

    }
    system("PAUSE");
}

int main(){
    inicializar();
    ler_arquivo();

    int opc;
    while(opc!=6){

        printf("\n\n---------Menu--------\n\n");
        printf("1 - Incluir Reserva\n\n");
        printf("2 - Alterar Reserva\n\n");
        printf("3 - Excluir Reserva\n\n");
        printf("4 - Consultar Reserva\n\n");
        printf("5 - Salvar Arquivo\n\n");
        printf("6 - Sair\n\n");
        printf("Digite a sua opcao: ");
        scanf("%d", &opc);

        switch(opc){

            case 1:
            incluir();
            break;

            case 2:
            alterar();
            break;

            case 3:
            excluir();
            break;

            case 4:
            consultar();
            break;

            case 5:
                printf("antes de salvar 1 ...");
    system("PAUSE");
            salvar_arquivo();
            break;

            default:
            printf("opcao invalida");
            break;
        }
        system("cls");
    }


    system("PAUSE");
}
