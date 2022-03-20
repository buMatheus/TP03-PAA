/*
  estrutura pensada em
  2 caracteres e uma flag
  quando achar a chave de mudança, muda a flag
*/
#ifndef STRUCTURE
#define STRUCTURE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
  Teremos dois caracteres para mapear junto com a flag de switch
  que quer dizer que ja foi decodificado e o caracter decode está 
  correto e ocurrence que é a quantidade de ocorrencia de cada letra
*/
typedef struct Structure {
  char code, decode;
  int switch_status, occurrence;
} Structure;



#endif