#ifndef PROGRAM_EXCEPTIONS_H
#define PROGRAM_EXCEPTIONS_H

#include <exception>


class FileDoesNotExistException : public std::exception {
	public:

		virtual const char* what() const noexcept {
			return "File doesn't exist.";
		}
};


class InvalidFilePathException : public std::exception {
	public:

		virtual const char* what() const noexcept {
			return "Wrong file path format.";
		}
};


class InvalidUrlNameException : public std::exception {
	public:

		virtual const char* what() const noexcept {
			return "Wrong url name format.";
		}
};


class InvalidDomainNameException : public std::exception {
	public:

		virtual const char* what() const noexcept {
			return "Wrong domain name format.";
		}
};


class InvalidIpAddressException : public std::exception {
	public:

		virtual const char* what() const noexcept {
			return "Wrong ip-address format.";
		}
};


#endif // PROGRAM_EXCEPTIONS_H
