#include <iostream>
#include <fstream>
#include "Admin.h"
#include "Utils.h"

using namespace std;

bool Admin::loginAdmin() {
    string user, pass;
    cout << "Nhap ten admin: ";
    cin >> user;
    cout << "Nhap mat khau admin: ";
    cin >> pass;

    if (user == adminUsername && pass == adminPassword) {
        cout << "Dang nhap admin thanh cong!" << endl;
        return true;
    } else {
        cout << "Ten dang nhap hoac mat khau admin khong dung!" << endl;
        return false;
    }
}

void Admin::viewUsers() {
    ifstream inputFile("users.txt");
    if (inputFile) {
        string line;
        cout << "Danh sach nguoi dung:\n";
        while (getline(inputFile, line)) {
            if (line.find("Ten Dang Nhap:") != string::npos) {
                cout << line << endl;
                for (int i = 0; i < 5; ++i) {
                    if (getline(inputFile, line)) {
                        cout << line << endl;
                    }
                }
                cout << "------------------------" << endl;
            }
        }
    } else {
        cerr << "Danh Sach Nguoi Dung Trong!" << endl;
    }
}

void Admin::deleteUser(const string& username) {
    ifstream inputFile("users.txt");
    ofstream tempFile("temp.txt");
    bool found = false;
    string line;

    if (inputFile && tempFile) {
        while (getline(inputFile, line)) {
            if (line == "Ten Dang Nhap: " + username) {
                found = true;
                // Bỏ qua 6 dòng thông tin của user (bao gồm cả dòng phân cách)
                for (int i = 0; i < 6; i++) {
                    getline(inputFile, line);
                }
                continue;
            }
            tempFile << line << endl;
        }

        inputFile.close();
        tempFile.close();

        if (found) {
            remove("users.txt");
            rename("temp.txt", "users.txt");
            
            // Xóa các file liên quan đến user
            remove((username + "_history.txt").c_str());
            remove((username + "_feedback.txt").c_str());
            
            cout << "Da xoa nguoi dung: " << username << endl;
        } else {
            remove("temp.txt");
            cout << "Khong tim thay nguoi dung: " << username << endl;
        }
    } else {
        cerr << "Khong the mo file de doc hoac ghi!" << endl;
    }
}

void Admin::manageMovies() {
    int choice;
    do {
        drawBorder(40);
        cout << "**          QUAN LY PHIM           **\n";
        drawBorder(40);
        cout << "** 1. Them phim                     **\n";
        cout << "** 2. Xoa phim                     **\n";
        cout << "** 3. Cap nhat phim                **\n";
        cout << "** 4. Xem danh sach phim           **\n";
        cout << "** 5. Thoat                        **\n";
        drawBorder(40);
        cout << "Chon chuc nang: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string movieName, genre;
                vector<string> genres = movieManager.getGenres();
                cout << "Danh sach the loai phim:\n";
                for (size_t i = 0; i < genres.size(); ++i) {
                    cout << i + 1 << ". " << genres[i] << endl;
                }
                cout << genres.size() + 1 << ". Them the loai moi" << endl;
                int genreChoice;
                cout << "Chon the loai phim (nhap so): ";
                cin >> genreChoice;
                cin.ignore();
                if (genreChoice > 0 && genreChoice <= genres.size()) {
                    genre = genres[genreChoice - 1];
                } else if (genreChoice == genres.size() + 1) {
                    cout << "Nhap ten the loai moi: ";
                    getline(cin, genre);
                    ofstream genreFile("TheLoaiPhim.txt", ios::app);
                    if (genreFile) {
                        genreFile << genre << endl;
                    }
                } else {
                    cout << "Lua chon khong hop le!" << endl;
                    break;
                }
                cout << "Nhap ten phim can them: ";
                getline(cin, movieName);
                movieManager.addMovie(movieName, genre);
                break;
            }
            case 2: {
                string movieName, genre;
                vector<string> genres = movieManager.getGenres();
                cout << "Danh sach the loai phim:\n";
                for (size_t i = 0; i < genres.size(); ++i) {
                    cout << i + 1 << ". " << genres[i] << endl;
                }
                int genreChoice;
                cout << "Chon the loai phim (nhap so): ";
                cin >> genreChoice;
                cin.ignore();
                if (genreChoice > 0 && genreChoice <= genres.size()) {
                    genre = genres[genreChoice - 1];
                } else {
                    cout << "Lua chon khong hop le!" << endl;
                    break;
                }
                cout << "Danh sach phim trong the loai " << genre << ":\n";
                movieManager.viewMoviesByGenre(genre);
                cout << "Nhap ten phim can xoa: ";
                getline(cin, movieName);
                movieManager.deleteMovie(movieName, genre);
                break;
            }
            case 3: {
                string oldName, newName, genre;
                vector<string> genres = movieManager.getGenres();
                cout << "Danh sach the loai phim:\n";
                for (size_t i = 0; i < genres.size(); ++i) {
                    cout << i + 1 << ". " << genres[i] << endl;
                }
                int genreChoice;
                cout << "Chon the loai phim (nhap so): ";
                cin >> genreChoice;
                cin.ignore();
                if (genreChoice > 0 && genreChoice <= genres.size()) {
                    genre = genres[genreChoice - 1];
                } else {
                    cout << "Lua chon khong hop le!" << endl;
                    break;
                }
                cout << "Danh sach phim trong the loai " << genre << ":\n";
                movieManager.viewMoviesByGenre(genre);
                cout << "Nhap ten phim cu: ";
                getline(cin, oldName);
                cout << "Nhap ten phim moi: ";
                getline(cin, newName);
                movieManager.updateMovie(oldName, newName, genre);
                break;
            }
            case 4:
                movieManager.viewAllMovies();
                break;
            case 5:
                cout << "Thoat chuc nang quan ly phim." << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    } while (choice != 5);
}

void Admin::addMovie(const string& movieName) {
    ofstream outputFile("movies.txt", ios::app);
    if (outputFile) {
        outputFile << movieName << endl;
        cout << "Da them phim: " << movieName << endl;
    } else {
        cerr << "Khong the mo file de ghi!" << endl;
    }
}

void Admin::deleteMovie(const string& movieName) {
    ifstream inputFile("movies.txt");
    ofstream tempFile("temp_movies.txt");
    bool found = false;

    if (inputFile && tempFile) {
        string fileMovie;
        while (getline(inputFile, fileMovie)) {
            if (fileMovie == movieName) {
                found = true;
                cout << "Da xoa phim: " << movieName << endl;
                continue;
            }
            tempFile << fileMovie << endl;
        }
    } else {
        cerr << "Khong the mo file de doc hoac ghi!" << endl;
    }

    inputFile.close();
    tempFile.close();

    remove("movies.txt");
    rename("temp_movies.txt", "movies.txt");

    if (!found) {
        cout << "Khong tim thay phim: " << movieName << endl;
    }
}

void Admin::updateMovie(const string& oldName, const string& newName) {
    ifstream inputFile("movies.txt");
    ofstream tempFile("temp_movies.txt");
    bool found = false;

    if (inputFile && tempFile) {
        string fileMovie;
        while (getline(inputFile, fileMovie)) {
            if (fileMovie == oldName) {
                found = true;
                tempFile << newName << endl;
                cout << "Da cap nhat phim: " << oldName << " thanh " << newName << endl;
            } else {
                tempFile << fileMovie << endl;
            }
        }
    } else {
        cerr << "Khong the mo file de doc hoac ghi!" << endl;
    }

    inputFile.close();
    tempFile.close();

    remove("movies.txt");
    rename("temp_movies.txt", "movies.txt");

    if (!found) {
        cout << "Khong tim thay phim: " << oldName << endl;
    }
}

void Admin::manageUsers() {
    int choice;
    do {
        drawBorder(40);
        cout << "**        QUAN LY NGUOI DUNG        **\n";
        drawBorder(40);
        cout << "** 1. Xem danh sach nguoi dung      **\n";
        cout << "** 2. Xoa nguoi dung                **\n";
        cout << "** 3. Xem hoat dong cua nguoi dung  **\n";
        cout << "** 4. Thoat                         **\n";
        drawBorder(40);
        cout << "Chon chuc nang: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                viewUsers();
                break;
            case 2: {
                string username;
                cout << "Nhap ten nguoi dung can xoa: ";
                getline(cin, username);
                deleteUser(username);
                break;
            }
            case 3: {
                string username;
                cout << "Nhap ten nguoi dung: ";
                getline(cin, username);
                viewUserActivity(username);
                break;
            }
            case 4:
                cout << "Thoat chuc nang quan ly nguoi dung." << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    } while (choice != 4);
}

void Admin::viewUserActivity(const string& username) {
    ifstream inputFile(username + "_history.txt");
    if (inputFile) {
        string line;
        cout << "Lich su xem phim cua nguoi dung " << username << ":\n";
        while (getline(inputFile, line)) {
            cout << "- " << line << endl;
        }
    } else {
        cerr << "Khong the mo file lich su hoat dong!" << endl;
    }

    ifstream feedbackFile(username + "_feedback.txt");
    if (feedbackFile) {
        string feedbackLine;
        cout << "Binh luan cua nguoi dung " << username << ":\n";
        while (getline(feedbackFile, feedbackLine)) {
            cout << "- " << feedbackLine << endl;
        }
    } else {
        cerr << "Khong the mo file binh luan!" << endl;
    }
}
