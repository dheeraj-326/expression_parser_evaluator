////
////  ExprEval_1.cpp
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
//    double evaluateExpression() {
//        numberStack.empty();
//        double result = (double)NULL;
//        currentToken = nextToken();
//        expr();
//        result = numberStack.top();
//        numberStack.pop();
//        return result;
//    }
//
//    void expr() {
//        TOKEN lToken;
//        term();
//        if (currentToken == TOKEN::TOK_PLUS || currentToken == TOKEN::TOK_SUB) {
//            lToken = currentToken;
//            currentToken = nextToken();
//            term();
//            double y = numberStack.top();
//            numberStack.pop();
//            double x = numberStack.top();
//            numberStack.pop();
//            y = lToken == TOKEN::TOK_PLUS ? x + y : x - y;
//            numberStack.push(y);
//        }
//    }
//
//    void term() {
//        TOKEN lToken;
//        factor();
//        if (currentToken == TOKEN::TOK_MUL || currentToken == TOKEN::TOK_DIV) {
//            lToken = currentToken;
//            currentToken = nextToken();
//            term();
//            double y = numberStack.top();
//            numberStack.pop();
//            double x = numberStack.top();
//            numberStack.pop();
//            if (lToken == TOKEN::TOK_DIV) {
//                if (y == 0)
//                    throw std::invalid_argument("Division by ZERO error");
//                y = x / y;
//            } else {
//                y = x * y;
//            }
//            numberStack.push(y);
//        }
//    }
//
//    void factor() {
//        TOKEN lToken;
//        if (currentToken == TOKEN::TOK_DOUBLE) {
//            numberStack.push(getNumber());
//            currentToken = nextToken();
//        } else if (currentToken == TOKEN::TOK_OPAREN) {
//            lToken = currentToken;
//            currentToken = nextToken();
//            expr();
//            if (currentToken != TOKEN::TOK_CPAREN) {
//                throw std::invalid_argument("No Closing paranthesis");
//            }
//            currentToken = nextToken();
//        } else if (currentToken == TOKEN::TOK_PLUS || currentToken == TOKEN::TOK_SUB) {
//            lToken = currentToken;
//            currentToken = nextToken();
//            factor();
//            double intermediate = numberStack.top();
//            numberStack.pop();
//            intermediate = lToken == TOKEN::TOK_SUB ? intermediate * -1 : intermediate;
//            numberStack.push(intermediate);
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
//    RDParser parser("2*-(3+2)/-10"); // 10
//    double result = parser.evaluateExpression();
//    cout << "\nResult: " << result << "\n";
//}
//
//
//
