#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <lex.h>
#include <main.h>
#include <parse.h>

void usage() {
  printf("Usage: fibonaphi [OPTIONS] [POSITIONAL ARGUEMENTS]\n");
  printf("Positional options:\n");
  printf(" Name of file to compile\n");
  printf("Required options:\n");
  printf("Optional arguements:\n");
  printf(" -o                   Specify name of output file");
}

int main(int argc, char *argv[]) {
  output = NULL;
  input = NULL;

  char opt;
  char *input_name;

  if (argc == 1) {
    usage();
    return 1;
  }

  while ((opt = getopt(argc, argv, "o:h")) != -1) {
    switch (opt) {
    case 'o':
      output = fopen(optarg, "w");
      if (!output) {
        printf("fibonaphi: error: File \"%s\" cannot be opened! Make sure you "
               "own the "
               "file/the place where the file will be created!\n",
               optarg);
        return 1;
      }
      break;
    case 'h':
      usage();
      return 0;
      break;
    }
  }

  for (int i = optind; i < argc; i++) {
    switch (i - optind) {
    case 0:
      input = fopen(argv[i], "r");
      if (!input) {
        printf(
            "fibonaphi: error: file \"%s\" could not be opened! Make sure that "
            "this file exists and you have the rights to it!",
            argv[i]);
        return 1;
      }
      input_name = malloc(strlen(argv[i]) + 1);
      input_name = argv[i];
      break;
    }
  }

  if (!input) {
    printf(
        "fibonaphi: error: input file needs to be specified! can be done via "
        "the positional arguements!\n");
    return 1;
  } else if (!output) {
    char *name = malloc(strlen(input_name) + strlen(".S") + 1);
    strcpy(name, input_name);
    strcat(name, ".S");
    output = fopen(name, "w");
    if (!output) {
      printf("fibonaphi: error: File \"%s\" cannot be opened! Make sure you "
             "own the "
             "file/the place where the file will be created!\n",
             optarg);
      return 1;
    }
  }

  token_program_t tprogram = lex(input);

  for (size_t i = 0; i < tprogram.token_count; i++) {
    printf("Token: type=%lu, length=%lu, line=%lu, column=%lu\n",
           tprogram.tokens[i].type, tprogram.tokens[i].length,
           tprogram.tokens[i].line, tprogram.tokens[i].column);
  }

  parse(tprogram);

  fclose(input);
  fclose(output);

  return 0;
}
