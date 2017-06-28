#ifndef TERM_H
#define TERM_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "fraction.h"

using namespace std;

enum ERROR {INVALID, CANNOT_HAPPEN};

class term
{
    public:
        term();
        term(const fraction &c, const fraction &p_x, const fraction &ln_p=(long long int)0);
        ~term();
        term(const term& other);
        term& operator=(const term&other);
        fraction evaluate(fraction &x);
        term derivative();
        term integral();
        void setTerm(fraction &c, fraction &p_x, fraction &p_ln);
        fraction& getCoeff();
        fraction& x_getPower();
        fraction& ln_getPower();
        term*& link();
        void setLink(term *nex_lnk);

        fraction ln_f(fraction x);

        string print_da_term();

        friend
        term operator+(term& x, term& y);

        friend
        term operator-(term& x, term& y);

        friend
        term operator-(term& x);

        friend
        term operator*(term& x, term& y);

        friend
        ostream& operator<<(ostream& out, term &other);

        friend
        istream& operator>>(istream& in, term &other);

    private:
        fraction coeff, power_x, ln_power;
        term *next;
        void copy(const term& other);
        bool valid();
        double ln_func(double numbero);
        double ln_funk(double numbero);
};


#endif // TERM_H
