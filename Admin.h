#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>
#include "MovieManager.h" // Thêm header cho MovieManager

class Admin {
private:
    const std::string adminUsername = "admin"; // Ten dang nhap admin
    const std::string adminPassword = "admin123"; // Mat khau admin
    MovieManager movieManager; // Đối tượng MovieManager

public:
    bool loginAdmin();
    void viewUsers();
    void deleteUser(const std::string& username);
    void manageMovies();
    void addMovie(const std::string& movieName);
    void deleteMovie(const std::string& movieName);
    void updateMovie(const std::string& oldName, const std::string& newName);
    void manageUsers(); // Khai báo phương thức quản lý người dùng
    void viewUserActivity(const std::string& username); // Khai báo phương thức xem hoạt động của người dùng
};

#endif // ADMIN_H
