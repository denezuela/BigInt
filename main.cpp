#include "bigint.hpp"

using namespace std;

Integer Euclid (Integer a, Integer b, int base)
{
    Integer c (base, "1", 1);
    Integer null (base, "0", 1);
    while (c != null)
    {
        c = a % b;
        a = b;
        b = c;
    }
    return a.abs();
}

int main()
{
    ifstream fin("data10.txt");
    string s;
    int base, sign;
    fin>>base; //прочитали ситему счисления

    while (s=="") getline(fin, s);
    if (s[0] == '+')
        sign = 1;
    else
        sign = -1; //прочитали первое число и определили знак
    Integer a (base , s, sign);
    cout<<"a = "<<a<<endl;

    s.clear();
    while (s=="") getline(fin, s);
    if (s[0] == '+')
        sign = 1;
    else
        sign = -1; //прочитали второе число и определили знак
    Integer b (base , s, sign);
    cout<<"b = "<<b<<endl;

    cout<<"a+b = "<<a+b<<endl;
    cout<<"a-b = "<<a-b<<endl;
    cout<<"a*b = "<<a*b<<endl;
    cout<<"a div b = "<<a/b<<endl;
    cout<<"gcd = "<<Euclid(a, b, base)<<endl;
    return 0;
}

