//yunseon lee
//048757140
#define _CRT_SECURE_NO_WARNINGS
#ifndef IPRODUCT_H
#define IPRODUCT_H
#pragma once
#include <iostream>

namespace ama {
	const int max_length_label = 30;
	const int max_length_sku = 7;
	const int max_length_name = 75;
	const int max_length_unit = 10;
	const int write_condensed = 0;
	const int write_table = 1;
	const int write_human = 2;
	const double tax_rate = 0.13;

	class iProduct  {
	public:
	//pure virtual functions
		virtual std::ostream& write(std::ostream& os, int writeMode) const = 0;
		virtual std::istream& read(std::istream& is, bool interractive) = 0;
		virtual bool operator==(const char* sky) const = 0;
		virtual double total_cost() const = 0;
		virtual int qtyNeeded() const = 0;
		virtual int qtyAvailable() const = 0;

		virtual const char* name() const = 0;

		virtual int operator+=(int qty) = 0;
		virtual bool operator>(const iProduct& other) const = 0;
		virtual ~iProduct() {};


		 


	};



}
#endif 
