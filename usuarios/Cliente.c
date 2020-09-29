#include <stdio.h>
#include <stdlib.h>
#define FILE_CLIENTE "CLIENTE.txt"
typedef struct cliente{
int cpf;
char nome[50];
char email[50];
}Cliente;

int verife () {
  FILE *f;
  int cont = 0;

  if ((f = fopen(FILE_CLIENTE, "r+"))) {
    fclose(f);
    cont = 1;
  }

  return cont;
}


void addC(){
  FILE *f = fopen(FILE_CLIENTE, "ab+");
  Cliente c; 

  printf("Digite os seguintes dados para realizar o cadastro do cliente\n");
  //ler os dados do cliente
  printf("Digite o CPF sem os caracteres especiais /./ /-/\n");
  printf("CPF: ");
  scanf("%d",&c.cpf);
  printf("\nNome e sobrenome: ");
  scanf(" %[^\n]", c.nome);
  printf("\nE-mail do cliente: ");
  scanf(" %[^\n]", c.email);
  
  fwrite(&c, sizeof(Cliente), 1, f);
  fclose(f);
  printf("=============================\n");
    printf("Cadastro realizado com sucesso.");
    printf("\n=============================\n");
}
void removC(){
  FILE *f = fopen(FILE_CLIENTE, "rb");
  int cpfaux, cont = 0;
  Cliente c;
  if(verife()== 1){
  Cliente *clientes = (Cliente*) malloc(sizeof(Cliente));
  printf("Digite o CPF do cliente a ser removido");
  scanf("%d", &cpfaux);

  while(fread(&c, sizeof(Cliente), 1, f)){
    if (c.cpf != cpfaux){ 
      *(clientes + cont) = c;
      cont++;
      clientes = (Cliente*) realloc(clientes, (cont+1)*sizeof(Cliente));
    }
  }

  fclose(f);

  FILE *fw = fopen(FILE_CLIENTE, "wb");
  for (int i=0; i< cont; i++){
    fwrite(clientes+i, sizeof(Cliente), 1, fw);
  }

  fclose(fw);

  
}else{
   printf("=============================\n");
    printf("Nenhuma cadastro realizado.");
    printf("\n=============================\n");
}
}
void listC(){
  FILE *f = fopen(FILE_CLIENTE, "r+");
  Cliente c;
  if (verife()==1){
    while(fread(&c, sizeof(Cliente), 1, f)){
      printf("=============================\n");
      printf("CPF: %d\n", c.cpf);
      printf("Nome: %s\n",c.nome);
      printf("E-mail: %s\n",c.email);
      printf("=============================\n");
    }
  } else{
    printf("=============================\n");
    printf("Nenhuma cadastro relaizado.");
    printf("\n=============================\n");
  }

  fclose(f);
}
void serchC(){
  int clienteCpf, contagem = 0;
  FILE *f = fopen (FILE_CLIENTE, "rb");
  Cliente c;

  if (verife() == 1) {
    printf("Insira o CPF do Cliente para realizar a pesquisa: ");
    scanf("%d", &clienteCpf);

    printf("\nCadastro realizadas para o Cliente de CPF %d: ", clienteCpf);
    printf("\n=============================\n");

    while (fread(&c, sizeof(Cliente), 1, f)) {
      if (c.cpf == clienteCpf) {
        printf("CPF: %d\n", c.cpf);
        printf("Nome: %s\n", c.nome);
        printf("Email:%s\n",  c.email);
        printf("=============================\n");

        contagem++;
      }
    }

    if (contagem == 0) {
      printf("Não há cadastrps realizadas para o CPF do Cliente indicado.\n");
      printf("=============================\n");
    }
  } else {
    printf("=============================\n");
    printf("Nenhum cadastro realizado.");
    printf("\n=============================\n");
  }
}

void MenuCliente (){
int opt1;
 printf("\n=============================\n");
        printf("Menu de Clientes:");
        printf("\n=============================\n");
        printf("1. Cadastrar um cliente\n");
        printf("2. Listar pacotes\n");
        printf("3. Consultar pacotes\n");
        printf("4. Remover um pacote\n");
        printf("5. Encerrar programa");
        printf("\n=============================\n");
do{
  printf("Digite aqui sua opcao: ");
scanf("%d", &opt1);
switch (opt1){
  case 1:
  addC();
  break;
  case 2:
  listC();
  break;
  case 3:
  serchC();
  break;
  case 4:
  removC();
  break;
  case 5:
  printf("Programa encerrado com sucesso!");
  break;
  default:
  printf("Codigo da operação invalido.\n");
}
  
}while(opt1!=5);

}