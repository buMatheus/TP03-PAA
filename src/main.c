#include "../includes/CasamentoCaracteres/CasamentoCaracteres.h"
#include "../includes/Decoder/Decoder.h"

int main(int argc, char **argv) {
  ArrayList decoderList;
  ArrayList tabelaFreqPortBR;
  Text text;
  int controle;
  int in;
  char *codigo;
  char nome_arquivo[100];
  
  // quando o nome do arquivo eh passado como argumento iniciamos nossa variavel
  if (argc > 0) {
    for (int i = 0; i < argc; i++) {
      if (strcmp(argv[i], "--file") == 0 || strcmp(argv[i], "--arquivo") == 0) {
        strcpy(nome_arquivo, argv[i+1]);
      }
    }
  } 

  if (strlen(nome_arquivo) == 0) {
    printf("\nVoce nao passou um arquivo de entrada! O programa sera fechado\n");
    exit(1);
  }

  codigo = readEncryptedTextFromFile(nome_arquivo);

  initText(&text, codigo);

  initializeArrayList(&decoderList);
  initializeArrayList(&tabelaFreqPortBR);

  // inicia tabelas de frequencia da lingua portuguesa
  createFreqTablePortBR(&tabelaFreqPortBR);  

  do {
    controle = interface(&decoderList, &text, tabelaFreqPortBR);

    printf("\n\nAperte [0] para continuar: ");
    scanf("%d", &in);
    getchar();
    if (in == 0 && controle != 0) {
      clearScreen();
    }   

  } while (controle != 0);

  return 0;
}