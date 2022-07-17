//
//  AST.hpp
//  FirstCppApp
//
//  Created by Dheeraj P B on 16/07/22.
//

#ifndef AST_hpp
#define AST_hpp

#include <string>
#include "Constants.hpp"
#include "ExecutionContext.hpp"

using namespace std;

class Expr {
public:
    virtual double evaluate(unique_ptr<ExecutionContext> context) = 0;
    
    virtual ~Expr() = default;
};

class NumericConstant : public Expr {
private:
    double _value;
public:
    NumericConstant(double value);
    
    static unique_ptr<NumericConstant> getInstance(double value) {
        return unique_ptr<NumericConstant>(new NumericConstant(value));
    }
    
    double evaluate(unique_ptr<ExecutionContext> context);
};

class BinaryExpression : public Expr {
private:
    OPERATION _op;
    unique_ptr<Expr> _expressionA;
    unique_ptr<Expr> _expressionB;
    
public:
    BinaryExpression(unique_ptr<Expr> expressionA, OPERATION op, unique_ptr<Expr> expressionB);
    
    static unique_ptr<BinaryExpression> getInstance(unique_ptr<Expr> expressionA, OPERATION op, unique_ptr<Expr> expressionB) {
        return unique_ptr<BinaryExpression>(new BinaryExpression(move(expressionA), op, move(expressionB)));
    }
    
    double evaluate(unique_ptr<ExecutionContext> context);
};

class UnaryExpression : public Expr {
private:
    OPERATION _op;
    unique_ptr<Expr> _expression;
    
public:
    UnaryExpression(OPERATION op, unique_ptr<Expr> expression);
    
    double evaluate(unique_ptr<ExecutionContext> context);
    
    static unique_ptr<UnaryExpression> getInstance(OPERATION op, unique_ptr<Expr> expression) {
        return unique_ptr<UnaryExpression>(new UnaryExpression(op, move(expression)));
    }

};

#endif /* AST_hpp */

