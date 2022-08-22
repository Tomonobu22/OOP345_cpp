/*
Name: Tomonobu Christian Fukuhara Tengan
Seneca Student ID: 123475212
Seneca email: tcfukuhara-tengan@myseneca.ca
Date of completion: August 03, 2022
I confirm that I am the only author of this file and the content was created entirely by me.
Final Project - Milestone 3
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "Utilities.h"

namespace sdds {
	size_t Utilities::m_widthField = 1;
	char Utilities::m_delimiter = ',';

	Utilities::Utilities() {
		m_widthField = 1;
	}

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}
	
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string tkn = "";
		int pos = str.find(m_delimiter, next_pos);
		int offset = 0;

		if (str[next_pos] == m_delimiter)
		{
			more = false;
			throw "Delimiter found at the next_pos position";
		}

		if (pos > 0 && pos > (int)next_pos) {
			tkn = str.substr(next_pos, pos - next_pos);
			if (tkn.find_first_not_of(" ") == 0) offset = 1;
			tkn = tkn.substr(tkn.find_first_not_of(" "), tkn.find_last_not_of(" ") + offset);
			next_pos = ++pos;
			more = true;
		}
		else {
			tkn = str.substr(next_pos, str.find('\n'));
			if (tkn.find_first_not_of(" ") == 0) offset = 1;
			tkn = tkn.substr(tkn.find_first_not_of(" "), tkn.find_last_not_of(" ") + offset);
			more = false;
		}

		if(m_widthField < tkn.length()) m_widthField = tkn.length();
		return tkn;
	}
	
	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}

}