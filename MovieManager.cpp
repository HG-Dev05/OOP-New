#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "MovieManager.h"

void MovieManager::addMovie(const std::string& movieName, const std::string& genre) {
    std::ofstream outputFile("Phim" + genre + ".txt", std::ios::app); // Tạo file cho thể loại
    if (outputFile) {
        outputFile << movieName << std::endl; // Ghi tên phim vào file thể loại
        std::cout << "Da them phim: " << movieName << " vao the loai: " << genre << std::endl;
    } else {
        std::cerr << "Khong the mo file de ghi!" << std::endl;
    }
}

void MovieManager::viewMoviesByGenre(const std::string& genre) {
    std::ifstream movieFile("Phim" + genre + ".txt");
    if (movieFile) {
        std::string line;
        std::cout << "Phim trong the loai " << genre << ":\n";
        while (std::getline(movieFile, line)) {
            std::cout << "- " << line << std::endl; // In tên phim
        }
    } else {
        std::cerr << "Khong the mo file danh sach phim!" << std::endl;
    }
}

std::vector<std::string> MovieManager::getGenres() {
    std::ifstream genreFile("TheLoaiPhim.txt");
    std::vector<std::string> genres;
    std::string line;

    if (genreFile) {
        while (std::getline(genreFile, line)) {
            if (!line.empty()) {
                genres.push_back(line); // Thêm thể loại vào danh sách
            }
        }
    }
    return genres;
}

void MovieManager::viewAllMovies() {
    std::ifstream genreFile("TheLoaiPhim.txt");
    if (genreFile) {
        std::string line;
        while (std::getline(genreFile, line)) {
            std::cout << "The loai: " << line << std::endl;
            viewMoviesByGenre(line); // Gọi phương thức để in danh sách phim
        }
    } else {
        std::cerr << "Khong the mo file danh sach the loai!" << std::endl;
    }
}

std::vector<std::string> MovieManager::getMoviesByGenre(const std::string& genre) {
    std::ifstream movieFile("Phim" + genre + ".txt");
    std::vector<std::string> movies;
    std::string line;

    if (movieFile) {
        while (std::getline(movieFile, line)) {
            movies.push_back(line); // Thêm tên phim vào danh sách
        }
    }
    return movies; // Trả về danh sách phim
}

void MovieManager::deleteMovie(const std::string& movieName, const std::string& genre) {
    std::ifstream inputFile("Phim" + genre + ".txt");
    std::ofstream tempFile("temp_" + genre + ".txt");
    bool found = false;

    if (inputFile && tempFile) {
        std::string fileMovie;
        while (std::getline(inputFile, fileMovie)) {
            if (fileMovie == movieName) {
                found = true; // Đánh dấu là đã tìm thấy phim
                std::cout << "Da xoa phim: " << movieName << std::endl;
                continue; // Bỏ qua việc ghi vào file tạm
            }
            tempFile << fileMovie << std::endl; // Ghi lại phim khác
        }
    } else {
        std::cerr << "Khong the mo file de doc hoac ghi!" << std::endl;
    }

    inputFile.close();
    tempFile.close();

    // Xóa file cũ và đổi tên file tạm thành file gốc
    remove(("Phim" + genre + ".txt").c_str());
    rename(("temp_" + genre + ".txt").c_str(), ("Phim" + genre + ".txt").c_str());

    if (!found) {
        std::cout << "Khong tim thay phim: " << movieName << std::endl;
    }
}

void MovieManager::updateMovie(const std::string& oldName, const std::string& newName, const std::string& genre) {
    std::ifstream inputFile("Phim" + genre + ".txt");
    std::ofstream tempFile("temp_" + genre + ".txt");
    bool found = false;

    if (inputFile && tempFile) {
        std::string fileMovie;
        while (std::getline(inputFile, fileMovie)) {
            if (fileMovie == oldName) {
                found = true; // Đánh dấu là đã tìm thấy phim
                tempFile << newName << std::endl; // Ghi tên phim mới
                std::cout << "Da cap nhat phim: " << oldName << " thanh " << newName << std::endl;
            } else {
                tempFile << fileMovie << std::endl; // Ghi lại phim khác
            }
        }
    } else {
        std::cerr << "Khong the mo file de doc hoac ghi!" << std::endl;
    }

    inputFile.close();
    tempFile.close();

    // Xóa file cũ và đổi tên file tạm thành file gốc
    remove(("Phim" + genre + ".txt").c_str());
    rename(("temp_" + genre + ".txt").c_str(), ("Phim" + genre + ".txt").c_str());

    if (!found) {
        std::cout << "Khong tim thay phim: " << oldName << std::endl;
    }
}
