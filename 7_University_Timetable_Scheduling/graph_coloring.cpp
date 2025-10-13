/*
 * File: graph_coloring.cpp
 * Author: 123B1F052

 * Description: Implements graph coloring algorithm for university exam scheduling.
 * Usage:
 *   Compile: g++ -O2 -std=c++17 graph_coloring.cpp -o graph_coloring
 *   Run:     ./graph_coloring < input.txt > output.txt
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

struct Course
{
    int id;
    string name;
    int color;  // -1 means not colored yet
    int degree; // number of conflicts (for DSATUR)
};

// Check if a color is safe to assign to a vertex
bool isSafe(int vertex, int color, const vector<vector<int>> &graph, const vector<int> &colors)
{
    // Check all adjacent vertices
    for (int adj : graph[vertex])
    {
        if (colors[adj] == color)
        {
            return false;
        }
    }
    return true;
}

// Greedy coloring algorithm - simple but effective
int greedyColoring(int n, const vector<vector<int>> &graph, vector<int> &colors)
{
    // Initialize all colors as -1 (unassigned)
    fill(colors.begin(), colors.end(), -1);

    // Assign first color to first vertex
    colors[0] = 0;

    int max_color = 0;

    // Assign colors to remaining vertices
    for (int v = 1; v < n; v++)
    {
        // Find available colors for current vertex
        set<int> unavailable;
        for (int adj : graph[v])
        {
            if (colors[adj] != -1)
            {
                unavailable.insert(colors[adj]);
            }
        }

        // Find first available color
        int color = 0;
        while (unavailable.count(color))
        {
            color++;
        }

        colors[v] = color;
        max_color = max(max_color, color);
    }

    return max_color + 1; // Number of colors used
}

// DSATUR algorithm - colors vertex with maximum saturation degree first
int dsaturColoring(int n, const vector<vector<int>> &graph, vector<int> &colors)
{
    fill(colors.begin(), colors.end(), -1);

    vector<set<int>> saturation(n); // adjacent colors for each vertex
    vector<int> degree(n, 0);

    // Calculate initial degrees
    for (int i = 0; i < n; i++)
    {
        degree[i] = graph[i].size();
    }

    int colored_count = 0;
    int max_color = 0;

    while (colored_count < n)
    {
        // Find uncolored vertex with maximum saturation degree
        int max_sat = -1;
        int max_deg = -1;
        int selected = -1;

        for (int i = 0; i < n; i++)
        {
            if (colors[i] == -1)
            {
                int sat = saturation[i].size();
                if (sat > max_sat || (sat == max_sat && degree[i] > max_deg))
                {
                    max_sat = sat;
                    max_deg = degree[i];
                    selected = i;
                }
            }
        }

        // Find smallest available color
        set<int> available_colors;
        for (int c = 0; c <= max_color + 1; c++)
        {
            available_colors.insert(c);
        }

        for (int adj : graph[selected])
        {
            if (colors[adj] != -1)
            {
                available_colors.erase(colors[adj]);
            }
        }

        int chosen_color = *available_colors.begin();
        colors[selected] = chosen_color;
        max_color = max(max_color, chosen_color);

        // Update saturation of adjacent vertices
        for (int adj : graph[selected])
        {
            if (colors[adj] == -1)
            {
                saturation[adj].insert(chosen_color);
            }
        }

        colored_count++;
    }

    return max_color + 1;
}

// Entry point: read graph, apply coloring, output schedule
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, algorithm;

    if (!(cin >> n >> m >> algorithm))
    {
        cerr << "Invalid input format" << endl;
        return 1;
    }

    // Validate inputs
    if (n <= 0 || m < 0 || algorithm < 1 || algorithm > 2)
    {
        cerr << "Invalid parameters. Algorithm: 1=Greedy, 2=DSATUR" << endl;
        return 1;
    }

    // Read course names
    vector<string> course_names(n);
    cin.ignore();
    for (int i = 0; i < n; i++)
    {
        getline(cin, course_names[i]);
    }

    // Build adjacency list
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        // Validate edge
        if (u < 0 || u >= n || v < 0 || v >= n || u == v)
        {
            cerr << "Invalid edge: " << u << " " << v << endl;
            continue;
        }

        // Add edge (undirected)
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Apply coloring algorithm
    vector<int> colors(n);
    int num_colors;

    if (algorithm == 1)
    {
        cout << "Using Greedy Coloring Algorithm" << endl;
        num_colors = greedyColoring(n, graph, colors);
    }
    else
    {
        cout << "Using DSATUR Coloring Algorithm" << endl;
        num_colors = dsaturColoring(n, graph, colors);
    }

    cout << "\nMinimum exam slots needed: " << num_colors << endl;
    cout << "\nExam Schedule:" << endl;
    cout << "========================================" << endl;

    // Group courses by time slot
    vector<vector<int>> slots(num_colors);
    for (int i = 0; i < n; i++)
    {
        slots[colors[i]].push_back(i);
    }

    // Output schedule
    for (int slot = 0; slot < num_colors; slot++)
    {
        cout << "\nTime Slot " << (slot + 1) << ":" << endl;
        for (int course : slots[slot])
        {
            cout << "  Course " << course << ": " << course_names[course] << endl;
        }
    }

    // Statistics
    cout << "\n========================================" << endl;
    cout << "Statistics:" << endl;
    cout << "Total courses: " << n << endl;
    cout << "Total conflicts: " << m << endl;
    cout << "Exam slots used: " << num_colors << endl;
    cout << "Average courses per slot: " << fixed;
    cout.precision(2);
    cout << (double)n / num_colors << endl;

    return 0;
}
