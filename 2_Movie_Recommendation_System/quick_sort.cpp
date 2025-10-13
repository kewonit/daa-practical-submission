/*
 * File: quick_sort.cpp
 * Author: 123B1F052

 * Description: Implements Quick Sort algorithm to sort movies by different criteria.
 * Usage:
 *   Compile: g++ -O2 -std=c++17 quick_sort.cpp -o quick_sort
 *   Run:     ./quick_sort < input.txt > output.txt
 */

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

// Global variable to track sorting criteria: 1=rating, 2=year, 3=watch_time
int sort_by = 1;

// Compare two movies based on the selected sorting criteria
bool compareMovies(const Movie &a, const Movie &b)
{
    if (sort_by == 1)
        return a.rating > b.rating; // descending for rating
    else if (sort_by == 2)
        return a.year > b.year; // descending for year
    else
        return a.watch_time > b.watch_time; // descending for watch_time
}

// Partition the array around a pivot element for quick sort
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

// Recursively sort the array using quick sort algorithm
void quickSort(vector<Movie> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Entry point: read movies, sort by selected criteria, output sorted list
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, criteria;
    if (!(cin >> n >> criteria))
        return 0;

    // Validate sorting criteria input
    if (criteria < 1 || criteria > 3)
    {
        cerr << "Invalid sorting criteria. Use 1=rating, 2=year, 3=watch_time" << endl;
        return 1;
    }

    sort_by = criteria;
    vector<Movie> movies(n);

    // Read movie data from input
    for (int i = 0; i < n; i++)
    {
        cin >> movies[i].id;
        cin.ignore();
        getline(cin, movies[i].name);
        cin >> movies[i].rating >> movies[i].year >> movies[i].watch_time;
        cin.ignore();
    }

    // Handle edge case of empty or single movie
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        cout << movies[0].id << ' ' << movies[0].name << ' ' << movies[0].rating << ' ' << movies[0].year << ' ' << movies[0].watch_time << '\n';
        return 0;
    }

    // Sort movies using quick sort
    quickSort(movies, 0, n - 1);

    // Output sorted movies
    for (const auto &m : movies)
    {
        cout << m.id << ' ' << m.name << ' ' << m.rating << ' ' << m.year << ' ' << m.watch_time << '\n';
    }

    return 0;
}
