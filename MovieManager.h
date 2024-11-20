#ifndef MOVIE_MANAGER_H
#define MOVIE_MANAGER_H

#include <string>
#include <vector>

using namespace std;

class MovieManager {
public:
    void addMovie(const string& movieName, const string& genre);
    void deleteMovie(const string& movieName, const string& genre); 
    void updateMovie(const string& oldName, const string& newName, const string& genre);

    void viewMoviesByGenre(const string& genre);
    vector<string> getGenres();
    void viewAllMovies();
    vector<string> getMoviesByGenre(const string& genre);

    void initializeViewCounts();
};

#endif 
