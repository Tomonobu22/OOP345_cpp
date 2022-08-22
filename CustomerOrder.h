/*
Name: Tomonobu Christian Fukuhara Tengan
Seneca Student ID: 123475212
Seneca email: tcfukuhara-tengan@myseneca.ca
Date of completion: August 04, 2022
I confirm that I am the only author of this file and the content was created entirely by me.
Final Project - Milestone 3
*/

#ifndef SDDS_CUSTOMER_ORDER_H
#define SDDS_CUSTOMER_ORDER_H

namespace sdds {
	
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder {
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{ 0 };
		Item** m_lstItem{nullptr};
		static size_t m_widthField;
	public:
		CustomerOrder();
		CustomerOrder(const std::string str);
		CustomerOrder(const CustomerOrder& auxCo);
		CustomerOrder& operator=(const CustomerOrder& auxCo) = delete;
		CustomerOrder(CustomerOrder&& auxCo) noexcept;
		CustomerOrder& operator=(CustomerOrder&& auxCo) noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif
