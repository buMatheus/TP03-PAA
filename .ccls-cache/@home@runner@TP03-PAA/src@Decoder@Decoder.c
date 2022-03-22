#include "../../includes/Decoder/Decoder.h"

int interface(ArrayList *decoder, Text *text, ArrayList tabelaFreqPortBR) {
  int operacao, tolerancia;
  char padrao[MAXCHAR], original, mapeada;
  // char texto_parcial[strlen(text->encrypted) + 1];
  ArrayList decoderCopy;
  createFreqTable(decoder, text->encrypted);

  printf("\nEscolha uma opcao:");
  printf("\n");
  printf("\n1 - Apresentar estado atual da criptoanalise");
  printf("\n2 - Fazer analise de frequencia no texto criptografado");
  printf("\n3 - Realizar casamento exato de caracteres no texto criptografado");
  printf("\n4 - Realizar casamento aproximado de caracteres no texto "
         "parcialmente decifrado");
  printf("\n5 - Alterar chave de criptografia");
  printf("\n6 - Exportar resultado e encerrar o programa");
  printf("\n> ");
  fflush(stdin);
  scanf("%d", &operacao);

  switch (operacao) {
  case 1:
    strcpy(text->decrypted, criaTextoParcial(decoder, text->encrypted));
    mostraEstadoAtual(decoder, text->encrypted, text->decrypted);
    break;
  case 2:
    initializeArrayList(&decoderCopy);
    createFreqTable(&decoderCopy, text->encrypted);
    quicksort(&decoderCopy, 0, decoder->last - 1);
    imprimeTabelaFreq(&decoderCopy);
    imprimeFreqTablePortBR(tabelaFreqPortBR);
    break;
  case 3:
    printf("\nQual o padrao deseja utiliza?\n> ");
    scanf("%s", &padrao);
    getchar();
    fazCasamentoNoTextoCriptografado(text->encrypted, padrao);
    break;
  case 4:
    printf("\nQual o padrão e a tolerância utilizados?\n> ");
    scanf("%s %d", &padrao, &tolerancia);
    strcpy(text->decrypted, criaTextoParcial(decoder, text->encrypted));
    fazerCasamentoNoTextoParcial(text->decrypted, padrao, tolerancia);
    mostraEstadoAtual(decoder, text->encrypted, text->decrypted);

    break;
  case 5:
    // Pega caracteres
    printf("\nInforme a letra original, seguida da letra para a qual foi "
           "mapeada:\n> ");
    scanf("%s %s", &original, &mapeada);
    printf("\noriginal: %c", original);
    printf("\nmapeada: %c", mapeada);
    // Verifica se são válidos
    if ((checkIsValidChar(original) == TRUE) &&
        (checkIsValidChar(mapeada) == TRUE)) {
      // substitui em decode
      printf("\nVALIDOS!");
      for (int j = 0; j < decoder->last; j++) {
        DecoderStructure *decoder_current =
            (DecoderStructure *)decoder->array[j].item;
        if (decoder_current->code == mapeada) {
          decoder_current->decode = original;
          decoder_current->switch_status = TRUE;
          printf("\nCODE: %c", decoder_current->code);
          printf("\nDECODE: %c", decoder_current->decode);
        } else if (decoder_current->decode == original &&
                   decoder_current->code != mapeada) {
          decoder_current->decode = ' ';
        }
      }
    }
    break;
  case 6:
    printf("\nTexto decifrado:");
    printf("\n%s", text->decrypted);
    saveKey(decoder);
    saveText(text);
    printf("\nEncerrando o programa\n");
    break;
  default:
    printf("\nOpcao invalida!\n");
    break;
  }
  return operacao == 6 ? 0 : 1;
}

void fazerCasamentoNoTextoParcial(char *texto_parcial, char *padrao, int erro) {
  ShiftAndAproximado(texto_parcial, strlen(texto_parcial), padrao,
                     strlen(padrao), erro);
}

char *criaTextoParcial(ArrayList *decoder, char *codigo) {
  char *texto_parcial = (char *)malloc(strlen(codigo) + 1);
  int texto_tam = strlen(codigo);
  for (int i = 0; i < texto_tam; i++) {
    if (checkIsValidChar(codigo[i]) == TRUE) {
      for (int j = 0; j < decoder->last; j++) {
        DecoderStructure decoder_current =
            *(DecoderStructure *)decoder->array[j].item;
        if (codigo[i] == decoder_current.code &&
            decoder_current.switch_status == TRUE) {
          texto_parcial[i] = decoder_current.decode;
        } else if (codigo[i] == decoder_current.code) {
          texto_parcial[i] = decoder_current.code;
        }
      }
    } else {
      texto_parcial[i] = codigo[i];
    }
  }

  return texto_parcial;
}

void mostraEstadoAtual(ArrayList *decoder, char *codigo, char *texto_parcial) {
  // 1. mostra texto criptografado
  printf("\nTexto criptografado >");
  printf("\n%s", codigo);
  // 2. mostra chave
  printf("\n\nChave > ");
  char alfabeto[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  printf("\n%s\n", alfabeto);
  int flagPrintDecode;
  for (int i = 0; i < 26; i++) {
    flagPrintDecode = FALSE;
    for (int j = 0; j < decoder->last; j++) {
      DecoderStructure decoder_current =
          *(DecoderStructure *)decoder->array[j].item;
      if (decoder_current.switch_status == TRUE &&
          decoder_current.decode == alfabeto[i]) {
        printf("%c", decoder_current.code);
        flagPrintDecode = TRUE;
      } else if (decoder_current.decode == alfabeto[i]) {
        printf(" ");
        flagPrintDecode = TRUE;
      }
    }

    if (flagPrintDecode == FALSE) {
      printf(" ");
    }
  }
  // 3. mostra texto parcial
  printf("\n\nTexto parcialmente decifrado >\n");

  int tam = strlen(texto_parcial);
  for (int i = 0; i < tam; i++) {
    flagPrintDecode = FALSE;
    for (int j = 0; j < decoder->last; j++) {
      DecoderStructure decoder_current =
          *(DecoderStructure *)decoder->array[j].item;
      if (decoder_current.switch_status == TRUE &&
          decoder_current.code == codigo[i]) {
        green();
        printf("%c", texto_parcial[i]);
        reset();
        flagPrintDecode = TRUE;
      }
    }

    if (flagPrintDecode == FALSE) {
      printf("%c", texto_parcial[i]);
    }
  }
  // printf("\n%s", texto_parcial);
}

int countCharInText(char *text) {
  int qtd = 0;

  for (int i = 0; i < strlen(text); i++) {
    if (checkIsValidChar(text[i]) == TRUE)
      qtd++;
  }

  return qtd;
}

int coutPalavrasInText(char *text) {
  char *plvr = strtok(text, " ");
  int qtd = 0;
  while (plvr) {
    qtd++;
    plvr = strtok(NULL, " ");
  }

  return qtd;
}

void fazCasamentoNoTextoCriptografado(char *codigo, char *padrao) {
  ArrayList occ;
  int tamPadrao = strlen(padrao);
  initializeArrayList(&occ);
  int qtd_occ =
      BoyerMooreHorspool(codigo, strlen(codigo), padrao, strlen(padrao), &occ);
  printf("\nOcorrencias: %d", qtd_occ);

  printf("\nOcorrencais no texto: \n");
  int occ_iterator = 0;
  for (int index_codigo = 0; index_codigo < strlen(codigo); index_codigo++) {
    int index_occ =
        occ_iterator < occ.last ? *(int *)occ.array[occ_iterator].item : -1;

    if (index_codigo == index_occ) {
      int end_occ = index_occ + tamPadrao;
      while (index_occ < end_occ) {
        green();
        printf("%c", codigo[index_occ]);

        reset();
        index_occ++;
      }
      index_codigo = index_occ - 1;
      occ_iterator++;
      continue;
    }

    printf("%c", codigo[index_codigo]);
  }

  // mostra frequencia do padrao
  char *str_codigo;
  str_codigo = (char *)malloc(sizeof(char) * strlen(codigo));
  strcpy(str_codigo, codigo);
  int totalPalvr = coutPalavrasInText(str_codigo);
  int totalChar = countCharInText(codigo);
  double freqPalvr = (qtd_occ * 100) / totalPalvr;
  double freqChar = (qtd_occ * 100) / totalChar;

  printf("\n\n       |     Letras    | Palvras");
  printf("\n-------|---------------|----------");
  printf("\n Freq  |       %6.2lf% |    %4.2lf%", freqChar, freqPalvr);
}

// procura por um caracter na lista e retorna seu index
// caso existir, e -1 caso nao for encontrado
int checkForCharInDecoderList(ArrayList *decoder, char ch) {
  int index_decoder = -1;
  for (int i = 0; i < decoder->last; i++) {
    DecoderStructure decode = *(DecoderStructure *)decoder->array[i].item;

    if (decode.code == ch) {
      index_decoder = i;
    }
  }

  return index_decoder;
}

bool checkIsValidChar(char ch) {
  // Verifica se o char passado esta fora dos valores
  // de A e Z maiusculos na tabela ASCII
  if (ch < 65 || ch > 90)
    return FALSE;

  return TRUE;
}

void createFreqTable(ArrayList *decoder_list, char *text_encrypted) {
  int size_text = strlen(text_encrypted);

  for (int i = 0; i < size_text; i++) {
    char current_encrypted_char = text_encrypted[i];

    // se for um char que nao seja uma letra maiuscula vamos para a proxima
    // iteracao
    if (checkIsValidChar(current_encrypted_char) == FALSE)
      continue;

    int index_char_decoder =
        checkForCharInDecoderList(decoder_list, current_encrypted_char);

    // se achamos o char no array decoder entao incrementamos as ocorrencias
    // se nao, adicionamos uma nova occorencia para ele;
    if (index_char_decoder > -1 && current_encrypted_char != ' ') {
      DecoderStructure *decode;
      decode = (DecoderStructure *)decoder_list->array[index_char_decoder].item;
      decode->occurrence++;
      // printf("\nAdd freq > %c", current_encrypted_char);
    } else {
      DecoderStructure decode;
      decode.code = current_encrypted_char;
      decode.decode = ' ';
      decode.switch_status = FALSE;

      // se estivermos lendo um espaco em branco deve ser sempre 0
      decode.occurrence = current_encrypted_char == ' ' ? 0 : 1;
      // printf("\ntentando inserir > %c", current_encrypted_char);
      addItemArrayList(decoder_list, &decode, sizeof(DecoderStructure));
    }
  }

  // percorre a lista para calcular a freq das letras
  int sum_occurrences = 0;

  for (int i = 0; i < decoder_list->last; i++) {
    DecoderStructure decode_item =
        *(DecoderStructure *)decoder_list->array[i].item;
    sum_occurrences += decode_item.occurrence;
  }

  for (int i = 0; i < decoder_list->last; i++) {
    DecoderStructure *decode_item =
        (DecoderStructure *)decoder_list->array[i].item;
    decode_item->freq =
        ((float)decode_item->occurrence * 100.00) / sum_occurrences;
  }
}

void imprimeTabelaFreq(ArrayList *decoder_list) {
  printf("\n\nTabela de frequencia do texto criptografado");
  printf("\nLetra  |     Qtd    |   Freq");
  printf("\n-------|------------|--------");
  for (int i = 0; i < decoder_list->last; i++) {
    DecoderStructure decode_item =
        *(DecoderStructure *)decoder_list->array[i].item;

    // nao vamos mostrar os espacos em branco na tabela
    // if (decode_item.code == ' ') continue;
    printf("\n%-1c      |        %-4d|  %-2.2lf%c", decode_item.code,
           decode_item.occurrence, decode_item.freq, '%');
  }
}

void createFreqTablePortBR(ArrayList *list) {
  FreqTablePortBR item;

  // array com as frequencias das letras do alfabeto em
  // ordem alfabetica. Essa ordem pode ser econtrada na
  // documentacao do trabalho.
  float freqArr[26] = {14.63, 1.04, 3.88, 4.99, 12.57, 1.02,  1.30, 1.28, 6.18,
                       0.40,  0.02, 2.78, 4.74, 5.05,  10.73, 2.52, 1.20, 6.53,
                       7.81,  4.34, 4.63, 1.67, 0.01,  0.21,  0.01, 0.47};

  for (int i = 0; i < 26; i++) {
    item.freq = freqArr[i];
    item.letraAlfabeto = i + 65; // valor de A na tablea ASCII
    addItemArrayList(list, &item, sizeof(item));
  }
}

void imprimeFreqTablePortBR(ArrayList list) {
  printf("\n\nTabela de frequencia da lingua portuguesa");
  printf("\nLetra  |   Freq");
  printf("\n-------|--------");
  for (int i = 0; i < list.last; i++) {
    FreqTablePortBR decode_item = *(FreqTablePortBR *)list.array[i].item;
    printf("\n%-1c      |  %-2.2lf%c", decode_item.letraAlfabeto,
           decode_item.freq, '%');
  }
}

void initText(Text *text, char *codigo) {
  text->encrypted = (char *)malloc(sizeof(char) * strlen(codigo));
  text->decrypted = (char *)malloc(sizeof(char) * strlen(codigo));

  strcpy(text->encrypted, codigo);
  // iniciamos o texto encriptado para
  // facilitar a impressao do mesmo
  // semi-decifrado
  strcpy(text->decrypted, codigo);
}

char *readEncryptedTextFromFile(char *file_name) {
  FILE *file;
  char *texto;
  char ch;
  int iterator = 0;

  texto = (char *)malloc(sizeof(char) * MAXTEXTTAM);
  file = fopen(file_name, "r");

  if (file == NULL) {
    printf("\nErro ao abrir o arquivo");
    exit(1);
  }

  while ((ch = fgetc(file)) != EOF) {
    texto[iterator] = ch;
    iterator++;
  }

  fclose(file);

  return texto;
}

void saveKey(ArrayList *decoder) {
  FILE *file;

  file = fopen("resultado-chave.txt", "w");

  if (file == NULL) {
    printf("\nErro ao abrir o arquivo");
    exit(1);
  }

  fprintf(file, "Chave > ");
  char alfabeto[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  fprintf(file, "\n%s\n", alfabeto);
  int flagPrintDecode;
  for (int i = 0; i < 26; i++) {
    flagPrintDecode = FALSE;
    for (int j = 0; j < decoder->last; j++) {
      DecoderStructure decoder_current =
          *(DecoderStructure *)decoder->array[j].item;
      if (decoder_current.switch_status == TRUE &&
          decoder_current.decode == alfabeto[i]) {
        fprintf(file, "%c", decoder_current.code);
        flagPrintDecode = TRUE;
      } else if (decoder_current.decode == alfabeto[i]) {
        fprintf(file, " ");
        flagPrintDecode = TRUE;
      }
    }

    if (flagPrintDecode == FALSE) {
      fprintf(file, " ");
    }
  }

  printf("\nChave salva com sucesso!");

  fclose(file);
}

void saveText(Text *text) {
  FILE *file;

  file = fopen("resultado-texto.txt", "w");

  if (file == NULL) {
    printf("\nErro ao abrir o arquivo");
    exit(1);
  }

  fprintf(file, "Texto decifrado > ");
  fprintf(file, "\n%s\n", text->decrypted);

  printf("\nTexto decifrado salvo com sucesso!");

  fclose(file);
}