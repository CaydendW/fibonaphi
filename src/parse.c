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

  for (size_t i = program->tokens[program->index].line;
       i < program->tokens[program->index].line + 1; i++)
    if (program->tokens[i].line == program->tokens[program->index].line)
      fprintf(stderr, "%.*s", (int)program->tokens[i].length,
              program->tokens[i].buffer);

  puts("\n");

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

static inline int parse_detect_type(token_program_t *program) {
  size_t curr_line_tokens;
  for (curr_line_tokens = program->tokens[program->index].line;
       curr_line_tokens < program->tokens[program->index].line + 1;
       curr_line_tokens++)
    ;


}

parsed_t parse(token_program_t program) {
  parsed_t parsed =
      (parsed_t){.node_count = 0, .nodes = malloc(sizeof(node_t))};

  while (program.index < program.token_count) {
    if (parse_eat(&program, T_IDENTIFIER)) {

    } else
      parse_die_expect(&program, T_IDENTIFIER);
  }

  return parsed;
}
