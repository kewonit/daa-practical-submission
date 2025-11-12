#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const int INFINITY_COST = numeric_limits<int>::max();

struct Edge
{
    int from_node;
    int to_node;
    int delivery_cost;
};

// find cheapest path through all delivery stages
pair<int, vector<int>> multistageGraph(int total_nodes, int total_stages, const vector<Edge> &all_edges, const vector<int> &node_stages)
{
    vector<int> cheapest_cost(total_nodes, INFINITY_COST);
    vector<int> previous_node(total_nodes, -1);

    cheapest_cost[0] = 0;

    vector<vector<Edge>> adjacency_list(total_nodes);
    for (int i = 0; i < all_edges.size(); i++)
    {
        adjacency_list[all_edges[i].from_node].push_back(all_edges[i]);
    }

    for (int current_node = 0; current_node < total_nodes; current_node++)
    {
        if (cheapest_cost[current_node] == INFINITY_COST)
            continue;

        for (int edge_index = 0; edge_index < adjacency_list[current_node].size(); edge_index++)
        {
            int next_node = adjacency_list[current_node][edge_index].to_node;
            int edge_cost = adjacency_list[current_node][edge_index].delivery_cost;
            int total_cost = cheapest_cost[current_node] + edge_cost;

            if (total_cost < cheapest_cost[next_node])
            {
                cheapest_cost[next_node] = total_cost;
                previous_node[next_node] = current_node;
            }
        }
    }

    vector<int> delivery_path;
    int destination_node = total_nodes - 1;

    if (cheapest_cost[destination_node] == INFINITY_COST)
    {
        return {-1, delivery_path};
    }

    int path_node = destination_node;
    while (path_node != -1)
    {
        delivery_path.push_back(path_node);
        path_node = previous_node[path_node];
    }

    reverse(delivery_path.begin(), delivery_path.end());

    return {cheapest_cost[destination_node], delivery_path};
}

int main()
{
    int total_nodes = 8;
    int total_edges = 13;
    int total_stages = 4;

    vector<int> node_stages = {0, 1, 1, 2, 2, 2, 3, 3};

    vector<Edge> delivery_edges = {
        {0, 1, 2}, {0, 2, 3}, {0, 3, 6}, {1, 4, 4}, {1, 5, 5}, {2, 4, 2}, {2, 5, 4}, {3, 5, 3}, {4, 6, 3}, {4, 7, 6}, {5, 6, 5}, {5, 7, 2}, {6, 7, 4}};

    auto result = multistageGraph(total_nodes, total_stages, delivery_edges, node_stages);
    int minimum_cost = result.first;
    vector<int> optimal_path = result.second;

    if (minimum_cost == -1)
    {
        cout << "No path exists from source to destination" << endl;
    }
    else
    {
        cout << "Minimum delivery cost: " << minimum_cost << endl;
        cout << "Optimal route: ";
        for (int i = 0; i < optimal_path.size(); i++)
        {
            cout << optimal_path[i];
            if (i < optimal_path.size() - 1)
                cout << " -> ";
        }
        cout << endl;

        cout << "\nStage breakdown:" << endl;
        for (int i = 0; i < optimal_path.size(); i++)
        {
            cout << "Node " << optimal_path[i] << " (Stage " << node_stages[optimal_path[i]] << ")";
            if (i < optimal_path.size() - 1)
                cout << " -> ";
        }
        cout << endl;
    }

    return 0;
}
