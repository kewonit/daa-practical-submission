#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Movie
{
    int id;
    string name;
    double rating;
    int year;
    long long watch_time;
};

int sort_by = 1;

// Determines the sort order based on user-selected criteria
bool compareMovies(const Movie &a, const Movie &b)
{
    if (sort_by == 1)
        return a.rating > b.rating;
    else if (sort_by == 2)
        return a.year > b.year;
    else
        return a.watch_time > b.watch_time;
}

// Rearranges elements around a pivot for efficient sorting
int partition(vector<Movie> &arr, int low, int high)
{
    Movie pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (compareMovies(arr[j], pivot))
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Recursively sorts the movie list using quicksort algorithm
void quickSort(vector<Movie> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Hardcoded input data
    vector<Movie> movies = {
        {101, "The Shawshank Redemption", 9.3, 1994, 15000000},
        {102, "The Godfather", 9.2, 1972, 12000000},
        {103, "The Dark Knight", 9.0, 2008, 20000000},
        {104, "Pulp Fiction", 8.9, 1994, 10000000},
        {105, "Forrest Gump", 8.8, 1994, 18000000}};

    int criteria = 1; // Sort by rating
    sort_by = criteria;
    int n = movies.size();

    quickSort(movies, 0, n - 1);

    for (const auto &m : movies)
    {
        cout << m.id << ' ' << m.name << ' ' << m.rating << ' ' << m.year << ' ' << m.watch_time << '\n';
    }

    return 0;
}
