/*
Name: Tomonobu Christian Fukuhara Tengan
Seneca Student ID: 123475212
Seneca email: tcfukuhara-tengan@myseneca.ca
Date of completion: August 04, 2022
I confirm that I am the only author of this file and the content was created entirely by me.
Final Project - Milestone 3
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
	Utilities ut;
	unsigned Station::id_generator = 1;
	size_t Station::m_widthField = 0;

	Station::Station(const std::string& str) {
		//single record (one line)
		//Armchair,    654321,  10,  Upholstered Wing Chair
		ut.setFieldWidth(1);
		size_t pos = 0;
		bool more = true;
		std::string tkn = "";
		id = id_generator++;
		if (more) name = ut.extractToken(str, pos, more);
		if (more) serialNumber = stoi(ut.extractToken(str, pos, more));
		if (more) stock = stoi(ut.extractToken(str, pos, more));
		if (Station::m_widthField < ut.getFieldWidth()) Station::m_widthField = ut.getFieldWidth();
		if (more) description = ut.extractToken(str, pos, more);

	}

	const std::string& Station::getItemName() const {
		return name;
	}

	size_t Station::getNextSerialNumber() {
		return serialNumber++;
	}

	size_t Station::getQuantity() const {
		return stock;
	}

	void Station::updateQuantity() {
		if (stock > 0) stock--;
	}

	void Station::display(std::ostream& os, bool full) const {
		// ID | NAME | SERIAL | QUANTITY | DESCRIPTION
		// 001 | Armchair        | 654321 |   10 | Upholstered Wing Chair
		os << std::setw(3) << std::setfill('0') << id << " | " << std::setfill(' ');
		os.setf(std::ios::left);
		os << std::setw(m_widthField) << name << "  | ";
		os.unsetf(std::ios::left);
		os << std::setw(6) << std::setfill('0') << serialNumber << " | " << std::setfill(' ');

		if(full) {
			os.width(4);
			os << stock << " | ";
			os << description;
		}

		os << std::endl;
	}


}