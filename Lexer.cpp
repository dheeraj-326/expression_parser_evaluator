//
//  Lexer.cpp
//  FirstCppApp
//
//  Created by Dheeraj P B on 16/07/22.
//

#include <iostream>
#include <string>
#include "Lexer.hpp"
#include "Constants.hpp"

using namespace std;

Lexer::Lexer(string expression) {
   index = -1;
   this->expression = expression;
}

TOKEN Lexer::nextToken() {
    TOKEN token;
    number = NULL;
    index++;
    if (index >= expression.length()) {
        cout << "\nReturning token: " << tokenStr[TOKEN::TOK_NULL];
        return TOKEN::TOK_NULL;
    }
    char ch = expression.at(index);
    if (ch >= '0' && ch <= '9') {
        number = 0;
        while (ch >= '0' && ch <= '9') {
            number *= 10;
            number += ch - '0';
            index++;
            if (index >= expression.length())
                break;
            ch = expression.at(index);
        }
        index--;
        token = TOKEN::TOK_DOUBLE;
    } else if (ch == '+') {
        token = TOKEN::TOK_PLUS;
    } else if (ch == '-') {
        token = TOKEN::TOK_SUB;
    } else if (ch == '*') {
        token = TOKEN::TOK_MUL;
    } else if (ch == '/') {
        token = TOKEN::TOK_DIV;
    } else if (ch == '(') {
        token = TOKEN::TOK_OPAREN;
    } else if (ch == ')') {
        token = TOKEN::TOK_CPAREN;
    } else {
        token = TOKEN::ILLEGAL_TOKEN;
    }
    cout << "\nReturning token: " << tokenStr[token];
    return token;
}

double Lexer::getNumber() {
    return number;
}
