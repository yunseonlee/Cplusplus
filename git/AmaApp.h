//yunseon lee
//048757140
#ifndef AMA_AMAAPP_H
#define AMA_AMAAPP_H
#include "iProduct.h"
#include "Utilities.h"

namespace ama {
	class AmaApp {

		char m_filename[256];
		iProduct* m_products[100];
		int m_noOfProducts;

		void loadProductRecords();
		void saveProductRecords() const;
		void listProducts() const;
		iProduct* find(const char* sku) const;
		void addQty(iProduct* product);
		void addProduct(char tag);		

	public: 
		AmaApp(const char* filename);
		AmaApp(const AmaApp& other) = delete;
		AmaApp& operator=(const AmaApp& other) = delete;
		~AmaApp();
		int run();
		void pause() const;
		int menu() const;

	};

}
#endif // !AMA_AMAAPP_H

