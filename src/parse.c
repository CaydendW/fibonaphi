#include <ast.h>
#include <lex.h>
#include <parse.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <token_type.h>

char *token_strings[] = {
    "T_INVALID",     "T_NEWLINE",    "T_NUM",       "T_IDENTIFIER",
    "T_STRING",      "T_RIGHTPAREN", "T_LEFTPAREN", "T_RIGHTBRACKET",
    "T_LEFTBRACKET", "T_RIGHTBRACE", "T_LEFTBRACE", "T_COMMA",
    "T_COLON",       "T_MUL",        "T_DIV",       "T_ADD",
    "T_MIN",         "T_LEFTARR",    "T_RIGHTARR",  "T_ASSIGN",
    "T_NOT",         "T_EQUAL",      "T_NOTEQUAL",  "T_LESSTHAN",
    "T_GREATERTHAN",
};

static inline void parse_die_expect(token_program_t *program,
                                    size_t expected_type) {
  fprintf(stderr,
          "fibonaphi: error: Expected type %s, received %s on line %lu, "
          "column %lu\n",
          token_strings[expected_type],
          token_strings[program->tokens[program->index].type],
          program->tokens[program->index].line,
          program->tokens[program->index].column);

  exit(1);
}

static inline int parse_eat(token_program_t *program, size_t expected_type) {
  if (program->index >= program->token_count)
    return 0;

  if (program->tokens[program->index].type == expected_type) {
    program->index++;
    return 1;
  }

  return 0;
}

static inline int parse_token_in_line(token_program_t *program, size_t type) {
  size_t curr_line = program->tokens[program->index].line;

  size_t base_token_index;
  for (base_token_index = 0; base_token_index + program->index < curr_line + 1;
       base_token_index++)
    ;

  size_t curr_line_tokens;
  for (curr_line_tokens = program->index - base_token_index;
       curr_line_tokens < program->index - base_token_index; curr_line_tokens++)
    ;

  for (size_t i = program->index - (curr_line_tokens - base_token_index);
       program->tokens[i].line < curr_line + 1; i++)
    if (program->tokens[i].type == type)
      return 1;

  return 0;
}

static inline int parse_detect_type(token_program_t *program) {
  if (parse_token_in_line(program, T_EQUAL)) {
    if (parse_token_in_line(program, T_LEFTPAREN) &&
        parse_token_in_line(program, T_RIGHTPAREN))
      return A_ASSIGN_FUNC;
    else if (parse_token_in_line(program, T_LEFTBRACKET) &&
             parse_token_in_line(program, T_RIGHTPAREN))
      return A_ASSIGN_MATRIX;
    else
      return A_ASSIGN_VAR;
  } else {
    if (parse_token_in_line(program, T_LEFTPAREN) &&
        parse_token_in_line(program, T_RIGHTPAREN))
      return A_CALL_FUNC;
    else if (parse_token_in_line(program, T_LEFTBRACKET) &&
             parse_token_in_line(program, T_RIGHTPAREN))
      return A_CALL_MATRIX;
    else
      return A_CALL_VAR;
  }

  return T_INVALID;
}

void parse_assign_function(token_program_t *program, parsed_t parsed) {

}

parsed_t parse(token_program_t program) {
  parsed_t parsed =
      (parsed_t){.node_count = 0, .nodes = malloc(sizeof(node_t))};

  while (program.index < program.token_count) {
    switch (parse_detect_type(&program)) {
      case A_ASSIGN_FUNC:
        parse_assign_function(&program, parsed);
        break;
    }
  }

  return parsed;
}
