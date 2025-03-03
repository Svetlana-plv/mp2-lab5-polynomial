#pragma once
#include <iostream>
#include <string>
#include <vector>

class Parser {

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

	std::vector<std::pair< double, int>> snt_analysis(std::string str) {

		int status = 0;
		int count_point = 0;
		bool flag_num = true; // true - number, false - degree
		int flag_degree = 0; // x -> 1, y -> 2, z -> 3
		int operation = 1; // operation = 1 -> +, operation = -1 -> -
		int count_monoms = 0;
		std::string coefficient;
		std::vector<std::pair< double, int>> v;
		std::pair<double, int> pair;

		size_t sz = str.size();

		for (int i = 0; i < sz; i++) {
			switch (status)
			{
			case 0:
				count_point = 0;
				flag_num = true;
				flag_degree = 0;
				pair.first = 0;
				pair.second = 0;

				if (count_monoms != 0) {
					if (str[i] == '-') {
						status = 7;
						operation = -1;
					}
					else if (str[i] == '+') {
						status = 7;
						operation = 1;
					}
					else {
						std::string incorrect_symbol = "There must be an arithmmetic sign between the monoms!";
						throw incorrect_symbol;
					}
				}
				else {

					if ('1' <= str[i] && str[i] <= '9') {
						pair.first += str[i];
						status = 1;
					}

					else if (str[i] == '.') {
						count_point++;
						status = 2;
					}
					else if (str[i] == 'x') {
						flag_num = false;
						flag_degree = 1;
						status = 4;
					}
					else if (str[i] == '-') {
						status = 7;
						operation = -1;
					}
					else {
						std::string incorrect_symbol = "Incorrect symbol at index " + std::to_string(i) + "!";
						throw incorrect_symbol;
					}
				}
				break;
			case 1:
				if ('0' <= str[i] && str[i] <= '9') { 
					if (flag_num) { 
						coefficient += str[i];
						status = 1; 
					}
					else {
						std::string incorrect_symbol = "Degree can only be a single digit!";
						throw incorrect_symbol;
					}
				}
				else if (str[i] == '.') status = 2;
				else if (str[i] == 'x') status = 4;
				else if (str[i] == 'y') status = 5;
				else if (str[i] == 'z') status = 6;
				else {
					std::string incorrect_symbol = "Incorrect symbol at index " + std::to_string(i) + "!";
					throw incorrect_symbol;
				}
				break;
			case 2:
				count_point++;
				if (count_point == 1) {
					if ('0' <= str[i] && str[i] <= '9') status = 1;
					else if (str[i] == 'x') {
						status = 4;
					}
					else {
						std::string incorrect_symbol = "Incorrect symbol at index " + std::to_string(i) + "!";
						throw incorrect_symbol;
					}
				}
				else {
					std::string incorrect_symbol = "Incorrect number of point!";
					throw incorrect_symbol;
				}
				break;
			case 3:
				if ('0' <= str[i] && str[i] <= '9') { 
					if (flag_degree == 1) {
						pair.second += (int)str[i]*100;
						status = 0;
					}
					if (flag_degree == 2) {
						pair.second += (int)str[i] * 10;
						status = 0;
					}
					if (flag_degree == 3) {
						count_monoms++;
						pair.first = operation * std::stod(coefficient);
						pair.second += (int)str[i];
						v.push_back(pair);
						status = 0;
					}
					else status = 1;
				}
				else {
					std::string incorrect_symbol = "Incorrect symbol at index " + std::to_string(i) + "!";
					throw incorrect_symbol;
				}
				break;
			case 4:
				flag_num = false;
				flag_degree = 1;
				if (str[i]=='^') status = 3;
				else {
					std::string incorrect_symbol = "Incorrect symbol at index " + std::to_string(i) + "!";
					throw incorrect_symbol;
				}
				break;
			case 5:
				flag_degree = 2;
				if (str[i] == '^') status = 3;
				else {
					std::string incorrect_symbol = "Incorrect symbol at index " + std::to_string(i) + "!";
					throw incorrect_symbol;
				}
				break;
			case 6:
				flag_degree = 3;
				if (str[i] == '^') status = 3;
				else {
					std::string incorrect_symbol = "Incorrect symbol at index " + std::to_string(i) + "!";
					throw incorrect_symbol;
				}
				break;
			case 7:

				if (str[i] == '.') status = 2;
				else if ('1' <= str[i] && str[i] <= '9') status = 1;
				else if (str[i] < sz && str[i] == '0') {
					if (str[i + 1] == '.' || str[i] == 'x') status = 1;
					else {
						std::string incorrect_symbol = "Number can't start from zero!";
						throw incorrect_symbol;
					}
				}
				else if (str[i] == 'x') status = 4;
				else {
					std::string incorrect_symbol = "Incorrect symbol at index " + std::to_string(i) + "!";
					throw incorrect_symbol;
				}
				break;
			default:
				break;
			}
		}
		if (status == 2) {
			std::string incorrect_symbol = "Expression cannnot end with a point!";
			throw incorrect_symbol;
		}
		else if (status == 3) {
			std::string incorrect_symbol = "Expression cannnot end with a ^!";
			throw incorrect_symbol;
		}
		else if (status == 4 || status == 5 || status == 6) {
			std::string incorrect_symbol = "Expression cannnot end with a letter!";
			throw incorrect_symbol;
		}
		else if (status == 7) {
			std::string incorrect_symbol = "Expression cannnot end with a operation!";
			throw incorrect_symbol;
		}
		
		return v;
	}
};