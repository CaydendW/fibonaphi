#ifndef __TOKE_TYPE_H__
#define __TOKE_TYPE_H__

enum tokens {
  T_INVALID,
  T_NEWLINE,
  T_NUM,
  T_IDENTIFIER,
  T_STRING,

  T_RIGHTPAREN,
  T_LEFTPAREN,
  T_RIGHTBRACKET,
  T_LEFTBRACKET,
  T_RIGHTBRACE,
  T_LEFTBRACE,

  T_COMMA,
  T_COLON,

  T_MUL,
  T_DIV,
  T_ADD,
  T_MIN,

  T_LEFTARR,
  T_RIGHTARR,

  T_ASSIGN,

  T_NOT,

  T_EQUAL,
  T_NOTEQUAL,
  T_LESSTHAN,
  T_GREATERTHAN,
};

#endif