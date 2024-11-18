#include <iostream>
#include <limits> 
#include <fstream>
#include <map>
#include "UserAuth.h"
#include <ctime>
#include <cstdio>
#include <sstream>

using namespace std;

User::User(string user, string pass) : username(user), password(pass) {}

// Đăng ký tài khoản mới và lưu vào file
void User::registerUser() {
    cout << "\n=== DANG KY TAI KHOAN ===\n";

    // Nhập tên người dùng
    do {
        cin.ignore();
        cout << "Nhap ten nguoi dung (toi thieu 3 ky tu): ";
        getline(cin, username);

        if (username.length() < 3) {
            cout << "Ten nguoi dung qua ngan! Vui long nhap lai.\n";
        }
    } while (username.length() < 3);

    // Kiểm tra tên đăng nhập đã tồn tại
    ifstream inputFile("users.txt");
    string line;
    while (getline(inputFile, line)) {
        if (line.find("Ten Dang Nhap: " + username) != string::npos) {
            cout << "Ten dang nhap da ton tai! Vui long chon ten khac.\n";
            return; 
        }
    }
    inputFile.close();

    // Nhập mật khẩu
    do {
        cout << "Nhap mat khau (toi thieu 6 ky tu): ";
        getline(cin, password);
        if (password.length() < 6) {
            cout << "Mat khau qua ngan! Vui long nhap lai.\n";
        }
    } while (password.length() < 6);

    // Nhập email
    do {
        cout << "Nhap email (example@domain.com): ";
        getline(cin, email);
        if (!isValidEmail(email)) {
            cout << "Email khong hop le! Vui long nhap lai.\n";
        }
    } while (!isValidEmail(email));

    // Nhập số điện thoại
    do {
        cout << "Nhap so dien thoai (10 so, bat dau bang so 0): ";
        getline(cin, phone);
        if (!isValidPhone(phone)) {
            cout << "So dien thoai khong hop le! Vui long nhap lai.\n";
        }
    } while (!isValidPhone(phone));

    // Nhập địa chỉ
    do {
        cout << "Nhap dia chi: ";
        getline(cin, address);
        if (address.empty()) {
            cout << "Dia chi khong duoc de trong! Vui long nhap lai.\n";
        }
    } while (address.empty());

    // Nhập ngày sinh
    do {
        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        getline(cin, birthdate);
        if (!isValidBirthdate(birthdate)) {
            cout << "Ngay sinh khong hop le! Vui long nhap lai.\n";
        }
    } while (!isValidBirthdate(birthdate));

    // Ghi thông tin người dùng vào file
    ofstream outputFile("users.txt", ios::app);
    if (outputFile) {
        outputFile << "Ten Dang Nhap: " << username << "\n"
                   << "Mat Khau: " << password << "\n"
                   << "Email: " << email << "\n"
                   << "So Dien Thoai: " << phone << "\n"
                   << "Dia Chi: " << address << "\n"
                   << "Ngay Sinh: " << birthdate << "\n"
                   << "------------------------" << endl;
        cout << "\nDang ky thanh cong!\n";
    } else {
        cerr << "Loi: Dang Ky That Bai!\n";
    }
}

// Kiểm tra thông tin đăng nhập 
bool User::loginUser() {
    string inputUser, inputPass;
    cout << "\n=== DANG NHAP ===\n";
    cout << "Nhap ten nguoi dung: ";
    cin >> inputUser;
    cout << "Nhap mat khau: ";
    cin >> inputPass;

    ifstream inputFile("users.txt");
    if (inputFile) {
        string line;
        while (getline(inputFile, line)) {
            if (line.find("Ten Dang Nhap: " + inputUser) != string::npos) {
                getline(inputFile, line); 
                if (line == "Mat Khau: " + inputPass) {
                    getline(inputFile, line);
                    getline(inputFile, line);
                    getline(inputFile, line);
                    getline(inputFile, line);

                    username = inputUser;
                    password = inputPass;
                    
                    cout << "\nDang nhap thanh cong!\n";
                    return true;
                } else {
                    cout << "\nMat khau khong dung!\n";
                    return false;
                }
            }
        }
        cout << "\nTen nguoi dung khong ton tai!\n";
    } else {
        cerr << "Loi: Khong the mo file de doc!\n";
    }
    return false;
}

// Xem và chọn phim để xem
void User::viewMovies() {

    vector<string> genres = movieManager.getGenres();
    
    // Hiển thị danh sách thể loại cho người dùng chọn
    cout << "\n==============================\n";
    cout << "Danh sach the loai phim:\n";
    cout << "==============================\n";
    for (size_t i = 0; i < genres.size(); ++i) {
        cout << i + 1 << ". " << genres[i] << endl;
    }
    cout << "==============================\n";

    // Cho người dùng chọn thể loại phim
    int genreChoice;
    do {
        cout << "Chon the loai phim (nhap so): ";
        cin >> genreChoice;
        
        if (genreChoice <= 0 || genreChoice > genres.size()) {
            cout << "Lua chon khong hop le! Vui long chon lai.\n";
        }
    } while (genreChoice <= 0 || genreChoice > genres.size());

    string selectedGenre = genres[genreChoice - 1];
    cout << "Ban da chon the loai: " << selectedGenre << endl;

    // Hiển thị danh sách phim theo thể loại đã chọn
    cout << "\n======================================\n";
    cout << "Danh sach phim trong the loai " << selectedGenre << ":\n";
    cout << "========================================\n";
    vector<string> movies = movieManager.getMoviesByGenre(selectedGenre);
    for (size_t i = 0; i < movies.size(); ++i) {
        cout << i + 1 << ". " << movies[i] << endl;
    }
    cout << "----------------------------------------\n";

    // Cho phép người dùng chọn phim
    int movieChoice;
    do {
        cout << "Chon phim de xem (nhap so): ";
        cin >> movieChoice;
        
        if (movieChoice <= 0 || movieChoice > movies.size()) {
            cout << "Lua chon khong hop le! Vui long chon lai.\n";
        }
    } while (movieChoice <= 0 || movieChoice > movies.size());

    string selectedMovie = movies[movieChoice - 1];
    cout << "==============================\n";
    cout << "     ĐANG XEM PHIM: " << selectedMovie << "     \n";
    cout << "==============================\n";
    cout << "        Hãy thưởng thức!        \n";
    cout << "==============================\n";
    // Cập nhật số lượt xem cho phim được chọn
    ifstream viewCountFile("view_counts.txt");
    map<string, int> viewCounts;
    string line;

    // Đọc số lượt xem từ file
    while (getline(viewCountFile, line)) {
        size_t pos = line.find(":");
        if (pos != string::npos) {
            string movieName = line.substr(0, pos);
            int count = stoi(line.substr(pos + 1));
            viewCounts[movieName] = count;
        }
    }
    viewCountFile.close();


    viewCounts[selectedMovie]++;

    // Ghi lại số lượt xem vào file
    ofstream outputFile("view_counts.txt");
    for (const auto& entry : viewCounts) {
        outputFile << entry.first << ": " << entry.second << endl;
    }
    outputFile.close();

    // Ghi lịch sử xem phim với timestamp
    ofstream historyFile(username + "_history.txt", ios::app);
    if (historyFile) {
        time_t now = time(nullptr);
        tm* localTime = localtime(&now);
        historyFile << selectedMovie << " - " 
                    << (localTime->tm_year + 1900) << "-" 
                    << (localTime->tm_mon + 1) << "-" 
                    << localTime->tm_mday << " " 
                    << localTime->tm_hour << ":" 
                    << localTime->tm_min << endl;
    }

    // Xử lý các tùy chọn sau khi xem phim (dừng/bình luận)
    int actionChoice;
    do {
        cout << "Chon hanh dong:\n"
                  << "1. Dung phim\n"
                  << "2. Them binh luan\n"
                  << "3. Thoat\n";
        cout << "Nhap so: ";
        
        while (!(cin >> actionChoice) || actionChoice < 1 || actionChoice > 3) {
            cout << "Lua chon khong hop le! Vui long chon lai (1-3): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (actionChoice) {
            case 1: {
                cout << "Phim da duoc dung!" << endl;
                cout << "\nNhan Enter de tiep tuc...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }
            case 2: {
                string feedback;
                cout << "Nhap phan hoi ve phim: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, feedback);

                ofstream feedbackFile(selectedMovie + "_feedback.txt", ios::app);
                if (feedbackFile) {
                    feedbackFile << username << ": " << feedback << endl;
                    cout << "Binh luan da duoc luu!" << endl;
                } else {
                    cerr << "Khong the mo file de ghi phan hoi!" << endl;
                }
                
                cout << "\nNhan Enter de tiep tuc...";
                cin.get();
                break;
            }
            case 3: {
                cout << "Thoat khoi chuc nang xem phim." << endl;
                break;
            }
        }
    } while (actionChoice != 3);
}

// Xem lịch sử các phim đã xem
void User::viewWatchHistory() {
    ifstream historyFile(username + "_history.txt");
    if (historyFile) {
        string line;
        cout << "Lich su phim da xem:\n";
        while (getline(historyFile, line)) {
            cout << "- " << line << endl; 
        }
    } else {
        cerr << "Lich Su Xem Rong!" << endl;
    }
}


// Xóa toàn bộ lịch sử xem phim
void User::clearWatchHistory() {
    string historyFileName = username + "_history.txt";
    if (remove(historyFileName.c_str()) == 0) {
        cout << "Da xoa lich su xem phim!" << endl;
    } else {
        cerr << "Lich Su Xem Rong!" << endl;
    }
}

// Thêm các hàm kiểm tra tính hợp lệ
bool User::isValidEmail(const string& email) {
    // Kiểm tra email có chứa @ và .
    return email.find('@') != string::npos && 
           email.find('.') != string::npos &&
           email.find('@') < email.find_last_of('.');
}

bool User::isValidPhone(const string& phone) {
    // Kiểm tra số điện thoại có 10 số và bắt đầu bằng 0
    if (phone.length() != 10 || phone[0] != '0') return false;
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool User::isValidBirthdate(const string& birthdate) {
    // Kiểm tra định dạng dd/mm/yyyy
    if (birthdate.length() != 10) return false;
    if (birthdate[2] != '/' || birthdate[5] != '/') return false;

    try {
        int day = stoi(birthdate.substr(0, 2));
        int month = stoi(birthdate.substr(3, 2));
        int year = stoi(birthdate.substr(6, 4));

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
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
