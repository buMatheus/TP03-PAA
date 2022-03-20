#include "../includes/Decoder/Decoder.h"
#include "../includes/CasamentoCaracteres/CasamentoCaracteres.h"

int main(void) {
  ArrayList decoderList;
  ArrayList tabelaFreqPortBR;
  Text text;
  int controle;
  char codigo[70] = "R KHXRQ MQZI EXHGQYS BS SOPBS BS EXQZGHYS UHMBS ESXS APHTXSX R GRBQLR.";

  initText(&text, codigo);

  initializeArrayList(&decoderList);
  initializeArrayList(&tabelaFreqPortBR);

  // inicia tabelas de frequencia da lingua portuguesa
  createFreqTablePortBR(&tabelaFreqPortBR);
  imprimeFreqTablePortBR(tabelaFreqPortBR);

  do {
    controle = interface(&decoderList, codigo);
    
  } while(controle != 0);


  
  return 0;
}