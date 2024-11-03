#ifndef USER_AUTH_H
#define USER_AUTH_H

#include <string>
#include <vector>
#include "MovieManager.h" // Thêm header cho MovieManager

class User {
public:
    std::string username;
    std::string password;
    MovieManager movieManager; // Đối tượng MovieManager

    User(std::string user, std::string pass);
    
    void registerUser();
    bool loginUser();
    void viewMovies(); // Chỉ khai báo, không định nghĩa
    void viewWatchHistory();
};

#endif // USER_AUTH_H
