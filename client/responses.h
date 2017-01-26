#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>


typedef enum {
	ITEM_IS_STILL_IN_QUEUE = -2,
	ITEM_DOES_NOT_EXIST = 0,
	ITEM_IS_PRESENT = 1
} response_code_t;


class ItemDoesNotExistException : public std::exception {
	public:

		virtual const char* what() const throw() {
			return "Item you searched for was not present in VirusTotal's dataset.";
		}
};


class RequestStillInQueueException : public std::exception {
	public:

		virtual const char* what() const throw() {
			return "Requested item is still queued for analysis.";
		}
};


#endif // EXCEPTIONS_H
