
//yunseon lee
//048757140
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include "Date.h"

using namespace std;

namespace ama {


	// Sets the status of the date object to the value of the parameter. 

	void Date::status(int newStatus)
	{
		m_status = newStatus;
	}





	// Returns the number of days in a given month for a given year.

	int Date::mdays(int year, int mon) const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;

		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}





	//   Safe Empty State

	void Date::setEmpty() {
		m_year = 0;
		m_month = 0;
		m_date = 0;
		status(no_error);
	}




	//return true, if it's in safe empty state

	bool Date::isEmpty() const {
		return (m_year == 0 && m_month == 0 && m_date == 0);
	}




	// Default Constructor. set to empty
	 

	Date::Date() {
		setEmpty();
	}




	// Constructor with 3 arguments  
	Date::Date(int a_Year, int a_Month, int a_Day) {

		if (a_Year < min_year || a_Year > max_year) {
			setEmpty();
			status(error_year);
		}
		else if (a_Month < 1 || a_Month > 12) {
			setEmpty();
			status(error_mon);
		}
		else if (a_Day < 1 || a_Day > mdays(a_Year, a_Month)) {
			setEmpty();
			status(error_day);
		}
		else {
			m_year = a_Year;
			m_month = a_Month;
			m_date = a_Day;
			status(no_error);
		}
	}



	// returns an int  status of the current object.

	int Date::status() {
		return m_status;
	}





	//  resets the status of an object to no_error.  

	void Date::clearError() {
		status(no_error);
	}






	// returns true, if  valid date and not error mode.

	bool Date::isGood() const {
		//check range
		bool value = ((m_year >= min_year && m_year <= max_year)
			&& (m_month >= 1 && m_month <= 12)
			&& (m_date >= 1 && m_date <= mdays(m_year, m_month))
			&& (m_status == no_error));

		return value;

	}





	// Check vaild condition, after add days. 

	bool Date::valid_plus_Date(int days) {
		int maxday = mdays(m_year, m_month);
		int temp = m_date + days;

		bool value = true;
		if ( isEmpty() || !isGood() || temp > maxday || temp < 1) {
			status(error_invalid_operation);
			value = false;
		}
		return value;
	}





	//add the date 
	// check if it's valid
	Date& Date::operator+=(int days) {
		if (valid_plus_Date(days)) {    
			m_date += days;
		}
		return *this;
	}




	// prefix
	 // check if it's valid after add one day.

	Date& Date::operator++() {

		if (valid_plus_Date(1)) {   
			m_date += 1;
		}
		return *this;
	}




	// Add date 
 

	Date Date::operator+(int days) {

		Date temp = *this;

		if (temp.valid_plus_Date(days)) {   
			temp.m_date += days;
		}
		return temp;
	}




	//postfix
	// Return a copy(Temp) of the instance before upeate

	Date Date::operator++ (int) {

		Date temp = *this;
		if (valid_plus_Date(1)) {     
			m_date += 1;
		}
		return temp;
	}



 //



	bool Date::operator==(const Date& rhs) const {

		return ((m_year == rhs.m_year) && (m_month == rhs.m_month) && (m_date == rhs.m_date));

	}

	bool Date::operator!=(const Date& rhs) const {

		return ((m_year != rhs.m_year) || (m_month != rhs.m_month) || (m_date != rhs.m_date));

		

	}
	//operator<
	//one return statement is good code style
	bool Date::operator<(const Date& rhs) const {

		bool value = false;
		if (m_year < rhs.m_year) {
			value = true;
		}
		else if (m_month < rhs.m_month) {
			value = true;
		}
		else if (m_date < rhs.m_date) {
			value = true;
		}
		return value;
	}

	//operator>
	bool Date::operator>(const Date& rhs) const {

		return !(*this < rhs) && *this != rhs;
	}
	//operator<=
	bool Date::operator<=(const Date& rhs) const {

		return   *this < rhs || *this == rhs;
	}

	//operator>=
	bool Date::operator>=(const Date& rhs) const {

		return   *this > rhs || *this == rhs;
	}




	
	//read
	std::istream& Date::read(std::istream& is)
	{
		char symbol;

		is.clear();

		is >> m_year >> symbol >> m_month >> symbol >> m_date;

		int iMaxDay = mdays(m_year, m_month);
		status(no_error);

		if (is.fail())
		{
			setEmpty();
			status(error_input);
		}
		else if (min_year > m_year || m_year > max_year)
		{
			setEmpty();
			status(error_year);
		}
		else if (m_month < 1 || m_month > 12)
		{
			setEmpty();
			status(error_mon);
		}
		else if (m_date < 1 || m_date > iMaxDay)
		{
			setEmpty();
			status(error_day);
		}

		return is;
	}


	//write
	std::ostream& Date::write(std::ostream& os) const {

			os << std::setfill(' ')
			<< std::setfill('0') << std::setw(4) << m_year << '/'
			<< std::setfill('0') << std::right << std::setw(2) << m_month << '/'
			<< std::setfill('0') << std::right << std::setw(2) << m_date
			<< std::setfill(' ');

		return os;
	}





	istream& operator>> (istream& is, Date& d) {
		return d.read(is);

		 
	}


	ostream& operator<< (ostream& os, const Date& d) {
		return d.write(os);

		 
	}

}

