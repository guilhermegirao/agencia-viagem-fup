#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_PACOTES "./db/pacotes.txt"

typedef struct pacote
{
    long int idPacote;
    int numHospedes;
    char nomePacote[100], destinoViagem[100], dataPartida[100], dataRetorno[100];
}Pacote;

int contElementosVetor(Pacote *vec_pacote){ // função para contar elementos do vetor de struct

    int cont_elementos_struct = 0;

    FILE *frb;

    if ((frb = fopen(FILE_PACOTES, "rb"))) {
        while(fread(vec_pacote, sizeof(Pacote), 1, frb)){
            cont_elementos_struct++;
            if (cont_elementos_struct >= 1) {
                break;
            }
        }
        fclose(frb);
    }

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

    //checa se o arquivo possui ou nao pacotes

    FILE *frb = fopen(FILE_PACOTES, "rb");
    int cont_elementos = contElementosVetor(vec_pacote);

    // se cont_elementos = 0, nao ha pacotes no arquivo
    if(cont_elementos == 0){

        printf("\nNao ha pacotes cadastrados.\n");

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
        fclose(frb);

    }
}

void consultarPacotes(Pacote *vec_pacote){
    
    FILE *frb = fopen(FILE_PACOTES, "rb");

    int cont_elementos = contElementosVetor(vec_pacote);

    int op, cont = 0;

    // se cont_elementos = 0, nao ha pacotes no arquivo
    if(cont_elementos == 0){

        printf("\nNao ha pacotes cadastrados.\n");

    }else{

        printf("\nDigite o ID do pacote que deseja consultar: ");
        scanf("%d", &op);

        while(fread(vec_pacote, sizeof(Pacote), 1, frb)){
            if(vec_pacote->idPacote == op){
                printf("\n=============================\n");
                printf("ID do pacote: %ld\n", vec_pacote->idPacote);
                printf("Nome do pacote: %s\n", vec_pacote->nomePacote);
                printf("Destino: %s\n", vec_pacote->destinoViagem);
                printf("Numero de hospedes: %d\n", vec_pacote->numHospedes);
                printf("Data de partida: %s\n", vec_pacote->dataPartida);
                printf("Data de retorno: %s", vec_pacote->dataRetorno);
                printf("\n=============================\n");
                cont++;
            }
        }
        fclose(frb);

        if(cont == 0){
            printf("\nNao ha pacotes com o ID informado.\n");
        }
    }
}

void removerPacotes(Pacote *vec_pacote){

    //checa se o arquivo possui ou nao pacotes
    
    FILE *frb = fopen(FILE_PACOTES, "rb");
    Pacote p;
    int cont_elementos = contElementosVetor(vec_pacote);
    
    // se cont_elementos = 0, nao ha pacotes no arquivo
    
    if(cont_elementos == 0){

        printf("\nNao ha pacotes cadastrados.\n");

    }else{

        Pacote *pac = (Pacote*) malloc(sizeof(Pacote));
        long int id;
        int cont = 0;

        printf("Digite o ID do pacote a ser removido: ");
        scanf("%ld", &id);

        while(fread(&p, sizeof(Pacote), 1, frb)){
            if(p.idPacote != id){
                *(pac + cont) = p;
                cont++;
                pac = (Pacote*) realloc(pac, (cont + 1) * sizeof(Pacote));
            }
        }

        FILE *fwb = fopen(FILE_PACOTES, "wb");

        for(int i = 0; i < cont; i++){
            fwrite(pac+i, sizeof(Pacote), 1, fwb);
        }
        fclose(fwb);
    }
}

//Checa se o pacote informado existe
int checarPacotes(Pacote *vec_pacote, int idPacote){
    
    FILE *frb = fopen(FILE_PACOTES, "rb");

    int cont_elementos = contElementosVetor(vec_pacote);

    int cont = 0;

    // se cont_elementos = 0, nao ha pacotes no arquivo
    if(cont_elementos > 0){
        
        while(fread(vec_pacote, sizeof(Pacote), 1, frb)){
            if(vec_pacote->idPacote == idPacote){
                cont = 1;
            }
        }

        fclose(frb);
    }

    return cont;
}

void menuPacotes(){

    int op;

    Pacote *vec_pacote = (Pacote*) malloc(sizeof(Pacote)); //vetor dinamico de struct;

    do{
        printf("\n=============================\n");
        printf("Menu de pacotes:");
        printf("\n=============================\n");
        printf("1. Cadastrar um pacote;\n");
        printf("2. Listar pacotes;\n");
        printf("3. Consultar pacotes;\n");
        printf("4. Remover um pacote;\n");
        printf("5. Voltar ao Menu de Gerenciamento.");
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
                printf("Voltando ao Menu de Gerenciamento...");
                break;
            default:
                printf("\nOpcao invalida, tente outra.\n");
        }

    }while(op != 5);

    free(vec_pacote);
}
