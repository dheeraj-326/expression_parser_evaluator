////
////  ExprEval.cpp
////  FirstCppApp
////
////  Created by Dheeraj P B on 26/06/22.
////
//
//#include <iostream>
//#include <vector>
//#include <stack>
//#include <cstdio>
//#include <stdexcept>
//
//using namespace std;
//
//enum TOKEN {
//    ILLEGAL_TOKEN,
//    TOK_PLUS,
//    TOK_MUL,
//    TOK_DIV,
//    TOK_SUB,
//    TOK_OPAREN,
//    TOK_CPAREN,
//    TOK_DOUBLE,
//    TOK_NULL
//};
//
//static const char *tokenStr[] = {
//    "ILLEGAL_TOKEN",
//    "TOK_PLUS",
//    "TOK_MUL",
//    "TOK_DIV",
//    "TOK_SUB",
//    "TOK_OPAREN",
//    "TOK_CPAREN",
//    "TOK_DOUBLE",
//    "TOK_NULL"
//};
//
//enum OPERATION {
//    PLUS,
//    SUB,
//    MUL,
//    DIV
//};
//
//class ExecutionContext {
//public:
//    ExecutionContext() {
//        
//    }
//};
//
//class Expr {
//public:
//    virtual double evaluate(unique_ptr<ExecutionContext> context) = 0;
//    
//    virtual ~Expr() = default;
//};
//
//class NumericConstant : public Expr {
//private:
//    double _value;
//public:
//    NumericConstant(double value) {
//        _value = value;
//    }
//    
//    static unique_ptr<NumericConstant> getInstance(double value) {
//        return unique_ptr<NumericConstant>(new NumericConstant(value));
//    }
//    
//    double evaluate(unique_ptr<ExecutionContext> context) {
//        return _value;
//    }
//};
//
//class BinaryExpression : public Expr {
//private:
//    OPERATION _op;
//    unique_ptr<Expr> _expressionA;
//    unique_ptr<Expr> _expressionB;
//    
//public:
//    BinaryExpression(unique_ptr<Expr> expressionA, OPERATION op, unique_ptr<Expr> expressionB) {
//        _expressionA = move(expressionA);
//        _expressionB = move(expressionB);
//        _op = op;
//    }
//    
//    static unique_ptr<BinaryExpression> getInstance(unique_ptr<Expr> expressionA, OPERATION op, unique_ptr<Expr> expressionB) {
//        return unique_ptr<BinaryExpression>(new BinaryExpression(move(expressionA), op, move(expressionB)));
//    }
//    
//    double evaluate(unique_ptr<ExecutionContext> context) {
//        switch (_op) {
//            case OPERATION::PLUS:
//                return _expressionA->evaluate(move(context)) + _expressionB->evaluate(move(context));
//            case OPERATION::SUB:
//                return _expressionA->evaluate(move(context)) - _expressionB->evaluate(move(context));
//            case OPERATION::MUL:
//                return _expressionA->evaluate(move(context)) * _expressionB->evaluate(move(context));
//            case OPERATION::DIV:
//                double b = _expressionB->evaluate(move(context));
//                if (b == 0)
//                    throw std::invalid_argument("Division by ZERO error");
//                return _expressionA->evaluate(move(context)) / b;
//        }
//    }
//};
//
//class UnaryExpression : public Expr {
//private:
//    OPERATION _op;
//    unique_ptr<Expr> _expression;
//    
//public:
//    UnaryExpression(OPERATION op, unique_ptr<Expr> expression) {
//        _expression = move(expression);
//        _op = op;
//    }
//    
//    double evaluate(unique_ptr<ExecutionContext> context) {
//        return (BinaryExpression::getInstance(NumericConstant::getInstance(0), _op, move(_expression)))->evaluate(move(context));
//    }
//    
//    static unique_ptr<UnaryExpression> getInstance(OPERATION op, unique_ptr<Expr> expression) {
//        return unique_ptr<UnaryExpression>(new UnaryExpression(op, move(expression)));
//    }
//
//};
//
//class Lexer {
//protected:
//    int index;
//    string expression;
//    double number;
//    
//public:
//    Lexer(string expression) {
//        index = -1;
//        this->expression = expression;
//    }
//    
//    TOKEN nextToken() {
//        TOKEN token;
//        number = NULL;
//        index++;
//        if (index >= expression.length()) {
//            cout << "\nReturning token: " << tokenStr[TOKEN::TOK_NULL];
//            return TOKEN::TOK_NULL;
//        }
//        char ch = expression.at(index);
//        if (ch >= '0' && ch <= '9') {
//            number = 0;
//            while (ch >= '0' && ch <= '9') {
//                number *= 10;
//                number += ch - '0';
//                index++;
//                if (index >= expression.length())
//                    break;
//                ch = expression.at(index);
//            }
//            index--;
//            token = TOKEN::TOK_DOUBLE;
//        } else if (ch == '+') {
//            token = TOKEN::TOK_PLUS;
//        } else if (ch == '-') {
//            token = TOKEN::TOK_SUB;
//        } else if (ch == '*') {
//            token = TOKEN::TOK_MUL;
//        } else if (ch == '/') {
//            token = TOKEN::TOK_DIV;
//        } else if (ch == '(') {
//            token = TOKEN::TOK_OPAREN;
//        } else if (ch == ')') {
//            token = TOKEN::TOK_CPAREN;
//        } else {
//            token = TOKEN::ILLEGAL_TOKEN;
//        }
//        cout << "\nReturning token: " << tokenStr[token];
//        return token;
//    }
//    
//    double getNumber() {
//        return number;
//    }
//};
//
//class RDParser : public Lexer {
//protected:
//    TOKEN currentToken;
//    stack<double> numberStack;
//    
//public:
//    RDParser(string expression) : Lexer(expression) {
//        
//    }
//    
//    unique_ptr<Expr> buildExpressionTree() {
//        numberStack.empty();
//        currentToken = nextToken();
//        return expr();
//    }
//    
//    unique_ptr<Expr> expr() {
//        unique_ptr<Expr> expressionA = term();
//        if (currentToken == TOKEN::TOK_PLUS || currentToken == TOKEN::TOK_SUB) {
//            OPERATION op = currentToken == TOKEN::TOK_PLUS ? OPERATION::PLUS : OPERATION::SUB;
//            currentToken = nextToken();
//            unique_ptr<Expr> expressionB = term();
//            return BinaryExpression::getInstance(move(expressionA), op, move(expressionB));
//        }
//        return expressionA;
//    }
//    
//    unique_ptr<Expr> term() {
//        unique_ptr<Expr> expressionA = factor();
//        if (currentToken == TOKEN::TOK_MUL || currentToken == TOKEN::TOK_DIV) {
//            OPERATION op = currentToken == TOKEN::TOK_MUL ? OPERATION::MUL : OPERATION::DIV;
//            currentToken = nextToken();
//            unique_ptr<Expr> expressionB = term();
//            return BinaryExpression::getInstance(move(expressionA), op, move(expressionB));
//        }
//        return expressionA;
//    }
//    
//    unique_ptr<Expr> factor() {
//        if (currentToken == TOKEN::TOK_DOUBLE) {
//            unique_ptr<NumericConstant> constant = NumericConstant::getInstance(getNumber());
//            currentToken = nextToken();
//            return constant;
//        } else if (currentToken == TOKEN::TOK_OPAREN) {
//            currentToken = nextToken();
//            unique_ptr<Expr> expression = expr();
//            if (currentToken != TOKEN::TOK_CPAREN) {
//                throw std::invalid_argument("No Closing paranthesis");
//            }
//            currentToken = nextToken();
//            return expression;
//        } else if (currentToken == TOKEN::TOK_PLUS || currentToken == TOKEN::TOK_SUB) {
//            OPERATION op = currentToken == TOKEN::TOK_PLUS ? OPERATION::PLUS : OPERATION::SUB;
//            currentToken = nextToken();
//            return UnaryExpression::getInstance(op, factor());
//        } else {
//            throw std::invalid_argument("Encountered illegal TOKEN");
//        }
//    }
//};
//
//int main(int argc, char** argv) {
//    stack<int> testStack;
//    testStack.push(12);
//    testStack.push(13);
//    testStack.push(14);
//    RDParser parser("2*(2+2)---(2+2)"); // 10
//    unique_ptr<Expr> treeRoot = parser.buildExpressionTree();
//    cout << "\nResult: " << treeRoot->evaluate(NULL) << "\n";
//}
//
//
//
//
//
//
