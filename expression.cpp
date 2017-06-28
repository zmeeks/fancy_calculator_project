#include "expression.h"

expression::expression(){
    myExpression = NULL;
}

expression::~expression(){
    zero();
}

expression::expression(const expression &other){
    copy(other);
}

expression& expression::operator=(const expression &other){
    if(this != &other)
    {
        zero();
        copy(other);
    }
    return *this;
}


expression& expression::operator<<(term &input){
    term *newTerm = new term(input);
    term *thenext = myExpression;
    term *theprev;
    theprev= new term;
    theprev->setLink(myExpression);
    if(thenext==NULL){
        newTerm->setLink(NULL);
        myExpression= newTerm;
        return *this;
    }
    while(thenext!=NULL){
        if(newTerm->x_getPower()>(thenext->x_getPower())){
            newTerm->setLink(thenext);
            theprev->setLink(newTerm);
            if(thenext==myExpression)
                myExpression= newTerm;
            return *this;
        }
        else if(newTerm->x_getPower()==thenext->x_getPower() && newTerm->ln_getPower()>(thenext->ln_getPower())){
            newTerm->setLink(thenext);
            theprev->setLink(newTerm);
            if(thenext==myExpression)
                myExpression= newTerm;
            return *this;
        }
        else if(newTerm->x_getPower()==thenext->x_getPower() && newTerm->ln_getPower()==(thenext->ln_getPower())){
            fraction co_eff_a, co_eff_b, co_eff_c, pow_pow_x, pow_pow_LN;
            pow_pow_x=newTerm->x_getPower();
            pow_pow_LN=newTerm->ln_getPower();
            co_eff_a=newTerm->getCoeff();
            co_eff_b=thenext->getCoeff();
            co_eff_c=co_eff_a+co_eff_b;
            thenext->setTerm(co_eff_c, pow_pow_x, pow_pow_LN);
            return *this;
        }
        if(thenext->link()==NULL){
            thenext->setLink(newTerm);
            newTerm->setLink(NULL);
            return *this;
        }
        theprev=thenext;
        thenext=thenext->link();
    }
    return *this;
}

expression& expression::operator<<(string &input){      //currently superflous
   cout<<"reimplement me (expression class)"<<endl; 
}

expression& expression::operator>>(string &output){      //currently superflous
    cout<<"reimplement me (expression class)"<<endl;  
}

fraction expression::evaluate_ND(fraction &x){
    fraction running_ans, temp_ans;
    for(term *pointinger=myExpression; pointinger!=NULL; pointinger=pointinger->link()){
        temp_ans=(*pointinger).evaluate(x);
        running_ans=running_ans+temp_ans;
    }
    return running_ans;
}


expression expression::derivative(){
    expression ans;
    term *pointinger = myExpression;
    term temp, term_deriv, x_t, ln_t;
    fraction x_f, ln_f, ccf, zz((long long int)0, (long long int)1);
    fraction x1, x2, ln2, c1, c2;

    while(pointinger!=NULL)
    {
        temp=*pointinger;

        if(temp.x_getPower()==(long long int)0 && temp.ln_getPower()==(long long int)0)         //this stmnt possibly superflous
        {                                                                                       
            if(pointinger->link()==NULL)
                return ans;
            else
            {
                pointinger=pointinger->link();
                temp=*pointinger;
            }

        }

        if(temp.x_getPower()!=(long long int)0 && temp.ln_getPower()!=(long long int)0)         //"chain rule"
        {
            x_f=temp.x_getPower();
            ln_f=temp.ln_getPower();
            ccf=temp.getCoeff();

            x_t.setTerm(ccf, x_f, zz);
            ln_t.setTerm(ccf, zz, ln_f);

            x_t=x_t.derivative();
            ln_t=ln_t.derivative();


            x1=x_t.x_getPower();
            x2=ln_t.x_getPower();

            ln2=ln_t.ln_getPower();                 

            c1=x_t.getCoeff();
            c2=ln_t.getCoeff();     

            x2= x2+x_f;

            x_t.setTerm(c1, x1, ln_f);
            ln_t.setTerm(c2, x2, ln2);

            ans<<x_t;
            ans<<ln_t;

        }
        else
        {
            term_deriv=temp.derivative();
            ans<<term_deriv;

        }
            pointinger=pointinger->link();
    }

    return ans;
}

expression expression::integral(){
    expression ans, ibp_anz, extr;
    term *pointinger = myExpression;
    term temp, term_ingral;
    term t;
    fraction zero((long long int)0, (long long int)1), one((long long int)1, (long long int)1);
    t.setTerm(zero, zero, zero);            
    ans<<t;
    extr<<t;                                
    ibp_anz<<t;

    while(pointinger!=NULL)
    {
        temp=*pointinger;

        if(temp.ln_getPower()!=(long long int)0)
        {
            ibp_anz=integration_by_parts(temp);
            extr=ans+ibp_anz;
            ans=extr;
        }
        else
        {
            term_ingral=temp.integral();
            ans<<term_ingral;
        }
        pointinger=pointinger->link();
    }
    return ans;
}

expression expression::integration_by_parts(term t_IBP){
    expression ans, u_dv, v_du, u_v;
    term temp, u, v, du, dv, udv, vdu, uv;
    fraction x_f, ln_f, ccf, neg_one((long long int)-1, (long long int)1);
    fraction zzz((long long int)0, (long long int)1), one((long long int)1, (long long int)1), two((long long int)2, (long long int)1);
    term t;                                     //
    t.setTerm(zzz, zzz, zzz);                   // these lines possibly superflous
    ans<<t;                                     // but they are implemented properly in case they are not...
    u_dv<<t;                                    //
    v_du<<t;
    u_v<<t;

    if(t_IBP.x_getPower()==neg_one && t_IBP.ln_getPower()==one){
        ccf=t_IBP.getCoeff();
        ccf=ccf/(long long int)2;
        temp.setTerm(ccf, zzz, two);
        ans<<temp;
        return ans;
    }
    else
    {
        x_f=t_IBP.x_getPower();
        ln_f=t_IBP.ln_getPower();
        ccf=t_IBP.getCoeff();
        u.setTerm(ccf, zzz, ln_f);
        du=u.derivative();
        dv.setTerm(one, x_f, zzz);
        v=dv.integral();
        udv= u*dv;
        vdu= v*du;
        uv= u*v;
        u_dv<<udv;
        u_v<<uv;

        if(vdu.ln_getPower()!=(long long int)0)
        {
            ans= u_v - integration_by_parts(vdu);
        }
        else
        {
            vdu=vdu.integral();
            v_du<<vdu;
            ans= u_v - v_du;
        }
        return ans;
    }
}


void expression::copy(const expression &other){
    term *otherHead = other.myExpression, *end;
    if(otherHead)
    {
        term * newCopiedTerm = new term(*otherHead);
        myExpression = end = newCopiedTerm;
        /*
          Note: the above is the same as
          expression = newCopiedTerm;
          end = newCopiedTerm;
        */
        otherHead = otherHead->link();
        while( otherHead)
        {
            newCopiedTerm = new term(*otherHead);
            end->link() = newCopiedTerm;
            end = end->link();
            otherHead = otherHead->link();
        }
    }
}

void expression::zero(){
    term *bye;
    while(myExpression)
    {
        bye = myExpression;
        myExpression = myExpression->link();
        delete bye;
    }
}

ostream& operator<<(ostream &out, expression &p){
    term *head = p.myExpression;
    while(head)
    {
        out<<*head;
        head = head->link();
    }
    return out;
}

istream& operator>>(istream &in, expression &p){
    term newTerm;
    while(in>>newTerm)
        p<<newTerm;
    return in;
}

expression operator+(const expression &x, const expression &y){
    expression tempo=x;
    for(term* pointinger=y.return_my_exp(); pointinger!=NULL; pointinger=pointinger->link()) 
    {
        tempo<<*pointinger;
    }

    return tempo;

    //^iterates through adding coeffs together of like powers
}

expression operator-(const expression &x, const expression &y){
    expression tempo=x;
    term neg_term;
    for(term* pointinger=y.return_my_exp(); pointinger!=NULL; pointinger=pointinger->link())
    {
        neg_term= -(*pointinger);
        tempo<<neg_term;
    }
    return tempo;

    //^iterates though subtracting coeffs together of like powers
}

expression operator*(const expression &x, const expression &y){
    term *pointinger_x=x.myExpression;
    term *pointinger_y=y.myExpression;

    expression tempo;
    term a, b, c;

    if(pointinger_y==NULL)
        return x;

    for(pointinger_x; pointinger_x!=NULL; pointinger_x=pointinger_x->link())
        for(pointinger_y=y.myExpression; pointinger_y!=NULL; pointinger_y=pointinger_y->link())
        {
            a=*pointinger_x;
            b=*pointinger_y;
            c=a*b;
            tempo<<c;
        }
    return tempo;

    //^iterates through multiplying everything together
}

//Note: for divide, changes expression so that it has a denominator, then just flips it over and multiplies... this is done in super class 

term* expression::return_my_exp() const{
    return myExpression;
}

string expression::print_expr() const{
    string outString;
    term* headinger;
    headinger= new term;
    headinger=myExpression;
    int counter=1;
    if(headinger!=NULL)
        if(headinger->getCoeff()<(long long int)0)
        {
            outString="-";
            cout<<"-";
        }
    while(headinger!=NULL)
    {
        outString+=headinger->print_da_term();
        if(headinger->link()!=NULL && headinger->link()->getCoeff()<(long long int)0)
        {
            outString+="-";
            cout<<" - ";
        }
        else if(headinger->link()!=NULL && headinger->link()->getCoeff()!=(long long int)0)
        {
            outString+="+";
            cout<<" + ";
        }

        if((headinger->link())== NULL)
        {
            return outString;
        }

        if(headinger->link()!=NULL)
            headinger=headinger->link();

         counter++;
    }

    cout<<"error:"<<endl;       //Note: this statement never reached.  Should have used try/catch instead
    cout<<"headinger was:";
    headinger->print_da_term();
    cout<<endl;
    exit(1);
}
