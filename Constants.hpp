//
//  Constants.hpp
//  FirstCppApp
//
//  Created by Dheeraj P B on 16/07/22.
//

#ifndef Constants_hpp
#define Constants_hpp

enum TOKEN {
    ILLEGAL_TOKEN,
    TOK_PLUS,
    TOK_MUL,
    TOK_DIV,
    TOK_SUB,
    TOK_OPAREN,
    TOK_CPAREN,
    TOK_DOUBLE,
    TOK_NULL,
    TOK_PRINT, // Print Statement
    TOK_PRINTLN, // PrintLine
    TOK_UNQUOTED_STRING,
    TOK_SEMI // ;
};

static const char *tokenStr[] = {
    "ILLEGAL_TOKEN",
    "TOK_PLUS",
    "TOK_MUL",
    "TOK_DIV",
    "TOK_SUB",
    "TOK_OPAREN",
    "TOK_CPAREN",
    "TOK_DOUBLE",
    "TOK_NULL",
    "TOK_PRINT", // Print Statement
    "TOK_PRINTLN", // PrintLine
    "TOK_UNQUOTED_STRING",
    "TOK_SEMI" // ;
};

enum OPERATION {
    PLUS,
    SUB,
    MUL,
    DIV
};

#endif /* Constants_hpp */
