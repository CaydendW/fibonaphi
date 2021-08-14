#ifndef __AST_H__
#define __AST_H__

#include <stddef.h>

enum {
  A_FUNC,
  A_VAR,
  A_MATRIX,
  A_EXPR,
  A_STATEMENT,
};

enum {
  A_T_DOUBLE,
  A_T_UNUM,
  A_T_INUM,
  A_T_STRING,
};

struct node;

typedef struct function {
  char *name;
  size_t return_type;
  struct node *args;
  struct node *value;
} function_t;

typedef struct matrix {
  char *name;
  size_t type;
  size_t width;
  size_t height;
  struct node *values;
} matrix_t;

typedef struct var {
  char *name;
  size_t type;
  union {
    double num_val;
    char *string_val;
  };
} var_t;

typedef struct node {
  size_t type;

  union {
    function_t *func;
    matrix_t *matrix;
    var_t *variable;
  };
} node_t;

#endif
