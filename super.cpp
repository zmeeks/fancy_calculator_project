#include "super.h"
#include "term.h"


using namespace std;

super::super(){
    fraction zero((long long int)0, (long long int)1), one((long long int)1, (long long int)1);
    term t, b;
    expression tt, bb;
    t.setTerm(zero, zero, zero);            
    b.setTerm(one, zero, zero);             
    tt<<t;
    bb<<b;
    numerator=tt;
    denominator=bb;
}

super::super(expression numer){
    fraction zero(0, 1), one(1, 1);
    term b;
    expression bb;
    b.setTerm(one, zero, zero);               
    bb<<b;
    numerator=numer;
    denominator=bb;
}

super::~super(){
    numerator.~expression();
    denominator.~expression();
}

super::super(const super &other){
    numerator=other.numerator;
    denominator=other.denominator;
}

super& super::operator=(const super &other){
    if(this != &other)                 
    {
        numerator=other.numerator;
        denominator=other.denominator;
    }
    return *this;
}

super operator*(const super &x, const super &y){
    expression top, bot;
    super tempo;
    top=(x.numerator)*(y.numerator);
    bot=(x.denominator)*(y.denominator);
    tempo.numerator=top;
    tempo.denominator=bot;
    return tempo;
}

super operator+(const super &x, const super &y){
    expression top_x, top_y, topper, bot;
    super tempo;
    expression a, b, c, d;
    a=x.numerator;
    b=x.denominator;
    c=y.numerator;
    d=y.denominator;
    top_x=(x.numerator)*(y.denominator);                    
    top_y=(y.numerator)*(x.denominator);
    topper=top_x+top_y;
    bot=(x.denominator)*(y.denominator);
    tempo.numerator=topper;
    tempo.denominator=bot;
    return tempo;
}

super operator-(const super &x, const super &y){
    expression top_x, top_y, topper, bot;
    super tempo;
    top_x=(x.numerator)*(y.denominator);
    top_y=(y.numerator)*(x.denominator);
    topper= top_x-top_y;
    bot=(x.denominator)*(y.denominator);
    tempo.numerator=topper;
    tempo.denominator=bot;
    return tempo;
}

super operator/(const super &x, const super &y){
    expression top, bot;
    super tempo;
    top=(x.numerator)*(y.denominator);
    bot=(x.denominator)*(y.numerator);
    tempo.numerator=top;
    tempo.denominator=bot;
    return tempo;
}


super operator%(const super &x, const super &y){
    expression x_n, x_d, y_n, y_d, zz_n, zz_d;
    super testie;
    fraction one(1, 1), zero(0, 1);
    term b;
    b.setTerm(zero, zero, zero);                
    zz_n<<b;
    x_n=x.numerator;
    x_d=x.denominator;
    y_n=y.numerator;
    y_d=y.denominator;
    expression temp, the_cof, blanker;
    blanker<<b;
    term co_effish;
    super owally, temper;
    bool go_neg=false;
    bool was_neg=false;
    fraction c, p, w((long long int)0);
    int p_numer;
    for(term* xxxn=x.numerator.return_my_exp(); xxxn!=NULL; xxxn=xxxn->link())
    {
        the_cof=blanker;
        temp=y_n;
        go_neg=false;
        p=xxxn->x_getPower();
        if(p.denom()!=(long long int)1)
        {
            int a_jelly_donut=1;
            cout<<"illegal arithmetic per this test! f=g(h) may only handle polynomial values for g"<<endl;
            throw a_jelly_donut; 
        }
        p_numer=p.num();
        c=xxxn->getCoeff();
        co_effish.setTerm(c, w, w);  
        the_cof<<co_effish;    
        if(p_numer<0)
            go_neg=true;
        
        while(p_numer<-1)
        {
            temp=temp*y_n;
            p_numer++;
        }
        if(go_neg)
        {
            fraction one(1, 1), zero(0, 1);
            term b;
            expression bb;
            b.setTerm(one, zero, zero); 
            bb<<b;
            temper.numerator=the_cof;
            temper.denominator=temp;
        }
        while(p_numer>1)
        {
            temp=temp*y_n;
            p_numer--;
        }
        if(p_numer==(-1))
        {
            testie=testie+temper;
            was_neg=true;
        }
        if(p_numer==1)
        {
            temp=temp*the_cof;  
            zz_n= zz_n+temp;
        }
        else if(p_numer==0)
        {
            zz_n<<co_effish;
        }
    }
    for(term* xxxd=x.denominator.return_my_exp(); xxxd!=NULL; xxxd=xxxd->link())
    {
        temp=y_d;
        p=xxxd->x_getPower();
        p_numer=p.num();
        c=xxxd->getCoeff();
        co_effish.setTerm(c, w, w);        
        the_cof<<co_effish;
        while(p_numer>1)
        {
            temp=temp*y_d;
            p_numer--;
        }

        if(p_numer==1)
        {
            temp=temp*the_cof;
            zz_d=temp;
        }
        else if(p_numer==0)
        {
            zz_d<<co_effish;
        }
    }
    owally.numerator=zz_n;
    owally.denominator=zz_d;
    if(was_neg)
        return owally+testie;

    return owally;
}

fraction super::evaluate(fraction &x){
    fraction topper, botter;
    botter=denominator.evaluate_ND(x);
    topper=numerator.evaluate_ND(x);
    expression lhopital_N=numerator, lhopital_D=denominator;
    while(topper==(long long int)0 && botter==(long long int)0)
    {
     lhopital_N=lhopital_N.derivative();
     lhopital_D=lhopital_D.derivative();
     botter=lhopital_D.evaluate_ND(x);
     topper=lhopital_N.evaluate_ND(x);
    }
    if(botter==(long long int)0)
    {
        cout<<"illegal division by zero"<<endl;
        int donuts=0;
        throw donuts;
    }
    return topper/botter;
}


void super::derivative(int x){
    super tempo;
    term *pointinger = denominator.return_my_exp();
    for(int i=0; i<x; i++)
    {
        if(pointinger->x_getPower()==(long long int)0 && pointinger->link()==NULL)
        {
            expression deriv=numerator.derivative();
            numerator=deriv;
        }
        else
        {
            expression f=numerator;
            expression deriv_f=numerator.derivative();
            expression g=denominator;
            expression deriv_g=denominator.derivative();
            denominator=g*g;
            numerator=(g*deriv_f)-(f*deriv_g);
        }
    }
}

void super::integral_def(int a, int b){
    //haven't implemented this yet.  Program should be able to handle this without too much modification
}

void super::integral_indef(int x){
    //if() need to write statement to make sure denominator == 1
    numerator=numerator.integral();
}

ostream& operator<<(ostream &out, super &k){      //superfluous code?  not sure if used in current implementation. Had note from 2014 that this func has yet to be called
    term *head_n = k.numerator.return_my_exp();
    while(head_n)
    {
        out<<head_n;
        head_n = head_n->link();
    }
    term *head_d = k.denominator.return_my_exp();
    if(head_d->getCoeff()==(long long int)1 && head_d->x_getPower()==(long long int)0 && head_d->ln_getPower()==(long long int)0 && head_d->link()==NULL)
        return out;
    out<<"/";
    while(head_d)
    {
        out<<head_d;
        head_d = head_d->link();
    }
    return out;
}

void super::set_super(expression n, expression d){
    numerator=n;
    denominator=d;
}

string super::print_super(){
    string outString;
    outString = numerator.print_expr();
    if(denominator.return_my_exp()->getCoeff()==(long long int)1 && denominator.return_my_exp()->x_getPower()==(long long int)0 &&denominator.return_my_exp()->link()==NULL)
        return outString;
    outString+="/";
    cout<<"/";
    outString+=denominator.print_expr();
    return outString;
}
