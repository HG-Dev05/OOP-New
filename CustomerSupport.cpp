#include "CustomerSupport.h"

// Constructor
CustomerSupport::CustomerSupport() {
    loadFeedbacks(); // Tải phản hồi khi khởi tạo
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
    std::cout << "Danh sach phan hoi khach hang:\n";
    for (const auto& feedback : feedbacks) {
        std::cout << "- " << feedback << std::endl;
    }
}

// Hàm tải phản hồi từ file
void CustomerSupport::loadFeedbacks() {
    // Giả định có một số phản hồi mẫu
    feedbacks.push_back("Phim rất hay!");
    feedbacks.push_back("Tôi không thích kết thúc.");
    feedbacks.push_back("Diễn viên diễn xuất rất tốt.");
}

// Hàm đọc phản hồi từ file theo tên phim
void CustomerSupport::readFeedbackByMovie(const std::string& movieName) {
    std::ifstream feedbackFile(movieName + "_feedback.txt");
    if (feedbackFile) {
        std::string line;
        std::cout << "Phan hoi ve phim " << movieName << ":\n";
        while (std::getline(feedbackFile, line)) {
            std::cout << "- " << line << std::endl;
        }
    } else {
        std::cerr << "Khong the mo file phan hoi cho phim " << movieName << "!" << std::endl;
    }
}

