#ifndef TOKENIZZER_H_
#define TOKENIZZER_H_

typedef enum {
  LITERAL,
  OPERATOR,
  END_OF_TOKENS
} TokenType;

typedef struct {
  TokenType type;
  char *value;
} Token;

Token *tokenizze(FILE *file);
Token *generate_operator(char *current_char, int *current_char_index);
Token *generate_number(char *current_char, int *current_char_index);

#endif
