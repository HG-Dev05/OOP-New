#ifndef USER_AUTH_H
#define USER_AUTH_H

#include <limits>
#include <string>
#include <vector>
#include "MovieManager.h" 

class User {
private:
    std::string username;
    std::string password;
    std::string email;
    std::string phone;
    std::string address;
    std::string birthdate;
    MovieManager movieManager;

    bool isValidEmail(const std::string& email);
    bool isValidPhone(const std::string& phone);
    bool isValidBirthdate(const std::string& birthdate);
    void clearInputBuffer();
    
public:
    User(std::string user, std::string pass);
    
    void registerUser();
    bool loginUser();
    void viewMovies(); 
    void viewWatchHistory();
    void clearWatchHistory();
};

#endif 