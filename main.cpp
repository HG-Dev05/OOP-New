#include <iostream>
#include "UserAuth.h" // Thêm header cho User
#include "Admin.h" // Thêm header cho Admin
#include "MovieManager.h" // Thêm header cho MovieManager
#include <string>
#include "Utils.h" 
// new 
void huhu(){
    
}
void displayMainMenu() {
    int width = 40; // Chiều rộng của menu
    drawBorder(width);
    std::cout << "**    CHUONG TRINH QUAN LY PHIM       **\n";
    drawBorder(width);
    std::cout << "**            *MENU*                **\n";
    drawBorder(width);
    std::cout << "** 1. Dang ky                         **\n";
    std::cout << "** 2. Dang nhap                       **\n";
    std::cout << "** 3. Dang nhap Admin                 **\n";
    std::cout << "** 4. Thoat                           **\n";
    drawBorder(width);
    std::cout << "Nhap tuy chon: ";
}

void displayUserMenu() {
    int width = 40; // Chiều rộng của menu
    drawBorder(width);
    std::cout << "**             MENU NGUOI DUNG       **\n";
    drawBorder(width);
    std::cout << "** 1. Xem phim                        **\n";
    std::cout << "** 2. Xem lich su phim da xem         **\n";
    std::cout << "** 3. Thoat                          **\n";
    drawBorder(width);
    std::cout << "Nhap tuy chon: ";
}

void displayAdminMenu() {
    int width = 40; // Chiều rộng của menu
    drawBorder(width);
    std::cout << "**            MENU QUAN LY ADMIN     **\n";
    drawBorder(width);
    std::cout << "** 1. Quan ly nguoi dung              **\n";
    std::cout << "** 2. Quan ly phim                    **\n";
    std::cout << "** 3. Thoat                          **\n";
    drawBorder(width);
    std::cout << "Nhap tuy chon: ";
}

int main() {
    int choice;
    User user("", ""); // Khoi tao doi tuong User
    Admin admin; // Khoi tao doi tuong Admin

    do {
        displayMainMenu(); // Hiển thị menu chính
        std::cin >> choice;

        switch (choice) {
            case 1:
                user.registerUser();
                break;
            case 2:
                if (user.loginUser()) {
                    int userChoice;
                    do {
                        displayUserMenu(); // Hiển thị menu người dùng
                        std::cin >> userChoice;

                        switch (userChoice) {
                            case 1:
                                user.viewMovies();
                                break;
                            case 2:
                                user.viewWatchHistory();
                                break;
                            case 3:
                                std::cout << "Thoat chuc nang nguoi dung." << std::endl;
                                break;
                            default:
                                std::cout << "Lua chon khong hop le!" << std::endl;
                        }
                    } while (userChoice != 3);
                }
                break;
            case 3:
                if (admin.loginAdmin()) {
                    int adminChoice;
                    do {
                        displayAdminMenu(); // Hiển thị menu quản lý admin
                        std::cin >> adminChoice;

                        switch (adminChoice) {
                            case 1:
                                admin.manageUsers();
                                break;
                            case 2:
                                admin.manageMovies();
                                break;
                            case 3:
                                std::cout << "Thoat chuc nang quan ly admin." << std::endl;
                                break;
                            default:
                                std::cout << "Lua chon khong hop le!" << std::endl;
                        }
                    } while (adminChoice != 3);
                }
                break;
            case 4:
                std::cout << "Thoat chuong trinh." << std::endl;
                break;
            default:
                std::cout << "Lua chon khong hop le!" << std::endl;
        }
    } while (choice != 4);

    return 0;
}
