#include"polynom.h"

Polynom::Polynom() {
	this->polynom.insert_front(Monom());
}

Polynom::Polynom(const Monom& m) {
	this->polynom.insert_front(m);
}

bool Polynom::operator==(const Polynom& p)const {

	List<Monom>::Iterator it1 = this->polynom.begin();
	List<Monom>::Iterator it2 = p.polynom.begin();

	while (it1 != this->polynom.end() && it2 != this->polynom.end()) {
		if (it1.value() != it2.value()) {
			return false;
		}
		it1++;
		it2++;
	}
	if (it1 == this->polynom.end() && it2 == this->polynom.end()) return true;
	return false;
}

bool Polynom::operator!=(const Polynom& p)const {

	return !((*this)==p);
}

Polynom Polynom::operator*(const double c)const {
	Monom m(c);
	return (*this) * m;
}

Polynom operator*(double c, const Polynom& p) {
	return p * c;
}

Polynom Polynom::operator+(const Monom& m)const {

	Polynom tmp = (*this);

	tmp.add_monom(m);

	return tmp;
}

Polynom Polynom::operator-(const Monom& m)const {

	Polynom tmp = (*this);

	tmp.add_monom(Monom(-m.get_coef(), m.get_deg()));

	return tmp;
}

Polynom Polynom::operator*(const Monom& m)const {

	Polynom tmp;

	List<Monom>::Iterator it = this->polynom.begin();

	while (it != this->polynom.end()) {
		tmp.add_monom(it.value() * m);
		it++;
	}
	
	return tmp;
}

Polynom Polynom::operator+(const Polynom& p)const {
	Polynom tmp;

	List<Monom>::Iterator it1 = this->polynom.begin();
	List<Monom>::Iterator it2 = p.polynom.begin();

	while (it1 != polynom.end() && it2 != polynom.end()) {
		if (it1.value() < it2.value()) {
			tmp.add_monom(it1.value());
			it1++;
		}
		else if (it1.value() > it2.value()) {
			tmp.add_monom(it2.value());
			it2++;
		}
		else {
			if (it1.value().get_coef() + it2.value().get_coef() > EPS)
				tmp.add_monom(it1.value() + it2.value());
			it1++;
			it2++;
		}
	}

	// Define polinom that has the remaining monoms
	bool flag = true;
	if (it2 != polynom.end()) {
		flag = false;
	}

	// Add remaining monoms from this polinom
	if (flag) {
		while (it1 != polynom.end()) {
			tmp.add_monom(it1.value());
			it1++;
		}
	}

	// Add remaining monoms from other polinom
	else {
		while (it2 != polynom.end()) {
			tmp.add_monom(it2.value());
			it2++;
		}
	}

	return tmp;
}

Polynom Polynom::operator-(const Polynom& p)const {
	if ((*this) == p) return Polynom();
	Polynom tmp;

	List<Monom>::Iterator it1 = this->polynom.begin();
	List<Monom>::Iterator it2 = p.polynom.begin();

	while (it1 != polynom.end() && it2 != polynom.end()) {
		if (it1.value() < it2.value()) {
			tmp.add_monom(it1.value());
			it1++;
		}
		else if (it1.value() > it2.value()) {
			tmp.add_monom(Monom(-it2.value().get_coef(), it2.value().get_deg()));
			it2++;
		}
		else {
			if (it1.value().get_coef() - it2.value().get_coef() > EPS)
				tmp.add_monom(it1.value() - it2.value());
			it1++;
			it2++;
		}
	}

	// Define polinom that has the remaining monoms
	bool flag = true;
	if (it2 != polynom.end()) {
		flag = false;
	}

	// Add remaining monoms from this polinom
	if (flag) {
		while (it1 != polynom.end()) {
			tmp.add_monom(it1.value());
			it1++;
		}
	}

	// Add remaining monoms from other polinom
	else {
		while (it2 != polynom.end()) {
			tmp.add_monom(Monom(-it2.value().get_coef(), it2.value().get_deg()));
			it2++;
		}
	}

	return tmp;
}

Polynom Polynom::operator*(const Polynom& p)const {
	Polynom tmp;

	if ((*this) == tmp || p == tmp) return tmp;

	for (List<Monom>::Iterator it1 = this->polynom.begin(); it1 != this->polynom.end(); it1++) {
		tmp = tmp + p * it1.value();
	}

	return tmp;
}

double Polynom::point(double x, double y, double z) {
	double result = 0;
	for (List<Monom>::Iterator it = polynom.begin(); it != polynom.end(); it++) {
		result += it->value.get_coef() * pow(x, it->value.deg_x()) * pow(y, it->value.deg_y()) * pow(z, it->value.deg_z());
	}
	return result;
}

void Polynom::print() {
	for (List<Monom>::Iterator it = polynom.begin(); it != polynom.end(); it++) {
		it.value().print();
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Polynom::add_monom(const Monom& m) {
	if (polynom.empty()) {
		polynom.insert_front(m);
		return;
	}
	List<Monom>::Iterator it = polynom.begin();
	List<Monom>::Iterator it1 = it;
	while (it1 != polynom.end() && it1.value() <= m) {
		it = it1;
		it1++;
	}
	if (it.value().get_deg() == m.get_deg()) {
		if (it.value().get_coef() + m.get_coef() > EPS) {
			this->polynom.set_value(it.value() + m, it);
		}
	}
	else {
		if(it==it1) this->polynom.insert_front(m);
		else this->polynom.insert_after(m, it);
	}

	(*this).erase_zero();
}

void Polynom::add_monom_after(const Monom& m, List<Monom>::Iterator it) {
	if (polynom.empty()) {
		polynom.insert_front(m);
		return;
	}
	if (it.value().get_deg() == m.get_deg())
		if(it.value().get_coef() + m.get_coef()>EPS)
			it.value() += m;
	else {
		this->polynom.insert_after(m, it);
	}

	(*this).erase_zero();
}

void Polynom::erase_zero() {
	if (this->polynom.get_size() == 1) return;

	else {
		List<Monom>::Iterator it = this->polynom.begin();
		if (it.value().get_coef() < EPS) {
			this->polynom.erase_front();
		}
	}
}