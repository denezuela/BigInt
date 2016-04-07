#include "bigint.hpp"

void strToInteger(const string& s, vector <int> & v) //вспомогательная функция (перевод корректной строки в целое)
{
	int i = 0, j = 0, count = 0;
	string temp;
	while (i < s.size() && s[i] < '0' && s[i] > '9') i++;
	while (i < s.size())
	{
		while (s[i] != ' ')
		{
			temp += s[i];
			i++;
			if (i >= s.size()) break;
		}
        v.push_back(atoi(temp.c_str()));
		temp.clear();
		i++;
	}
}

void integerToStr(const vector<int>& v, string& s) //вспомогательная функция (перевод целого в корректную строку)
{
	char temp[33];
	for (int i = v.size()-1; i > -1; --i)
	{
		itoa(v[i], temp, 10);
		s += (string)temp;
		if (i != 0) s += ' ';
	}
}

int log2 (int degree) //вспомогательная
{
	int res = 0;
	while (degree != 1)
	{
		degree /= 2;
		res++;
	}
	return res;
}

void shift(vector<int> & v) //вспомогательная
{
	v.resize(v.size()+1);
	for (int i = v.size()-1; i>0; --i)
		v[i] = v[i-1];
}

void Integer::normal() //нормализация
{
    while (num.size() > 1 && num.back() == 0)
        num.pop_back();
}

Integer::Integer() //конструктор по умолчанию
{
    b = 2;
    sign = 1;
    num.push_back(0);
}

void Integer::changeSys (int b_) //изменение основания системы счисления
{
    b = b_;
}

Integer::Integer(int b_, string num_, int sign_) //основной конструктор
{
    b = b_;
    sign = sign_;
    strToInteger(num_, num);
    reverse(num.begin(), num.end());
    (*this).normal();
}

Integer::Integer (const Integer& t) //конструктор копирования
{
    b = t.b;
    sign = t.sign;
    num.resize(t.num.size());
    for (int i = 0; i < t.num.size(); ++i)
        num[i] = t.num[i];
}

void Integer::print(ostream& out) const //печать
{
    string s;
    if (sign == 1) out<<"+ ";
        else out<<"- ";
    integerToStr(num,s);
    out << s;
}

bool Integer::operator>(const Integer& right) //сравнение на >
{
    if (sign > right.sign) return true;
        else if (sign < right.sign) return false;
    if (num.size() != right.num.size())
        if (num.size() > right.num.size())
            if (sign > 0) return true;
                else return false;
            else return false;
    else
    {
        for (int i = num.size()-1; i>-1; --i)
            if (num[i]*sign > right.num[i]*right.sign) return true;
                else if (num[i]*sign < right.num[i]*right.sign) return false;
        return false;
    }
}

bool Integer::operator<(const Integer& right) //сравнение на <
{
    if (sign < right.sign) return true;
        else if (sign > right.sign) return false;
    if (num.size() != right.num.size())
        if (num.size() < right.num.size())
            if (sign > 0) return true;
                else return false;
            else return false;
    else
    {
        for (int i = num.size()-1; i>-1; --i)
            if (num[i]*sign < right.num[i]*right.sign) return true;
                else if (num[i]*sign > right.num[i]*right.sign) return false;
    }
}

bool Integer::operator>=(const Integer& right) //сравнение на >=
{
    return !(*this < right);
}

bool Integer::operator<=(const Integer& right) //сравнение на <=
{
    return !(*this > right);
}

bool Integer::operator==(const Integer& right)//сравнение на ==
{
    if (num.size() == right.num.size() && sign == right.sign)
        {
            for (int i = 0; i < num.size(); ++i)
                if (num[i] != right.num[i]) return false;
            return true;
        }
    return false;
}

bool Integer::operator!=(const Integer& right)//сравнение на !=
{
    return !(*this == right);
}

Integer Integer::abs() const //модуль
{
    Integer res(*this);
    res.sign = 1;
    return res;
}

Integer Integer::operator-() const //унарный минус
{
    Integer res(*this);
    res.sign *= -1;
    return res;
}

Integer Integer::minus(const Integer& right) const //вспомогательная для вычитания
{
    int add = 0;
    int t;
    Integer res(*this);
    for (int i = 0; i < right.num.size() || add > 0; ++i)
    {
        if (i < right.num.size()) t = right.num[i];
            else t = 0;
        res.num[i] = res.num[i] - add - t;
        if (res.num[i] < 0) add = 1;
            else add = 0;
        if (add)  res.num[i] += b;
    }
    res.normal();
    return res;
}

Integer Integer::operator-(const Integer& right) const //вычитание
{
    if (sign > 0 && right.sign > 0)
        if ((*this).abs() >= right.abs()) return (*this).minus(right);
            else return -(right.minus(*this));
    else if (sign > 0 && right.sign < 0)
            return (*this) + (-right);
    else if (sign < 0 && right.sign > 0)
            return - ((-(*this)) + right);
    else
        if ((*this).abs() >= right.abs()) return -(*this).minus(right);
            else return ((-right).minus(*this));
}

Integer Integer::operator+(const Integer& right) const //сложение
{
    if (sign > 0 && right.sign < 0) return (*this) - (-right);
    if (sign < 0 && right.sign > 0) return right - (-(*this));
    Integer res(this->b, "", sign > 0 ? 1 : -1);
    int add = 0;
    int l, r;
    for (int i = 0; i < max(num.size(), right.num.size()) || add > 0; ++i)
    {
        if (i < num.size()) l = num[i];
            else l = 0;
        if (i < right.num.size()) r = right.num[i];
            else r = 0;
        res.num.resize(i+1);
        res.num[i] = (l+r+add) % b;
        if ((l+r+add) >= b) add = 1;
                else add = 0;
   }
   res.normal();
   return res;
}

Integer& Integer::operator=(const Integer& right) //присваивание
{
    if (this != &right && b == right.b)
    {
        num.clear();
        num.resize(right.num.size());
        for (int i = 0; i < num.size(); ++i)
            num[i] = right.num[i];
        sign = right.sign;
    }
    return *this;
}

void Integer::multiply(int n) //умножение на 2^n
{
    int shiftNumber = n / log2(b);
    int multiplyNumber = n % log2(b);
    num.resize(num.size() + shiftNumber);
    for (int i = num.size() - 1; i >= shiftNumber; --i)
            num[i] = num[i - shiftNumber];
    for (int i = 0; i < shiftNumber; ++i)
        num[i] = 0;
    if (multiplyNumber == 0) return;
    int p = 2;
    for (int i = 1; i < multiplyNumber; ++i)
        p *= 2;
    int add = 0;
    int s = 0;
    for (int i = 0; i < num.size() || add > 0; ++i)
    {
        if (i==num.size()) num.push_back(0);
        s = add + num[i]*p;
        num[i] = s % b;
        add = s / b;
    }
    (*this).normal();
}

void Integer::divide (int n) //деление на 2^n
{
    int shiftNumber = n / log2(b);
    int divideNumber = n % log2(b);
    if (shiftNumber >= num.size())
    {
        num.clear();
        num.push_back(0);
        return;
    }
    for (int i = 0; i < num.size() - shiftNumber; ++i)
            num[i] = num[i + shiftNumber];
    num.resize(num.size() - shiftNumber);
    if (divideNumber == 0) return;
    int p = 2;
    for (int i = 1; i < divideNumber; ++i)
        p *= 2;
    int add = 0;
    int s = 0;
    for (int i = num.size()-1; i > -1; --i)
    {
        s = num[i] + add*b;
        num[i] = s / p;
        add = s % p;
    }
    (*this).normal();
}

Integer Integer::operator*(const Integer& right) //умножение на длинное
{
    int sign_;
    if ( (sign == -1) ^ (right.sign == -1)) sign_ = -1;
        else sign_ = 1;
    Integer res(b, "", sign_);
    int add = 0;
    int s = 0, t = 0;
    res.num.resize(num.size()+right.num.size());
    for (int i = 0; i < num.size(); ++i)
    {
        add = 0;
        for (int j = 0; j < right.num.size() || add > 0; ++j)
        {
            if (j < right.num.size()) t = right.num[j];
                else t = 0;
            s = t*num[i] + add + res.num[i+j];
            res.num[i+j] = s % b;
            add = s/b;
        }
    }
    res.normal();
    return res;
}

Integer Integer::operator*(int right) const  //right<b умножение на короткое
{
    int sign_;
    if ( (sign == -1) ^ (right < 0)) sign_ = -1;
        else sign_ = 1;
    Integer res(b, "", sign_);
    int add = 0;
    int s = 0;
    int t;
    for (int i = 0; i < num.size() || add > 0; ++i)
    {
        if (i != num.size())
            t = num[i];
        else
            t = 0;
        s = add + t*right;
        res.num.push_back(s % b);
        add = s / b;
    }
    res.normal();
    return res;
}

Integer Integer::operator/(const Integer& right) const //деление длинных
{
    int sign_;
    int x, l, m, r;
    int count = 1;
    if ( (sign == -1) ^ (right.sign == -1)) sign_ = -1;
        else sign_ = 1;
    Integer res(b, "", sign_);
    Integer temp(b,"", 1);
    Integer t(b, "", 1);
    for (int i = num.size()-1; i >-1; --i)
    {
        shift(temp.num);
        temp.num[0] = num[i];
        int x = 0;
        int l = 0, r = b;
        while (l <= r)
         {
            int m = (l + r)/2;
            Integer t = right * m;
            if (t <= temp)
             {
                x = m;
                l = m+1;
             }
            else
                r = m-1;
         }
        if (x == b) x = 0;
        res.num.push_back(x);
        temp = temp - right*x;
    }
    reverse(res.num.begin(), res.num.end());
    res.normal();
    return res;
}


Integer Integer::operator%(const Integer& right) const
{
    Integer div = (*this)/right;
    div = div*right;
    return (*this)-div;
}

ostream& operator<< (ostream& out, const Integer& t)
{
	t.print(out);
	return out;
}

