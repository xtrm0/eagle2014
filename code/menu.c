#include "../include/menu.h"

void clearbuffer() {
  while(getchar()!='\n');
}

int menu(void) {
  char opcao;

  printf("1. Especificação dos dados do módulo e das condições iniciais do voo.\n");
  printf("2. Simulação do voo em modo de “cockpit”.\n");
  printf("3. Apresentação em modo gráfico da trajectória do módulo.\n");
  printf("4. Definição do perfil da superfície lunar.\n");
  printf("5. Simulação do voo em modo gráfico.\n");
  printf("Opção: ");
  opcao = getchar();
  if (opcao!='\n') clearbuffer();

  switch (opcao)
  {
    case '0':
      return 1;
    case '1':
      
      break;
    case '2':
      break;
    case '3':
      break;
    case '4':
      break;
    case '5':
      break;
    break;
      default:
      printf("Opção desconhecida.");
  }

  return 0;
}
