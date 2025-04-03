////////////////////////////////////////////////////////
//
// ECE 3574, A6, Walter Pereira Cruz
// File name: db.cpp
// Description: Contains the implementations for the Database class
// functions
// - 04/03/2025 : Added exceptions for move and copy assignment operators
//        as well as the move and copy constructors. Implemented isTimeout
//        and refreshConnection which are used to modify and track a last_activity
//        variable. a timeout occurs when the last_activity was more than TIMEOUT
//        seconds ago. In this case 5 seconds.
//				
// Date:        03/14/2025
//
#include "db.h"

// intializes instance to nullptr

Database* Database::instance = nullptr;

// default destructor
Database::~Database() {

}

// checks if the instance is occupied which determines if it's "the first run" or not. 
// creates an instance and returns it or checks for matching information and either returns the instance
// or throws a runtime error.
Database* Database::getInstance(const std::string& dbName, const std::string& usrname, const std::string& pasword) {
	if (!instance) {
		instance = new Database(dbName, usrname, pasword);
	}
	else {
		if (instance->db != dbName || instance->username != usrname || instance->password != pasword) {
			throw std::runtime_error("invalid database name, username, or password");
		}
	}
	return instance;
}

// sets connected to true
void Database::connect() {
	refreshConnection();
	connected = true;
}

// sets connected to false
void Database::disconnect() {
	refreshConnection();
	connected = false;
}

// returns the state of connected
bool Database::isConnected() {
	refreshConnection();
	return connected;
}

// override the new operator with new definition
void* Database::operator new(size_t size) {
	std::cout << "overloaded new ";
	void* ptr = std::malloc(size);
	if (!ptr) {
		throw std::bad_alloc();
	}
	return ptr;
}

// override the delete operator with another definition
void Database::operator delete(void* pt) {
	std::cout << "overloaded delete ";
	if (instance) {
		instance->refreshConnection();
	}
	std::free(pt);

}

// sets the username member variable
void Database::set_username(const std::string& usrname) {
	refreshConnection();
	username = usrname;
}

// sets the password member variable
void Database::set_password(const std::string& pasword) {
	refreshConnection();
	password = pasword;
}

// gets the username member variable
const std::string Database::get_username() {
	refreshConnection();
	return username;
}

// gets the password member variable
const std::string Database::get_password() {
	refreshConnection();
	return password;
}

// reset the instance
void Database::resetInstance() {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

// copy assignment operator. throws
void Database::operator=(const Database& db)
{
	throw(std::runtime_error("Copy or Move operations are not allowed"));
}

// copy constructor. throws
Database::Database(const Database& db)
{
	throw(std::runtime_error("Copy or Move operations are not allowed"));
}

// move constructor. throws
Database::Database(Database&& db)
{
	throw(std::runtime_error("Copy or Move operations are not allowed"));
}

// move assignment operator. throws
void Database::operator=(Database&& db)
{
	throw(std::runtime_error("Copy or Move operations are not allowed"));
}

// timeout. returns whether the last activity was more than TIMEOUT seconds ago.
bool Database::isTimeout() {
	return (std::difftime(std::time(0), last_activity) > TIMEOUT);
}
// used to set the last activity to the current time. therefore refreshing
void Database::refreshConnection() {
	last_activity = std::time(0);
}