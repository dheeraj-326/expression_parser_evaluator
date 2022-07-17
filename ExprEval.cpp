//
//  ExprEval.cpp
//  FirstCppApp
//
//  Created by Dheeraj P B on 26/06/22.
//

#include <iostream>
#include <vector>
#include <stack>
#include <cstdio>
#include <stdexcept>
#include "Lexer.hpp"
#include "Constants.hpp"
#include "AST.hpp"
#include "RDParser.hpp"

using namespace std;


int main(int argc, char** argv) {
    stack<int> testStack;
    testStack.push(12);
    testStack.push(13);
    testStack.push(14);
    RDParser parser("2*(2+2)---(2+2)"); // 10
    unique_ptr<Expr> treeRoot = parser.buildExpressionTree();
    cout << "\nResult: " << treeRoot->evaluate(NULL) << "\n";
}






