//yunseon lee
//048757140

#pragma once
#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H
#include<iostream>

namespace ama {
	class ErrorState {
		char* MESSAGE;

	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& other) = delete;
		ErrorState& operator=(const ErrorState& other) = delete;
		~ErrorState();
		operator bool() const;
		ErrorState& operator=(const char* pText);
		void message(const char* pText);
		const char* message() const;
	};
	std::ostream& operator<<(std::ostream&, const ErrorState&);
}


#endif

