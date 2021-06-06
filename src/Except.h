#pragma once
#include <exception>
#include <string>

using namespace std;
class Except : virtual public exception {

protected:
    int error_line;              
    string error_message;   

public:

    explicit
        Except(const string& msg, int err_line) :
        error_line(err_line),
        error_message(msg)
    {}

    Except(const string& msg) :
        error_message(msg),
        error_line(NULL)
    {}

    virtual const char* what() const throw () {
        return error_message.c_str();
    }

    virtual int getErrorLine() const throw() {
        return error_line;
    }

};