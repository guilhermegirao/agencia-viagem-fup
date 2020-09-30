#include <stdio.h>
#include <stdlib.h>
#define FILE_CLIENTE "./db/clientes.txt"
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


void addC(Cliente *vec_cliente){
  FILE *f = fopen(FILE_CLIENTE, "ab+");

  printf("Digite os seguintes dados para realizar o cadastro do cliente\n");
  //ler os dados do cliente
  printf("Digite o CPF sem os caracteres especiais /./ /-/\n");
  printf("CPF: ");
  scanf("%d",&vec_cliente->cpf);
  printf("\nNome e sobrenome: ");
  scanf(" %[^\n]", vec_cliente->nome);
  printf("\nE-mail do cliente: ");
  scanf(" %[^\n]", vec_cliente->email);
  
  fwrite(vec_cliente, sizeof(Cliente), 1, f);
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
  printf("Digite o CPF do cliente a ser removido: ");
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
    printf("Nenhum cadastro realizado.");
    printf("\n=============================\n");
}
}
void listC(Cliente *vec_cliente){
  FILE *f = fopen(FILE_CLIENTE, "r+");

  if (verife()==1){
    while(fread(vec_cliente, sizeof(Cliente), 1, f)){
      printf("=============================\n");
      printf("CPF: %d\n", vec_cliente->cpf);
      printf("Nome: %s\n", vec_cliente->nome);
      printf("E-mail: %s\n", vec_cliente->email);
      printf("=============================\n");
    }
  } else{
    printf("=============================\n");
    printf("Nenhum cadastro realizado.");
    printf("\n=============================\n");
  }

  fclose(f);
}
void serchC(Cliente *vec_cliente){
  int clienteCpf, contagem = 0;
  FILE *f = fopen (FILE_CLIENTE, "rb");

  if (verife() == 1) {
    printf("Insira o CPF do Cliente para realizar a pesquisa: ");
    scanf("%d", &clienteCpf);

    while (fread(vec_cliente, sizeof(Cliente), 1, f)) {
      if (vec_cliente->cpf == clienteCpf) {
        printf("CPF: %d\n", vec_cliente->cpf);
        printf("Nome: %s\n", vec_cliente->nome);
        printf("E-mail:%s\n",  vec_cliente->email);
        printf("=============================\n");

        contagem++;
      }
    }

    if (contagem == 0) {
      printf("Não há cadastros realizados para o CPF do Cliente indicado.\n");
      printf("=============================\n");
    }
  } else {
    printf("=============================\n");
    printf("Nenhum cadastro realizado.");
    printf("\n=============================\n");
  }
}
//Checa se o cliente informado existe
int checarCliente(Cliente *vec_cliente, int clienteCpf){
  int contagem = 0;
  FILE *f = fopen (FILE_CLIENTE, "rb");

  if (verife() == 1) {
    while (fread(vec_cliente, sizeof(Cliente), 1, f)) {
      if (vec_cliente->cpf == clienteCpf) {
        contagem = 1;
      }
    }

    fclose(f);
  }

  return contagem;
}
void menuCliente (){
int opt1;

Cliente *vec_cliente = (Cliente*) malloc(sizeof(Cliente)); 

do{
printf("\n=============================\n");
        printf("Menu de Clientes:");
        printf("\n=============================\n");
        printf("1. Cadastrar um cliente;\n");
        printf("2. Listar Cadastros;\n");
        printf("3. Consultar Cadastro;\n");
        printf("4. Remover um Cadastro;\n");
        printf("5. Voltar ao Menu de Gerenciamento.");
        printf("\n=============================\n");
  printf("Digite aqui sua opcao: ");
scanf("%d", &opt1);
switch (opt1){
  case 1:
  addC(vec_cliente);
  break;
  case 2:
  listC(vec_cliente);
  break;
  case 3:
  serchC(vec_cliente);
  break;
  case 4:
  removC();
  break;
  case 5:
  printf("Voltando ao Menu de Gerenciamento...");
  break;
  default:
  printf("Codigo da operação invalido.\n");
}
  
}while(opt1!=5);

free(vec_cliente);

}