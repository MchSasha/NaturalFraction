/*!\file 
* This file stores the realisation of Natural class.
*/
#include "header.h"
Natural::Natural()
{
	num = 1;
	denom = 1;
}
Natural::Natural(int i)
{
	if (i == 0)
		/*! \throws Throws the exception if int i equals 0. Because 0 is not a natural number.*/
		throw "Zero is not natural.\n";
	num = i;
	denom = 1;
}
Natural::Natural(int i, int n, int d)
{
	if (n == 0)
		/*! \throws Throws the exception if int n equals 0. Because 0 is not a natural number.*/
		throw "Zero is not natural.\n";
	if (d == 0)
		/*! \throws Throws the exception if int d equals 0. Otherwise division by 0.*/
		throw "Division by zero.\n";
	num = fabs(i) * d + fabs(n); if (i < 0) num = -num; if (n < 0) num = -num;  
	denom = d;
	reduce();
}
Natural::Natural(int n, int d)
{
	if (n == 0)
		/*! \throws Throws the exception if int i equals 0. Because 0 is not a natural number.*/
		throw "Zero is not natural.\n";
	if (d == 0)
		/*! \throws Throws the exception if int d equals 0. Otherwise division by 0.*/
		throw "Division by zero.\n";
	num = n; if (n < 0) num = -num;
	denom = d;
	reduce();
}

Natural::~Natural() {};

Natural::Natural(const Natural& x) {
	num = x.num;
	denom = x.denom;
}
/*! Finds NOD to be able to reduce fraction in further calculations 
* \param x, y numerator and denominator of the fraction
* \return NOD 
*/
int Natural::NOD(int x, int y)
{
	x = fabs(x);
	while (y)
	{
		int temp = y;
		y = x % y;
		x = temp;
	}
	return x;
}
/*! Reduces a fraction*/
void Natural::reduce()
{
	int del = NOD(num, denom);
	num /= del;
	denom /= del;
}
/*! Makes fraction upside-down in the operation of division
*\return reversed fraction
*/
Natural& Natural::reversal()
{
	Natural t;
	t.denom = fabs(num);
	t.num = denom;
	if (num < 0) t.num = -t.num;
	return t;
}
/*! 
* \return integer part of the fraction */
const int Natural::getInt()
{
	return num / denom;
}
/*!
\return the numerator of the fraction*/
const int Natural::getNum()
{
	return num;
}
/*! \return the denominator of the fraction*/
const int Natural::getDenom()
{
	return denom;
}
/*! \return natural fraction into double*/
double Natural::ntod()
{
	double n = num, d = denom;
	return n / d;
}

bool operator ==(Natural& x, Natural& y)
{
	return ((x.num == y.num) & (x.denom == y.denom)) ? 1 : 0;
}
bool operator !=(Natural& x, Natural& y)
{
	return ((x.num != y.num) || (x.denom != y.denom)) ? 1 : 0;
}
ostream& operator <<(ostream& os, Natural& x)
{
	return os << x.num << "/" << x.denom;
}
istream& operator >>(istream& is, Natural& x)
{
	if (!is)
		throw "Zero is not natural.\n";
	return is >> x.num >> x.denom;
}

Natural operator +(Natural& x, Natural& y)
{
	Natural t;
	t.num = x.getNum() * y.getDenom() + x.getDenom() * y.getNum();
	t.denom = x.getDenom() * y.getDenom();
	t.reduce();/*
	if (!t.num || !t.denom)
		throw "Zero is not natural.\n";*/
	return t;
};
void operator +=(Natural& x, Natural& y)
{
	x = operator +(x, y);
};
Natural operator +(int x, Natural& y)
{
	Natural t(x);
	return operator+(t, y);
}
Natural operator +(Natural& y, int x) {
	return operator+(x, y);
}
void operator +=(Natural& x, int y) {
	x = operator+(x, y);
}

Natural operator -(Natural& x, Natural& y)
{
	Natural t;
	t.num = x.getNum() * y.getDenom() - x.getDenom() * y.getNum();
	t.denom = x.getDenom() * y.getDenom();
	t.reduce();/*
	if (!t.num || !t.denom)
		throw "Zero is not natural.\n";*/
	return t;
}
void operator -=(Natural& x, Natural& y)
{
	x = operator -(x, y);
}
Natural operator -(Natural& y, int x)
{
	Natural t(x);
	return operator-(y, t);
}
void operator -=(Natural& y, int x)
{
	y = operator-(y, x);
}

Natural operator *(Natural& x, Natural& y)
{
	Natural t;
	t.num = x.num * y.num;
	t.denom = x.denom * y.denom;
	t.reduce();
	return t;
}
void operator *=(Natural& x, Natural& y)
{
	x = operator*(x, y);
}
Natural operator *(int x, Natural& y)
{
	Natural t(x * y.num, y.denom);
	t.reduce();
	return t;
}
Natural operator *(Natural& y, int x)
{
	return operator*(x, y);
}
void operator *=(Natural& y, int x)
{
	y = operator*(y, x);
}

Natural operator /(Natural& x, Natural& y)
{
	Natural t = y.reversal();
	return operator*(x, t);
}
void operator /=(Natural& x, Natural& y)
{
	x = operator /(x, y);
}
Natural operator /(Natural& y, int x)
{
	if (!x)
		throw "Division by zero.\n";
	Natural t(y.num, y.denom * x);
	t.reduce();
	return t;
}
void operator /=(Natural& y, int x)
{
	y = operator /(y, x);
}

Natural operator ++(Natural& x, int)
{
	Natural t = x;
	x += 1;
	return t;
}
void operator ++(Natural& x)
{
	x += 1;
}
Natural operator --(Natural& x, int)
{
	Natural t = x;
	x -= 1;
	return t;
}
void operator --(Natural& x)
{
	x -= 1;
}

bool operator >(Natural& x, Natural& y)
{
	return ((x - y).num > 0) ? 1 : 0;
}
bool operator >(Natural& x, int y)
{
	Natural t(y);
	return operator>(x, t);
}
bool operator >=(Natural& x, Natural& y)
{
	if (operator>(x, y))
		return 1;
	return (x == y) ? 1 : 0;
}
bool operator >=(Natural& x, int y)
{
	Natural t(y);
	return operator>=(x, t);
}
bool operator <(Natural& x, Natural& y)
{
	return ((x - y).num < 0) ? 1 : 0;
}
bool operator <(Natural& x, int y)
{
	Natural t(y);
	return operator<(x, t);
}
bool operator <=(Natural& x, Natural& y)
{
	if (operator<(x, y))
		return 1;
	return (x == y) ? 1 : 0;
}
bool operator <=(Natural& x, int y)
{
	Natural t(y);
	return operator<=(x, t);
}

/*
https://google.github.io/styleguide/cppguide.html#Local_Variables
code style....
*/

