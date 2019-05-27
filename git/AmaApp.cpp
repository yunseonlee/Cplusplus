//yunseon lee
//048757140
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "AmaApp.h"

using namespace std;

namespace ama {
	// custom constructor that sets the members to a safe empty state, copies the filename, and loads the records from the file.
	AmaApp::AmaApp(const char* filename)
	{	
		m_filename[0] = '\0';
		for (int i = 0; i < 100; i++)
			m_products[i] = nullptr; 		
		m_noOfProducts = 0;		

		if (filename != nullptr)
		{
			strcpy(m_filename, filename);
			loadProductRecords();
		}
	}

	//destructor deallocates all dynamic instances stored in the m_products array
	AmaApp::~AmaApp()
	{
		for (int i = 0; i < 100; i++)
		{
			if (m_products[i] != nullptr)
			{
				delete m_products[i];
			}
		}
	}

	//A query that waits for the user to hit enter. 	
	void AmaApp::pause() const
	{
		cout << "Press Enter to continue..." << endl;
		cin.ignore();		
	}

	//This function displays a menu and waits for the user to select an option.	
	int AmaApp::menu() const
	{
		int choice;
		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "--------------------------------------" << endl;
		cout << "1- List products" << endl;
		cout << "2- Search product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to product quantity" << endl;
		cout << "6- Delete product" << endl;
		cout << "7- Sort products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";		
		cin >> choice;
		if (!cin)
		{
			cin.clear();
			choice = -1;
		}	
		cin.ignore(1024, '\n');

		return choice;
	}

	//Opens the data file for reading, but first prepares the array where they will be stored. If there is no file, a new file is created.
	void AmaApp::loadProductRecords() 
	{
		int j = 0;
		char tag;
		for (int i = 0; i < 100; i++)
		{
			if (m_products[i] != nullptr)
			{
				delete m_products[i];
			}
		}
				
		fstream fin(m_filename, ios::in);				
		if (fin)
		{	//hello everybody		
			do {			
				fin >> tag;
				if (fin)
				{					
					iProduct* p = createInstance(tag);					
					if (p != nullptr)
					{						
						m_products[j] = p;						
						fin.get();	//skip the comma					
						p->read(fin, false);						
						j++;
					}
				}
			} while (fin);
			m_noOfProducts = j;			
			fin.close();
		}		
		else
		{
			fstream fout(m_filename, ios::out);
			fout.close();
		}

	}

	//stores the products in a file
	void AmaApp::saveProductRecords() const
	{
		fstream fout(m_filename, ios::out);
		if (fout)
		{
			for (int i = 0; i < m_noOfProducts; i++)
			{
				if (m_products[i] != nullptr)
				{
					m_products[i]->write(fout, ama::write_condensed);
					fout << endl;
				}
			}
			fout.close();
		}
	}

	//generates an updated list of products in table format
	void AmaApp::listProducts() const 
	{
		double totalCost = 0;
		
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |" << endl;
		cout << "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << endl;
				
		for (int i = 0; i < m_noOfProducts; i++)
		{
			if (m_products[i] != nullptr)
			{		
				cout << "|" << setw(4)<<right << (i + 1) << " |";
				m_products[i]->write(cout, write_table);
				cout << endl;				
				totalCost += *m_products[i];
			}
		}
		
		std::cout << "------------------------------------------------------------------------------------------------" << endl;
		std::cout << "|                                                      Total cost of support ($): | ";
		std::cout << setw(10) << right << setprecision(2) << totalCost << " |" << endl;
		std::cout << "------------------------------------------------------------------------------------------------" << endl;

	}
	
	//finds a product based on the sku
	iProduct* AmaApp::find(const char* sku) const
	{
		iProduct *p = nullptr;
				
		for (int i = 0; i < m_noOfProducts; i++)
		{
			if (*m_products[i] == sku)
			{
				p = m_products[i];
			}
		}

		return p;
	}

	//adds to the inventory based on user input
	void AmaApp::addQty(iProduct* product) 
	{
		int newInventory, excessAmount;
				
		product->write(cout, write_human);
		cout << endl << endl;
				
		cout << "Please enter the number of purchased items: ";
		cin >> newInventory;
		
		if (!cin)
		{			
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "Invalid quantity value!" << std::endl;
		}		
		else
		{			
			if ((product->qtyNeeded() - product->qtyAvailable()) >= newInventory)
			{				
				*product += newInventory;
			}			
			else
			{
				excessAmount = newInventory - (product->qtyNeeded() - product->qtyAvailable());
				cout << "Too many items; only " << (product->qtyNeeded() - product->qtyAvailable());
				cout << " is needed. Please return the extra " << excessAmount << " items." << endl;
				*product += (product->qtyNeeded() - product->qtyAvailable());
				
				saveProductRecords();
			}
			cout << endl;
			cout << "Updated!" << endl;
			cin.ignore(1024, '\n'); 
		}

	}

	//adds a new iproduct to the end of the array
	void AmaApp::addProduct(char tag) 
	{		
		iProduct* p = createInstance(tag);
		
		if (p != nullptr)
		{					
			if (!p->read(cin, true))
			{			
				cin.clear();
				cin.ignore(256, '\n');			
				cout << endl;
				p->write(cout, ama::write_condensed);
				cout << endl << endl;
			}			
			else
			{				
				m_products[m_noOfProducts] = p;
				m_noOfProducts++;				
				saveProductRecords();
				std::cout << std::endl << "Success!" << std::endl << std::endl;
			}
		}
	}


	//run the menu and execute the choices based on user input
	int AmaApp::run()
	{
		int choice = 0;
		iProduct* p = nullptr;
		char sku[max_length_sku + 1];	

		do {
			choice = menu();
			switch (choice)
			{				
			case 1:		//list	products
				listProducts();
				cout << endl;
				pause();
				break;

				
			case 2:		//search products				
				cout << "Please enter the product SKU: ";
				cin.getline(sku, max_length_sku, '\n');
				cout << endl;				
				p = find(sku);				
				if (p != nullptr)
				{
					p->write(cout, write_human);
					cout << endl;
				}			
				else
				{
					cout << "No such product!" << endl;
				}				
				pause();
				break;
				
			case 3:		//add non-perishable product				
				addProduct('N');
				loadProductRecords();
				break;
				
			case 4:		//add perishable product				
				addProduct('P');
				loadProductRecords();
				break;

			case 5:		//add to product quantity				
				cout << "Please enter the product SKU: ";
				cin.getline(sku, max_length_sku, '\n');
				cout << endl;				
				p = find(sku);				
				if (p != nullptr)
				{
					addQty(p);
				}				
				else
				{
					cout << "No such product!" << endl;
				}				
				std::cout << std::endl;
				break;				
				
			case 0:		//exit				
				std::cout << "Goodbye!" << std::endl;
				break;

			default:	//invalid menu selection				
				cout << "~~~Invalid selection, try again!~~~" << endl;				
				pause();
				break;

			} 

		} while (choice != 0);

		
		return 0;
	}

}
	

		