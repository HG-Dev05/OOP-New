#ifndef USER_AUTH_H
#define USER_AUTH_H

#include <limits>
#include <string>
#include <vector>
#include "MovieManager.h" // Thêm header cho MovieManager

class User {
private:
    std::string username;
    std::string password;
    std::string email;
    std::string phone;
    std::string address;
    std::string birthdate;
    MovieManager movieManager; // Đối tượng MovieManager

    // Thêm các hàm kiểm tra tính hợp lệ
    bool isValidEmail(const std::string& email);
    bool isValidPhone(const std::string& phone);
    bool isValidBirthdate(const std::string& birthdate);
    void clearInputBuffer();
    
public:
    User(std::string user, std::string pass);
    
    void registerUser();
    bool loginUser();
    void viewMovies(); // Chỉ khai báo, không định nghĩa
    void viewWatchHistory();
    void clearWatchHistory();
};

#endif // USER_AUTH_H
