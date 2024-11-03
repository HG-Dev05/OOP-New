#ifndef MOVIE_MANAGER_H
#define MOVIE_MANAGER_H

#include <string>
#include <vector>

class MovieManager {
public:
    void addMovie(const std::string& movieName, const std::string& genre);
    void deleteMovie(const std::string& movieName, const std::string& genre); 
    void updateMovie(const std::string& oldName, const std::string& newName, const std::string& genre);

    void viewMoviesByGenre(const std::string& genre);
    std::vector<std::string> getGenres();
    void viewAllMovies();
    std::vector<std::string> getMoviesByGenre(const std::string& genre);
};

#endif // MOVIE_MANAGER_H
