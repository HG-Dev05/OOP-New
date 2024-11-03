#include "CustomerSupport.h"

// Định nghĩa hàm khởi tạo
CustomerSupport::CustomerSupport() {
    movieManager.initializeViewCounts(); // Gọi phương thức khởi tạo
}


// Hàm đăng nhập cho tài khoản chăm sóc khách hàng
bool CustomerSupport::loginCustomerSupport() {
    std::string username, password;
    std::cout << "Nhap ten dang nhap: ";
    std::cin >> username;
    std::cout << "Nhap mat khau: ";
    std::cin >> password;

    // Kiểm tra thông tin đăng nhập (giả định thông tin đăng nhập là đúng)
    return (username == "Bin" && password == "123");
}

// Hàm đọc phản hồi của khách hàng
void CustomerSupport::readCustomerFeedback() {
    MovieManager movieManager; // Tạo đối tượng MovieManager

    // Đọc danh sách thể loại từ file
    std::vector<std::string> genres = movieManager.getGenres(); // Sử dụng phương thức getGenres

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

        // Đọc danh sách phim theo thể loại từ MovieManager
        std::vector<std::string> movies = movieManager.getMoviesByGenre(selectedGenre); // Sử dụng phương thức getMoviesByGenre

        // Hiển thị danh sách phim theo thể loại
        std::cout << "Danh sach phim trong the loai " << selectedGenre << ":\n";
        for (size_t i = 0; i < movies.size(); ++i) {
            std::cout << i + 1 << ". " << movies[i] << std::endl;
        }

        // Cho phép người dùng chọn phim
        int movieChoice;
        std::cout << "Chon phim de xem phan hoi (nhap so): ";
        std::cin >> movieChoice;

        if (movieChoice > 0 && movieChoice <= movies.size()) {
            std::string selectedMovie = movies[movieChoice - 1];
            std::ifstream feedbackFile(selectedMovie + "_feedback.txt");
            if (feedbackFile) {
                std::string line;
                std::cout << "Danh sach phan hoi cho phim " << selectedMovie << ":\n";
                bool hasFeedback = false; // Biến kiểm tra có bình luận hay không
                while (std::getline(feedbackFile, line)) {
                    std::cout << "- " << line << std::endl; // In ra từng bình luận
                    hasFeedback = true; // Đã có bình luận
                }
                if (!hasFeedback) {
                    std::cout << "Phim " << selectedMovie << " chua co binh luan nao!" << std::endl; // Thông báo nếu không có bình luận
                }
            } else {
                std::cerr << "Khong the mo file phan hoi cho phim " << selectedMovie << "!" << std::endl;
            }
        } else {
            std::cout << "Lua chon khong hop le!" << std::endl;
        }
    } else {
        std::cout << "Lua chon khong hop le!" << std::endl;
    }
}

// Định nghĩa hàm statistics
void CustomerSupport::statistics() {
    std::ifstream viewCountFile("view_counts.txt");
    if (viewCountFile) {
        std::string line;
        std::cout << "Thong ke so luot xem cho tung phim:\n";
        while (std::getline(viewCountFile, line)) {
            std::cout << line << std::endl; // In ra số lượt xem cho từng phim
        }
    } else {
        std::cerr << "Khong the mo file thong ke so luot xem!" << std::endl;
    }
}
