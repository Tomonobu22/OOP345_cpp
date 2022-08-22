/*
Name: Tomonobu Christian Fukuhara Tengan
Seneca Student ID: 123475212
Seneca email: tcfukuhara-tengan@myseneca.ca
Date of completion: August 04, 2022
I confirm that I am the only author of this file and the content was created entirely by me.
Final Project - Milestone 3
*/

#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <functional>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "Station.h"
#include "Workstation.h"
#include "CustomerOrder.h"
#include "LineManager.h"

namespace sdds {

	std::string removeBlankSpace(std::string aux) {
		int offset = 0;
		size_t first, last;
		first = aux.find_first_not_of(" ");
		last = aux.find_last_not_of(" ");
		if (first == 0) offset = 1;
		return aux.substr(first, last - first + offset);
	}

	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		std::ifstream f(file);
		if (!f)
			throw std::string("Unable to open [") + file + "] file.";

		size_t cnt = 0;
		std::string record;

		while (!f.eof())
		{
			std::getline(f, record);
			std::string tkn = "";
			size_t pos = record.find('|');

			if (pos > 0) tkn = record.substr(0, pos);
			else tkn = record.substr(0, record.find('\n'));

			tkn = removeBlankSpace(tkn);
			m_activeLine.push_back(*std::find_if(stations.begin(), stations.end(), [=](const Workstation* w) {return w->getItemName() == tkn; }));
			//m_activeLine.push_back(new Workstation(tkn));
			cnt++;
		}

		f.seekg(0, std::ios_base::beg);
		size_t reRead = 0;
		while (!f.eof())
		{
			std::getline(f, record);
			std::string tkn = "";
			size_t pos = record.find('|');
			if (pos > 0 && pos < record.length()) {
				tkn = record.substr(++pos, record.find('\n'));
				tkn = removeBlankSpace(tkn);
				std::vector<Workstation*>::iterator it = std::find_if(m_activeLine.begin(), m_activeLine.end(), [=](const Workstation* w) {return w->getItemName() == tkn; });
				m_activeLine[reRead]->setNextStation(*it);
			}
			else {
				m_activeLine[reRead]->setNextStation(nullptr);
			}

			reRead++;
		}

		m_cntCustomerOrder = cnt;

		//Get the first station
		size_t counter = 0;
		std::string aux = "";
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			if (ws->getNextStation() == nullptr) {
				aux = ws->getItemName();
				counter++;
			}
		});
		while (counter < m_cntCustomerOrder) {
			std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
				if (ws->getNextStation() != nullptr) {
					if (ws->getNextStation()->getItemName() == aux) {
						aux = ws->getItemName();
						counter++;
						if (counter == m_cntCustomerOrder) m_firstStation = ws;
					}
				}
			});
		}

	}

	void LineManager::reorderStations() {
		size_t counter = 0;
		std::string aux = "";
		std::vector<Workstation*> sorted;

		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			if (ws->getNextStation() == nullptr){
				sorted.push_back(ws);
				aux = ws->getItemName();
				counter++;
			}
		});

		while (counter < m_cntCustomerOrder) {
			std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
				if (ws->getNextStation() != nullptr) {
					if (ws->getNextStation()->getItemName() == aux) {
						sorted.push_back(ws);
						aux = ws->getItemName();
						counter++;
					}
				}
			});
		}
		std::reverse_copy(sorted.begin(), sorted.end(), m_activeLine.begin());
		sorted.clear();
	}

	bool LineManager::run(std::ostream& os) {
		static int itNum = 1;
		static size_t a = 1;
		size_t aux = 0;

		std::cout << "Line Manager Iteration: " << itNum << std::endl;
		if (g_pending.size() > 0) {
			m_firstStation->operator+=(std::move(g_pending[0]));
			g_pending.pop_front();
		}
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			aux = ws->getQuantity();
			ws->fill(os);
		});
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			ws->attemptToMoveOrder();
		});

		if (a < m_cntCustomerOrder - 1) a++;
		itNum++;

		if (g_incomplete.size() + g_completed.size() == 5) return true;

		else return false;
	}

	void LineManager::display(std::ostream& os) const {
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			ws->display(os);
		});
	}
}