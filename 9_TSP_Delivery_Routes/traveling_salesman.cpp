#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;

const long long INFINITY_VALUE = numeric_limits<long long>::max();

struct Node
{
    int tree_level;
    long long lower_bound;
    int last_city;
    vector<int> visited_path;
    vector<vector<long long>> cost_matrix;
};

struct CompareNode
{
    bool operator()(const Node &first_node, const Node &second_node) const
    {
        return first_node.lower_bound > second_node.lower_bound;
    }
};

// reduce matrix rows and columns
long long reduceCostMatrix(vector<vector<long long>> &cost_matrix, int city_count)
{
    long long total_reduction = 0;

    for (int row = 0; row < city_count; row++)
    {
        long long min_value = INFINITY_VALUE;
        for (int col = 0; col < city_count; col++)
        {
            if (cost_matrix[row][col] < min_value)
            {
                min_value = cost_matrix[row][col];
            }
        }
        if (min_value != INFINITY_VALUE && min_value != 0)
        {
            total_reduction += min_value;
            for (int col = 0; col < city_count; col++)
            {
                if (cost_matrix[row][col] != INFINITY_VALUE)
                {
                    cost_matrix[row][col] -= min_value;
                }
            }
        }
    }

    for (int col = 0; col < city_count; col++)
    {
        long long min_value = INFINITY_VALUE;
        for (int row = 0; row < city_count; row++)
        {
            if (cost_matrix[row][col] < min_value)
            {
                min_value = cost_matrix[row][col];
            }
        }
        if (min_value != INFINITY_VALUE && min_value != 0)
        {
            total_reduction += min_value;
            for (int row = 0; row < city_count; row++)
            {
                if (cost_matrix[row][col] != INFINITY_VALUE)
                {
                    cost_matrix[row][col] -= min_value;
                }
            }
        }
    }

    return total_reduction;
}

// find shortest tour visiting all cities
pair<long long, vector<int>> tspBranchAndBound(const vector<vector<long long>> &distance_matrix)
{
    int city_count = distance_matrix.size();
    long long best_cost = INFINITY_VALUE;
    vector<int> best_tour;

    Node starting_node;
    starting_node.tree_level = 0;
    starting_node.lower_bound = 0;
    starting_node.last_city = 0;
    starting_node.visited_path.push_back(0);
    starting_node.cost_matrix = distance_matrix;

    starting_node.lower_bound = reduceCostMatrix(starting_node.cost_matrix, city_count);

    priority_queue<Node, vector<Node>, CompareNode> search_queue;
    search_queue.push(starting_node);

    while (!search_queue.empty())
    {
        Node current_node = search_queue.top();
        search_queue.pop();

        if (current_node.lower_bound >= best_cost)
        {
            continue;
        }

        if (current_node.tree_level == city_count - 1)
        {
            long long final_cost = current_node.lower_bound + current_node.cost_matrix[current_node.last_city][0];
            if (final_cost < best_cost)
            {
                best_cost = final_cost;
                best_tour = current_node.visited_path;
                best_tour.push_back(0);
            }
            continue;
        }

        for (int next_city = 0; next_city < city_count; next_city++)
        {
            bool already_visited = false;
            for (int i = 0; i < current_node.visited_path.size(); i++)
            {
                if (current_node.visited_path[i] == next_city)
                {
                    already_visited = true;
                    break;
                }
            }

            if (already_visited)
            {
                continue;
            }

            Node child_node;
            child_node.tree_level = current_node.tree_level + 1;
            child_node.last_city = next_city;
            child_node.visited_path = current_node.visited_path;
            child_node.visited_path.push_back(next_city);

            child_node.cost_matrix = current_node.cost_matrix;

            child_node.lower_bound = current_node.lower_bound + child_node.cost_matrix[current_node.last_city][next_city];

            for (int i = 0; i < city_count; i++)
            {
                child_node.cost_matrix[current_node.last_city][i] = INFINITY_VALUE;
                child_node.cost_matrix[i][next_city] = INFINITY_VALUE;
            }

            child_node.cost_matrix[next_city][current_node.last_city] = INFINITY_VALUE;

            long long additional_reduction = reduceCostMatrix(child_node.cost_matrix, city_count);
            child_node.lower_bound += additional_reduction;

            if (child_node.lower_bound < best_cost)
            {
                search_queue.push(child_node);
            }
        }
    }

    return {best_cost, best_tour};
}

int main()
{
    int city_count;
    cin >> city_count;

    vector<vector<long long>> distance_matrix(city_count, vector<long long>(city_count));
    for (int i = 0; i < city_count; i++)
    {
        for (int j = 0; j < city_count; j++)
        {
            cin >> distance_matrix[i][j];
        }
    }

    auto result = tspBranchAndBound(distance_matrix);
    long long minimum_cost = result.first;
    vector<int> optimal_tour = result.second;

    cout << "=== Traveling Salesman Problem (TSP) - LC Branch and Bound ===" << endl;
    cout << "Number of cities: " << city_count << endl;
    cout << endl;

    cout << "Optimal Route:" << endl;
    for (int i = 0; i < optimal_tour.size(); i++)
    {
        cout << optimal_tour[i];
        if (i < optimal_tour.size() - 1)
        {
            cout << " -> ";
        }
    }
    cout << endl;
    cout << endl;

    cout << "Minimum Cost (Total Distance): " << minimum_cost << endl;
    cout << endl;

    cout << "Route Details:" << endl;
    cout << "City\tNext City\tDistance" << endl;
    cout << "-----------------------------" << endl;
    long long running_total = 0;
    for (int i = 0; i < optimal_tour.size() - 1; i++)
    {
        int from_city = optimal_tour[i];
        int to_city = optimal_tour[i + 1];
        long long segment_distance = distance_matrix[from_city][to_city];
        cout << from_city << "\t" << to_city << "\t\t" << segment_distance << endl;
        running_total += segment_distance;
    }
    cout << "-----------------------------" << endl;
    cout << "TOTAL COST: " << running_total << endl;

    return 0;
}
