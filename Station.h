/*
Name: Tomonobu Christian Fukuhara Tengan
Seneca Student ID: 123475212
Seneca email: tcfukuhara-tengan@myseneca.ca
Date of completion: August 04, 2022
I confirm that I am the only author of this file and the content was created entirely by me.
Final Project - Milestone 3
*/

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

namespace sdds {

	class Station {
		int id{};
		std::string name{};
		std::string description{};
		unsigned int serialNumber{};
		unsigned int stock{};
		static unsigned id_generator;
		static size_t m_widthField;
	public:
		Station(const std::string& str); 
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};

}

#endif
