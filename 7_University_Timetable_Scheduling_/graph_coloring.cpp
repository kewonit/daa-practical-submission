#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

struct Course
{
    int course_id;
    string course_name;
    int time_slot;
    int conflict_count;
};

// check if color is safe for this node
bool isSafe(int node_index, int color_choice, const vector<vector<int> > &graph, const vector<int> &node_colors)
{
    for (int i = 0; i < graph[node_index].size(); i++)
    {
        int neighbor_node = graph[node_index][i];
        if (node_colors[neighbor_node] == color_choice)
        {
            return false;
        }
    }
    return true;
}

// assign colors to nodes one by one
int greedyColoring(int total_nodes, const vector<vector<int> > &graph, vector<int> &node_colors)
{
    for (int i = 0; i < total_nodes; i++)
    {
        node_colors[i] = -1;
    }

    node_colors[0] = 0;
    int highest_color = 0;

    for (int node = 1; node < total_nodes; node++)
    {
        set<int> used_colors;
        for (int i = 0; i < graph[node].size(); i++)
        {
            int neighbor = graph[node][i];
            if (node_colors[neighbor] != -1)
            {
                used_colors.insert(node_colors[neighbor]);
            }
        }

        int chosen_color = 0;
        while (used_colors.count(chosen_color))
        {
            chosen_color++;
        }

        node_colors[node] = chosen_color;
        highest_color = max(highest_color, chosen_color);
    }

    return highest_color + 1;
}

// prioritize nodes with most color conflicts
int dsaturColoring(int total_nodes, const vector<vector<int> > &graph, vector<int> &node_colors)
{
    for (int i = 0; i < total_nodes; i++)
    {
        node_colors[i] = -1;
    }

    vector<set<int> > neighbor_colors(total_nodes);
    vector<int> node_degree(total_nodes, 0);

    for (int i = 0; i < total_nodes; i++)
    {
        node_degree[i] = graph[i].size();
    }

    int nodes_colored = 0;
    int highest_color = 0;

    while (nodes_colored < total_nodes)
    {
        int max_saturation = -1;
        int max_degree = -1;
        int selected_node = -1;

        for (int node = 0; node < total_nodes; node++)
        {
            if (node_colors[node] == -1)
            {
                int saturation_degree = neighbor_colors[node].size();
                if (saturation_degree > max_saturation || (saturation_degree == max_saturation && node_degree[node] > max_degree))
                {
                    max_saturation = saturation_degree;
                    max_degree = node_degree[node];
                    selected_node = node;
                }
            }
        }

        set<int> available_colors;
        for (int color = 0; color <= highest_color + 1; color++)
        {
            available_colors.insert(color);
        }

        for (int i = 0; i < graph[selected_node].size(); i++)
        {
            int neighbor = graph[selected_node][i];
            if (node_colors[neighbor] != -1)
            {
                available_colors.erase(node_colors[neighbor]);
            }
        }

        int chosen_color = *available_colors.begin();
        node_colors[selected_node] = chosen_color;
        highest_color = max(highest_color, chosen_color);

        for (int i = 0; i < graph[selected_node].size(); i++)
        {
            int neighbor = graph[selected_node][i];
            if (node_colors[neighbor] == -1)
            {
                neighbor_colors[neighbor].insert(chosen_color);
            }
        }

        nodes_colored++;
    }

    return highest_color + 1;
}

int main()
{
    int total_courses = 6;
    int total_conflicts = 7;
    int algorithm_choice = 2;

    vector<string> course_names;
    course_names.push_back("Data Structures");
    course_names.push_back("Algorithms");
    course_names.push_back("Database Systems");
    course_names.push_back("Operating Systems");
    course_names.push_back("Computer Networks");
    course_names.push_back("Software Engineering");

    vector<vector<int> > conflict_graph(total_courses);
    vector<pair<int, int> > conflict_pairs;
    conflict_pairs.push_back(make_pair(0, 1));
    conflict_pairs.push_back(make_pair(0, 2));
    conflict_pairs.push_back(make_pair(0, 3));
    conflict_pairs.push_back(make_pair(1, 2));
    conflict_pairs.push_back(make_pair(1, 4));
    conflict_pairs.push_back(make_pair(2, 3));
    conflict_pairs.push_back(make_pair(3, 5));

    for (int i = 0; i < conflict_pairs.size(); i++)
    {
        int course_a = conflict_pairs[i].first;
        int course_b = conflict_pairs[i].second;
        conflict_graph[course_a].push_back(course_b);
        conflict_graph[course_b].push_back(course_a);
    }

    vector<int> time_slots(total_courses);
    int slots_needed;

    if (algorithm_choice == 1)
    {
        cout << "Using Greedy Coloring Algorithm" << endl;
        slots_needed = greedyColoring(total_courses, conflict_graph, time_slots);
    }
    else
    {
        cout << "Using DSATUR Coloring Algorithm" << endl;
        slots_needed = dsaturColoring(total_courses, conflict_graph, time_slots);
    }

    cout << "\nMinimum exam slots needed: " << slots_needed << endl;
    cout << "\nExam Schedule:" << endl;
    cout << "========================================" << endl;

    vector<vector<int> > courses_per_slot(slots_needed);
    for (int course = 0; course < total_courses; course++)
    {
        courses_per_slot[time_slots[course]].push_back(course);
    }

    for (int slot = 0; slot < slots_needed; slot++)
    {
        cout << "\nTime Slot " << (slot + 1) << ":" << endl;
        for (int i = 0; i < courses_per_slot[slot].size(); i++)
        {
            int course = courses_per_slot[slot][i];
            cout << "  Course " << course << ": " << course_names[course] << endl;
        }
    }

    cout << "\n========================================" << endl;
    cout << "Statistics:" << endl;
    cout << "Total courses: " << total_courses << endl;
    cout << "Total conflicts: " << total_conflicts << endl;
    cout << "Exam slots used: " << slots_needed << endl;
    cout << "Average courses per slot: ";
    cout << (double)total_courses / slots_needed << endl;

    return 0;
}
