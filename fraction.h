#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <cstring>
#include <iomanip>

using namespace std;

enum FRACTION_ERRORS {DIV_BY_ZERO, INVALID_FRACTION};

class fraction
{
    public:
        fraction();
        fraction(long long int n, long long int d);                                 
        fraction(double v);
        fraction(long long int n);
        fraction(const fraction &other);
        fraction& operator=(const fraction &other);
        fraction& operator+=( fraction &other);
        fraction& operator-=( fraction &other);
        fraction& operator*=( fraction &other);
        fraction& operator/=( fraction &other);
        fraction operator^=( fraction &other);
        fraction& operator=(long long int other);
        fraction& operator+=(long long int other);
        fraction& operator-=(long long int other);
        fraction& operator*=(long long int other);
        fraction& operator/=(long long int other);
        fraction& operator^=(long long int other);
        fraction& operator=(double other);
        fraction& operator+=(double other);
        fraction& operator-=(double other);
        fraction& operator*=(double other);
        fraction& operator/=(double other);
        fraction& operator^=(double other);
        void make_numer_neg();
        void set_term(long long int n, long long int d);
        void display();
        long long int& num();
        long long int& denom();
        void newValue(long long int n, long long int d);

        friend
        ostream& operator<<(ostream &out, fraction &x);

        friend
        istream& operator>>(istream &in, fraction &x);

        friend
        fraction& operator+(fraction &x, fraction &y);

        friend
        fraction& operator-(fraction &x, fraction &y);

        friend
        fraction& operator*(fraction &x, fraction &y);

        friend
        fraction& operator/(fraction &x, fraction &y);

        friend
        fraction operator^(fraction &x, fraction &y);

  //For Integers
        friend
        fraction& operator+(fraction &x, long long int y);

        friend
        fraction& operator-(fraction &x, long long int y);

        friend
        fraction& operator*(fraction &x, long long int y);

        friend
        fraction& operator/(fraction &x, long long int y);

        friend
        fraction& operator^(fraction &x, long long int y);

        friend
        fraction& operator+(long long int x, fraction &y);

        friend
        fraction& operator-(long long int x, fraction &y);

        friend
        fraction& operator*(long long int x, fraction &y);

        friend
        fraction& operator/(long long int x, fraction &y);

        friend
        fraction& operator^(long long int x, fraction &y);

 //For doubles and float
        friend
        fraction& operator+(fraction &x, double y);

        friend
        fraction& operator-(fraction &x, double y);

        friend
        fraction& operator*(fraction &x, double y);

        friend
        fraction& operator/(fraction &x, double y);

        friend
        fraction& operator^(fraction &x, double y);

        friend
        fraction& operator+(double x, fraction &y);

        friend
        fraction& operator-(double x, fraction &y);

        friend
        fraction& operator*(double x, fraction &y);

        friend
        fraction& operator/(double x, fraction &y);

        friend
        fraction& operator^(double x, fraction &y);


//Comparison operators -- fraction to fraction
        friend
        bool operator==(const fraction &x,const fraction &y);

        friend
        bool operator<=(const fraction &x,const  fraction &y);

        friend
        bool operator<(const fraction &x,const  fraction &y);

        friend
        bool operator>(const fraction &x, const fraction &y);

        friend
        bool operator>=(const fraction &x,const  fraction &y);

        friend
        bool operator!=(const fraction &x, const fraction &y);

//Comparison operators -- fraction to integer and vise versa
        friend
        bool operator==(const fraction &x, long long int y);

        friend
        bool operator<=(const fraction &x,long long int y);

        friend
        bool operator<(const fraction &x,long long int y);

        friend
        bool operator>(const fraction &x, long long int y);

        friend
        bool operator>=(const fraction &x,long long int y);

        friend
        bool operator!=(const fraction &x,long long int y);

        friend
        bool operator==(long long int x,const fraction &y);

        friend
        bool operator<=(long long int x,const  fraction &y);

        friend
        bool operator<(long long int x,const  fraction &y);

        friend
        bool operator>(long long int x, const fraction &y);

        friend
        bool operator>=(long long int x,const  fraction &y);

        friend
        bool operator!=(long long int x, const fraction &y);


//Comparison operators -- fraction to double and vise versa
        friend
        bool operator==(const fraction &x, double y);

        friend
        bool operator<=(const fraction &x,double y);

        friend
        bool operator<(const fraction &x,double y);

        friend
        bool operator>(const fraction &x, double y);

        friend
        bool operator>=(const fraction &x,double y);

        friend
        bool operator!=(const fraction &x,double y);

        friend
        bool operator==(double x,const fraction &y);

        friend
        bool operator<=(double x,const  fraction &y);

        friend
        bool operator<(double x,const  fraction &y);

        friend
        bool operator>(double x, const fraction &y);

        friend
        bool operator>=(double x,const  fraction &y);

        friend
        bool operator!=(double x, const fraction &y);

        friend
        fraction& aabs(fraction &x);

    private:
        long long int numerator, denominator;
        void reduce();
        long long int gcd(long long int p, long long int q);
        void makeNew(long long int n, long long int d);
        void doubleInitialize(double d);
        long long int atoint(char car);
};

#endif // FRACTION_H
