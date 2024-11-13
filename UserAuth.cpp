#include <iostream>
#include <limits> 
#include <fstream>
#include <map>
#include "UserAuth.h"
#include <map> 
#include <ctime>
#include <cstdio>
#include <limits>
#include <sstream>

// Constructor cho class User
User::User(std::string user, std::string pass) : username(user), password(pass) {}

// Đăng ký tài khoản mới và lưu vào file
void User::registerUser() {
    std::cout << "\n=== DANG KY TAI KHOAN ===\n";

    // Nhập tên người dùng
    do {
        std::cin.ignore();
        std::cout << "Nhap ten nguoi dung (toi thieu 3 ky tu): ";
        std::getline(std::cin, username);

        if (username.length() < 3) {
            std::cout << "Ten nguoi dung qua ngan! Vui long nhap lai.\n";
        }
    } while (username.length() < 3);

    // Kiểm tra tên đăng nhập đã tồn tại
    std::ifstream inputFile("users.txt");
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.find("Ten Dang Nhap: " + username) != std::string::npos) {
            std::cout << "Ten dang nhap da ton tai! Vui long chon ten khac.\n";
            return; 
        }
    }
    inputFile.close();

    // Nhập mật khẩu
    do {
        std::cout << "Nhap mat khau (toi thieu 6 ky tu): ";
        std::getline(std::cin, password);
        if (password.length() < 6) {
            std::cout << "Mat khau qua ngan! Vui long nhap lai.\n";
        }
    } while (password.length() < 6);

    // Nhập email
    do {
        std::cout << "Nhap email (example@domain.com): ";
        std::getline(std::cin, email);
        if (!isValidEmail(email)) {
            std::cout << "Email khong hop le! Vui long nhap lai.\n";
        }
    } while (!isValidEmail(email));

    // Nhập số điện thoại
    do {
        std::cout << "Nhap so dien thoai (10 so, bat dau bang so 0): ";
        std::getline(std::cin, phone);
        if (!isValidPhone(phone)) {
            std::cout << "So dien thoai khong hop le! Vui long nhap lai.\n";
        }
    } while (!isValidPhone(phone));

    // Nhập địa chỉ
    do {
        std::cout << "Nhap dia chi: ";
        std::getline(std::cin, address);
        if (address.empty()) {
            std::cout << "Dia chi khong duoc de trong! Vui long nhap lai.\n";
        }
    } while (address.empty());

    // Nhập ngày sinh
    do {
        std::cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        std::getline(std::cin, birthdate);
        if (!isValidBirthdate(birthdate)) {
            std::cout << "Ngay sinh khong hop le! Vui long nhap lai.\n";
        }
    } while (!isValidBirthdate(birthdate));

    // Ghi thông tin người dùng vào file
    std::ofstream outputFile("users.txt", std::ios::app);
    if (outputFile) {
        outputFile << "Ten Dang Nhap: " << username << "\n"
                   << "Mat Khau: " << password << "\n"
                   << "Email: " << email << "\n"
                   << "So Dien Thoai: " << phone << "\n"
                   << "Dia Chi: " << address << "\n"
                   << "Ngay Sinh: " << birthdate << "\n"
                   << "------------------------" << std::endl; // Dấu phân cách giữa các người dùng
        std::cout << "\nDang ky thanh cong!\n";
    } else {
        std::cerr << "Loi: Dang Ky That Bai!\n";
    }
}

// Kiểm tra thông tin đăng nhập từ file users.txt
bool User::loginUser() {
    std::string inputUser, inputPass;
    std::cout << "\n=== DANG NHAP ===\n";
    std::cout << "Nhap ten nguoi dung: ";
    std::cin >> inputUser;
    std::cout << "Nhap mat khau: ";
    std::cin >> inputPass;

    std::ifstream inputFile("users.txt");
    if (inputFile) {
        std::string line;
        while (std::getline(inputFile, line)) {
            // Kiểm tra tên đăng nhập
            if (line.find("Ten Dang Nhap: " + inputUser) != std::string::npos) {
                // Đọc mật khẩu
                std::getline(inputFile, line); // Đọc dòng mật khẩu
                if (line == "Mat Khau: " + inputPass) {
                    // Nếu mật khẩu đúng, đọc các thông tin khác
                    std::getline(inputFile, line); // Đọc email
                    std::getline(inputFile, line); // Đọc số điện thoại
                    std::getline(inputFile, line); // Đọc địa chỉ
                    std::getline(inputFile, line); // Đọc ngày sinh

                    // Lưu thông tin vào biến
                    username = inputUser;
                    password = inputPass;
                    // Lưu các thông tin khác nếu cần
                    std::cout << "\nDang nhap thanh cong!\n";
                    return true;
                } else {
                    std::cout << "\nMat khau khong dung!\n";
                    return false;
                }
            }
        }
        std::cout << "\nTen nguoi dung khong ton tai!\n";
    } else {
        std::cerr << "Loi: Khong the mo file de doc!\n";
    }
    return false;
}

// Xem và chọn phim để xem
void User::viewMovies() {
    // Lấy và hiển thị danh sách thể loại
    std::vector<std::string> genres = movieManager.getGenres();
    
    // Hiển thị danh sách thể loại cho người dùng chọn
    std::cout << "Danh sach the loai phim:\n";
    for (size_t i = 0; i < genres.size(); ++i) {
        std::cout << i + 1 << ". " << genres[i] << std::endl;
    }

    // Cho người dùng chọn thể loại phim
    int genreChoice;
    do {
        std::cout << "Chon the loai phim (nhap so): ";
        std::cin >> genreChoice;
        
        if (genreChoice <= 0 || genreChoice > genres.size()) {
            std::cout << "Lua chon khong hop le! Vui long chon lai.\n";
        }
    } while (genreChoice <= 0 || genreChoice > genres.size());

    std::string selectedGenre = genres[genreChoice - 1];
    std::cout << "Ban da chon the loai: " << selectedGenre << std::endl;

    // Hiển thị danh sách phim theo thể loại đã chọn
    std::vector<std::string> movies = movieManager.getMoviesByGenre(selectedGenre);
    std::cout << "Danh sach phim trong the loai " << selectedGenre << ":\n";
    for (size_t i = 0; i < movies.size(); ++i) {
        std::cout << i + 1 << ". " << movies[i] << std::endl;
    }

    // Cho phép người dùng chọn phim
    int movieChoice;
    do {
        std::cout << "Chon phim de xem (nhap so): ";
        std::cin >> movieChoice;
        
        if (movieChoice <= 0 || movieChoice > movies.size()) {
            std::cout << "Lua chon khong hop le! Vui long chon lai.\n";
        }
    } while (movieChoice <= 0 || movieChoice > movies.size());

    std::string selectedMovie = movies[movieChoice - 1];
    std::cout << "Dang xem phim: " << selectedMovie << "......." << std::endl;

    // Cập nhật số lượt xem cho phim được chọn
    std::ifstream viewCountFile("view_counts.txt");
    std::map<std::string, int> viewCounts;
    std::string line;

    // Đọc số lượt xem từ file
    while (std::getline(viewCountFile, line)) {
        size_t pos = line.find(":");
        if (pos != std::string::npos) {
            std::string movieName = line.substr(0, pos);
            int count = std::stoi(line.substr(pos + 1));
            viewCounts[movieName] = count;
        }
    }
    viewCountFile.close();

    // Tăng số lượt xem lên 1
    viewCounts[selectedMovie]++;

    // Ghi lại số lượt xem vào file
    std::ofstream outputFile("view_counts.txt");
    for (const auto& entry : viewCounts) {
        outputFile << entry.first << ": " << entry.second << std::endl;
    }
    outputFile.close();

    // Ghi lịch sử xem phim với timestamp
    std::ofstream historyFile(username + "_history.txt", std::ios::app);
    if (historyFile) {
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        historyFile << selectedMovie << " - " 
                    << (localTime->tm_year + 1900) << "-" 
                    << (localTime->tm_mon + 1) << "-" 
                    << localTime->tm_mday << " " 
                    << localTime->tm_hour << ":" 
                    << localTime->tm_min << std::endl;
    }

    // Xử lý các tùy chọn sau khi xem phim (dừng/bình luận)
    int actionChoice;
    do {
        std::cout << "Chon hanh dong:\n"
                  << "1. Dung phim\n"
                  << "2. Them binh luan\n"
                  << "3. Thoat\n";
        std::cout << "Nhap so: ";
        
        while (!(std::cin >> actionChoice) || actionChoice < 1 || actionChoice > 3) {
            std::cout << "Lua chon khong hop le! Vui long chon lai (1-3): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (actionChoice) {
            case 1: {
                std::cout << "Phim da duoc dung!" << std::endl;
                std::cout << "\nNhan Enter de tiep tuc...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 2: {
                std::string feedback;
                std::cout << "Nhap phan hoi ve phim: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, feedback);

                std::ofstream feedbackFile(selectedMovie + "_feedback.txt", std::ios::app);
                if (feedbackFile) {
                    feedbackFile << username << ": " << feedback << std::endl;
                    std::cout << "Binh luan da duoc luu!" << std::endl;
                } else {
                    std::cerr << "Khong the mo file de ghi phan hoi!" << std::endl;
                }
                
                std::cout << "\nNhan Enter de tiep tuc...";
                std::cin.get();
                break;
            }
            case 3: {
                std::cout << "Thoat khoi chuc nang xem phim." << std::endl;
                break;
            }
        }
    } while (actionChoice != 3);
}

// Xem lịch sử các phim đã xem
void User::viewWatchHistory() {
    std::ifstream historyFile(username + "_history.txt");
    if (historyFile) {
        std::string line;
        std::cout << "Lich su phim da xem:\n";
        while (std::getline(historyFile, line)) {
            std::cout << "- " << line << std::endl; // In lịch sử xem
        }
    } else {
        std::cerr << "Khong the mo file lich su!" << std::endl;
    }
}

// Xóa toàn bộ lịch sử xem phim
void User::clearWatchHistory() {
    std::string historyFileName = username + "_history.txt";
    if (remove(historyFileName.c_str()) == 0) {
        std::cout << "Da xoa lich su xem phim!" << std::endl;
    } else {
        std::cerr << "Khong the xoa lich su xem phim!" << std::endl;
    }
}

// Thêm các hàm kiểm tra tính hợp lệ
bool User::isValidEmail(const std::string& email) {
    // Kiểm tra email có chứa @ và .
    return email.find('@') != std::string::npos && 
           email.find('.') != std::string::npos &&
           email.find('@') < email.find_last_of('.');
}

bool User::isValidPhone(const std::string& phone) {
    // Kiểm tra số điện thoại có 10 số và bắt đầu bằng 0
    if (phone.length() != 10 || phone[0] != '0') return false;
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool User::isValidBirthdate(const std::string& birthdate) {
    // Kiểm tra định dạng dd/mm/yyyy
    if (birthdate.length() != 10) return false;
    if (birthdate[2] != '/' || birthdate[5] != '/') return false;

    try {
        int day = std::stoi(birthdate.substr(0, 2));
        int month = std::stoi(birthdate.substr(3, 2));
        int year = std::stoi(birthdate.substr(6, 4));

        if (year < 1900 || year > 2024) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;

        // Kiểm tra tháng 2 và năm nhuận
        if (month == 2) {
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (day > (isLeapYear ? 29 : 28)) return false;
        }

        // Kiểm tra các tháng có 30 ngày
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;

        return true;
    } catch (...) {
        return false;
    }
}

void User::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
