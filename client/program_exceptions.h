#ifndef PROGRAM_EXCEPTIONS_H
#define PROGRAM_EXCEPTIONS_H

#include <exception>


class FileDoesNotExistException : public std::exception {
	public:

		virtual const char* what() const noexcept {
			return "File doesn't exist.";
		}
};


#endif // PROGRAM_EXCEPTIONS_H
