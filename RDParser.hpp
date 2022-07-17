//
//  RDParser.hpp
//  FirstCppApp
//
//  Created by Dheeraj P B on 16/07/22.
//

#ifndef RDParser_hpp
#define RDParser_hpp

#include <stack>
#include <string>
#include "Lexer.hpp"
#include "Constants.hpp"
#include "AST.hpp"

class RDParser : public Lexer {
protected:
    TOKEN currentToken;
    stack<double> numberStack;
    
public:
    RDParser(string expression);
    
    unique_ptr<Expr> buildExpressionTree();
    
    unique_ptr<Expr> expr();
    
    unique_ptr<Expr> term();
    
    unique_ptr<Expr> factor();
};

#endif /* RDParser_hpp */
