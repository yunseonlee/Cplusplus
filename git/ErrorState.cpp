//yunseon lee
//048757140

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include"ErrorState.h"

// Starting namespace.
namespace ama {

 	ErrorState::ErrorState(const char* errorMessage) {
		this->MESSAGE = nullptr;
		*this = errorMessage;
	}
	

 	ErrorState::~ErrorState() {
		if (this->MESSAGE != nullptr) {
			delete[] this->MESSAGE;
		}
	}
	

 	ErrorState::operator bool() const {
		return this->message() == nullptr ? false : true;
	}

	
 	ErrorState& ErrorState::operator=(const char* pText) {
		if (this->MESSAGE != nullptr) {
			delete[] this->MESSAGE;
			this->MESSAGE = nullptr;
		}
		if (pText != nullptr && *pText != '\0') {
			int len = strlen(pText);
			this->MESSAGE = new(std::nothrow) char[len + 1];
			if (this->MESSAGE != nullptr) {
				strncpy(this->MESSAGE, pText, len);
				this->MESSAGE[len] = '\0';
			}
		}
		return *this;
	}
	

 	void ErrorState::message(const char* pText) {
		*this = pText;
	}

	
 	const char* ErrorState::message() const {
		return this->MESSAGE;
	}

	
 	std::ostream& operator<<(std::ostream& os, const ErrorState& error) {
		if (error) {
			os << error.message();
		}
		else {
			os << "";
		}
		return os;
	}
}