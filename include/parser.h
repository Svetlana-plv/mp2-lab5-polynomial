#pragma once
#include <iostream>
#include <string>

class Parser {
private:
	enum termtype {
		COEFFICIENT,
		OPERATION,
		DEG_X,
		DEG_Y,
		DEG_Z,
		NONTYPE
	};

	class Term {
	public:
		std::string term;
		termtype type;
		Term() :term(""), type(NONTYPE) {}
		Term(std::string term_, termtype type_) : term(term_), type(type_) {}
	};

public:

	void lex_analysis(std::string string) {
		string.erase(remove_if(string.begin(), string.end(), ::isspace), string.end());

		if (string == "") {
			std::string incorrect_symbol = "Cannot process empty expression!";
			throw incorrect_symbol;
		}

		for (int i = 0; i < string.size(); i++) {

			char cur = string[i];

			// check if every symbol is a letter, number or operation sign
			bool flage = false;
			flage |= ('0' <= cur && cur <= '9');
			flage |= ('x' <= cur && cur <= 'z');
			flage |= cur == '+';
			flage |= cur == '-';
			flage |= cur == '^';
			flage |= cur == '.';
			if (!flage) {
				std::string incorrect_symbol = "Invalid symbol at index ";
				incorrect_symbol += std::to_string(i);
				throw incorrect_symbol;
			}
		}
	}

	void snt_analysis(std::string string) {

		for (int i = 0; i < string.size(); i++) {

			char cur = string[i];
			std::string coef = "";

			if (cur==) {

			}

			while ('0' <= cur && cur <= '9') {
				coef.append(cur);
				i++;
			}
			
			if (cur=='.') {
				coef.append(cur);
			}

			while ('0' <= cur && cur <= '9') {
				coef.append(cur);
				i++;
			}
		}
	}
};