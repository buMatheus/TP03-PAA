#include "../includes/CasamentoCaracteres/CasamentoCaracteres.h"
#include "../includes/Decoder/Decoder.h"

int main(void) {
  ArrayList decoderList;
  ArrayList tabelaFreqPortBR;
  Text text;
  int controle;
  int in;
  char *codigo;

  codigo = readEncryptedTextFromFile("texto-criptografado.txt");

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