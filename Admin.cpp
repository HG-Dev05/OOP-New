#include <iostream>
#include <fstream>
#include "Admin.h"
#include "Utils.h" 


bool Admin::loginAdmin() {
    std::string user, pass;
    std::cout << "Nhap ten admin: ";
    std::cin >> user;
    std::cout << "Nhap mat khau admin: ";
    std::cin >> pass;

    if (user == adminUsername && pass == adminPassword) {
        std::cout << "Dang nhap admin thanh cong!" << std::endl;
        return true;
    } else {
        std::cout << "Ten dang nhap hoac mat khau admin khong dung!" << std::endl;
        return false;
    }
}

void Admin::viewUsers() {
    std::ifstream inputFile("users.txt");
    if (inputFile) {
        std::string fileUser, filePass;
        std::cout << "Danh sach nguoi dung:\n";
        while (inputFile >> fileUser >> filePass) {
            std::cout << "Ten nguoi dung: " << fileUser << std::endl;
        }
    } else {
        std::cerr << "Khong the mo file de doc!" << std::endl;
    }
}

void Admin::deleteUser(const std::string& username) {
    std::ifstream inputFile("users.txt");
    std::ofstream tempFile("temp.txt");
    bool found = false;

    if (inputFile && tempFile) {
        std::string fileUser, filePass;
        while (inputFile >> fileUser >> filePass) {
            if (fileUser == username) {
                found = true; // Danh dau la da tim thay nguoi dung
                std::cout << "Da xoa nguoi dung: " << username << std::endl;
                continue; // Bo qua viec ghi vao file tam
            }
            tempFile << fileUser << " " << filePass << std::endl; // Ghi lai nguoi dung khac
        }
    } else {
        std::cerr << "Khong the mo file de doc hoac ghi!" << std::endl;
    }

    inputFile.close();
    tempFile.close();

    // Xoa file cu va doi ten file tam thanh file goc
    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (!found) {
        std::cout << "Khong tim thay nguoi dung: " << username << std::endl;
    }
}

void Admin::manageMovies() {
    int choice;
    do {
        drawBorder(40);
        std::cout << "**          QUAN LY PHIM           **\n";
        drawBorder(40);
        std::cout << "** 1. Them phim                     **\n";
        std::cout << "** 2. Xoa phim                     **\n";
        std::cout << "** 3. Cap nhat phim                **\n";
        std::cout << "** 4. Xem danh sach phim           **\n";
        std::cout << "** 5. Thoat                        **\n";
        drawBorder(40);
        std::cout << "Chon chuc nang: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Thêm phim
                std::string movieName, genre;
                std::vector<std::string> genres = movieManager.getGenres(); // Lấy danh sách thể loại

                // Hiển thị danh sách thể loại
                std::cout << "Danh sach the loai phim:\n";
                for (size_t i = 0; i < genres.size(); ++i) {
                    std::cout << i + 1 << ". " << genres[i] << std::endl;
                }
                std::cout << genres.size() + 1 << ". Them the loai moi" << std::endl; // Thêm tùy chọn thêm thể loại mới

                // Cho phép người dùng chọn thể loại
                int genreChoice;
                std::cout << "Chon the loai phim (nhap so): ";
                std::cin >> genreChoice;
                std::cin.ignore(); // Bỏ qua ký tự newline còn lại

                if (genreChoice > 0 && genreChoice <= genres.size()) {
                    genre = genres[genreChoice - 1]; // Chọn thể loại đã có
                } else if (genreChoice == genres.size() + 1) {
                    // Thêm thể loại mới
                    std::cout << "Nhap ten the loai moi: ";
                    std::getline(std::cin, genre); // Sử dụng getline để nhập thể loại mới
                    // Ghi thể loại mới vào file TheLoaiPhim.txt
                    std::ofstream genreFile("TheLoaiPhim.txt", std::ios::app);
                    if (genreFile) {
                        genreFile << genre << std::endl; // Ghi thể loại mới
                    }
                } else {
                    std::cout << "Lua chon khong hop le!" << std::endl;
                    break;
                }

                // Nhập tên phim
                std::cout << "Nhap ten phim can them: ";
                std::getline(std::cin, movieName); // Sử dụng getline để nhập tên phim
                movieManager.addMovie(movieName, genre); // Gọi hàm thêm phim với thể loại
                break;
            }
            case 2: {
                // Xóa phim
                std::string movieName, genre;
                std::vector<std::string> genres = movieManager.getGenres(); // Lấy danh sách thể loại

                // Hiển thị danh sách thể loại
                std::cout << "Danh sach the loai phim:\n";
                for (size_t i = 0; i < genres.size(); ++i) {
                    std::cout << i + 1 << ". " << genres[i] << std::endl;
                }

                // Cho phép người dùng chọn thể loại
                int genreChoice;
                std::cout << "Chon the loai phim (nhap so): ";
                std::cin >> genreChoice;
                std::cin.ignore(); // Bỏ qua ký tự newline còn lại

                if (genreChoice > 0 && genreChoice <= genres.size()) {
                    genre = genres[genreChoice - 1]; // Chọn thể loại đã có
                } else {
                    std::cout << "Lua chon khong hop le!" << std::endl;
                    break;
                }

                // Hiển thị danh sách phim trong thể loại đã chọn
                std::cout << "Danh sach phim trong the loai " << genre << ":\n";
                movieManager.viewMoviesByGenre(genre); // Gọi hàm để hiển thị danh sách phim

                // Nhập tên phim cần xóa
                std::cout << "Nhap ten phim can xoa: ";
                std::getline(std::cin, movieName); // Sử dụng getline để nhập tên phim
                movieManager.deleteMovie(movieName, genre); // Gọi hàm xóa phim với thể loại
                break;
            }
            case 3: {
                // Cập nhật phim
                std::string oldName, newName, genre;
                std::vector<std::string> genres = movieManager.getGenres(); // Lấy danh sách thể loại

                // Hiển thị danh sách thể loại
                std::cout << "Danh sach the loai phim:\n";
                for (size_t i = 0; i < genres.size(); ++i) {
                    std::cout << i + 1 << ". " << genres[i] << std::endl;
                }

                // Cho phép người dùng chọn thể loại
                int genreChoice;
                std::cout << "Chon the loai phim (nhap so): ";
                std::cin >> genreChoice;
                std::cin.ignore(); // Bỏ qua ký tự newline còn lại

                if (genreChoice > 0 && genreChoice <= genres.size()) {
                    genre = genres[genreChoice - 1]; // Chọn thể loại đã có
                } else {
                    std::cout << "Lua chon khong hop le!" << std::endl;
                    break;
                }

                // Hiển thị danh sách phim trong thể loại đã chọn
                std::cout << "Danh sach phim trong the loai " << genre << ":\n";
                movieManager.viewMoviesByGenre(genre); // Gọi hàm để hiển thị danh sách phim

                // Nhập tên phim cần cập nhật
                std::cout << "Nhap ten phim cu: ";
                std::getline(std::cin, oldName); // Sử dụng getline để nhập tên phim cũ
                std::cout << "Nhap ten phim moi: ";
                std::getline(std::cin, newName); // Sử dụng getline để nhập tên phim mới
                movieManager.updateMovie(oldName, newName, genre); // Gọi hàm cập nhật phim với thể loại
                break;
            }
            case 4: // Xem danh sách phim
                movieManager.viewAllMovies();
                break;
            case 5:
                std::cout << "Thoat chuc nang quan ly phim." << std::endl;
                break;
            default:
                std::cout << "Lua chon khong hop le!" << std::endl;
        }
    } while (choice != 5);
}

void Admin::addMovie(const std::string& movieName) {
    std::ofstream outputFile("movies.txt", std::ios::app); // Mo file o che do append
    if (outputFile) {
        outputFile << movieName << std::endl;
        std::cout << "Da them phim: " << movieName << std::endl;
    } else {
        std::cerr << "Khong the mo file de ghi!" << std::endl;
    }
}

void Admin::deleteMovie(const std::string& movieName) {
    std::ifstream inputFile("movies.txt");
    std::ofstream tempFile("temp_movies.txt");
    bool found = false;

    if (inputFile && tempFile) {
        std::string fileMovie;
        while (std::getline(inputFile, fileMovie)) {
            if (fileMovie == movieName) {
                found = true; // Danh dau la da tim thay phim
                std::cout << "Da xoa phim: " << movieName << std::endl;
                continue; // Bo qua viec ghi vao file tam
            }
            tempFile << fileMovie << std::endl; // Ghi lai phim khac
        }
    } else {
        std::cerr << "Khong the mo file de doc hoac ghi!" << std::endl;
    }

    inputFile.close();
    tempFile.close();

    // Xoa file cu va doi ten file tam thanh file goc
    remove("movies.txt");
    rename("temp_movies.txt", "movies.txt");

    if (!found) {
        std::cout << "Khong tim thay phim: " << movieName << std::endl;
    }
}

void Admin::updateMovie(const std::string& oldName, const std::string& newName) {
    std::ifstream inputFile("movies.txt");
    std::ofstream tempFile("temp_movies.txt");
    bool found = false;

    if (inputFile && tempFile) {
        std::string fileMovie;
        while (std::getline(inputFile, fileMovie)) {
            if (fileMovie == oldName) {
                found = true; // Danh dau la da tim thay phim
                tempFile << newName << std::endl; // Ghi ten phim moi
                std::cout << "Da cap nhat phim: " << oldName << " thanh " << newName << std::endl;
            } else {
                tempFile << fileMovie << std::endl; // Ghi lai phim khac
            }
        }
    } else {
        std::cerr << "Khong the mo file de doc hoac ghi!" << std::endl;
    }

    inputFile.close();
    tempFile.close();

    // Xoa file cu va doi ten file tam thanh file goc
    remove("movies.txt");
    rename("temp_movies.txt", "movies.txt");

    if (!found) {
        std::cout << "Khong tim thay phim: " << oldName << std::endl;
    }
}

void Admin::manageUsers() {
    int choice;
    do {
        drawBorder(40);
        std::cout << "**        QUAN LY NGUOI DUNG      **\n";
        drawBorder(40);
        std::cout << "** 1. Xem danh sach nguoi dung     **\n";
        std::cout << "** 2. Xoa nguoi dung                **\n";
        std::cout << "** 3. Xem hoat dong cua nguoi dung  **\n";
        std::cout << "** 4. Thoat                        **\n";
        drawBorder(40);
        std::cout << "Chon chuc nang: ";
        std::cin >> choice;
        std::cin.ignore(); // Bỏ qua ký tự newline còn lại

        switch (choice) {
            case 1:
                viewUsers(); // Gọi hàm xem danh sách người dùng
                break;
            case 2: {
                std::string username;
                std::cout << "Nhap ten nguoi dung can xoa: ";
                std::getline(std::cin, username); // Nhập tên người dùng cần xóa
                deleteUser(username); // Gọi hàm xóa người dùng
                break;
            }
            case 3: {
                std::string username;
                std::cout << "Nhap ten nguoi dung: ";
                std::getline(std::cin, username); // Nhập tên người dùng để xem hoạt động
                viewUserActivity(username); // Gọi hàm xem hoạt động của người dùng
                break;
            }
            case 4:
                std::cout << "Thoat chuc nang quan ly nguoi dung." << std::endl;
                break;
            default:
                std::cout << "Lua chon khong hop le!" << std::endl;
        }
    } while (choice != 4);
}

void Admin::viewUserActivity(const std::string& username) {
    std::ifstream inputFile(username + "_activity.txt"); // Giả sử lịch sử xem của người dùng được lưu trong file <username>_activity.txt
    if (inputFile) {
        std::string line;
        std::cout << "Lich su xem phim cua nguoi dung " << username << ":\n";
        while (std::getline(inputFile, line)) {
            std::cout << "- " << line << std::endl; // In lịch sử xem
        }
    } else {
        std::cerr << "Khong the mo file lich su hoat dong!" << std::endl;
    }
}
