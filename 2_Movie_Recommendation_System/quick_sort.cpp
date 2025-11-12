#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Movie
{
    int movie_id;
    string movie_name;
    double movie_rating;
    int release_year;
    long long total_watch_time;
};

int sort_criteria = 1;

// compare two movies based on selected criteria
bool compareMovies(const Movie &first_movie, const Movie &second_movie)
{
    if (sort_criteria == 1)
        return first_movie.movie_rating > second_movie.movie_rating;
    else if (sort_criteria == 2)
        return first_movie.release_year > second_movie.release_year;
    else
        return first_movie.total_watch_time > second_movie.total_watch_time;
}

// partition array around pivot element
int partition(vector<Movie> &movie_list, int low_index, int high_index)
{
    Movie pivot_movie = movie_list[high_index];
    int smaller_element_index = low_index - 1;

    for (int current_index = low_index; current_index < high_index; current_index++)
    {
        if (compareMovies(movie_list[current_index], pivot_movie))
        {
            smaller_element_index++;
            swap(movie_list[smaller_element_index], movie_list[current_index]);
        }
    }
    swap(movie_list[smaller_element_index + 1], movie_list[high_index]);
    return smaller_element_index + 1;
}

// sort movies using quicksort algorithm
void quickSort(vector<Movie> &movie_list, int low_index, int high_index)
{
    if (low_index < high_index)
    {
        int pivot_index = partition(movie_list, low_index, high_index);
        quickSort(movie_list, low_index, pivot_index - 1);
        quickSort(movie_list, pivot_index + 1, high_index);
    }
}

int main()
{
    vector<Movie> all_movies = {
        {101, "The Shawshank Redemption", 9.3, 1994, 15000000},
        {102, "The Godfather", 9.2, 1972, 12000000},
        {103, "The Dark Knight", 9.0, 2008, 20000000},
        {104, "Pulp Fiction", 8.9, 1994, 10000000},
        {105, "Forrest Gump", 8.8, 1994, 18000000}};

    int user_criteria = 1;
    sort_criteria = user_criteria;
    int total_movies = all_movies.size();

    quickSort(all_movies, 0, total_movies - 1);

    for (int i = 0; i < total_movies; i++)
    {
        cout << all_movies[i].movie_id << ' ' << all_movies[i].movie_name << ' '
             << all_movies[i].movie_rating << ' ' << all_movies[i].release_year << ' '
             << all_movies[i].total_watch_time << '\n';
    }

    return 0;
}
