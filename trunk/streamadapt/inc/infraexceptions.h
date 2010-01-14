/*
 * CannotCreateSessionException.h
 *
 *  Created on: 29/12/2009
 *      Author: ivocalado
 */

#ifndef INFRA_EXCEPTIONS_H_
#define INFRA_EXCEPTIONS_H_

#include <exception>
#include <string>
using namespace std;

namespace infrastream {

class CannotCreateSessionException: public exception {
	string message;
public:
	CannotCreateSessionException() :
		message("Invalid Session") {
	}

	CannotCreateSessionException(std::string m) :
		message(m) {
	}

	virtual const char* what() const throw() {
		return message.c_str();
	}

	virtual ~CannotCreateSessionException() throw() {
	}
};

class CannotLoadPolicyException: public exception {
	string message;
public:
	CannotLoadPolicyException() :
		message("Invalid Policy") {
	}

	CannotLoadPolicyException(std::string m) :
		message(m) {
	}

	virtual const char* what() const throw() {
		return message.c_str();
	}

	virtual ~CannotLoadPolicyException() throw() {
	}
};

class InvalidPolicyException: public std::exception {
	std::string message;
public:
	InvalidPolicyException() :
		message("The policy used is invalid") {
	}
	InvalidPolicyException(std::string m) :
		message(m) {
	}
	virtual const char* what() const throw() {
		return message.c_str();
	}

	virtual ~InvalidPolicyException() throw() {
	}

};

class InvalidEventException: public std::exception {
	std::string message;
public:
	InvalidEventException() :
		message("Invalid event") {
	}
	InvalidEventException(std::string m) :
		message(m) {
	}
	virtual const char* what() const throw() {
		return message.c_str();
	}

	virtual ~InvalidEventException() throw() {
	}

};

}

#endif /* INFRA_EXCEPTIONS_H_ */
