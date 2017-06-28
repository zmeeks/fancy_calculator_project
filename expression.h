#ifndef expression_H
#define expression_H


#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "term.h"

using namespace std;

class expression
{
    public:
        expression();
        ~expression();
        expression(const expression &other);
        expression& operator=(const expression &other);
        expression& operator<<(string &input);
        expression& operator<<(term &input);
        expression& operator>>(string &output);
        fraction evaluate_ND(fraction &x);
        expression derivative();
        expression integral();
        expression integration_by_parts(term t);
        term* return_my_exp() const;

        friend
        expression operator*(const expression &x, const expression &y);

        friend
        expression operator+(const expression &x, const expression &y);


        friend
        expression operator-(const expression &x, const expression &y);


        friend
        ostream& operator<<(ostream &out, expression &p);

        friend
        istream& operator>>(istream &in, expression &p);

        string print_expr() const;

    private:
        term* myExpression;
        void copy(const expression &other);
        void zero();
};

#endif // expression_H
