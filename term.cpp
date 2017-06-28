#include "term.h"

term::term(){
    next = NULL;
}

term::term(const term& x){
    copy(x);
}

term::term(const fraction &c, const fraction &p_x, const fraction &ln_p){
    coeff =  c;
    power_x = p_x;
    ln_power = ln_p;
    if(!valid())
        throw INVALID;
}

term::~term(){
    next = NULL;
}

term& term::operator=(const term&other){
    if(this != &other)
        copy(other);
    return *this;
}

fraction term::evaluate(fraction &x){
    int a_temper_tantrum=2;
    if(power_x<(long long int)0 && x==(long long int)0)     // possibly superflous if stmnt: has never executed true, including in bug testing
    {
        cout<<"cannot divide by zero!"<<endl;
        throw a_temper_tantrum;
    }
    fraction answer, bla, bly;
    if(ln_power==(long long int)0)
    {
        bla=x^power_x;
        answer = coeff*(bla);
    }
    else
    {
        fraction ln_x = ln_f(x);
        bla=x^power_x;
        bly=ln_x^ln_power;
        answer = coeff*(bla)*(bly);
    }
    return answer;
}

term term::derivative(){
    term temprairie;
    fraction pow_x=power_x;
    fraction pow_ln=ln_power;
    fraction coef=coeff;
    fraction blah((long long int)1, (long long int)1);    
    fraction pow_xk=power_x-blah;
    fraction pow_lnk=ln_power-blah;
    if(power_x!=(long long int)0 && ln_power == (long long int)0)
    {
        temprairie.coeff = pow_x*coef;
        temprairie.power_x = pow_xk;
    }
    else if(power_x==(long long int)0 && ln_power != (long long int)0)
    {
        temprairie.coeff = pow_ln*coef;
        temprairie.ln_power = pow_lnk;
        temprairie.power_x = pow_xk;
    }
    else
        temprairie.coeff=(long long int)0;

    return temprairie;
}

term term::integral(){
    term temp;
    fraction pow_x=power_x;
    fraction integrated_coeff;
    fraction coef=coeff;
    fraction neg_one((long long int)-1, (long long int)1), zzz((long long int)0, (long long int)1);
    fraction one((long long int)1, (long long int)1);
    if(pow_x==neg_one)
    {
        temp.setTerm(coef, zzz, one);
        return temp;
    }
    else
    {
        temp.setTerm(zzz, zzz, zzz);             
        pow_x=pow_x + one;                                          
        integrated_coeff = pow_x;
        integrated_coeff = coef/integrated_coeff;
        temp.setTerm(integrated_coeff, pow_x, zzz);
        return temp;
    }
}

void term::setTerm(fraction &c, fraction &p_x, fraction &p_ln){
    coeff = c;
    power_x = p_x;
    ln_power = p_ln;
}

void term::setLink(term *nex_lnk){
    next = nex_lnk;
}

fraction& term::getCoeff(){
    return coeff;
}

fraction& term::x_getPower(){
    return power_x;
}

fraction& term::ln_getPower(){
    return ln_power;
}

term*& term::link(){
    return next;
}

void term::copy(const term& x){
    coeff = x.coeff;
    power_x = x.power_x;
    ln_power= x.ln_power;
    next = NULL;                    // Note: next = NULL and not x.next() --> this is copying the node value only
}

bool term::valid(){
    return coeff.denom() != 0 && power_x.denom() != 0 && ln_power.denom() != 0;
}

term operator+(term& x, term& y){
    if(x.power_x != y.power_x || x.ln_power != y.ln_power)
        throw CANNOT_HAPPEN;
    term ans(x.coeff + y.coeff, x.power_x, x.ln_power);
    return ans;
}


term operator-(term& x, term& y){
    if(x.power_x != y.power_x || x.ln_power != y.ln_power)
        throw CANNOT_HAPPEN;
    term ans(x.coeff - y.coeff, x.power_x, x.ln_power);
    return ans;
}


term operator*(term& x, term& y){
    fraction x__pow=x.power_x + y.power_x;
    fraction ln_pow=x.ln_power + y.ln_power;
    term ans(x.coeff * y.coeff, x__pow, ln_pow);  
    return ans;
}

ostream& operator<<(ostream& out, term &other){
    if(other.coeff < (long long int)0)
        out<<"- ";
    else
        cout<<"+ ";
    out<<aabs(other.coeff);  
    if(other.power_x != (long long int)0)                                   
        out<<"X^"<<other.power_x;                                             
    if(other.ln_power != (long long int)0)
        out<<"ln(X)^"<<other.ln_power;
    return out;
}


istream& operator>>(istream& in, term &other){
    // cout<<"instream >> called"<<endl;            // NOTE: this func hasn't been called in a very long time. Might now be superfluous
    char junk;
    in>>other.coeff>>junk>>junk>>other.power_x;
    return in;
}


term operator-(term& x){
    term j=x;
    fraction c, p_x, p_ln;
    c=j.getCoeff();
    p_x=j.x_getPower();
    p_ln=j.ln_getPower();
    c.make_numer_neg();
    j.setTerm(c, p_x, p_ln);
    return j;
}

string term::print_da_term(){
    string outString = "";
    string tempOutString;
    stringstream ss;
    fraction test_xp=x_getPower();
    fraction test_lnp=ln_getPower();
    long long int txp=test_xp.num();
    long long int tlnp=test_lnp.num();
    long long int czech_c=coeff.denom(), czech_p=power_x.denom(), czech_cn=coeff.num(), czech_pn=power_x.num();
    long long int LNczech_p=ln_power.denom(), LNczech_pn=ln_power.num();
    if(czech_cn==(long long int)0)
        return outString;
    if(czech_c==(long long int)1 && czech_cn==(long long int)1 && czech_pn!=(long long int)0){  
        /*blank*/
    }
    else if(czech_c==(long long int)1)
    {
        ss<<abs(czech_cn);
        ss>>outString;
        cout<<abs(czech_cn);
    }
    else
    {        
        ss<<aabs(coeff);
        ss>>outString;
        cout<<aabs(coeff);
    }

    if(czech_pn==(long long int)0 && LNczech_pn==(long long int)0)
        return outString;

    if(czech_pn==(long long int)0){
        /*blank*/
    }
    else if(czech_p==(long long int)1 && czech_pn==(long long int)1)
    {
        outString+="x";
        cout<<"x";
    }
    else if(czech_p==(long long int)1)
    {
        ss.clear();
        ss<<power_x.num();
        ss>>tempOutString;
        outString+="x^"+tempOutString;
        cout<<"x^"<<power_x.num();
    }
    else
    {
        ss.clear();
        ss<<power_x;
        ss>>tempOutString;
        outString+="x^"+tempOutString;
        cout<<"x^"<<power_x;
    }

    if(LNczech_pn==(long long int)0){
        /*blank*/
    }
    else if(LNczech_p==(long long int)1 && LNczech_pn==(long long int)1)
    {
        outString+="Ln(x)";
        cout<<"Ln(x)";
    }
    else if(LNczech_p==(long long int)1)
    {
        ss.clear();
        outString+="Ln(x)";
        ss<<ln_power.num();
        ss>>tempOutString;
        outString+=tempOutString;
        cout<<"Ln(x)^"<<ln_power.num();
    }
    else
    {
        ss.clear();
        outString+="Ln(x)^";
        ss<<ln_power;
        ss>>tempOutString;
        outString+=tempOutString;
        cout<<"Ln(x)^"<<ln_power;
    }
    return outString;
}

fraction term::ln_f(fraction x){
    double float_ver, ans;
    float_ver= (double)x.num()/(double)x.denom();
    if(float_ver<1.5)
        ans = ln_func(float_ver);
    else
        ans = ln_funk(float_ver);
    fraction lnx(ans);
    return lnx;
}

double term::ln_func(double numbero){
    double comparo=numbero;
    int count=1;
    numbero=numbero-1;
    double numee = numbero;
    while(fabs(comparo-numbero)>.000000001)
    {
        count++;
        comparo=numbero;
        numbero= numbero + ((pow(-1,count+1))*((pow(numee, count)/(double)count)));
    }
    return numbero;
}


double term::ln_funk(double numbero)
{                                           
    double comparo=numbero+.5;
    int count=1;
    double numee=1 - (double)1/numbero;
    numee = double(1)/numee;
    cout<<"numee="<<numee<<endl;
    numbero = (double)1/numee;
    while(fabs(comparo-numbero)>.000000001) 
    {
        count++;
        comparo=numbero;
        numbero= numbero + double(1)/(count*pow(numee, count));
        cout<<numbero<<endl;
    }
    return numbero;
}
