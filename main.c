#include <stdio.h>
#include <stdlib.h>

#include "global.h"

int main () {
  int opcao;

  do {
    printf("\n\n=============================\n");
    printf("Menu de Gerenciamento:");
    printf("\n=============================\n");
    printf("1. Gerenciar Clientes;\n");
    printf("2. Gerenciar Pacotes de Viagem;\n");
    printf("3. Gerenciar Vendas;\n");
    printf("4. Encerrar programa.");
    printf("\n=============================\n");
    
    printf("Selecione uma das opções acima: ");
    scanf("%d", &opcao);
    printf("=============================\n\n");

    switch (opcao) {
      case 1:
        MenuCliente();
        break;
      case 2:
        menuPacotes();
        break;
      case 3:
        menuVendas();
        break;
      case 4:
        printf("Encerrando o programa...");
        break;
      default:
        printf("\nOpção inválida, tente outra.\n");
    }

  } while (opcao != 4);

  return 0;
}
