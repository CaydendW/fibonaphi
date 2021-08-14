#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <stdio.h>

typedef struct token {
  size_t type;
  size_t length;
  size_t line;
  size_t column;
  char *buffer;
} token_t;

typedef struct token_program {
  size_t token_count;
  token_t *tokens;
  size_t index;
} token_program_t;

token_program_t lex(FILE *in);

#endif
