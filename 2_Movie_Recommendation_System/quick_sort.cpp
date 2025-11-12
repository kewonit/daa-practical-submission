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
    vector<Movie> all_movies;
    
    Movie movie1; movie1.movie_id = 101; movie1.movie_name = "The Shawshank Redemption"; movie1.movie_rating = 9.3; movie1.release_year = 1994; movie1.total_watch_time = 15000000; all_movies.push_back(movie1);
    Movie movie2; movie2.movie_id = 102; movie2.movie_name = "The Godfather"; movie2.movie_rating = 9.2; movie2.release_year = 1972; movie2.total_watch_time = 12000000; all_movies.push_back(movie2);
    Movie movie3; movie3.movie_id = 103; movie3.movie_name = "The Dark Knight"; movie3.movie_rating = 9.0; movie3.release_year = 2008; movie3.total_watch_time = 20000000; all_movies.push_back(movie3);
    Movie movie4; movie4.movie_id = 104; movie4.movie_name = "Pulp Fiction"; movie4.movie_rating = 8.9; movie4.release_year = 1994; movie4.total_watch_time = 10000000; all_movies.push_back(movie4);
    Movie movie5; movie5.movie_id = 105; movie5.movie_name = "Forrest Gump"; movie5.movie_rating = 8.8; movie5.release_year = 1994; movie5.total_watch_time = 18000000; all_movies.push_back(movie5);

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
