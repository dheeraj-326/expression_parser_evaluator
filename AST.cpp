//
//  AST.cpp
//  FirstCppApp
//
//  Created by Dheeraj P B on 16/07/22.
//

#include <string>
#include "AST.hpp"
#include "Constants.hpp"
#include "ExecutionContext.hpp"

// NumericConstant

NumericConstant::NumericConstant(double value) {
    _value = value;
}

double NumericConstant::evaluate(unique_ptr<ExecutionContext> context) {
    return _value;
}

// BinaryExpression

BinaryExpression::BinaryExpression(unique_ptr<Expr> expressionA, OPERATION op, unique_ptr<Expr> expressionB) {
    _expressionA = move(expressionA);
    _expressionB = move(expressionB);
    _op = op;
}

double BinaryExpression::evaluate(unique_ptr<ExecutionContext> context) {
    switch (_op) {
        case OPERATION::PLUS:
            return _expressionA->evaluate(move(context)) + _expressionB->evaluate(move(context));
        case OPERATION::SUB:
            return _expressionA->evaluate(move(context)) - _expressionB->evaluate(move(context));
        case OPERATION::MUL:
            return _expressionA->evaluate(move(context)) * _expressionB->evaluate(move(context));
        case OPERATION::DIV:
            double b = _expressionB->evaluate(move(context));
            if (b == 0)
                throw std::invalid_argument("Division by ZERO error");
            return _expressionA->evaluate(move(context)) / b;
    }
}

// UnaryExpression

UnaryExpression::UnaryExpression(OPERATION op, unique_ptr<Expr> expression) {
    _expression = move(expression);
    _op = op;
}

double UnaryExpression::evaluate(unique_ptr<ExecutionContext> context) {
    return (BinaryExpression::getInstance(NumericConstant::getInstance(0), _op, move(_expression)))->evaluate(move(context));
}



