#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>
#include "MovieManager.h" 

class Admin {
private:
    const string adminUsername = "admin"; 
    const string adminPassword = "admin123"; 
    MovieManager movieManager; 

public:
    bool loginAdmin();
    void viewUsers();
    void deleteUser(const string& username);
    void manageMovies();
    void addMovie(const string& movieName);
    void deleteMovie(const string& movieName);
    void updateMovie(const string& oldName, const string& newName);
    void manageUsers(); 
    void viewUserActivity(const string& username); 
};

#endif 
