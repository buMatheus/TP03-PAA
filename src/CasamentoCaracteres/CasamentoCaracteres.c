#include "../../includes/CasamentoCaracteres/CasamentoCaracteres.h"

//Algoritmo Boyer-Moore-Horspool
int BoyerMooreHorspool(char* Texto, long tamTexto, char* Padrao, long tamPadrao, ArrayList *ocorrencias) { 
    int i, j, k;
    int qtd = 0;

    //cria tabela de deslocamento
    int *d = (int*)malloc(sizeof(int)*MAXCHAR);
    for (i = 0; i < MAXCHAR; i++) d[i] = tamPadrao;
    for (i = 0; i < tamPadrao-1; i++) d[Padrao[i]] = tamPadrao-i-1;

    //faz a pesquisa
    i = tamPadrao-1;
    while (i < tamTexto) {
        k = i;
        j = tamPadrao-1;
        while (Texto[k] == Padrao[j] && j >= 0) {
            k--;
            j--;
        }
        if (j == -1) {
            int index_occ = k + 1;
            // printf("Casamento na posição: %d\n", index_occ);
            addItemArrayList(ocorrencias, &index_occ, sizeof(index_occ));
            qtd ++;
        }
        i += d[Texto[i]];
    }

    free(d);

    return qtd;
}

//Shif-And Aproximado
void ShiftAndAproximado(char* T, long n, char* P, long m, long k) {
  long Masc[128], i, j, Ri, Rant, Rnovo;
  long R[11];

  for (i = 0; i < MAXCHAR; i++) Masc[i] = 0;

  for (i = 1; i <= m; i++) Masc[P[i - 1] + 127] |= 1 << (m - i);

  R[0] = 0;
  Ri = 1 << (m - 1);

  for (j = 1; j <= k; j++) R[j] = (1 << (m - j)) | R[j - 1];

  for (i = 0; i < n; i++) {
    Rant = R[0];
    Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & Masc[T[i] + 127];
    R[0] = Rnovo;

    for (j = 1; j <= k; j++) {
      // Consideramos apenas erro por substituição
      Rnovo = ((((unsigned long)R[j]) >> 1) & Masc[T[i] + 127]) | (((unsigned long)Rant) >> 1); 

      Rant = R[j];
      R[j] = Rnovo | Ri;
    }

    if ((Rnovo&1) != 0) printf("Casamento aproximado na posicao %12ld\n", i + 1);
  }
    // if (!MODO_DEBUG)
    //     printf("Quantidade de casamentos: %d\n", contCasamento);
}
