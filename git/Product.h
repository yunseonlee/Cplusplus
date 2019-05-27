//yunseon lee
//048757140

#pragma once

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

#include<iostream>
#include"ErrorState.h"
#include "iProduct.h"

namespace ama {
	

	class Product : virtual public iProduct {
		char m_type;
		char m_sku[max_length_sku];
		char m_unit[max_length_unit];
		int qty;
		int qtyNeed;
		double m_price;
		bool m_status;
		char* m_name;
		ErrorState errorState;

	protected:
		//char m_name[max_length_name];
		void message(const char*);
		bool isClear() const;
		void name(const char* name);
		const char* name() const;

	public:
		Product(char type = 'N');
		Product(const char* sku, const char* name, const char* unit, double price = 0, int qtyneed = 0, int qtyhand = 0, bool status = true);
		
		Product(const Product&);
		Product& operator=(const Product&);
		~Product();

		int operator+=(int);
		bool operator==(const char*) const;
		bool operator> (const char*) const;
		//bool operator> (const Product&) const; update
		 bool operator>(const iProduct& other) const;
		int qtyAvailable() const;
		int qtyNeeded() const;
		double total_cost() const;
		bool isEmpty() const;

		std::istream& read(std::istream& in, bool interractive);
		std::ostream& write(std::ostream& out, int writeMode) const;

	};
}

#endif

