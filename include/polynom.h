#include "list.h"

class Polynom;

class Monom {

private:

	double coef = 0; // coefficient

	size_t deg = 0; // degrees of xyz

	// degree of x = deg / 100
	// degree of y = deg / 10 % 10
	// degree of z = deg % 10

public:

	Monom();
	Monom(double cf, size_t dg = 0);

	Monom operator+(const Monom& m)const;
	Monom operator-(const Monom& m)const;
	Monom operator*(double c)const;
	Monom operator*(const Monom& m)const;
	Polynom operator*(const Polynom& p)const;


	size_t deg_x()const;
	size_t deg_y()const;
	size_t deg_z()const;

	double point(double x, double y, double z);
};


class Polynom {
private: 

	List<Monom> polynom;

public:

	Polynom();
	Polynom(const Monom&);

	~Polynom() { polynom.clear(); }
};