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
		void normal(); //������������
		Integer(); //����������� �� ���������
		void changeSys (int b_); //��������� ��������� ������� ���������
		Integer(int b_, string num_, int sign_); //�������� �����������
        Integer (const Integer& t); //����������� �����������
		void print(ostream& out) const;//������
		bool operator>(const Integer& right); //��������� �� >
		bool operator<(const Integer& right); //��������� �� <
		bool operator>=(const Integer& right); //��������� �� >=
		bool operator<=(const Integer& right); //��������� �� <=
		bool operator==(const Integer& right);//��������� �� ==
		bool operator!=(const Integer& right);//��������� �� !=
		Integer abs() const; //������
		Integer operator-() const; //������� �����
		Integer operator-(const Integer& right) const; //���������
		Integer operator+(const Integer& right) const;//��������
		Integer& operator=(const Integer& right); //������������
		void multiply(int n); //��������� �� 2^n
		void divide (int n); //������� �� 2^n
		Integer operator*(const Integer& right); //��������� �� �������
		Integer operator*(int right) const;  //right<b ��������� �� ��������
		Integer operator/(const Integer& right) const; //������� �������
		Integer operator%(const Integer& right) const; //������� �� �������
		friend ostream& operator<< (ostream& out, const Integer & t); //����� � �����
};
