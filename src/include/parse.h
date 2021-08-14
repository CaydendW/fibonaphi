#ifndef __PARSE_H__
#define __PARSE_H__

#include <ast.h>
#include <lex.h>
#include <stddef.h>

typedef struct parsed {
  size_t node_count;
  node_t *nodes;
} parsed_t;

parsed_t parse(token_program_t program);

#endif
