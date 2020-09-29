#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILE_VENDAS "./db/vendas.txt"

typedef struct vendas {
  int id, cpf_cliente, id_pacote;
  struct Data {
    int dia, mes, ano;
  } data;
} Vendas;

int vendasExiste () {
  FILE *f;
  int existe = 0;

  if ((f = fopen(FILE_VENDAS, "r+"))) {
    fclose(f);
    existe = 1;
  }

  return existe;
}

void adicionarVenda () {
  FILE *f = fopen(FILE_VENDAS, "ab+");

  time_t timeVenda;
  Vendas v;

  int id = 0;

  printf("Cadastro de Venda:");
  printf("\n=============================");
  printf("\nInsira o CPF do Cliente: ");
  scanf("%d", &v.cpf_cliente);
  printf("Insira o ID do Pacote de Viagem requirido: ");
  scanf("%d", &v.id_pacote);

  timeVenda = time(NULL);
  struct tm tm = *localtime(&timeVenda);

  v.data.dia = tm.tm_mday;
  v.data.mes = tm.tm_mon + 1;
  v.data.ano = tm.tm_year + 1900;

  //Gera ID da venda
  if (vendasExiste() == 1) {
    Vendas v2;
    FILE *frb = fopen(FILE_VENDAS, "rb");

    while (fread(&v2, sizeof(Vendas), 1, frb)) id = v2.id;
    id++;

    fclose(frb);
  }

  v.id = id;

  fwrite(&v, sizeof(Vendas), 1, f);

  fclose(f);

  printf("\nCadastro realizado com sucesso.");
}

void listarVendas () {
  FILE *f = fopen (FILE_VENDAS, "rb");
  Vendas v;

  if (vendasExiste() == 1) {
    printf("Vendas realizadas: ");
    printf("\n=============================\n");

    while (fread(&v, sizeof(Vendas), 1, f)) {
      printf("ID da Venda: %d\n", v.id);
      printf("CPF do Cliente: %d\n", v.cpf_cliente);
      printf("ID do Pacote: %d\n", v.id_pacote);
      printf("Data da venda: %02d/%02d/%d\n",  v.data.dia, v.data.mes, v.data.ano);
      printf("=============================\n");
    }
  } else {
    printf("=============================\n");
    printf("Nenhuma venda foi realizada.");
    printf("\n=============================\n");
  }

  fclose(f);
}

void listarVendasCliente () {
  int clienteCpf, contagem = 0;
  FILE *f = fopen (FILE_VENDAS, "rb");
  Vendas v;

  if (vendasExiste() == 1) {
    printf("Insira o CPF do Cliente para realizar a pesquisa: ");
    scanf("%d", &clienteCpf);

    printf("\nVendas realizadas para o Cliente de CPF %d: ", clienteCpf);
    printf("\n=============================\n");

    while (fread(&v, sizeof(Vendas), 1, f)) {
      if (v.cpf_cliente == clienteCpf) {
        printf("ID da Venda: %d\n", v.id);
        printf("ID do Pacote: %d\n", v.id_pacote);
        printf("Data da venda: %02d/%02d/%d\n",  v.data.dia, v.data.mes, v.data.ano);
        printf("=============================\n");

        contagem++;
      }
    }

    if (contagem == 0) {
      printf("Não há vendas realizadas para o CPF do Cliente indicado.\n");
      printf("=============================\n");
    }
  } else {
    printf("=============================\n");
    printf("Nenhuma venda foi realizada.");
    printf("\n=============================\n");
  }

  fclose(f);
}

void listarVendasPacote () {
  int pacoteId, contagem = 0;
  FILE *f = fopen (FILE_VENDAS, "rb");
  Vendas v;

  if (vendasExiste() == 1) {
    printf("Insira o ID do Pacote para realizar a pesquisa: ");
    scanf("%d", &pacoteId);

    printf("\nVendas realizadas para o Pacote de ID %d: ", pacoteId);
    printf("\n=============================\n");

    while (fread(&v, sizeof(Vendas), 1, f)) {
      if (v.id_pacote == pacoteId) {
        printf("ID da Venda: %d\n", v.id);
        printf("CPF do Cliente: %d\n", v.cpf_cliente);
        printf("Data da venda: %02d/%02d/%d\n",  v.data.dia, v.data.mes, v.data.ano);
        printf("=============================\n");

        contagem++;
      }
    }

    if (contagem == 0) {
      printf("Não há vendas realizadas para o ID do Pacote indicado.\n");
      printf("=============================\n");
    }
  } else {
    printf("=============================\n");
    printf("Nenhuma venda foi realizada.");
    printf("\n=============================\n");
  }

  fclose(f);
}

void removerVenda () {
  int vendaId, contagem = 0;
  FILE *f = fopen (FILE_VENDAS, "rb");
  Vendas v;

  if (vendasExiste() == 1) {
    Vendas *vd = (Vendas*) malloc(sizeof(Vendas));

    printf("Insira o ID da Venda a ser removida: ");
    scanf("%d", &vendaId);

    while (fread(&v, sizeof(Vendas), 1, f)) {
      if (v.id != vendaId) {
        *(vd + contagem) = v;
        contagem++;

        vd = (Vendas*) realloc(vd, (contagem + 1) * sizeof(Vendas));
      }
    }

    fclose(f);

    if (contagem != 0) {
      FILE *fw = fopen (FILE_VENDAS, "wb");

      for (int i = 0; i < contagem; i++) {
        fwrite((vd + i), sizeof(Vendas), 1, fw);
      }

      fclose(fw);
    } else {
      printf("Não há resultados para a venda indicada.\n");
      printf("=============================\n");
    }
  } else {
    printf("=============================\n");
    printf("Nenhuma venda foi realizada.");
    printf("\n=============================\n");
  }
}
