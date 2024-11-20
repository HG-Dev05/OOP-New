#ifndef USER_AUTH_H
#define USER_AUTH_H

#include <limits>
#include <string>
#include <vector>
#include "MovieManager.h" 

class User {
private:
    string username;
    string password;
    string email;
    string phone;
    string address;
    string birthdate;
    MovieManager movieManager;

    bool isValidEmail(const string& email);
    bool isValidPhone(const string& phone);
    bool isValidBirthdate(const string& birthdate);
    void clearInputBuffer();
    
public:
    User(string user, string pass);
    
    void registerUser();
    bool loginUser();
    void viewMovies(); 
    void viewWatchHistory();
    void clearWatchHistory();
};

#endif 