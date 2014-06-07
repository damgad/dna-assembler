#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

using std::exception;
using std::string;

namespace dnasm {
    class AsmException : public exception {
    public:
	    AsmException (const string message) : message_(message) {}
        ~AsmException() throw() {}
        const string getMessage() const {
            return message_;
        }
    private:
	    const string message_;
    };


    class FileNotFoundException : public AsmException {
    public:
	    FileNotFoundException(const string message) : AsmException(message) {}
	    ~FileNotFoundException() throw () {}
    };

    class WrongCallException : public AsmException {
    public:
	    WrongCallException(const string message) : AsmException(message) {}
	    ~WrongCallException() throw () {}
    };
  
    class NotImplementedYetException : public AsmException {
    public:
	    NotImplementedYetException(const string message) : AsmException(message) {}
	    ~NotImplementedYetException() throw () {}
    };
}

#endif