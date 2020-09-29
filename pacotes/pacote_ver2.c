#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_PACOTES "./db/pacotes.txt"

typedef struct pacote
{
    long int idPacote;
    int numHospedes;
    char nomePacote[100], destinoViagem[100], dataPartida[10], dataRetorno[10];
}Pacote;

int contElementosVetor(Pacote *vec_pacote){ // função para contar elementos do vetor de struct

    int cont_elementos_struct = 0;

    FILE *frb = fopen(FILE_PACOTES, "rb");
    while(fread(vec_pacote, sizeof(Pacote), 1, frb)){
        cont_elementos_struct++;
    }
    fclose(frb);

    return(cont_elementos_struct);

}

void cadastrarPacotes(Pacote *vec_pacote){

    FILE *fab = fopen(FILE_PACOTES, "ab+");

    printf("\n=============================\n");
    printf("Exemplo de modelo:");
    printf("\n=============================\n");
    printf("ID: 12345 (apenas numeros)\n");
    printf("Nome do pacote: Pacote Villa Hotel\n");
    printf("Destino: Recife-PE\n");
    printf("Numero de hospedes: 8 (apenas numeros)\n");
    printf("Data de partida: 12/03\n");
    printf("Data de retorno: 16/04");
    printf("\n=============================\n");

    printf("ID do pacote: ");
    scanf("%ld", &vec_pacote->idPacote);

    printf("Nome do pacote: ");
    scanf(" %[^\n]", vec_pacote->nomePacote);

    printf("Destino: ");
    scanf(" %[^\n]", vec_pacote->destinoViagem);

    printf("Numero de hospedes: ");
    scanf("%d", &vec_pacote->numHospedes);

    printf("Data de partida: ");
    scanf(" %[^\n]", vec_pacote->dataPartida);

    printf("Data de retorno: ");
    scanf(" %[^\n]", vec_pacote->dataRetorno);

    fwrite(vec_pacote, sizeof(Pacote), 1, fab);
    fclose(fab);
}

void listarPacotes(Pacote *vec_pacote){

    FILE *frb = fopen(FILE_PACOTES, "rb");

    //se contElementosVetor = 0, nao ha pacotes

    if(contElementosVetor(vec_pacote) == 0){

        printf("\nNao ha cadastros de pacotes.\n");

    }else{

        while(fread(vec_pacote, sizeof(Pacote), 1, frb)){
            printf("\n=============================\n");
            printf("ID do pacote: %ld\n", vec_pacote->idPacote);
            printf("Nome do pacote: %s\n", vec_pacote->nomePacote);
            printf("Destino: %s\n", vec_pacote->destinoViagem);
            printf("Numero de hospedes: %d\n", vec_pacote->numHospedes);
            printf("Data de partida: %s\n", vec_pacote->dataPartida);
            printf("Data de retorno: %s", vec_pacote->dataRetorno);
            printf("\n=============================\n");
        }
    }

    fclose(frb);

}

void removerPacotes(Pacote *vec_pacote){

    long int id, cont = 0; 

    Pacote p;
    Pacote *pac = (Pacote*) malloc(sizeof(Pacote)); 

    //se contElementosVetor = 0, nao ha pacotes

    if(contElementosVetor(vec_pacote) == 0){ 

        printf("\nNao ha cadastros de pacotes.\n");

    }else{
        FILE *frb = fopen(FILE_PACOTES, "rb");
        printf("Digite o id do pacote a ser removido: ");
        scanf("%ld", &id);
        //populando o vetor pac com os pacotes cujos ids nao correspondem ao que foi informado
        while(fread(&p, sizeof(Pacote), 1, frb)){

            if (p.idPacote != id){ 

                *(pac + cont) = p;
                cont++;
                pac = (Pacote*) realloc(pac, (cont+1) * sizeof(Pacote));

            }
        }
        fclose(frb);
        //reescrevendo no arquivo
        FILE *fwb = fopen(FILE_PACOTES, "wb");
        for (int i = 0; i < cont; i++){
            fwrite(pac + i, sizeof(Pacote), 1, fwb);
        }
        fclose(fwb);
    }
}

void consultarPacotes(Pacote *vec_pacote){

    int op, cont = 0;

    //se contElementosVetor = 0, nao ha pacotes

    if(contElementosVetor(vec_pacote) == 0){

        printf("\nNao ha cadastros de pacotes.\n");

    }else{

        FILE *frb = fopen(FILE_PACOTES, "rb");
    
        printf("Digite o ID do pacote que deseja consultar: ");
        scanf("%d", &op);
    
        while(fread(vec_pacote, sizeof(Pacote), 1, frb)){
            if(op == vec_pacote->idPacote){
                printf("\n=============================\n");
                printf("ID do pacote: %ld\n", vec_pacote->idPacote);
                printf("Nome do pacote: %s\n", vec_pacote->nomePacote);
                printf("Destino: %s\n", vec_pacote->destinoViagem);
                printf("Numero de hospedes: %d\n", vec_pacote->numHospedes);
                printf("Data de partida: %s\n", vec_pacote->dataPartida);
                printf("Data de retorno: %s", vec_pacote->dataRetorno);
                printf("\n=============================\n");
                cont++; //caso hajam pacotes com o ID informado, cont sera diferente de zero
            }
        }

        fclose(frb);

        if(cont == 0){
            printf("\nNao ha pacotes com o ID informado.\n");
        }
    }
}

void menuPacotes(Pacote *vec_pacote)
{
    //declarar Pacote *vec_pacote na main do programa
    //Pacote *vec_pacote = (Pacote*) malloc(sizeof(Pacote)); //vetor dinamico de struct;

    int op;

    do{
        printf("\n=============================\n");
        printf("Menu de pacotes:");
        printf("\n=============================\n");
        printf("1. Cadastrar um pacote\n");
        printf("2. Listar pacotes\n");
        printf("3. Consultar pacotes\n");
        printf("4. Remover um pacote\n");
        printf("5. Encerrar programa");
        printf("\n=============================\n");
        printf("Digite aqui sua opcao: ");
        scanf("%d", &op);

        switch(op){
            case 1:
                cadastrarPacotes(vec_pacote);
                break;
            case 2:
                listarPacotes(vec_pacote);
                break;
            case 3:
                consultarPacotes(vec_pacote);
                break;
            case 4:
                removerPacotes(vec_pacote);
                break;
            case 5:
                printf("Encerrando o programa...");
                break;
            default:
                printf("Opcao invalida, tente outra.\n");
        }

    }while(op != 5);
    //declarar free(vec_pacote) na main do programa
    //free(vec_pacote);
}
