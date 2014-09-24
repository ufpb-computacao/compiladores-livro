
//
// minic_tokens.h
//
// Tipos e constantes para tokens da linguagem Mini C
//
// Andrei de A. Formiga, 2014-09-15
//

#ifndef __MINIC_TOKENS_H

#define __MINIC_TOKENS_H

// Tipos de token
#define TOK_PCHAVE                              1
#define TOK_ID                                  4
#define TOK_NUM                                 5
#define TOK_PONT                                6
#define TOK_OP                                  7
#define TOK_STRING                              8
#define TOK_PROLOGO                             9
#define TOK_ERRO                                100

// valores para palavra-chave 
#define PC_IF                                   0
#define PC_ELSE                                 1
#define PC_WHILE                                2
#define PC_RETURN                               3
#define PC_PRINTF                               4

// valores para pontuacao
#define PARESQ                                  1
#define PARDIR                                  2
#define CHVESQ                                  3
#define CHVDIR                                  4
#define VIRG                                    5
#define PNTVIRG                                 6

// valores para operadores
#define SOMA                                    1
#define SUB                                     2
#define MULT                                    3
#define DIV                                     4
#define MENOR                                   5
#define IGUAL                                   6
#define AND                                     7
#define NOT                                     8
#define ATRIB                                   9

// tipos
typedef struct 
{
  int tipo;
  int valor;
} Token;

#endif                                           // __MINIC_TOKENS_H

