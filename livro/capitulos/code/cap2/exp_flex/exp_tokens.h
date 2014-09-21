//
// exp_tokens.h
// 
// Tipos e constantes para tokens da linguagem Exp
//
// Andrei de A. Formiga - 2014-09-01
//

#ifndef __EXP_TOKENS_H

#define __EXP_TOKENS_H

// constantes booleanas
#define TRUE            1
#define FALSE           0

// constantes para tipo de token
#define TOK_NUM         0 
#define TOK_OP          1
#define TOK_PONT        2
#define TOK_ERRO        3 

// constantes para valores de operadores
#define SOMA            0
#define SUB             1
#define MULT            2
#define DIV             3

// constantes para valores de pontuacao (parenteses)
#define PARESQ          0
#define PARDIR          1

// estrutura que representa um token
typedef struct 
{
  int tipo;
  int valor;
} Token; 

// funcao para criar um token
extern Token *token();

// funcao principal do analisador lexico
extern Token *yylex(); 


#endif                                   // __EXP_TOKENS_H
