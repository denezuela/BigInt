#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

class Integer
{
	private:
		int b;
		int sign;
		vector <int> num;
		Integer minus(const Integer& right) const;
	public:
		void normal(); //нормализация
		Integer(); //конструктор по умолчанию
		void changeSys (int b_); //изменение основания системы счисления
		Integer(int b_, string num_, int sign_); //основной конструктор
        Integer (const Integer& t); //конструктор копирования
		void print(ostream& out) const;//печать
		bool operator>(const Integer& right); //сравнение на >
		bool operator<(const Integer& right); //сравнение на <
		bool operator>=(const Integer& right); //сравнение на >=
		bool operator<=(const Integer& right); //сравнение на <=
		bool operator==(const Integer& right);//сравнение на ==
		bool operator!=(const Integer& right);//сравнение на !=
		Integer abs() const; //модуль
		Integer operator-() const; //унарный минус
		Integer operator-(const Integer& right) const; //вычитание
		Integer operator+(const Integer& right) const;//сложение
		Integer& operator=(const Integer& right); //присваивание
		void multiply(int n); //умножение на 2^n
		void divide (int n); //деление на 2^n
		Integer operator*(const Integer& right); //умножение на длинное
		Integer operator*(int right) const;  //right<b умножение на короткое
		Integer operator/(const Integer& right) const; //деление длинных
		Integer operator%(const Integer& right) const; //остаток от деления
		friend ostream& operator<< (ostream& out, const Integer & t); //вывод в поток
};
