/*
Name: Tomonobu Christian Fukuhara Tengan
Seneca Student ID: 123475212
Seneca email: tcfukuhara-tengan@myseneca.ca
Date of completion: August 03, 2022
I confirm that I am the only author of this file and the content was created entirely by me.
Final Project - Milestone 3
*/

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

namespace sdds {

	class Utilities {
		static char m_delimiter;
		static size_t m_widthField;
	public:
		Utilities();
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};

}

#endif
