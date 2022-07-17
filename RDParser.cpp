//
//  RDParser.cpp
//  FirstCppApp
//
//  Created by Dheeraj P B on 16/07/22.
//

#include "RDParser.hpp"
#include <stack>
#include <string>
#include "Lexer.hpp"
#include "Constants.hpp"

RDParser::RDParser(string expression) : Lexer(expression) { }

unique_ptr<Expr> RDParser::buildExpressionTree() {
    numberStack.empty();
    currentToken = nextToken();
    return expr();
}

unique_ptr<Expr> RDParser::expr() {
    unique_ptr<Expr> expressionA = term();
    if (currentToken == TOKEN::TOK_PLUS || currentToken == TOKEN::TOK_SUB) {
        OPERATION op = currentToken == TOKEN::TOK_PLUS ? OPERATION::PLUS : OPERATION::SUB;
        currentToken = nextToken();
        unique_ptr<Expr> expressionB = term();
        return BinaryExpression::getInstance(move(expressionA), op, move(expressionB));
    }
    return expressionA;
}

unique_ptr<Expr> RDParser::term() {
    unique_ptr<Expr> expressionA = factor();
    if (currentToken == TOKEN::TOK_MUL || currentToken == TOKEN::TOK_DIV) {
        OPERATION op = currentToken == TOKEN::TOK_MUL ? OPERATION::MUL : OPERATION::DIV;
        currentToken = nextToken();
        unique_ptr<Expr> expressionB = term();
        return BinaryExpression::getInstance(move(expressionA), op, move(expressionB));
    }
    return expressionA;
}

unique_ptr<Expr> RDParser::factor() {
    if (currentToken == TOKEN::TOK_DOUBLE) {
        unique_ptr<NumericConstant> constant = NumericConstant::getInstance(getNumber());
        currentToken = nextToken();
        return constant;
    } else if (currentToken == TOKEN::TOK_OPAREN) {
        currentToken = nextToken();
        unique_ptr<Expr> expression = expr();
        if (currentToken != TOKEN::TOK_CPAREN) {
            throw std::invalid_argument("No Closing paranthesis");
        }
        currentToken = nextToken();
        return expression;
    } else if (currentToken == TOKEN::TOK_PLUS || currentToken == TOKEN::TOK_SUB) {
        OPERATION op = currentToken == TOKEN::TOK_PLUS ? OPERATION::PLUS : OPERATION::SUB;
        currentToken = nextToken();
        return UnaryExpression::getInstance(op, factor());
    } else {
        throw std::invalid_argument("Encountered illegal TOKEN");
    }
}

