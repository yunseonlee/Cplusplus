//yunseon lee
//048757140
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iomanip>
#include <cstring>
#include "Product.h"
#include "ErrorState.h"



using namespace std;

namespace ama {

	//  store the error message into ErrorState object.
	//protected
	void Product::name(const char* name) {
		if (name != nullptr) {	//If parameter name is not NULL

			if (m_name != nullptr) {	//If data member name is not NULL
				delete[] m_name;	//Deallocate Dynamic Allocated Memory
				m_name = nullptr;	//Set pointer to NULL
			}

			if (strlen(name) > max_length_name) {
				m_name = new char[max_length_name + 1];
				strncpy(m_name, name, max_length_name);
				if (m_name[strlen(name)] != '\0') m_name[strlen(name)] = '\0';
			}
			else {
				m_name = new char[strlen(name) + 1];
				strcpy(m_name, name);
				if (m_name[strlen(name)] != '\0') m_name[strlen(name)] = '\0';
			}
		}
	}




	const char* Product::name() const {
		if (m_name == nullptr || m_name[0] == '\0') return nullptr;
		else return m_name;
	}
	void Product::message(const char* pText) {
		this->errorState = pText;
	}


	// To check if the ErrorState attribute contains any attribute or not.
	bool Product::isClear() const {
		return this->errorState.message() == nullptr ? true : false;
	}

	//public member functions
	// The Zero/One argument constructor.
	Product::Product(const char type) : m_type(type) {
		strcpy(this->m_sku, "???");
		strcpy(this->m_unit, "???");
		this->m_name = nullptr;
		this->qty = 0;
		this->qtyNeed = 0;
		this->m_price = 0;
		this->m_status = true;
	}


	// constructor with 7 parameters to initialize the object of class.
	Product::Product(const char* SKU, const char* productName, const char* productUnit,
		double unitPrice, int qtyNeeded, int qty, bool taxable) : Product() {
		if (productName != nullptr || *productName != '\0') {
			int length = strlen(productName);
			this->m_name = new (std::nothrow) char[length + 1];
			if (this->m_name != nullptr) {
				strncpy(this->m_name, productName, length);
				this->m_name[length] = '\0';
				strncpy(this->m_sku, SKU, max_length_sku);
				this->m_sku[max_length_sku] = '\0';
				strncpy(this->m_unit, productUnit, max_length_unit);
				this->m_unit[max_length_unit] = '\0';
				this->m_price = unitPrice;
				this->qtyNeed = qtyNeeded;
				this->qty = qty;
				this->m_status = taxable;
			}
		}
	}


	//   copy constructor.
	Product::Product(const Product& rhs) : Product() {
		*this = rhs;
	}


	// The destructor.
	Product::~Product() {
		if (this->m_name != nullptr) {
			delete[] this->m_name;
		}
	}


	// The copy assignment operator.
	Product& Product::operator=(const Product& rhs) {
		if (rhs.isEmpty() == false) {
			if (this->m_name != nullptr) {
				delete[] this->m_name;
				this->m_name = nullptr;
			}
			int length = strlen(rhs.m_name);
			this->m_name = new (std::nothrow) char[length + 1];
			if (this->m_name != nullptr) {
				strncpy(this->m_name, rhs.m_name, length);
				this->m_name[length] = '\0';
				strncpy(this->m_sku, rhs.m_sku, max_length_sku);
				this->m_sku[max_length_sku] = '\0';
				strncpy(this->m_unit, rhs.m_unit, max_length_unit);
				this->m_unit[max_length_unit] = '\0';
				this->m_price = rhs.m_price;
				this->qtyNeed = rhs.qtyNeed;
				this->qty = rhs.qty;
				this->m_status = rhs.m_status;
			}
		}
		return *this;
	}


	// First check and then add the specified parameter to the quantity on hand.
	int Product::operator+=(int cnt) {
		if (cnt > 0) {
			if (this->isEmpty() == false) {
				this->qty += cnt;
			}
		}
		return this->qty;
	}


	// To check if the parameter specified is equal to the SKU for the current object.
	bool Product::operator==(const char* sku) const {
		return strcmp(this->m_sku, sku) == 0 ? true : false;
	}


	// To check if the SKU attribute of current object is greater than the parameter specified.
	bool Product::operator> (const char* sku) const {
		return strcmp(this->m_sku, sku) > 0 ? true : false;
	}


	// To check if the product name for the current object is greater than the name of the PRODUCT received as parameter.
	bool Product::operator>(const iProduct& other) const {

		return strcmp(m_name, other.name()) > 0 ? true : false;
	}


	// Returns the value of the attribute storing units of product available.
	int Product::qtyAvailable() const {
		return this->qty;
	}


	// Returns the value of attribute storing units of product needed.
	int Product::qtyNeeded() const {
		return this->qtyNeed;
	}


	// Returns the total cost of all availabe units of product, including tax.
	double Product::total_cost() const {
		return m_status ? this->m_price * this->qtyAvailable() * (1 + tax_rate) : this->m_price * this->qtyAvailable();
	}


	// To check if the object is in safe empty state or not.
	bool Product::isEmpty() const {
		return this->m_name == nullptr ? true : false;
	}


	// Reads data from stream and stores this data in the attributes.
	std::istream& Product::read(std::istream& in, bool interractive) {
		char sku[max_length_sku] = { '\0' };
		char name[max_length_name] = { '\0' };
		char unit[max_length_unit] = { '\0' };
		char yorn;
		bool taxable, flag = true;
		double price = 0;
		int qty = 0, qtyNeed = 0;
		if (interractive) {
			std::cout << std::right << std::setw(max_length_label) << "Sku: ";
			in >> sku;
			std::cout << std::setw(max_length_label) << "Name (no spaces): ";
			std::cin >> name;
			std::cout << std::setw(max_length_label) << "Unit: ";
			in >> unit;
			std::cout << std::setw(max_length_label) << "Taxed? (y/n): ";
			in >> yorn;
			if (yorn == 'y' || yorn == 'Y') {
				taxable = true;
			}
			else if (yorn == 'n' || yorn == 'N') {
				taxable = false;
			}
			else {
				in.setstate(std::ios::failbit);
				this->errorState.message("Only (Y)es or (N)o are acceptable!");
				flag = false;
			}
			if (flag) {
				std::cout << std::setw(max_length_label) << "Price: ";
				in >> price;
				if (price <= 0) {
					in.setstate(std::ios::failbit);
					this->errorState.message("Invalid Price Entry!");
					flag = false;
				}
			}
			if (flag) {						//notwork
				std::cout << std::setw(max_length_label) << "Quantity on hand: ";
				in >> qty;
				if (qty <= 0) {
					in.setstate(std::ios::failbit);
					this->errorState.message("Invalid Quantity Available Entry!");
					flag = false;
				}
			}
			if (flag && 0 < qty && qty <= 99999) {
				std::cout << std::setw(max_length_label) << "Quantity needed: " << std::left;
				in >> qtyNeed;
				if (qtyNeed <= 0) {
					in.setstate(std::ios::failbit);
					this->errorState.message("Invalid Quantity Needed Entry!");
					flag = false;
				}
				flag = false;
			}
		}
		else {
			in.getline(sku, max_length_sku, ',');
			in.getline(name, max_length_name, ',');
			in.getline(unit, max_length_unit, ',');
			in >> price;
			in.get();
			in >> taxable;
			in.get();
			in >> qty;
			in.get();
			in >> qtyNeed;
			if (price <= 0) {
				this->errorState.message("Invalid Price Entry!");
			}
			else if (taxable != true && taxable != false) {
				this->errorState.message("Only (Y)es or (N)o are acceptable!");
			}
			else if (qty < 0) {
				this->errorState.message("Invalid Quantity Available Entry!");
			}
			else if (qtyNeed <= 0) {
				this->errorState.message("Invalid Quantity Needed Entry!");
			}
		}
		if (!this->errorState) {
			*this = Product(sku, name, unit, price, qtyNeed, qty, taxable);
		}
		return in;
	}


	// Writes the content of the current instance in the stream received as the first parameter.
	std::ostream& Product::write(std::ostream& out, int writeMode) const {
		if (this->errorState) {
			out << this->errorState.message();
		}
		else if (!this->isEmpty()) {
			if (writeMode == write_condensed) {
				out << this->m_type << "," << this->m_sku << "," << this->m_name << ","
					<< this->m_unit << "," << std::fixed << std::setprecision(2) << this->m_price << ","
					<< this->m_status << "," << this->qtyAvailable() << "," << this->qtyNeeded();
			}
			else if (writeMode == write_table) {
				out << " " << std::right << std::setw(max_length_sku) << this->m_sku << " | ";
				if (strlen(this->m_name) > 16) {
					char tem[14] = { 0 };
					strncpy(tem, this->m_name, 13);
					out << std::left << std::setw(13) << tem << "... | ";
				}
				else {
					out << std::left << std::setw(16) << this->m_name << " | ";
				}
				out << std::left << std::setw(10) << this->m_unit << " | "
					<< std::right << std::setw(7) << std::fixed << std::setprecision(2) << this->m_price << " | "
					<< std::right << std::setw(3);
				if (this->m_status) {
					out << "yes";
				}
				else {
					out << "no";
				}
				out << " | " << std::right << std::setw(6) << this->qtyAvailable() << " | "
					<< std::right << std::setw(6) << this->qtyNeeded() << " |" << std::left;
			}
			else if (writeMode == write_human) {
				out << std::right << std::setw(max_length_label) << "Sku: " << this->m_sku << std::endl
					<< std::setw(max_length_label) << "Name: " << this->m_name << std::endl
					<< std::setw(max_length_label) << "Price: " << std::fixed << std::setprecision(2) << this->m_price << std::endl
					<< std::setw(max_length_label) << "Price after Tax: ";
				if (this->m_status) {
					out << this->m_price * 1.13;
				}
				else {
					out << this->m_price;
				}
				out << std::endl
					<< std::setw(max_length_label) << "Quantity Available: " << this->qtyAvailable() << " " << this->m_unit << std::endl
					<< std::setw(max_length_label) << "Quantity Needed: " << this->qtyNeeded() << " " << this->m_unit << std::endl;
			}
		}
		return out;
	}
}