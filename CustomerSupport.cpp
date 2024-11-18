#include "CustomerSupport.h"

using namespace std;

// Constructor - Khởi tạo số lượt xem cho các phim
CustomerSupport::CustomerSupport() {
    movieManager.initializeViewCounts();
}

// Kiểm tra thông tin đăng nhập CSKH
bool CustomerSupport::loginCustomerSupport() {
    string username, password;
    cout << "Nhap ten dang nhap: ";
    cin >> username;
    cout << "Nhap mat khau: ";
    cin >> password;

    return (username == "Bin" && password == "123");
}

// Đọc phản hồi của khách hàng theo thể loại và phim
void CustomerSupport::readCustomerFeedback() {
    MovieManager movieManager; 

    // Lấy và hiển thị danh sách thể loại
    vector<string> genres = movieManager.getGenres(); 

    // Hiển thị danh sách thể loại
    cout << "Danh sach the loai phim:\n";
    for (size_t i = 0; i < genres.size(); ++i) {
        cout << i + 1 << ". " << genres[i] << endl;
    }

    // Cho phép chọn thể loại và phim để xem phản hồi
    int genreChoice;
    cout << "Chon the loai phim (nhap so): ";
    cin >> genreChoice;

    if (genreChoice > 0 && genreChoice <= genres.size()) {
        string selectedGenre = genres[genreChoice - 1];
        cout << "Ban da chon the loai: " << selectedGenre << endl;

        // Đọc danh sách phim theo thể loại từ MovieManager
        vector<string> movies = movieManager.getMoviesByGenre(selectedGenre); 

        // Hiển thị danh sách phim theo thể loại
        cout << "Danh sach phim trong the loai " << selectedGenre << ":\n";
        for (size_t i = 0; i < movies.size(); ++i) {
            cout << i + 1 << ". " << movies[i] << endl;
        }

        // Cho phép người dùng chọn phim
        int movieChoice;
        cout << "Chon phim de xem phan hoi (nhap so): ";
        cin >> movieChoice;

        if (movieChoice > 0 && movieChoice <= movies.size()) {
            string selectedMovie = movies[movieChoice - 1];
            ifstream feedbackFile(selectedMovie + "_feedback.txt");
            if (feedbackFile) {
                string line;
                cout << "Danh sach phan hoi cho phim " << selectedMovie << ":\n";
                bool hasFeedback = false; 
                while (getline(feedbackFile, line)) {
                    cout << "- " << line << endl; // In ra từng bình luận
                    hasFeedback = true; // Đã có bình luận
                }
                if (!hasFeedback) {
                    cout << "Phim " << selectedMovie << " chua co binh luan nao!" << endl;
                }
            } else {
                cerr << "Khong the mo file phan hoi cho phim " << selectedMovie << "!" << endl;
            }
        } else {
            cout << "Lua chon khong hop le!" << endl;
        }
    } else {
        cout << "Lua chon khong hop le!" << endl;
    }
}

// Thống kê số lượt xem của các phim
void CustomerSupport::statistics() {
    ifstream viewCountFile("view_counts.txt");
    if (viewCountFile) {
        string line;
        cout << "Thong ke so luot xem cho tung phim:\n";
        while (getline(viewCountFile, line)) {
            cout << line << endl; 
        }
    } else {
        cerr << "Khong the mo file thong ke so luot xem!" << endl;
    }
}
