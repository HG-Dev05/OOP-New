#include <iostream>
#include "UserAuth.h" // Thêm header cho User
#include "Admin.h" // Thêm header cho Admin
#include "MovieManager.h" // Thêm header cho MovieManager
#include "CustomerSupport.h" // Thêm header cho CustomerSupport
#include <string>
#include "Utils.h" 
#include <limits>

// Hiển thị menu chính của chương trình
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
    std::cout << "** 4. Cham soc khach hang             **\n";
    std::cout << "** 5. Thoat                           **\n";
    drawBorder(width);
    std::cout << "Nhap tuy chon: ";
}

// Hiển thị menu chức năng cho người dùng đã đăng nhập
void displayUserMenu() {
    int width = 40; // Chiều rộng của menu
    drawBorder(width);
    std::cout << "**             MENU NGUOI DUNG       **\n";
    drawBorder(width);
    std::cout << "** 1. Xem phim                        **\n";
    std::cout << "** 2. Xem lich su phim da xem         **\n";
    std::cout << "** 3. Xoa lich su xem phim            **\n";
    std::cout << "** 4. Thoat                           **\n";
    drawBorder(width);
    std::cout << "Nhap tuy chon: ";
}

// Hiển thị menu quản lý cho admin
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

// Hiển thị menu chức năng chăm sóc khách hàng
void displayCustomerSupportMenu() {
    int width = 40; // Chiều rộng của menu
    drawBorder(width);
    std::cout << "**        MENU CHAM SOC KHACH HANG    **\n";
    drawBorder(width);
    std::cout << "** 1. Doc phan hoi khach hang          **\n";
    std::cout << "** 2. Thong ke the loai phim           **\n";
    std::cout << "** 3. Thoat                            **\n";
    drawBorder(width);
    std::cout << "Nhap tuy chon: ";
}

int main() {
    int choice;
    User user("", ""); // Khoi tao doi tuong User
    Admin admin; // Khoi tao doi tuong Admin
    CustomerSupport customerSupport; // Khoi tao doi tuong CustomerSupport

    do {
        displayMainMenu(); // Hiển thị menu chính
        do {
            std::cin >> choice;
            if (choice < 1 || choice > 5) {
                std::cout << "Lua chon khong hop le! Vui long chon lai (1-5): ";
            }
        } while (choice < 1 || choice > 5);

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
                                user.clearWatchHistory();
                                break;
                            case 4:
                                std::cout << "Thoat chuc nang nguoi dung." << std::endl;
                                break;
                            default:
                                std::cout << "Lua chon khong hop le! Vui long chon lai." << std::endl;
                        }
                    } while (userChoice != 4);
                } else {
                    std::cout << "Dang nhap khong thanh cong!" << std::endl;
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
                                std::cout << "Lua chon khong hop le! Vui long chon lai." << std::endl;
                        }
                    } while (adminChoice != 3);
                } else {
                    std::cout << "Dang nhap admin khong thanh cong!" << std::endl;
                }
                break;
            case 4:
                if (customerSupport.loginCustomerSupport()) {
                    int supportChoice;
                    do {
                        displayCustomerSupportMenu(); // Hiển thị menu chăm sóc khách hàng
                        std::cin >> supportChoice;

                        switch (supportChoice) {
                            case 1:
                                customerSupport.readCustomerFeedback();
                                break;
                            case 2:
                                customerSupport.statistics();
                                break;
                            case 3:
                                std::cout << "Thoat chuc nang cham soc khach hang." << std::endl;
                                break;
                            default:
                                std::cout << "Lua chon khong hop le! Vui long chon lai." << std::endl;
                        }
                    } while (supportChoice != 3);
                } else {
                    std::cout << "Dang nhap cham soc khach hang khong thanh cong!" << std::endl;
                }
                break;
            case 5:
                std::cout << "Thoat chuong trinh." << std::endl;
                break;
            default:
                std::cout << "Lua chon khong hop le! Vui long chon lai." << std::endl;
        }

        if (choice != 5) {  // Không đợi Enter khi thoát chương trình
            std::cout << "\nNhan Enter de tiep tuc...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    } while (choice != 5);

    return 0;
}
