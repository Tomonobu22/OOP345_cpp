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
#include "Workstation.h"

namespace sdds {

	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;


	void Workstation::fill(std::ostream& os) {
		if (m_orders.size() > 0) {
			m_orders[0].fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() {
		if (m_orders.size() > 0) {
			if (m_orders[0].isItemFilled(this->getItemName()) || this->getQuantity() == 0  ) {
				if (m_pNextStation != nullptr) {
					m_pNextStation->m_orders.push_back(std::move(m_orders.front()));
				}
				else {
					if (m_orders[0].isOrderFilled()) {
						g_completed.push_back(std::move(m_orders[0]));
					}
					else {
						g_incomplete.push_back(std::move(m_orders[0]));
					}
				}
				m_orders.pop_front();
				return true;
			}
		}
		return false;
	}

	void Workstation::setNextStation(Workstation* station) {
		if (station) {
			m_pNextStation = station;
		}
		else {
			m_pNextStation = nullptr;
		}
	}

	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const {
		os << this->getItemName() << " --> ";
		if (m_pNextStation != nullptr) {
			os << m_pNextStation->getItemName() << std::endl;
		}
		else {
			os << "End of Line" << std::endl;
		}

	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}