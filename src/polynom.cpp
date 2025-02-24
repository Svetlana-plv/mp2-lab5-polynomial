#include"polynom.h"

Polynom::Polynom() {
	polynom.insert_front(Monom());
}

Polynom::Polynom(const Monom& m) {
	polynom.insert_front(m);
}

Polynom Polynom::operator+(Polynom& p) {
	Polynom tmp;

	(*this).erase_zero();
	p.erase_zero();

	List<Monom>::Iterator it = tmp.polynom.begin();
	List<Monom>::Iterator it1 = this->polynom.begin();
	List<Monom>::Iterator it2 = p.polynom.begin();

	while (it1 != polynom.end() && it2 != polynom.end()) {
		if (it1.value() < it2.value()) {
			tmp.add_monom_after(it1.value(), it);
			it1++;
		}
		else if (it1.value() > it2.value()) {
			tmp.add_monom_after(it2.value(), it);
			it2++;
		}
		else {
			if (it1.value().get_coef() + it2.value().get_coef()>EPS)
				tmp.add_monom_after( it1.value() + it2.value(), it);
			it1++;
			it2++;
		}
		it++;
	}

	// Define polinom that has the remaining monoms
	bool flag = true;
	if (it2 != polynom.end()) {
		flag = false;
	}

	// Add remaining monoms from this polinom
	if (flag) {
		while (it1 != polynom.end()) {
			tmp.polynom.insert_after(it1.value(), it);
			it1++;
			it++;
		}
	}

	// Add remaining monoms from other polinom
	else {
		while (it2 != polynom.end()) {
			tmp.polynom.insert_after(it2.value(), it);
			it2++;
			it++;
		}
	}

	tmp.erase_zero();
	return tmp;
}

Polynom Polynom::operator-(Polynom& p){

	(*this).erase_zero();
	p.erase_zero();


	Polynom tmp;

	List<Monom>::Iterator it = tmp.polynom.begin();
	List<Monom>::Iterator it1 = this->polynom.begin();
	List<Monom>::Iterator it2 = p.polynom.begin();

	while (it1 != polynom.end() && it2 != polynom.end()) {
		if (it1.value() < it2.value()) {
			tmp.add_monom_after(it1.value(), it);
			it1++;
		}
		else if (it1.value() > it2.value()) {
			tmp.add_monom_after(Monom(-it2.value().get_coef(), it2.value().get_deg()), it);
			it2++;
		}
		else {
			if (it1.value().get_coef() + it2.value().get_coef() > EPS)
				tmp.add_monom_after(it1.value() - it2.value(), it);
			it1++;
			it2++;
		}
		it++;
	}

	// Define polinom that has the remaining monoms
	bool flag = true;
	if (it2 != polynom.end()) {
		flag = false;
	}
	
	// Add remaining monoms from this polinom
	if (flag) {
		while (it1 != polynom.end()) {
			tmp.polynom.insert_after(it1.value(), it);
			it1++;
			it++;
		}
	}

	// Sub remaining monoms from other polinom
	else {
		while (it2 != polynom.end()) {
			tmp.polynom.insert_after(Monom(-it2.value().get_coef(), it2.value().get_deg()), it);
			it2++;
			it++;
		}
	}

	tmp.erase_zero();
	return tmp;
}






double Polynom::point(double x, double y, double z) {
	double result;
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
	while (it1 != polynom.end() && it1.value() < m) {
		it = it1;
		it1++;
	}
	if (it.value().get_deg() == m.get_deg())
		this->polynom.set_value(it.value() + m, it);
	else {
		if(it==it1) this->polynom.insert_front(m);
		else this->polynom.insert_after(m, it);
	}
}

void Polynom::add_monom_after(const Monom& m, List<Monom>::Iterator it) {
	if (polynom.empty()) {
		polynom.insert_front(m);
		return;
	}
	if (it.value().get_deg() == m.get_deg())
		it.value() += m;
	else {
		this->polynom.insert_after(m, it);
	}
}

void Polynom::erase_zero() {
	if (this->polynom.get_size() == 1) return;

	else {
		List<Monom>::Iterator it = this->polynom.begin();
		if (it.value().get_coef() < EPS) {
			this->polynom.erase_front();
		}
	}

	//else {
	//	for (List<Monom>::Iterator it = this->polynom.begin(); it != this->polynom.end(); it++) {
	//		if (it == this->polynom.begin() && it.value().get_coef() < EPS) {
	//			this->polynom.erase_front();
	//			continue;
	//		}
	//		//if (it.value().get_coef() < EPS) {
	//		//	this->polynom.erase_after(it);
	//		//}
	//	}
	//}
}