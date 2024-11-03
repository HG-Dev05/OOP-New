#include <iostream>
#include <fstream>
#include "UserAuth.h"

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
    std::cout << "Chon the loai phim (nhap so): ";
    std::cin >> genreChoice;

    if (genreChoice > 0 && genreChoice <= genres.size()) {
        std::string selectedGenre = genres[genreChoice - 1];
        std::cout << "Ban da chon the loai: " << selectedGenre << std::endl;

        // Hiển thị danh sách phim theo thể loại
        std::vector<std::string> movies = movieManager.getMoviesByGenre(selectedGenre);
        std::cout << "Danh sach phim trong the loai " << selectedGenre << ":\n";
        for (size_t i = 0; i < movies.size(); ++i) {
            std::cout << movies[i] << std::endl;
        }

        // Cho phép người dùng chọn phim
        int movieChoice;
        std::cout << "Chon phim de xem (nhap so): ";
        std::cin >> movieChoice;

        if (movieChoice > 0 && movieChoice <= movies.size()) {
            std::string selectedMovie = movies[movieChoice - 1];
            std::cout << "Dang xem phim: " << selectedMovie << std::endl;

            // Ghi vào lịch sử xem phim
            std::ofstream historyFile(username + "_history.txt", std::ios::app);
            if (historyFile) {
                historyFile << selectedMovie << std::endl; // Ghi tên phim vào lịch sử
            }
        } else {
            std::cout << "Lua chon khong hop le!" << std::endl;
        }
    } else {
        std::cout << "Lua chon khong hop le!" << std::endl;
    }
}

void User::viewWatchHistory() {
    std::ifstream historyFile(username + "_history.txt");
    if (historyFile) {
        std::string movieName;
        std::cout << "Lich su phim da xem:\n";
        while (std::getline(historyFile, movieName)) {
            std::cout << "- " << movieName << std::endl;
        }
    } else {
        std::cerr << "Khong the mo file lich su!" << std::endl;
    }
}
