#ifndef STATUS_CODES_H
#define STATUS_CODES_H

#include <exception>


typedef enum {
	OK = 200,
	API_REQUEST_LIMIT_EXCEEDED = 204,
	FORBIDDEN = 403
} http_status_code_t;


class PublicAPIRequestRateExceededException : public std::exception {
	public:

		virtual const char* what() const throw() {
			return "Exceeded the public API request rate limit.";
		}
};


class ForbiddenException : public std::exception {
	public:

		virtual const char* what() const throw() {
			return "Attempt to perform calls to functions without having the required privileges.";
		}
};


#endif // STATUS_CODES_H
