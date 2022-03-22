#ifndef TEXT
#define TEXT

#define MAXTEXTTAM 100000

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Decoder/Decoder.h"

typedef struct Text {
  char *encrypted;
  char *decrypted;
} Text;



#endif