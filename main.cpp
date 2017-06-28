//#include <QtCore/QCoreApplication>
#include "fraction.h"
#include "expression.h"
#include "super.h"
#include "term.h"
#include <cstring>

using namespace std;

bool getLine(string &input);
void process(string &input, super list[]);
void normalize(string &input);
void doCommand(string &input, super *list);
void assignment(string &input, super *list);
super parse_it_out(string input, super *list);
long long int atoint(char car);

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    while(true)
    {
        try{
            super list[26];
            string input;

            while(getLine(input))
                process(input, list);
        }
        catch(int e)
        {
            //blank catch. back to while(true) unless internal error catching leads to exit
        }
    }
    return 0;
}


bool getLine(string &input){
    cout<<endl<<"Input: ";
    getline(cin, input);
    return input != "";
}


void normalize(string &input){
    for(int i = 0; i < input.size(); i++)
    {
        while(input[i] == ' ')
            input.erase(i,1);
        input[i] = tolower(input[i]);
    }
}


void process(string &input, super list[]){
    static string commandSet[] ={"let", "print", "eval", "plot"};
    normalize(input);
    int pos;
    int boolian_check_for_funcs=input.find_first_of("abcdefghijklmnopqrstuvw&yz", 2);
    for(int i = 0; i < 3; i++)
        if((pos = input.find(commandSet[i])) < string::npos)
                break;
    if(pos < string::npos)
        doCommand(input,list);
    else if(boolian_check_for_funcs>=0)
        assignment(input,list);
    else
    {
        input="let"+input;
        doCommand(input,list);
    }
}

void doCommand(string &input, super *list){
    bool otto_print=false;
    int pos;
    if(input.find("let") < string::npos)
    {
        super temper;
        input=input.substr(3);
        char result = input[0];
        if(result=='x')
        {
            cout<<"a function may not be designated \"x\", therefore for convenience your function"<<endl;
            cout<<"has been redesignated under the function \"&\", so please make note of this"<<endl;
        }
        if(result==38)          //ascii 38 = '&'
            result='x';
        temper=parse_it_out(input.substr(2), list);
        list[result-'a']=temper;
    }
    else if(input.find("=") < string::npos)   //superfluous code -- this stmnt hasn't ever evaluated true
    {
        expression numinator;
        input=input.substr(3);
        char result = input[0];
        stringstream ss;
        ss<<input.substr(2);
        ss>>numinator;
        super temper(numinator);
        list[result-'a']=temper;
    }
    else
        if(input.find("eval") < string::npos)
        {
            long long int top=0, bot=1;                 
            char who = input[4];
            bool neg_it_is=false;
            if(who=='x')
                cout<<"did you mean function \"&\"?"<<endl;
            if(who==36)
                who='x';
            fraction where, ans;
            input=input.substr(6);
            int longth=input.size() +1;             //don't change to long long
            char carvar[longth];
            strcpy(carvar, input.c_str());
            if(carvar[0]=='-')
            {                                   
                neg_it_is=true;
                carvar[0]='0';
            }
            int pass=0;
            for(int p=0; p<longth-1; pass++)
            {
                if(pass>p)
                {
                    p++;
                    pass=1;
                }
                while(isdigit(carvar[p]))
                {
                    top= (top*(long long int)10)+ atoint(carvar[p]);              
                    p++;
                }
                if(carvar[p]==47)           //47 = '/'
                {
                    p++;
                    bot=0;
                    while(isdigit(carvar[p]))
                    {
                        bot= (bot*10) + atoint(carvar[p]);       
                        p++;
                    }
                }
            }
            where.set_term(top, bot);
            if(neg_it_is)
            {
                long long int nN, dD;
                nN=where.num();
                dD=where.denom();
                nN=nN*(long long int)(-1);
                where.set_term(nN, dD);
            }
            ans = list[who-'a'].evaluate(where);
            if(who=='x')
                cout<<"&("<<where<<") = "<<ans<<endl;
            else
                cout<<who<<"("<<where<<") = "<<ans<<endl;
        }
        else
            if(input.find("print") < string::npos)
            {
                char exp = input[5];
                if(exp=='x')
                    cout<<"did you mean function \"&\"?"<<endl;
                if(exp==38)
                    exp='x';
                if(exp=='x')
                    cout<<"& = ";
                else
                    cout<<exp<<" = ";
                list[exp -'a'].print_super();
                cout<<endl;
            }
            else
                if(input.find("plot")  < string::npos)
                {
                    // Greg has a beta implementation.. removed from here bc beta version cannot handle ln's nor many corner cases
                }
                else
                    cout<<"Invalid input. Please re-enter Z"<<endl;
}

void assignment(string &input, super *list){
    super tempov;
    int pos = input.find("="),
        op = input.find_first_of("$*/+-(\'"),
        invalid = input.find_first_not_of("abcdefghijklmnopqrstuvwxyz$+-*/=\'()");
    if(pos >= string::npos || op >= string::npos || invalid < string::npos)
    {
        cout<<"Invalid input. Please re-enter "<<endl;
        return;
    }
    char result = input[0];

    if(result==38)                      //Possibly superflous if stmnt. Added just to be safe 
        result='x';

    pos = input.find_first_of("+-*/(");
    if(pos < string::npos)
    {
        char x = input[pos-1], y = input[pos+1];
        if(x=='&')
            x='x';
        if(y=='&')
            y='x';

        switch(input[pos])
        {
            case '+':   tempov = list[x-'a']+list[y-'a'];
                        list[result - 'a']=tempov;
                        break;

            case '-':   tempov = list[x-'a']-list[y-'a'];
                        list[result - 'a']=tempov;
                        break;

            case '*':   tempov = list[x-'a']*list[y-'a'];
                        list[result - 'a']=tempov;
                        break;

            case '/':   tempov = list[x-'a']/list[y-'a'];
                        list[result - 'a']=tempov;
                        break;

            case '(':   tempov = list[x-'a']%list[y-'a'];
                        list[result - 'a']=tempov;
        }
    }
    else
        if((pos = input.find("\'")) < string::npos)
        {
            int count = 1;
            char x = input[pos-1];            
            while((pos = input.find("\'", pos + 1))< string::npos)
                count++;
            super tempoo;
            tempoo = list[x-'a'];
            tempoo.derivative(count);
            list[result-'a'] = tempoo;
        }
        else if((pos = input.find("$")) < string::npos)
        {
            char x = input[pos+1];
            super tempoo;
            tempoo = list[x-'a'];
            tempoo.integral_indef(1);   
            list[result-'a'] = tempoo;
        }
}

super parse_it_out(string input, super *list){
    term nextTerm;
    char buf;
    long long int coeffer_n, coeffer_d, power_n, power_d;
    int lengther;
    bool decimal=false;
    int decimal_count=0;
    fraction coeffy, powie;
    expression numer_numer, denom_denom, blank;
    term cur_trm, blank_trm;
    super temp;
    long long int power_of_expression=0;
    int poss;                //<--don't make long long
    bool subtrationeg=false, expression_pow=false;
    coeffy.set_term(1, 1);
    powie.set_term(0, 1);
    cur_trm.setTerm(coeffy, powie, powie);   
    blank_trm.setTerm(coeffy, powie, powie); 
    denom_denom<<cur_trm;
    blank<<blank_trm;
    poss=input.find_first_of(")");
    bool neg_found=false;
    if(poss>0)  //accounting for expression being raised to a power
    {
        char buf=input[poss+2];
        if(buf==45)             //ascii 45 = '-'
        {
            buf=input[poss+3];
            neg_found=true;
            input.erase(poss+2, 1);
        }
        power_of_expression=atoint(buf);
        for(int i=poss+3; i<input.size(); i++)
        {
            buf=input[i];
            power_of_expression = power_of_expression*(long long int)10 +atoint(buf);
        }
        input.erase(poss, 5);   //only accounts for raising expressions to a power of 3 tens places or less
        poss=input.find_first_of("(");
        input.erase(poss,1);
        expression_pow=true;
    }   //end of accounting for the expression being raised to a power
    lengther=input.size()+1;
    char char_ver[lengther];
    strcpy(char_ver, input.c_str());
    for(int i=0; i<lengther-1; )
    {
        if(char_ver[i]==43 && i<lengther-1) //43=ascii '+'
        {
            subtrationeg=false;
            i++;
        }
        if(char_ver[i]==45 && i<lengther-1) //45=ascii '-'
        {
            subtrationeg=true;
            i++;
        }
        decimal=false;
        decimal_count=0;

        if((isdigit(char_ver[i]) || char_ver[i] == '.') && i<lengther-1)
        {
            if(char_ver[i] == '.')
            {
                decimal=true;
                i++;
            }
            coeffer_n=atoint(char_ver[i]);
            i++;
            while((isdigit(char_ver[i]) || char_ver[i] == '.') && i<lengther-1)
            {
                if(char_ver[i] == '.')
                {
                    decimal=true;
                    i++;
                }
                coeffer_n=(coeffer_n*10)+atoint(char_ver[i]); 
                i++;
                if(decimal)
                    decimal_count++;
            }

            if(char_ver[i]==47 && i<lengther-1)  //ascii 47 = '/'
            {
                i++;
                if(!isdigit(char_ver[i]) && i<lengther-1)
                    cout<<"Biggo error! wrong syntax in expression!"<<endl;
                coeffer_d=atoint(char_ver[i]);
                i++;
                while(isdigit(char_ver[i]) && i<lengther-1)
                {
                    coeffer_d=(coeffer_d*10)+atoint(char_ver[i]); 
                    i++;
                }
            }
            else
                coeffer_d=1;

            if(decimal)
                for(int z=0; z<decimal_count; z++)
                    coeffer_d = coeffer_d*10;

            coeffy.set_term(coeffer_n, coeffer_d);
            if(subtrationeg)
            {
                coeffy.make_numer_neg();
            }
        }
        if(char_ver[i]==120 && i<lengther-1) //120=ascii 'x'
        {
            if(char_ver[i-1]==43 || char_ver[i-1]==45)// accounting for cases when there is no coefficient and term before == '+' || '-'
            {
                coeffer_n=1;
                coeffer_d=1;
                coeffy.set_term(coeffer_n, coeffer_d);
                if(subtrationeg)
                {
                    coeffy.make_numer_neg();
                }
            }
            i++;
            if(char_ver[i]==94 && i<lengther-1) //94= ascii '^'
            {
                bool neg_pow=false;
                i++;
                if(char_ver[i]=='-')
                {
                    neg_pow=true;
                    i++;
                }
                power_n=atoint(char_ver[i]);
                i++;
                decimal=false;
                decimal_count=0;
                while((isdigit(char_ver[i]) || char_ver[i] == '.') && i<lengther-1)
                {
                    if(char_ver[i] == '.')
                    {
                        decimal=true;
                        i++;
                    }
                    power_n=(power_n*10)+atoint(char_ver[i]);
                    i++;
                    if(decimal)
                        decimal_count++;
                }
                if(neg_pow)
                    power_n=power_n*(long long int)(-1);
                if(char_ver[i]==47 && i<lengther-1) //47= ascii '/'
                {
                    i++;
                    power_d=atoint(char_ver[i]);
                    i++;
                    while(isdigit(char_ver[i]) && i<lengther-1)
                    {
                        power_d=(power_d*10)+atoint(char_ver[i]);
                        i++;
                    }
                }
                else
                    power_d=1;

                if(decimal)
                    for(int z=0; z<decimal_count; z++)
                        power_d=power_d*10;
            }
            else
            {
                power_n=1;
                power_d=1;
            }
        }
        else
        {
            power_n=0;
            power_d=1;
        }
        powie.set_term(power_n, power_d);
        long long int zn=0, zd=1;
        fraction zeero(zn, zd);
        cur_trm.setTerm(coeffy, powie, zeero); 
        numer_numer<<cur_trm;
    }

    if(!expression_pow)
        temp.set_super(numer_numer, denom_denom);
    else if(!neg_found)
    {
        expression tempee=numer_numer;
        if(power_of_expression==(long long int)0)
            tempee=blank;

        while(power_of_expression>1)
        {
            tempee= tempee*numer_numer;
            power_of_expression--;
        }
        temp.set_super(tempee, denom_denom);
    }
    else
    {
        expression tempee=numer_numer;
        while(power_of_expression>1)
        {
            tempee= tempee*numer_numer;
            power_of_expression--;
        }
        temp.set_super(denom_denom, tempee);
    }
    return temp;
}

long long int atoint(char car){
    if(car==48)
        return (long long int)0;
    else if(car==49)
        return (long long int)1;
    else if(car==50)
        return (long long int)2;
    else if(car==51)
        return (long long int)3;
    else if(car==52)
        return (long long int)4;
    else if(car==53)
        return (long long int)5;
    else if(car==54)
        return (long long int)6;
    else if(car==55)
        return (long long int)7;
    else if(car==56)
        return (long long int)8;
    else if(car==57)
        return (long long int)9;
    else
    {
        cout<<"error in atoint func... exiting"<<endl;
        cout<<"(encountered char: "<<car<<")"<<endl;
        exit(1);
    }
}

