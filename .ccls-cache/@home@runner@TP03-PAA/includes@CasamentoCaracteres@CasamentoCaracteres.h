/*
*   Programa: CASAMENTO DE CADEIAS DE CARACTERES
*   Referências dos algoritmos de casamento de cadeias:
*   AUTOR: Professor Nivio Ziviani do DCC da UFMG
*   LINK: http://www2.dcc.ufmg.br/livros/algoritmos/cap8/codigo/c/8.1a8.6e8.8-pesquisacadeia.c
*/
#ifndef CASAMENTOCARACTERES
#define CASAMENTOCARACTERES

#include <stdio.h>
#include "../ArrayList/ArrayList.h"
#include "../Color/Color.h"
#define MAXCHAR 128

int BoyerMooreHorspool(char* T, long n, char* P, long m, ArrayList *ocorrencias);
void ShiftAndAproximado(char* T, long n, char* P, long m, long k);

#endif