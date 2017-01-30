#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>


typedef enum {
	ITEM_IS_STILL_IN_QUEUE = -2,
	ITEM_DOES_NOT_EXIST = 0,
	ITEM_IS_PRESENT = 1
} response_code_t;


class ResponseException : public std::exception {
	protected:

		std::string _message{};

	public:

		explicit ResponseException(const char* message) :
			_message{message} {}

		explicit ResponseException(const std::string& message) :
			_message{message} {}

		virtual ~ResponseException() = default;
};


class RequestStillInQueueException : public ResponseException {
	public:

		explicit RequestStillInQueueException(const char* message) :
			ResponseException{message} {}

		explicit RequestStillInQueueException(const std::string& message) :
			ResponseException{message} {}

		virtual const char* what() const noexcept {
			return _message.c_str();
		}
};


class ItemDoesNotExistException : public ResponseException {
	public:

		explicit ItemDoesNotExistException(const char* message) :
			ResponseException{message} {}

		explicit ItemDoesNotExistException(const std::string& message) :
			ResponseException{message} {}

		virtual const char* what() const noexcept {
			if (_message.empty()) {
				return "Invalid sha256 key.";
			}

			return _message.c_str();
		}
};


class UnknownResponseCodeException : public std::exception {
	public:

		virtual const char* what() const noexcept {
			return "Unknown response code. Please contact the administration for more information.";
		}
};


#endif // EXCEPTIONS_H
