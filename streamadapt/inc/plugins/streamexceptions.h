/*
 * stream-exceptions.h
 *
 *  Created on: 17/08/2009
 *      Author: ivocalado
 */

#ifndef STREAMEXCEPTIONS_H_
#define STREAMEXCEPTIONS_H_

#include<exception>
#include<string>



class CannotLoadPluginException : public std::exception {
	std::string message;
public:
	 CannotLoadPluginException(): message("It's not possible load the plugin") {}
	 CannotLoadPluginException(std::string m) : message(m){}
	 virtual const char* what() const throw() {return message.c_str();}


	 virtual ~CannotLoadPluginException() throw() {}

};

class OperationNotSupportedException : public std::exception {
	std::string message;
public:
	OperationNotSupportedException(): message("Operation unavailable") {}
	OperationNotSupportedException(std::string m) : message(m){}
	 virtual const char* what() const throw() {return message.c_str();}


	 virtual ~OperationNotSupportedException() throw() {}
};

class CannotBindSocketException : public std::exception {
	std::string message;
public:
	CannotBindSocketException(): message("Bind unavailable for this configuration") {}
	CannotBindSocketException(std::string m) : message(m){}
	 virtual const char* what() const throw() {return message.c_str();}


	 virtual ~CannotBindSocketException() throw() {}
};

class CannotConnectSocketException : public std::exception {
	std::string message;
public:
	CannotConnectSocketException(): message("Connection failure") {}
	CannotConnectSocketException(std::string m) : message(m){}
	 virtual const char* what() const throw() {return message.c_str();}


	 virtual ~CannotConnectSocketException() throw() {}
};

class CannotCreateSocketException : public std::exception {
	std::string message;
public:
	CannotCreateSocketException(): message("It's not possible create socket") {}
	CannotCreateSocketException(std::string m) : message(m){}
	 virtual const char* what() const throw() {return message.c_str();}


	 virtual ~CannotCreateSocketException() throw() {}
};

class OperationNotPerfomedException : public std::exception {
	std::string message;
public:
	OperationNotPerfomedException(): message("It's not possible perform this operation") {}
	OperationNotPerfomedException(std::string m) : message(m){}
	 virtual const char* what() const throw() {return message.c_str();}


	 virtual ~OperationNotPerfomedException() throw() {}
};

class CannotCreateSessionException : public std::exception {
	std::string message;
public:
	CannotCreateSessionException(): message("It's not possible create the session") {}
	CannotCreateSessionException(std::string m) : message(m){}
	 virtual const char* what() const throw() {return message.c_str();}


	 virtual ~CannotCreateSessionException() throw() {}
};



#endif /* STREAMEXCEPTIONS_H_ */
