#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../clientes/clientesFuncoes.h"
#include "../pacotes/pacotesFuncoes.h"

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

void adicionarVendas (Vendas *vetVendas) {
  Pacote *vetPacote = (Pacote*) malloc(sizeof(Pacote));
  Cliente *vetCliente = (Cliente*) malloc(sizeof(Cliente));

  FILE *f = fopen(FILE_VENDAS, "ab+");

  time_t timeVenda;

  int id = 0;

  printf("Cadastro de Venda:");
  printf("\n=============================");
  printf("\nInsira o CPF do Cliente: ");
  scanf("%d", &vetVendas->cpf_cliente);
  printf("Insira o ID do Pacote de Viagem requirido: ");
  scanf("%d", &vetVendas->id_pacote);

  //Verificação se cliente e pacote existem para realizar o cadastro de uma venda
  if (checarCliente(vetCliente, vetVendas->cpf_cliente) == 1) {
    if (checarPacotes(vetPacote, vetVendas->id_pacote) == 1) {
      //Gerar Data atual
      timeVenda = time(NULL);
      struct tm tm = *localtime(&timeVenda);

      vetVendas->data.dia = tm.tm_mday;
      vetVendas->data.mes = tm.tm_mon + 1;
      vetVendas->data.ano = tm.tm_year + 1900;

      //Gera ID da venda
      if (vendasExiste() == 1) {
        Vendas v2;
        FILE *frb = fopen(FILE_VENDAS, "rb");

        while (fread(&v2, sizeof(Vendas), 1, frb)) id = v2.id;
        id++;
        
        fclose(frb);
      }

      vetVendas->id = id;

      fwrite(vetVendas, sizeof(Vendas), 1, f);
      
      printf("\nCadastro realizado com sucesso.");
    } else {
      printf("=============================\n");
      printf("Não há Pacotes cadastrados com este ID. Por favor, cadastre um antes de adicionar a uma venda.\n");
      printf("=============================\n");
    }
  } else {
    printf("=============================\n");
    printf("Não há Clientes cadastrados com este CPF. Por favor, cadastre-o antes de adicionar a uma venda.\n");
    printf("=============================\n");
  }
  
  fclose(f);
}

void listarVendas (Vendas *vetVendas) {
  int contagem = 0;
  FILE *f = fopen (FILE_VENDAS, "rb");

  if (vendasExiste() == 1) {
    printf("Vendas realizadas: ");
    printf("\n=============================\n");

    while (fread(vetVendas, sizeof(Vendas), 1, f)) {
      printf("ID da Venda: %d\n", vetVendas->id);
      printf("CPF do Cliente: %d\n", vetVendas->cpf_cliente);
      printf("ID do Pacote: %d\n", vetVendas->id_pacote);
      printf("Data da venda: %02d/%02d/%d\n", vetVendas->data.dia, vetVendas->data.mes, vetVendas->data.ano);
      printf("=============================\n");

      contagem++;
    }

    if (contagem == 0) {
      printf("Não há vendas cadastradas no momento.\n");
      printf("=============================\n");
    }
  } else {
    printf("=============================\n");
    printf("Nenhuma venda foi realizada.");
    printf("\n=============================\n");
  }

  fclose(f);
}

void listarVendasCliente (Vendas *vetVendas) {
  int clienteCpf, contagem = 0;
  FILE *f = fopen (FILE_VENDAS, "rb");

  if (vendasExiste() == 1) {
    printf("Insira o CPF do Cliente para realizar a pesquisa: ");
    scanf("%d", &clienteCpf);

    printf("\nVendas realizadas para o Cliente de CPF %d: ", clienteCpf);
    printf("\n=============================\n");

    while (fread(vetVendas, sizeof(Vendas), 1, f)) {
      if (vetVendas->cpf_cliente == clienteCpf) {
        printf("ID da Venda: %d\n", vetVendas->id);
        printf("CPF do Cliente: %d\n", vetVendas->cpf_cliente);
        printf("ID do Pacote: %d\n", vetVendas->id_pacote);
        printf("Data da venda: %02d/%02d/%d\n", vetVendas->data.dia, vetVendas->data.mes, vetVendas->data.ano);
        printf("=============================\n");

        contagem++;
      }
    }

    if (contagem == 0) {
      printf("\nNão há vendas realizadas para o CPF do Cliente indicado.\n");
      printf("=============================\n");
    }
  } else {
    printf("=============================\n");
    printf("Nenhuma venda foi realizada.");
    printf("\n=============================\n");
  }

  fclose(f);
}

void listarVendasPacote (Vendas *vetVendas) {
  int pacoteId, contagem = 0;
  FILE *f = fopen (FILE_VENDAS, "rb");

  if (vendasExiste() == 1) {
    printf("Insira o ID do Pacote para realizar a pesquisa: ");
    scanf("%d", &pacoteId);

    printf("\nVendas realizadas para o Pacote de ID %d: ", pacoteId);
    printf("\n=============================\n");

    while (fread(vetVendas, sizeof(Vendas), 1, f)) {
      if (vetVendas->id_pacote == pacoteId) {
        printf("ID da Venda: %d\n", vetVendas->id);
        printf("CPF do Cliente: %d\n", vetVendas->cpf_cliente);
        printf("ID do Pacote: %d\n", vetVendas->id_pacote);
        printf("Data da venda: %02d/%02d/%d\n", vetVendas->data.dia, vetVendas->data.mes, vetVendas->data.ano);
        printf("=============================\n");

        contagem++;
      }
    }

    if (contagem == 0) {
      printf("\nNão há vendas realizadas para o ID do Pacote indicado.\n");
      printf("=============================\n");
    }
  } else {
    printf("=============================\n");
    printf("Nenhuma venda foi realizada.");
    printf("\n=============================\n");
  }

  fclose(f);
}

void removerVendas () {
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

    FILE *fw = fopen (FILE_VENDAS, "wb");
    for (int i = 0; i < contagem; i++) {
      fwrite((vd + i), sizeof(Vendas), 1, fw);
    }

    fclose(fw);
  } else {
    printf("=============================\n");
    printf("Nenhuma venda foi realizada.");
    printf("\n=============================\n");
  }
}

void removerVendasCliente () {
  int clienteCpf, contagem = 0;
  FILE *f = fopen (FILE_VENDAS, "rb");
  Vendas v;

  if (vendasExiste() == 1) {
    Vendas *vd = (Vendas*) malloc(sizeof(Vendas));

    printf("Insira o CPF do Cliente a ter suas Vendas removidas: ");
    scanf("%d", &clienteCpf);

    while (fread(&v, sizeof(Vendas), 1, f)) {
      if (v.cpf_cliente != clienteCpf) {
        *(vd + contagem) = v;
        contagem++;

        vd = (Vendas*) realloc(vd, (contagem + 1) * sizeof(Vendas));
      }
    }

    fclose(f);

    FILE *fw = fopen (FILE_VENDAS, "wb");
    for (int i = 0; i < contagem; i++) {
      fwrite((vd + i), sizeof(Vendas), 1, fw);
    }

    fclose(fw);
  } else {
    printf("=============================\n");
    printf("Nenhuma venda foi realizada.");
    printf("\n=============================\n");
  }
}

void removerVendasPacote () {
  int pacoteId, contagem = 0;
  FILE *f = fopen (FILE_VENDAS, "rb");
  Vendas v;

  if (vendasExiste() == 1) {
    Vendas *vd = (Vendas*) malloc(sizeof(Vendas));

    printf("Insira o ID do Pacote a ter suas Vendas removidas: ");
    scanf("%d", &pacoteId);

    while (fread(&v, sizeof(Vendas), 1, f)) {
      if (v.id_pacote != pacoteId) {
        *(vd + contagem) = v;
        contagem++;

        vd = (Vendas*) realloc(vd, (contagem + 1) * sizeof(Vendas));
      }
    }

    fclose(f);

    FILE *fw = fopen (FILE_VENDAS, "wb");
    for (int i = 0; i < contagem; i++) {
      fwrite((vd + i), sizeof(Vendas), 1, fw);
    }

    fclose(fw);
  } else {
    printf("=============================\n");
    printf("Nenhuma venda foi realizada.");
    printf("\n=============================\n");
  }
}

void menuVendas () {
  int opcao;

  Vendas *vetVendas = (Vendas*) malloc(sizeof(Vendas)); 

  do {
    printf("\n\n=============================\n");
    printf("Menu de Vendas:");
    printf("\n=============================\n");
    printf("1. Adicionar uma Venda;\n");
    printf("2. Listar todas as Vendas;\n");
    printf("3. Listar Vendas por Cliente;\n");
    printf("4. Listar Vendas por Pacote;\n");
    printf("5. Remover alguma Venda;\n");
    printf("6. Remover Vendas por Cliente;\n");
    printf("7. Remover Vendas por Pacote;\n");
    printf("8. Voltar ao Menu de Gerenciamento.");
    printf("\n=============================\n");
    
    printf("Selecione uma das opções acima: ");
    scanf("%d", &opcao);
    printf("=============================\n\n");

    switch (opcao) {
      case 1:
        adicionarVendas(vetVendas);
        break;
      case 2:
        listarVendas(vetVendas);
        break;
      case 3:
        listarVendasCliente(vetVendas);
        break;
      case 4:
        listarVendasPacote(vetVendas);
        break;
      case 5:
        removerVendas();
        break;
      case 6:
        removerVendasCliente();
        break;
      case 7:
        removerVendasPacote();
        break;
      case 8:
        printf("Voltando ao Menu de Gerenciamento...");
        free(vetVendas);
        break;
      default:
        printf("\nOpção inválida, tente outra.\n");
    }

  } while (opcao != 8);
}
