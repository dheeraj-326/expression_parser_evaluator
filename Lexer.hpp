//
//  Lexer.hpp
//  FirstCppApp
//
//  Created by Dheeraj P B on 16/07/22.
//

#ifndef Lexer_hpp
#define Lexer_hpp

#include <iostream>
#include <string>
#include "Lexer.hpp"
#include "Constants.hpp"

using namespace std;

class Lexer {
protected:
    int index;
    string expression;
    double number;
    
public:
    Lexer(string expression);
    
    TOKEN nextToken();
    
    double getNumber();
};

#endif /* Lexer_hpp */
