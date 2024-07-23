#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
  LITERAL,
  OPERATOR,
  END_OF_TOKENS
} TokenType;

typedef struct {
  TokenType type;
  char *value;
} Token;

Token *generate_operator(char *current_char, int *current_char_index) {
  Token *token = malloc(sizeof(Token));
  token->value = malloc(sizeof(char) * 2);
  token->value[0] = current_char[*current_char_index];
  token->value[1] = '\0';
  token->type = OPERATOR;

  return token;
}

Token *generate_number(char *current_char, int *current_char_index) {
  Token *token = malloc(sizeof(Token));
  token->type = LITERAL;
  char *value = malloc(sizeof(char) * 8);
  int value_index = 0;

  while(isdigit(current_char[*current_char_index]) && current_char[*current_char_index] != '\0') {
    if(!isdigit(current_char[*current_char_index])) {
      break;
    }

    value[value_index] = current_char[*current_char_index];
    value_index++;
    *current_char_index += 1;
  }

  value[value_index] = '\0';
  token->value = value;

  return token;
}

Token *tokenizze(FILE *file){
  printf("tokenizze()\n");

  int file_length;
  char *current_char;

  //place file pointer to end of file to get file length
  //reset file tointer to the beggining
  //allocate space in memory for file length
  //read file in memory
  //close file
  fseek(file, 0, SEEK_END);
  file_length = ftell(file);
  fseek(file, 0, SEEK_SET);

  printf("File size: %d symbols\n", file_length);

  current_char = malloc(sizeof(char) * file_length);
  fread(current_char, 1, file_length, file);
  fclose(file);
  
  int current_char_index = 0;  
  current_char[file_length] = '\0';

  int max_tokens = 10;
  int tokens_size = 0;
  int tokens_index = 0;
  Token *tokens = malloc(sizeof(Token) * max_tokens);

  while(current_char[current_char_index] != '\0') {
    Token *token = malloc(sizeof(Token));
    tokens_size++;
    if(tokens_size > max_tokens){
      max_tokens *= 2;
      tokens = realloc(tokens, sizeof(Token) * max_tokens);
    }
    if(isdigit(current_char[current_char_index])) {
      token = generate_number(current_char, &current_char_index);

      tokens[tokens_index] = *token;
      tokens_index++;
    } else if(current_char[current_char_index] == '+'){
      token = generate_operator(current_char, &current_char_index);
      
      tokens[tokens_index] = *token;
      tokens_index++; 
    }

    free(token);
    current_char_index++;
  }

  printf("Tokens size: %d\n", tokens_index + 1);
  for(int i = 0; i < tokens_index; i++) {
    printf("Token: type = %d, value = %s\n", tokens[i].type, tokens[i].value);
  }
  
  tokens[tokens_index].value = '\0';
  tokens[tokens_index].type = END_OF_TOKENS;
  return tokens;

}
