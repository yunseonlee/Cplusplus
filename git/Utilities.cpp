//yunseon lee
//048757140


#include<iostream>
#include"Utilities.h"
#include "Product.h"



namespace ama {
	// Adds the total cost of the product into the first parameter and returns the result.
	double & operator+=(double& total, const iProduct& prod)
	{
		return total += prod.total_cost();
	}

	
	// Writes the first parameter, in a human readable format, the content of the second parameter.
	std::ostream & operator<<(std::ostream& out, const iProduct& prod)
	{
		prod.write(out, write_human);
		return out;
	}

	
	// Reads from the first parameter a product in interactive mode.
	std::istream & operator>>(std::istream& in, iProduct& prod)
	{
		prod.read(in, true);
		return in;
	}
	iProduct * createInstance(char tag)
	{
		iProduct* tptr = nullptr;
		if (tag == 'N' || tag == 'n') {
		tptr = new Product();
		}
		else if (tag == 'P' || tag == 'p') {
			tptr = new Perishable();
		}
		return tptr;
		
	}
}

