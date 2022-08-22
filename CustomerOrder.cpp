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
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds {


	size_t CustomerOrder::m_widthField = 1;
	Utilities ut2;
	CustomerOrder::CustomerOrder() {};

	CustomerOrder::CustomerOrder(const std::string str) {
		//Cornel B. | 1-Room Home Office             | Office Chair|Desk|Bookcase|Bookcase|Filing Cabinet
		Item** aux = nullptr;
		ut2.setFieldWidth(1);
		size_t pos = 0;
		bool more = true;
		std::string tkn = "|";
		if (more) m_name = ut2.extractToken(str, pos, more);
		if (more) m_product = ut2.extractToken(str, pos, more);
		if (m_cntItem == 0) {
			m_lstItem = new Item * [1];
			m_lstItem[m_cntItem] = new Item(ut2.extractToken(str, pos, more));
			m_cntItem++;
		}
		while (more) {
 			if (m_cntItem > 0) {
				aux = new Item * [m_cntItem + 1];
				for (size_t i = 0; i < m_cntItem; i++) {
					aux[i] = m_lstItem[i];
				}
				aux[m_cntItem] = new Item(ut2.extractToken(str, pos, more));
				delete[] m_lstItem;
				m_lstItem = aux;
				m_cntItem++;
			}
			
		}
		if(CustomerOrder::m_widthField < ut2.getFieldWidth()) CustomerOrder::m_widthField = ut2.getFieldWidth();
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& auxCo) {
		throw std::string("Copy Constructor not available");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& auxCo) noexcept {
		if (auxCo.m_lstItem != nullptr) {
			*this = std::move(auxCo);
		}
		else {
			m_lstItem = nullptr;
		}
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& auxCo) noexcept {
		if (this != &auxCo) {
			if (m_lstItem != 0) {
				for (size_t i = 0; i < m_cntItem; i++)
					delete m_lstItem[i];
				delete[] m_lstItem;
			}
			m_name = auxCo.m_name;
			m_cntItem = auxCo.m_cntItem;
			m_product = auxCo.m_product;
			m_widthField = auxCo.m_widthField;
			m_lstItem = auxCo.m_lstItem;
			auxCo.m_lstItem = nullptr;
		}
		else {
			m_lstItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		if (m_lstItem != 0) {
			for (size_t i = 0; i < m_cntItem; i++)
				delete m_lstItem[i];
			delete[] m_lstItem;
		}
	}

	bool CustomerOrder::isOrderFilled() const {
		bool res = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) res = false;
		}
		return res;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool res = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				res = false;
			}
		}
		return res;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool filled = true;
		bool outStock = false;
		bool match = false;
		size_t index = 0;

		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) { 
				match = true;
				if (station.getQuantity() > 0 && !m_lstItem[i]->m_isFilled) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;	
					filled = true; 
					index = i;
					i = m_cntItem; 
				}
				else filled = false;

				if (station.getQuantity() == 0 && !m_lstItem[index]->m_isFilled) {
					outStock = true;
					if (match && outStock) 
						os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
					}
				}
			}
		if (match && filled) 
			os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::setfill('0')  << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ');
			os.setf(std::ios::left);
			os << std::setw(m_widthField) << m_lstItem[i]->m_itemName << "   - ";
			os.unsetf(std::ios::left);
			if (isItemFilled(m_lstItem[i]->m_itemName)) os << "FILLED" << std::endl;
			else { os << "TO BE FILLED" << std::endl; }
		}
	}
}