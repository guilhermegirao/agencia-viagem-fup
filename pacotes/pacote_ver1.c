#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_PACOTES "fru.txt"

typedef struct pacote
{
    long int idPacote;
    int numHospedes;
    char nomePacote[100], destinoViagem[100], dataPartida[100], dataRetorno[100];
}Pacote;

void cadastrarPacotes(){
    FILE *fab = fopen(FILE_PACOTES, "ab+");

    Pacote p;
    
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
    scanf("%ld", &p.idPacote);

    printf("Nome do pacote: ");
    scanf(" %[^\n]", p.nomePacote);

    printf("Destino: ");
    scanf(" %[^\n]", p.destinoViagem);

    printf("Numero de hospedes: ");
    scanf("%d", &p.numHospedes);

    printf("Data de partida: ");
    scanf(" %[^\n]", p.dataPartida);

    printf("Data de retorno: ");
    scanf(" %[^\n]", p.dataRetorno);

    fwrite(&p, sizeof(Pacote), 1, fab);

    fclose(fab);
}

void listarPacotes(){

    //checa se o arquivo possui ou nao pacotes

    FILE *frb = fopen(FILE_PACOTES, "rb");
    Pacote p;
    int cont_elementos = 0;

    while(fread(&p, sizeof(Pacote), 1, frb)){ //cont_elementos: numero de pacotes
        cont_elementos++;
    }
    fclose(frb);
    
    // se cont_elementos = 0, nao ha pacotes no arquivo
    FILE *frb2 = fopen(FILE_PACOTES, "rb");

    if(cont_elementos == 0){

        printf("\nNao ha pacotes cadastrados.\n");

    }else{

        while(fread(&p, sizeof(Pacote), 1, frb)){
        printf("\n=============================\n");
        printf("ID do pacote: %ld\n", p.idPacote);
        printf("Nome do pacote: %s\n", p.nomePacote);
        printf("Destino: %s\n", p.destinoViagem);
        printf("Numero de hospedes: %d\n", p.numHospedes);
        printf("Data de partida: %s\n", p.dataPartida);
        printf("Data de retorno: %s", p.dataRetorno);
        printf("\n=============================\n");
        }
        fclose(frb);

    }

    fclose(frb2);
}

void consultarPacotes(){

    //checa se o arquivo possui ou nao pacotes

    FILE *frb = fopen(FILE_PACOTES, "rb");
    Pacote p;
    int cont_elementos = 0;

    while(fread(&p, sizeof(Pacote), 1, frb)){
        cont_elementos++;
    }
    fclose(frb);

    FILE *frb2 = fopen(FILE_PACOTES, "rb");
    int op, cont = 0;

    // se cont_elementos = 0, nao ha pacotes no arquivo

    if(cont_elementos == 0){

        printf("\nNao ha pacotes cadastrados.\n");

    }else{

        printf("\nDigite o ID do pacote que deseja consultar: ");
        scanf("%d", &op);

        while(fread(&p, sizeof(Pacote), 1, frb2)){
            if(p.idPacote == op){
                printf("\n=============================\n");
                printf("ID do pacote: %ld\n", p.idPacote);
                printf("Nome do pacote: %s\n", p.nomePacote);
                printf("Destino: %s\n", p.destinoViagem);
                printf("Numero de hospedes: %d\n", p.numHospedes);
                printf("Data de partida: %s\n", p.dataPartida);
                printf("Data de retorno: %s", p.dataRetorno);
                printf("\n=============================\n");
                cont++;
            }
        }
        fclose(frb2);

        if(cont == 0){
            printf("\nNao ha pacotes com o ID informado.\n");
        }
    }
}

void removerPacotes(){

    //checa se o arquivo possui ou nao pacotes
    
    FILE *frb = fopen(FILE_PACOTES, "rb");
    Pacote p;
    int cont_elementos = 0;

    while(fread(&p, sizeof(Pacote), 1, frb)){
        cont_elementos++;
    }
    fclose(frb);

    // se cont_elementos = 0, nao ha pacotes no arquivo
    
    if(cont_elementos == 0){

        printf("\nNao ha pacotes cadastrados.\n");

    }else{

        FILE *frb2 = fopen(FILE_PACOTES, "rb");
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
        fclose(frb2);

        FILE *fwb = fopen(FILE_PACOTES, "wb");

        for(int i = 0; i < cont; i++){
            fwrite(pac+i, sizeof(Pacote), 1, fwb);
        }
        fclose(fwb);
    }
}

void menuPacotes(){

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
                cadastrarPacotes();
                break;
            case 2:
                listarPacotes();
                break;
            case 3:
                consultarPacotes();
                break;
            case 4:
                removerPacotes();
                break;
            case 5:
                printf("Encerrando o programa...");
                break;
            default:
                printf("\nOpcao invalida, tente outra.\n");
        }

    }while(op != 5);
}
