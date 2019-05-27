//yunseon lee
//048757140
#include <iostream>
#include <iomanip>
#include "Perishable.h"
using namespace std;
namespace ama {
	Perishable::Perishable() : Product('P') {}
	std::istream& Perishable::read(std::istream& in, bool interractive) {
		Product::read(in, interractive);
		if (interractive) {
			cout << setw(max_length_label) << right << "Expiry date (YYYY/MM/DD): ";
			in >> expiryDate;
			if (expiryDate.status() != no_error) {
				in.setstate(std::ios::failbit);
				if (expiryDate.status() == error_year)
					message("Invalid Year in Date Entry");
				else if (expiryDate.status() == error_mon)
					message("invalid Month in Date Entry");
				else if (expiryDate.status() == error_day)
					message("Invalid Day in Date Entry");
				else
					message("Invalid Date Entry");
			}
		}
		else {
			in.get();
			in >> expiryDate;
			in.ignore();
		}
		return in;
	}

	std::ostream& Perishable::write(std::ostream& out, int writeMode) const {
		Product::write(out, writeMode);
		if (expiryDate.isGood() && !isEmpty()) {
			if (writeMode == write_human) {
				out << setw(max_length_label) << right << "Expiry Date: " << expiryDate << endl;
			}
			else if (writeMode == write_table) {
				out << " " << expiryDate << " |";
			}
			else if (writeMode == write_condensed) {
				out << "," << expiryDate;
			}
		}
			return out;
	}
}