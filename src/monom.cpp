#include <iostream>
#include "polynom.h"

Monom::Monom() : coef(0), deg(0) {};

Monom::Monom(double cf, size_t dg): coef(cf), deg(dg) {};

Monom Monom::operator+(const Monom& m)const {
	if (this->deg != m.deg) throw std::logic_error("Can't add monomials because degrees of the monomials don't match!");
	Monom tmp;
	tmp.coef = this->coef + m.coef;
	tmp.deg = this->deg;
	return tmp;
}

Monom Monom::operator-(const Monom& m)const {
	if (this->deg != m.deg) throw std::logic_error("Can't sub monomials because degrees of the monomials don't match!");
	Monom tmp;
	tmp.coef = this->coef - m.coef;
	tmp.deg = this->deg;
	return tmp;
}

Monom Monom::operator*(const Monom& m)const {
	if (this->deg_x() + m.deg_x() > 9 || this->deg_y() + m.deg_y() > 9 || this->deg_z() + m.deg_z() > 9) 
		throw std::logic_error("Can't mul monomials because degree more then 9!");
	Monom tmp;
	tmp.coef = this->coef * m.coef;
	tmp.deg = this->deg + m.deg;
	return tmp;
}

Monom Monom::operator*(double c)const {
	Monom tmp = *this;
	tmp.coef = this->coef * c;
	return tmp;
}


size_t Monom::deg_x()const {
	return this->deg / 100;
}

size_t Monom::deg_y()const {
	return this->deg / 10 % 10;
}
 
size_t Monom::deg_z()const {
	return this->deg % 10;
}

double Monom::point(double x, double y, double z) {
	double result = coef * pow(x, deg_x()) * pow(y, deg_y()) * pow(z, deg_z());
	return result;
}