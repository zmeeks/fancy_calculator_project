#ifndef DIVISION_H
#define DIVISION_H
#include "expression.h"
#include <fstream>
#include <cstdlib>

using namespace std;

class super
{
public:
    super();
    
    super(expression numer);

    ~super();

    super(const super &other);

    super& operator=(const super &other);

    fraction evaluate(fraction &x);

    void set_super(expression n, expression d);

    void derivative(int x);

    void integral_def(int a, int b);

    void integral_indef(int x);

    string print_super();

    friend
    super operator*(const super &x, const super &y);

    friend
    super operator+(const super &x, const super &y);

    friend
    super operator-(const super &x, const super &y);

    friend
    super operator/(const super &x, const super &y);

    friend
    super operator%(const super &x, const super &y);

    friend
    ostream& operator<<(ostream &out, super &k);

private:
    expression numerator;
    expression denominator;
};

#endif // DIVISION_H
