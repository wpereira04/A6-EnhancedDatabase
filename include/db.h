////////////////////////////////////////////////////////
//
// ECE 3574, A6, Walter Pereira Cruz
// File name: db.h
// Description: Contains the declarations for the Database class
// functions and variables.
// - 04/03/2025 : Added exceptions for move and copy assignment operators
//        as well as the move and copy constructors. Implemented isTimeout
//        and refreshConnection which are used to modify and track a last_activity
//        variable. a timeout occurs when the last_activity was more than TIMEOUT
//        seconds ago. In this case 5 seconds.
//				
// Date:        03/14/2025
//

#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <iostream>
#include <stdexcept>
#include <ctime>

class Database {
private:
    //member variable "db" is of string type
    std::string db;
    
    //member variable "username" is of string type
    std::string username;
    //member variable "password" is of string type
    
    std::string password;
    //member variable "connected" is of string type
    //The "connected" is set to false initially.
    
    bool connected{ false };
    //member variable "instance" is static 
    //"instance" (pointer to Database) is a staic variable that stores the instance of the database. Its value is set in the function "getInstance"
    
    static Database* instance;
    // tracks when the last time an activity is done. intialized to current time.
    time_t last_activity{ std::time(0) };
    // constant variable used for comparison for timeout.
    static const int TIMEOUT{ 5 };

    //constructor that helps creating instance of db(e.g. sales.db) accepts name of the database, username, password. 
    
    Database(const std::string& dbName, const std::string& usrname, const std::string& pasword)
        : db(dbName), username(usrname), password(pasword) {}

public:
    //destructor that disconnects the connection if connected.
    
    ~Database();
    //"getInstance" that creates and returns the instance of the database. If called first time it sets the username and password. However, subsequent time, it matches the database name, username and password and returns the previous instance if matched else it throws std::runtime_error("invalid database name, username or password"). We are using Singleton Design Pattern that creates only one instance of the databse. The instance is still created by the constructor.
    
    static Database* getInstance(const std::string& dbName, const std::string& usrname, const std::string& pasword);
    //"connect" that sets "connected" to true (return void)
    void connect();
    //"disconnect" that sets "connected" to false (return void)
    void disconnect();
    // return whether timeout has occured
    bool isTimeout();
    // refreshes the last_activity variable to the current time
    void refreshConnection();

    // retrun status of connected true/false (return bool)
    bool isConnected();
    //overload the new operator that allocates memory using malloc of given size and returns pointer of type void and prints " overloaded new " (cout is okay in this case). std::cout << "overloaded new ";
    //If the memory allocation fails it should throw std::bad_alloc()
    
    void* operator new(size_t size);
    //overload the delete operator that deallocates memory and prints "overloaded delete " (cout is okay in this). std::cout << "overloaded delete ";
    
    void operator delete(void* pt);
    //set_username and get_username for username
    
    
    void set_username(const std::string& username);
    const std::string get_username();
    //set_password and get_password for password.
    
    
    void set_password(const std::string& password);

    const std::string get_password();
    //The static "resetInstance" as defined below.
    static void resetInstance();

    // overloaded operators to prevent their use and throw
    void operator=(const Database& db);

    Database(const Database& db);

    Database(Database&& db);

    void operator=(Database&& db);
};


#endif