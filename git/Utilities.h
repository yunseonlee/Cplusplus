//yunseon lee
//048757140


#pragma once

#ifndef AMA_UTILITIES_H
#define AMA_UTILITIES_H

#include<iostream>
#include"Product.h"
#include"Perishable.h"

namespace ama {

	double& operator+=(double&, const iProduct&);
	std::ostream& operator<<(std::ostream&, const iProduct&);
	std::istream& operator>>(std::istream&, iProduct&);
	iProduct* createInstance(char tag);

}

#endif
