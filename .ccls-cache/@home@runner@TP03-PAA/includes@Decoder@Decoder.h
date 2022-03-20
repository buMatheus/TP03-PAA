#ifndef DECODER
#define DECODER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ArrayList/ArrayList.h"
#include "../Quicksort/Quicksort.h"
#include "../CasamentoCaracteres/CasamentoCaracteres.h"

#define FALSE 0
#define TRUE 1

typedef int bool;

/*
  Teremos dois caracteres para mapear junto com a flag de switch
  que quer dizer que ja foi decodificado e o caracter decode está 
  correto e ocurrence que é a quantidade de ocorrencia de cada letra
*/
typedef struct DecoderStructure {
  char code, decode;
  int occurrence;
  float freq;
  bool switch_status;
} DecoderStructure;

typedef struct Text {
  char *encrypted;
  char *decrypted;
} Text;

// estrutura que armazena a tabela de freq
// das letras na lingua portuguesa
typedef struct FreqTablePortBR {
  char letraAlfabeto;
  float freq;
} FreqTablePortBR;

// metodos
int interface(ArrayList *decoder, char *codigo);
void createFreqTable(ArrayList *decoder_list, char *text_encrypted);
void imprimeTabelaFreq(ArrayList *decoder_list);
void createFreqTablePortBR(ArrayList *list);
void imprimeFreqTablePortBR(ArrayList list);
void initText(Text *text, char *codigo);
void fazCasamentoNoTextoCriptografado(char *codigo, char *padrao);
bool checkIsValidChar(char ch);
void mostraEstadoAtual(ArrayList *decoder, char* codigo, char *texto_parcial);
char* criaTextoParcial(ArrayList *decoder, char* codigo);
void fazerCasamentoNoTextoParcial(char *texto_parcial, char *padrao, int erro);

#endif