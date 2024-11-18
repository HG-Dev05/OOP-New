#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
#include "MovieManager.h"

using namespace std;

// Thêm phim mới vào một thể loại
void MovieManager::addMovie(const string& movieName, const string& genre) {
    ofstream outputFile("Phim" + genre + ".txt", ios::app); 
    if (outputFile) {
        outputFile << movieName << endl; 
        cout << "Da them phim: " << movieName << " vao the loai: " << genre << endl;
    } else {
        cerr << "Khong the mo file de ghi!" << endl;
    }
}

// Hiển thị danh sách phim theo thể loại
void MovieManager::viewMoviesByGenre(const string& genre) {
    ifstream movieFile("Phim" + genre + ".txt");
    if (movieFile) {
        string line;
        cout << "Phim trong the loai " << genre << ":\n";
        while (getline(movieFile, line)) {
            cout << "- " << line << endl; // In tên phim
        }
    } else {
        cerr << "Khong the mo file danh sach phim!" << endl;
    }
}

// Lấy danh sách tất cả thể loại phim
vector<string> MovieManager::getGenres() {
    ifstream genreFile("TheLoaiPhim.txt");
    vector<string> genres;
    string line;

    if (genreFile) {
        while (getline(genreFile, line)) {
            if (!line.empty()) {
                genres.push_back(line); 
            }
        }
    }
    return genres;
}

// Hiển thị tất cả phim theo từng thể loại
void MovieManager::viewAllMovies() {
    ifstream genreFile("TheLoaiPhim.txt");
    if (genreFile) {
        string line;
        vector<string> genres;
        map<string, vector<string>> moviesByGenre;

        // Đọc tất cả thể loại
        while (getline(genreFile, line)) {
            genres.push_back(line);
            moviesByGenre[line] = getMoviesByGenre(line);
        }

        // Tìm số lượng phim tối đa trong một thể loại
        size_t maxMovies = 0;
        for (const auto& pair : moviesByGenre) {
            maxMovies = max(maxMovies, pair.second.size());
        }

        // In header với thể loại
        cout  << setw(20) << left << "The Loai";
        for (size_t i = 0; i < genres.size(); i++) {
            cout << "|" << setfill(' ') << setw(20) << left << genres[i];
        }
        cout << endl;

        // In đường kẻ ngang
        for (size_t i = 0; i <= genres.size(); i++) {
            cout << setfill('-') << setw(20) << "" << "+";
        }
        cout << endl;

        // In danh sách phim theo hàng
        for (size_t i = 0; i < maxMovies; i++) {
            cout << setfill(' ') << setw(20) << left << (i + 1);
            for (const auto& genre : genres) {
                cout << "|";
                if (i < moviesByGenre[genre].size()) {
                    cout << setw(20) << left << moviesByGenre[genre][i];
                } else {
                    cout << setw(20) << " ";
                }
            }
            cout << endl;
        }
    } else {
        cerr << "ERROR!" << endl;
    }
}

// Lấy danh sách phim của một thể loại
vector<string> MovieManager::getMoviesByGenre(const string& genre) {
    ifstream movieFile("Phim" + genre + ".txt");
    vector<string> movies;
    string line;

    if (movieFile) {
        while (getline(movieFile, line)) {
            movies.push_back(line); 
        }
    }
    return movies; 
}

// Khởi tạo số lượt xem cho tất cả phim
void MovieManager::initializeViewCounts() {
    ifstream genreFile("TheLoaiPhim.txt");
    ofstream viewCountFile("view_counts.txt");

    if (genreFile && viewCountFile) {
        string genre;
        while (getline(genreFile, genre)) {
            vector<string> movies = getMoviesByGenre(genre);
            for (const auto& movie : movies) {
                viewCountFile << movie << ": 0" << endl; 
            }
        }
    } else {
        cerr << "Khong the mo file de khoi tao!" << endl;
    }
}

void MovieManager::deleteMovie(const string& movieName, const string& genre) {
    ifstream inputFile("Phim" + genre + ".txt");
    ofstream tempFile("temp.txt");
    bool found = false;

    if (inputFile && tempFile) {
        string line;
        while (getline(inputFile, line)) {
            if (line == movieName) {
                found = true;
                cout << "Da xoa phim: " << movieName << " trong the loai: " << genre << endl;
                continue; 
            }
            tempFile << line << endl; 
        }
    } else {
        cerr << "Khong the mo file de doc hoac ghi!" << endl;
    }

    inputFile.close();
    tempFile.close();

    remove(("Phim" + genre + ".txt").c_str());
    rename("temp.txt", ("Phim" + genre + ".txt").c_str());

    if (!found) {
        cout << "Khong tim thay phim: " << movieName << " trong the loai: " << genre << endl;
    }
}

void MovieManager::updateMovie(const string& oldName, const string& newName, const string& genre) {
    ifstream inputFile("Phim" + genre + ".txt");
    ofstream tempFile("temp.txt");
    bool found = false;

    if (inputFile && tempFile) {
        string line;
        while (getline(inputFile, line)) {
            if (line == oldName) {
                found = true;
                tempFile << newName << endl;
                cout << "Da cap nhat phim: " << oldName << " thanh " << newName << endl;
            } else {
                tempFile << line << endl;
            }
        }
    } else {
        cerr << "Khong the mo file de doc hoac ghi!" << endl;
    }

    inputFile.close();
    tempFile.close();

    // Xóa file cũ và đổi tên file tạm thành file gốc
    remove(("Phim" + genre + ".txt").c_str());
    rename("temp.txt", ("Phim" + genre + ".txt").c_str());

    if (!found) {
        cout << "Khong tim thay phim: " << oldName << " trong the loai: " << genre << endl;
    }
}
