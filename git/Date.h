
//yunseon lee
//048757140


#ifndef AMA_DATE_H
#define AMA_DATE_H

#include <iostream>

namespace ama {

	const int min_year = 2019;
	const int max_year = 2028;

	const int no_error = 0;
	const int error_year = 1;
	const int error_mon = 2;
	const int error_day = 3;
	const int error_invalid_operation = 4;
	const int error_input = 5;


	class Date {
	private:
		int m_year;  
		int m_month; //an integer  value between 1 and 12.
		int m_date; // int mdays (int year, int month) 
		int m_status;   //  no_error or one of the error_* 

		void status(int);  // sets the status of the date object 
		int mdays(int, int) const; // returns the number of days in a given month for a given year

		void setEmpty();
		bool isEmpty() const;
		bool valid_plus_Date(int);


	public:
		Date();
		Date(int, int, int);  
		int status();
		void clearError();
		bool isGood() const;

		Date& operator+=(int days);
		Date& operator++();
		Date operator++(int);
		Date operator+(int days);

		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;

		std::istream& read(std::istream&);
		std::ostream& write(std::ostream& os) const;

	};

	std::ostream& operator<< (std::ostream&, const Date&);
	std::istream& operator>> (std::istream&, Date&);


}

#endif




#pragma once
