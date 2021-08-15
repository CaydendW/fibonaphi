#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lex.h>
#include <token_type.h>

static inline int is_num(char *buffer, size_t length) {
  for (size_t i = 0; i < length; i++)
    if (!isdigit(buffer[i]) && buffer[i] != '.')
      return 0;
  return 1;
}

static inline int is_identifier(char *buffer, size_t length) {
  for (size_t i = 0; i < length; i++)
    if (!isalpha(buffer[i]))
      return 0;
  return 1;
}

static inline int identify(char *buffer, size_t length) {
  if (strncmp(buffer, "", length) == 0)
    return T_INVALID;

  else if (strncmp(buffer, "(", length) == 0)
    return T_LEFTPAREN;
  else if (strncmp(buffer, ")", length) == 0)
    return T_RIGHTPAREN;
  else if (strncmp(buffer, "[", length) == 0)
    return T_LEFTBRACKET;
  else if (strncmp(buffer, "]", length) == 0)
    return T_RIGHTBRACKET;
  else if (strncmp(buffer, "{", length) == 0)
    return T_LEFTBRACE;
  else if (strncmp(buffer, "}", length) == 0)
    return T_RIGHTBRACE;

  else if (strncmp(buffer, ",", length) == 0)
    return T_COMMA;
  else if (strncmp(buffer, ":", length) == 0)
    return T_COLON;

  else if (strncmp(buffer, "*", length) == 0)
    return T_MUL;
  else if (strncmp(buffer, "/", length) == 0)
    return T_DIV;
  else if (strncmp(buffer, "+", length) == 0)
    return T_ADD;
  else if (strncmp(buffer, "-", length) == 0)
    return T_MIN;

  else if (strncmp(buffer, "=", length) == 0)
    return T_EQUAL;

  else if (strncmp(buffer, "<", length) == 0)
    return T_LESSTHAN;
  else if (strncmp(buffer, ">", length) == 0)
    return T_GREATERTHAN;
  else if (strncmp(buffer, "!", length) == 0)
    return T_NOT;

  else if (strncmp(buffer, "->", length) == 0)
    return T_RIGHTARR;
  else if (strncmp(buffer, "<-", length) == 0)
    return T_LEFTARR;

  else if (strncmp(buffer, "==", length) == 0)
    return T_EQUAL;
  else if (strncmp(buffer, "!=", length) == 0)
    return T_NOTEQUAL;

  else if (is_num(buffer, length))
    return T_NUM;
  else if (is_identifier(buffer, length))
    return T_IDENTIFIER;
  else
    return T_INVALID;
}

static inline void add_token(token_program_t *program, size_t length,
                             size_t columns, size_t lines, size_t type,
                             char *buffer) {
  token_t new_token = (token_t){
      .type = type,
      .length = length,
      .column = columns,
      .line = lines,
      .buffer = buffer,
  };

  program->tokens =
      realloc(program->tokens, sizeof(token_t) * (program->token_count + 1));
  program->tokens[program->token_count++] = new_token;
}

token_program_t lex(FILE *in) {
  token_program_t program = {
      .tokens = malloc(sizeof(token_t)), .token_count = 0, .index = 0};

  char ch;
  char *token_buffer = NULL;
  int token_length = 0;
  int lines = 1, columns = 1;

  while ((ch = fgetc(in)) != EOF) {
    if (ch == ';') {
      while (ch != '\n')
        ch = fgetc(in);

      /* add_token(&program, token_length, columns - token_length, lines, */
      /* T_NEWLINE, token_buffer); */
    }

    else if (ch == '"') {
      char previous_char = 0;
      ch = fgetc(in);

      while (ch != '"' && previous_char != '\\') {
        token_buffer = realloc(token_buffer, token_length + 1);
        token_buffer[token_length++] = ch;
        previous_char = ch;

        if (ch == '\n') {
          lines++;
          columns = 1;
        } else
          columns++;

        ch = fgetc(in);
      }

      add_token(&program, token_length, columns - token_length, lines, T_STRING,
                token_buffer);

      token_buffer = NULL;
      token_length = 0;

      continue;
    }

    int orig_ident = identify(token_buffer, token_length);

    char *duplicate = malloc(token_length + 1);
    memcpy(duplicate, token_buffer, token_length);
    duplicate[token_length] = ch;

    int dup_ident = identify(duplicate, token_length + 1);

    if (dup_ident == T_INVALID && orig_ident != T_INVALID) {
      add_token(&program, token_length, columns - token_length, lines,
                orig_ident, token_buffer);

      token_buffer = NULL;
      token_length = 0;

      if (!isspace(ch)) {
        token_buffer = realloc(token_buffer, 1);
        token_buffer[token_length++] = ch;
      }
    } else {
      if (!isspace(ch)) {
        token_buffer = realloc(token_buffer, token_length + 1);
        token_buffer[token_length++] = ch;
      }
    }

    free(duplicate);

    if (ch == '\n') {
      /* add_token(&program, token_length, columns - token_length, lines, */
      /* T_NEWLINE, token_buffer); */
      lines++;
      columns = 1;
    } else
      columns++;
  }

  return program;
}
