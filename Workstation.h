/*
Name: Tomonobu Christian Fukuhara Tengan
Seneca Student ID: 123475212
Seneca email: tcfukuhara-tengan@myseneca.ca
Date of completion: August 04, 2022
I confirm that I am the only author of this file and the content was created entirely by me.
Final Project - Milestone 3
*/

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <deque>
#include "CustomerOrder.h"

namespace sdds {

	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation = nullptr;
	public:
		Workstation(const std::string& str) : Station(str) {};
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
		Workstation& operator=(const Workstation& auxWs) = delete;
	};

}

#endif

