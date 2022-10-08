#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

/*
Diogo Vitor Oliveira Leme
RA: 836846
Engenharia de Software - UNAERP RP
*/

//Defini��o do escopo das STRUCTS
struct afazeres{
    char tarefa[50];
};

struct tarefas{
    int qtd;
    struct afazeres t[MAX];
};
//Defini��o do escopo das STRUCTS

//Vari�veis e Listas GLOBAIS
struct tarefas fazer, feito;
int Pdtqtd = 0, Ftoqtd = 0;
//

void inicia(){
   feito.qtd = -1;
   fazer.qtd = -1;
}//inicializa��o das listas

int vazia(int escolha){
    if(escolha == 1){
        return fazer.qtd == -1;
    }else if(escolha == 2){
        return feito.qtd == -1;
    }
}//Checa se as estruturas est�o VAZIAS
int cheia(){
    return fazer.qtd == MAX -1;
    return feito.qtd == MAX -1;
}//Checa se as estruturas est�o CHEIAS

void menu(){
    int opcao;

    system("cls");

    //Exibi��o da quantidade de registros em cada lista
    printf("PENDENTES: %i | REALIZADOS: %i\n", fazer.qtd+1, feito.qtd+1);
    printf("----------------------------\n");
    //Op��es do MENU
    printf("\tTo Do List - MENU\n");
    printf("1 > Registrar Tarefa\n");
    printf("2 > Visualizar Tarefa\n");
    printf("3 > Controle de Tarefa\n");
    printf("4 > Exclusao de Tarefa\n");
    printf("0 > Sair\n");
    printf("Escolha: ");
    scanf("%i", &opcao);

    //Condicionais das op��es do MENU
    if(opcao < 0 || opcao > 4){
        outra_atividade(fazer);
    }else if(opcao == 1){registrar(fazer);}
    else if(opcao == 2){visualizar(fazer);}
    else if(opcao == 3){transferir(fazer);}
    else if(opcao == 4){excluir();}
    else if(opcao == 0){sair(fazer, feito);}

}//menu

void registrar(){

    if (!cheia()){
        fazer.qtd ++;//�ndice e contador aumentam a cada registro
        Pdtqtd++;

        printf("\nRegistro %i\n", fazer.qtd+1);
        printf("Atividade: ");
        fflush(stdin);
        gets(fazer.t[fazer.qtd].tarefa);//Inscri��o da atividade � posi��o vigente
        printf("Registro realizado!!");

        outra_atividade();
    }else{
        printf("\t\nLista Cheia.");
    }

}//Registro de atividade a ser realizada

void visualizar(){
    int j = 0;
    int escolha;

    printf("\n\tExibicao de tarefas.\n");
    printf("Visualizar...\n");
    printf("1 > Pendentes\n");
    printf("2 > Concluidas\n");
    printf("Escolha: ");
    scanf("%i", &escolha);

    switch(escolha){//Escolha de lista a observar
//Exibi��o das tarefas PENDENTES
        case 1:
            if(vazia(escolha)){
                printf("\n\tLista Vazia.");
                outra_atividade();
            }else{
                printf("\n\n\tA Realizar\n");
                while(j <= fazer.qtd){
                    printf("\nRegistro N %i: %s", j+1, fazer.t[j].tarefa);
                    j++;
                }
            }
        break;
//Exibi��o das tarefas PENDENTES

//Exibi��o das tarefas CONCLU�DAS
        case 2:
            if(vazia(escolha)){
                printf("\n\tLista Vazia.");
                outra_atividade();
            }else{
                printf("\n\n\tConcluidas\n");
                while(j <= feito.qtd){
                    printf("\nRegistro N %i: %s", j+1, feito.t[j].tarefa);
                    j++;
                }
            }
        break;
//Exibi��o das tarefas CONCLU�DAS

        default://Op��o inv�lida
            printf("\nInvalido.\n");
            printf("Retornando ao menu.");
            sleep(1);printf(".");
            sleep(1);printf(".");
            menu();
        break;

    outra_atividade();

    }//switch
}//visualizar

void transferir(){//CONCLUS�O ou EXTORNO de registro
    int j = 0;
    int escolha;
    char tarefaProc[50];

    printf("\n\tControle de Tarefas\n");
    printf("1 > Concluir | 2 > Extornar: ");
    scanf("%i", &escolha);//Escolha de opera��o

//CONCLUS�O de registro
    if(escolha == 1){
        if(Ftoqtd < MAX){
            exibe_pendente();
            printf("\n\nDigite o nome da tarefa: ");
            fflush(stdin);
            gets(tarefaProc);
            while(j <= fazer.qtd){
                //Checagem nos registroS pelo indice procurado
                if(strcmp(tarefaProc, fazer.t[j].tarefa) == 0){
                    printf("\n\tTarefa N %i\n", j+1);
                    printf("Tarefa: %s", fazer.t[j].tarefa);
                    feito.qtd++;
                    Ftoqtd++;
                    //Atribui��o do indice PENDENTE a lista de CONCLU�DOS
                    strcpy(feito.t[feito.qtd].tarefa, fazer.t[j].tarefa);
                    while(j <= fazer.qtd){//Percorrimento do restante da lista para organiza��o do �ndice vazio
                        strcpy(fazer.t[j].tarefa, fazer.t[j+1].tarefa);
                        j++;
                    }
                }
                j++;
            }

            strcpy(fazer.t[fazer.qtd].tarefa, "");
            fazer.qtd--;
            Pdtqtd--;//�ndice e contador diminuem

            printf("\nConcluido com sucesso!!");
        }else{
            printf("\n\tLimite atingido\n");
            printf("Exclua algum registro e tente novamente.");
        }
//CONCLUS�O de registro

//EXTORNO de tarefa
    }else if(escolha == 2){
        if (Pdtqtd < MAX){
            exibe_concluido();
            printf("\n\nDigite o nome da tarefa: ");
            fflush(stdin);
            gets(tarefaProc);
            //Percorrimento dos �ndices para localizar o solicitado
            while(j <= feito.qtd){
                if(strcmp(tarefaProc, feito.t[j].tarefa) == 0){
                    printf("\n\tTarefa N %i\n", j+1);
                    printf("Tarefa: %s", feito.t[j].tarefa);
                    fazer.qtd++;
                    Pdtqtd++;
                    //Atribui��o do indice CONCLU�DO a lista de PENDENTES
                    strcpy(fazer.t[fazer.qtd].tarefa, feito.t[j].tarefa);
                    while(j <= feito.qtd){//Percorrimento do restante da lista para organiza��o do �ndice vazio
                        strcpy(feito.t[j].tarefa, feito.t[j+1].tarefa);
                        j++;
                    }
                }
                j++;
            }

            strcpy(feito.t[feito.qtd].tarefa, "");
            feito.qtd--;
            Ftoqtd--;//�ndice e contador diminuem

            printf("\nExtornado com sucesso!!");
        }else{
            printf("\n\tLimite atingido\n");
            printf("Exclua algum registro e tente novamente.");
        }
    }
    else{//Op��o inexistente
        printf("Invalido.");
        outra_atividade();
    }
//EXTORNO de tarefa

    outra_atividade();

}//Transferir

void excluir(){//EXCLUS�O de registro
    int opcao;
    int j = 0;
    char tarefaProc[50];

    printf("\nExclusao de registro.\n");
    printf("Visualizar...\n");
    printf("1 > Pendentes\n");
    printf("2 > Concluidas\n");
    printf("Escolha: ");
    scanf("%i", &opcao);

//Exclus�o de registro PENDENTE
    if(opcao == 1 && Pdtqtd > 0){
        exibe_pendente();
            printf("\n\nDigite o nome da tarefa: ");
            fflush(stdin);
            gets(tarefaProc);
            //Percorrimento dos �ndices para localizar o solicitado
            while(j <= fazer.qtd){
                if(strcmp(tarefaProc, fazer.t[j].tarefa) == 0){
                    printf("\n\tTarefa N %i\n", j+1);
                    printf("Tarefa: %s", fazer.t[j].tarefa);
                    while(j <= fazer.qtd){//Percorrimento do restante da lista para organiza��o do �ndice vazio
                        strcpy(fazer.t[j].tarefa, fazer.t[j+1].tarefa);
                        j++;
                    }
                }
                j++;
            }
            strcpy(fazer.t[fazer.qtd].tarefa, "");
            fazer.qtd--;
            Pdtqtd--;//�ndice e contador diminuem

            printf("\nExcluido com sucesso!!");

            outra_atividade();
//Exclus�o de registro PENDENTE

//Exclus�o de registro CONCLU�DO
    }else if(opcao == 2 && Ftoqtd > 0){
        exibe_concluido();
            printf("\n\nDigite o nome da tarefa: ");
            fflush(stdin);
            gets(tarefaProc);
            //Percorrimento dos �ndices para localizar o solicitado
            while(j <= feito.qtd){
                if(strcmp(tarefaProc, feito.t[j].tarefa) == 0){
                    printf("\n\tTarefa N %i\n", j+1);
                    printf("Tarefa: %s", feito.t[j].tarefa);
                    while(j <= feito.qtd){//Percorrimento do restante da lista para organiza��o do �ndice vazio
                        strcpy(feito.t[j].tarefa, feito.t[j+1].tarefa);
                        j++;
                    }
                }
                j++;
            }
            strcpy(feito.t[feito.qtd].tarefa, "");
            feito.qtd--;
            Ftoqtd--;//�ndice e contador diminuem

            printf("\nExcluido com sucesso!!");

            outra_atividade();
//Exclus�o de registro CONCLU�DO
    }else{//Op��o inexistente
        printf("\nInvalido.\n");
        printf("Retornando ao menu.");
        sleep(1);printf(".");
        sleep(1);printf(".");
        menu();
    }

}//excluir

void sair(){

    printf("\n\tObrigado.\n");
    sleep(3);
    exit("0");
}//sair

void exibe_pendente(){//EXIBIR LISTA DE PENDENTES
    int j = 0;

    while(j <= fazer.qtd){
        printf("\nTarefa N %i: %s", j+1, fazer.t[j].tarefa);
        j++;
    }
}//exibe_pendente
void exibe_concluido(){//EXIBIR LISTA DE CONCLUIDOS
    int j = 0;

    while(j <= feito.qtd){
        printf("\nTarefa N %i: %s", j+1, feito.t[j].tarefa);
        j++;
    }
}//exibe_concluido

void outra_atividade(){//Pergunta pro usu�rio de deseja realizar outra atividade
    int opcao, opcao2;
    int repetir = 1;

    while(repetir == 1){
        printf("\n\nExecutar outra atividade?\n");
        printf("1 > SIM | 0 > NAO: ");
        scanf("%i", &opcao);
        if (opcao == 1){
            menu(fazer);
        }else if (opcao == 0){
            sair(fazer);
        }else{
            printf("\nInvalido. ");
            outra_atividade();
        }
    }
}//outra_atividade

int main()
{
    inicia();
    menu(fazer);
}//main
