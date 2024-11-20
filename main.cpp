#include <iostream>
#include "UserAuth.h" 
#include "Admin.h" 
#include "MovieManager.h" 
#include "CustomerSupport.h" 
#include <string>
#include "Utils.h" 
#include <limits>

using namespace std;

void displayMainMenu() {
    int width = 40; 
    drawBorder(width);
    cout << "**    CHUONG TRINH QUAN LY PHIM       **\n";
    drawBorder(width);
    cout << "**              *MENU*                **\n";
    drawBorder(width);
    cout << "** 1. Dang ky                         **\n";
    cout << "** 2. Dang nhap                       **\n";
    cout << "** 3. Dang nhap Admin                 **\n";
    cout << "** 4. Cham soc khach hang             **\n";
    cout << "** 5. Thoat                           **\n";
    drawBorder(width);
    cout << "Nhap tuy chon: ";
}

// Hiển thị menu chức năng cho người dùng đã đăng nhập
void displayUserMenu() {
    int width = 40; 
    drawBorder(width);
    cout << "**             MENU NGUOI DUNG       **\n";
    drawBorder(width);
    cout << "** 1. Xem phim                        **\n";
    cout << "** 2. Xem lich su phim da xem         **\n";
    cout << "** 3. Xoa lich su xem phim            **\n";
    cout << "** 4. Thoat                           **\n";
    drawBorder(width);
    cout << "Nhap tuy chon: ";
}

// Hiển thị menu quản lý cho admin
void displayAdminMenu() {
    int width = 40; 
    drawBorder(width);
    cout << "**            MENU QUAN LY ADMIN      **\n";
    drawBorder(width);
    cout << "** 1. Quan ly nguoi dung              **\n";
    cout << "** 2. Quan ly phim                    **\n";
    cout << "** 3. Thoat                           **\n";
    drawBorder(width);
    cout << "Nhap tuy chon: ";
}

// Hiển thị menu chức năng chăm sóc khách hàng
void displayCustomerSupportMenu() {
    int width = 40; 
    drawBorder(width);
    cout << "**        MENU CHAM SOC KHACH HANG    **\n";
    drawBorder(width);
    cout << "** 1. Doc phan hoi khach hang          **\n";
    cout << "** 2. Thong ke the loai phim           **\n";
    cout << "** 3. Thoat                            **\n";
    drawBorder(width);
    cout << "Nhap tuy chon: ";
}

int main() {
    int choice;
    User user("", ""); 
    Admin admin;
    CustomerSupport customerSupport; 

    do {
        displayMainMenu(); 
        do {
            cin >> choice;
            if (choice < 1 || choice > 5) {
                cout << "Lua chon khong hop le! Vui long chon lai (1-5): ";
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
                        displayUserMenu(); 
                        cin >> userChoice;

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
                                cout << "Thoat chuc nang nguoi dung." << endl;
                                break;
                            default:
                                cout << "Lua chon khong hop le! Vui long chon lai." << endl;
                        }
                    } while (userChoice != 4);
                } else {
                    cout << "Dang nhap khong thanh cong!" << endl;
                }
                break;
            case 3:
                if (admin.loginAdmin()) {
                    int adminChoice;
                    do {
                        displayAdminMenu(); 
                        cin >> adminChoice;

                        switch (adminChoice) {
                            case 1:
                                admin.manageUsers();
                                break;
                            case 2:
                                admin.manageMovies();
                                break;
                            case 3:
                                cout << "Thoat chuc nang quan ly admin." << endl;
                                break;
                            default:
                                cout << "Lua chon khong hop le! Vui long chon lai." << endl;
                        }
                    } while (adminChoice != 3);
                } else {
                    cout << "Dang nhap admin khong thanh cong!" << endl;
                }
                break;
            case 4:
                if (customerSupport.loginCustomerSupport()) {
                    int supportChoice;
                    do {
                        displayCustomerSupportMenu();
                        cin >> supportChoice;

                        switch (supportChoice) {
                            case 1:
                                customerSupport.readCustomerFeedback();
                                break;
                            case 2:
                                customerSupport.statistics();
                                break;
                            case 3:
                                cout << "Thoat chuc nang cham soc khach hang." << endl;
                                break;
                            default:
                                cout << "Lua chon khong hop le! Vui long chon lai." << endl;
                        }
                    } while (supportChoice != 3);
                } else {
                    cout << "Dang nhap cham soc khach hang khong thanh cong!" << endl;
                }
                break;
            case 5:
                cout << "Thoat chuong trinh." << endl;
                break;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai." << endl;
        }

        if (choice != 5) { 
            cout << "\nNhan Enter de tiep tuc...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    } while (choice != 5);

    return 0;
}
