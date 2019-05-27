//yunseon lee
//048757140
#pragma once
#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H
#include <iostream>
#include "Product.h"
#include "Date.h"
namespace ama {

	class Perishable :public Product{
		Date expiryDate;

	public:
		Perishable();
		std::istream& read(std::istream& in, bool interractive);
		std::ostream& write(std::ostream& out, int writeMode) const;



	};

}
#endif // !AMA_PERISHABLE_H
