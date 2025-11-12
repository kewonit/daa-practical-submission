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
        pair<int, vector<int>> result;
        result.first = -1;
        result.second = delivery_path;
        return result;
    }

    int path_node = destination_node;
    while (path_node != -1)
    {
        delivery_path.push_back(path_node);
        path_node = previous_node[path_node];
    }

    reverse(delivery_path.begin(), delivery_path.end());

    pair<int, vector<int>> result;
    result.first = cheapest_cost[destination_node];
    result.second = delivery_path;
    return result;
}

int main()
{
    int total_nodes = 8;
    int total_edges = 13;
    int total_stages = 4;

    vector<int> node_stages;
    node_stages.push_back(0); node_stages.push_back(1); node_stages.push_back(1); node_stages.push_back(2);
    node_stages.push_back(2); node_stages.push_back(2); node_stages.push_back(3); node_stages.push_back(3);

    vector<Edge> delivery_edges;
    Edge e1; e1.from_node = 0; e1.to_node = 1; e1.delivery_cost = 2; delivery_edges.push_back(e1);
    Edge e2; e2.from_node = 0; e2.to_node = 2; e2.delivery_cost = 3; delivery_edges.push_back(e2);
    Edge e3; e3.from_node = 0; e3.to_node = 3; e3.delivery_cost = 6; delivery_edges.push_back(e3);
    Edge e4; e4.from_node = 1; e4.to_node = 4; e4.delivery_cost = 4; delivery_edges.push_back(e4);
    Edge e5; e5.from_node = 1; e5.to_node = 5; e5.delivery_cost = 5; delivery_edges.push_back(e5);
    Edge e6; e6.from_node = 2; e6.to_node = 4; e6.delivery_cost = 2; delivery_edges.push_back(e6);
    Edge e7; e7.from_node = 2; e7.to_node = 5; e7.delivery_cost = 4; delivery_edges.push_back(e7);
    Edge e8; e8.from_node = 3; e8.to_node = 5; e8.delivery_cost = 3; delivery_edges.push_back(e8);
    Edge e9; e9.from_node = 4; e9.to_node = 6; e9.delivery_cost = 3; delivery_edges.push_back(e9);
    Edge e10; e10.from_node = 4; e10.to_node = 7; e10.delivery_cost = 6; delivery_edges.push_back(e10);
    Edge e11; e11.from_node = 5; e11.to_node = 6; e11.delivery_cost = 5; delivery_edges.push_back(e11);
    Edge e12; e12.from_node = 5; e12.to_node = 7; e12.delivery_cost = 2; delivery_edges.push_back(e12);
    Edge e13; e13.from_node = 6; e13.to_node = 7; e13.delivery_cost = 4; delivery_edges.push_back(e13);

    pair<int, vector<int>> result = multistageGraph(total_nodes, total_stages, delivery_edges, node_stages);
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
