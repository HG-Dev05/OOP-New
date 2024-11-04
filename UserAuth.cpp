#include <iostream>
#include <limits> 
#include <fstream>
#include <map>
#include "UserAuth.h"
#include <map> 
#include <ctime>
#include <cstdio>
#include <limits>

User::User(std::string user, std::string pass) : username(user), password(pass) {}

void User::registerUser() {
    std::cout << "Nhap ten nguoi dung: ";
    std::cin >> username;
    std::cout << "Nhap mat khau: ";
    std::cin >> password;

    // Ghi thong tin nguoi dung vao file
    std::ofstream outputFile("users.txt", std::ios::app); // Mo file o che do append
    if (outputFile) {
        outputFile << username << " " << password << std::endl;
        std::cout << "Dang ky thanh cong!" << std::endl;
    } else {
        std::cerr << "Khong the mo file de ghi!" << std::endl;
    }
}

bool User::loginUser() {
    std::string user, pass;
    std::cout << "Nhap ten nguoi dung: ";
    std::cin >> user;
    std::cout << "Nhap mat khau: ";
    std::cin >> pass;

    // Doc thong tin tu file de kiem tra dang nhap
    std::ifstream inputFile("users.txt");
    if (inputFile) {
        std::string fileUser, filePass;
        while (inputFile >> fileUser >> filePass) {
            if (fileUser == user && filePass == pass) {
                std::cout << "Dang nhap thanh cong!" << std::endl;
                return true;
            }
        }
        std::cout << "Ten nguoi dung hoac mat khau khong dung!" << std::endl;
    } else {
        std::cerr << "Khong the mo file de doc!" << std::endl;
    }
    return false;
}

void User::viewMovies() {
    // Lấy danh sách thể loại phim
    std::vector<std::string> genres = movieManager.getGenres();
    
    // Hiển thị danh sách thể loại
    std::cout << "Danh sach the loai phim:\n";
    for (size_t i = 0; i < genres.size(); ++i) {
        std::cout << i + 1 << ". " << genres[i] << std::endl;
    }

    // Cho phép người dùng chọn thể loại
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

    // Hiển thị danh sách phim theo thể loại
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
    std::cout << "Dang xem phim: " << selectedMovie <<"......." << std::endl;

    // Cập nhật số lượt xem
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

    // Ghi vào lịch sử xem phim với thời gian
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

    // Tùy chọn cho người dùng
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

void User::clearWatchHistory() {
    std::string historyFileName = username + "_history.txt";
    if (remove(historyFileName.c_str()) == 0) {
        std::cout << "Da xoa lich su xem phim!" << std::endl;
    } else {
        std::cerr << "Khong the xoa lich su xem phim!" << std::endl;
    }
}
