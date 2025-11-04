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
    int color;
    int degree;
};

// Verifies if a color assignment doesn't conflict with adjacent vertices
bool isSafe(int vertex, int color, const vector<vector<int>> &graph, const vector<int> &colors)
{
    for (int adj : graph[vertex])
    {
        if (colors[adj] == color)
        {
            return false;
        }
    }
    return true;
}

// Simple greedy approach that assigns colors sequentially
int greedyColoring(int n, const vector<vector<int>> &graph, vector<int> &colors)
{
    fill(colors.begin(), colors.end(), -1);

    colors[0] = 0;

    int max_color = 0;

    for (int v = 1; v < n; v++)
    {
        set<int> unavailable;
        for (int adj : graph[v])
        {
            if (colors[adj] != -1)
            {
                unavailable.insert(colors[adj]);
            }
        }

        int color = 0;
        while (unavailable.count(color))
        {
            color++;
        }

        colors[v] = color;
        max_color = max(max_color, color);
    }

    return max_color + 1;
}

// Advanced coloring that prioritizes vertices with highest saturation degree
int dsaturColoring(int n, const vector<vector<int>> &graph, vector<int> &colors)
{
    fill(colors.begin(), colors.end(), -1);

    vector<set<int>> saturation(n);
    vector<int> degree(n, 0);

    for (int i = 0; i < n; i++)
    {
        degree[i] = graph[i].size();
    }

    int colored_count = 0;
    int max_color = 0;

    while (colored_count < n)
    {
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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Hardcoded input data
    int n = 6, m = 7, algorithm = 2;
    vector<string> course_names = {
        "Data Structures",
        "Algorithms",
        "Database Systems",
        "Operating Systems",
        "Computer Networks",
        "Software Engineering"};

    vector<vector<int>> graph(n);
    vector<pair<int, int>> conflicts = {
        {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 4}, {2, 3}, {3, 5}};

    for (const auto &edge : conflicts)
    {
        int u = edge.first;
        int v = edge.second;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Execute selected coloring algorithm
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

    // Organize courses by assigned time slot
    vector<vector<int>> slots(num_colors);
    for (int i = 0; i < n; i++)
    {
        slots[colors[i]].push_back(i);
    }

    for (int slot = 0; slot < num_colors; slot++)
    {
        cout << "\nTime Slot " << (slot + 1) << ":" << endl;
        for (int course : slots[slot])
        {
            cout << "  Course " << course << ": " << course_names[course] << endl;
        }
    }

    // Display scheduling statistics
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
