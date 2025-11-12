#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INFINITY_DISTANCE = numeric_limits<int>::max();

struct Edge
{
    int destination_node;
    int edge_weight;
};

struct Node
{
    int node_id;
    int distance_from_source;

    bool operator>(const Node &other_node) const
    {
        return distance_from_source > other_node.distance_from_source;
    }
};

// find shortest paths from start to all nodes
vector<int> dijkstra(int total_nodes, vector<vector<Edge>> &graph, int start_node, vector<int> &parent_nodes)
{
    vector<int> shortest_distances(total_nodes, INFINITY_DISTANCE);
    vector<bool> visited_nodes(total_nodes, false);
    priority_queue<Node, vector<Node>, greater<Node>> node_queue;

    shortest_distances[start_node] = 0;
    parent_nodes[start_node] = -1;
    node_queue.push({start_node, 0});

    while (!node_queue.empty())
    {
        Node current_node = node_queue.top();
        node_queue.pop();

        int current_id = current_node.node_id;

        if (visited_nodes[current_id])
            continue;

        visited_nodes[current_id] = true;

        for (int i = 0; i < graph[current_id].size(); i++)
        {
            int neighbor_id = graph[current_id][i].destination_node;
            int edge_weight = graph[current_id][i].edge_weight;

            if (!visited_nodes[neighbor_id] && shortest_distances[current_id] != INFINITY_DISTANCE)
            {
                int new_distance = shortest_distances[current_id] + edge_weight;
                if (new_distance < shortest_distances[neighbor_id])
                {
                    shortest_distances[neighbor_id] = new_distance;
                    parent_nodes[neighbor_id] = current_id;
                    node_queue.push({neighbor_id, shortest_distances[neighbor_id]});
                }
            }
        }
    }

    return shortest_distances;
}

// rebuild path from destination back to source
vector<int> getPath(int destination_node, const vector<int> &parent_nodes)
{
    vector<int> path_to_destination;
    int current_node = destination_node;

    if (parent_nodes[current_node] == -1 && current_node != 0)
        return path_to_destination;

    while (current_node != -1)
    {
        path_to_destination.push_back(current_node);
        current_node = parent_nodes[current_node];
    }

    reverse(path_to_destination.begin(), path_to_destination.end());
    return path_to_destination;
}

int main()
{
    int total_nodes = 6;
    int total_edges = 9;
    int ambulance_location = 0;

    vector<vector<Edge>> traffic_graph(total_nodes);

    traffic_graph[0].push_back({1, 4});
    traffic_graph[0].push_back({2, 2});
    traffic_graph[1].push_back({2, 1});
    traffic_graph[1].push_back({3, 5});
    traffic_graph[2].push_back({3, 8});
    traffic_graph[2].push_back({4, 10});
    traffic_graph[3].push_back({4, 2});
    traffic_graph[3].push_back({5, 6});
    traffic_graph[4].push_back({5, 3});

    vector<int> parent_nodes(total_nodes);
    vector<int> shortest_distances = dijkstra(total_nodes, traffic_graph, ambulance_location, parent_nodes);

    cout << "Shortest distances from ambulance location " << ambulance_location << ":" << endl;
    cout << "Hospital\tDistance\tPath" << endl;
    cout << "--------------------------------------------" << endl;

    for (int hospital = 0; hospital < total_nodes; hospital++)
    {
        cout << hospital << "\t\t";
        if (shortest_distances[hospital] == INFINITY_DISTANCE)
        {
            cout << "INF\t\tNo path" << endl;
        }
        else
        {
            cout << shortest_distances[hospital] << "\t\t";

            vector<int> path_to_hospital = getPath(hospital, parent_nodes);
            for (int step = 0; step < path_to_hospital.size(); step++)
            {
                cout << path_to_hospital[step];
                if (step < path_to_hospital.size() - 1)
                    cout << " -> ";
            }
            cout << endl;
        }
    }

    return 0;
}
