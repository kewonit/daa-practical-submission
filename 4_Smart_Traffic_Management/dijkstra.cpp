/*
 * File: dijkstra.cpp
 * Author: 123B1F052

 * Description: Implements Dijkstra's algorithm for shortest path in traffic management.
 * Usage:
 *   Compile: g++ -O2 -std=c++17 dijkstra.cpp -o dijkstra
 *   Run:     ./dijkstra < input.txt > output.txt
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge
{
    int to;
    int weight;
};

struct Node
{
    int vertex;
    int distance;

    // Comparator for priority queue (min heap)
    bool operator>(const Node &other) const
    {
        return distance > other.distance;
    }
};

// Dijkstra's algorithm to find shortest paths from source to all vertices
vector<int> dijkstra(int n, vector<vector<Edge>> &graph, int source, vector<int> &parent)
{
    vector<int> dist(n, INF);
    vector<bool> visited(n, false);
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // Initialize source
    dist[source] = 0;
    parent[source] = -1;
    pq.push({source, 0});

    while (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();

        int u = current.vertex;

        // Skip if already visited
        if (visited[u])
            continue;

        visited[u] = true;

        // Relax all adjacent edges
        for (const Edge &edge : graph[u])
        {
            int v = edge.to;
            int weight = edge.weight;

            // Update distance if shorter path found
            if (!visited[v] && dist[u] != INF && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }

    return dist;
}

// Reconstruct path from source to destination using parent array
vector<int> getPath(int dest, const vector<int> &parent)
{
    vector<int> path;
    int current = dest;

    // Handle case where destination is unreachable
    if (parent[current] == -1 && current != 0)
        return path;

    // Backtrack from destination to source
    while (current != -1)
    {
        path.push_back(current);
        current = parent[current];
    }

    reverse(path.begin(), path.end());
    return path;
}

// Entry point: read graph, find shortest paths, output results
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, source;

    if (!(cin >> n >> m >> source))
    {
        cerr << "Invalid input format" << endl;
        return 1;
    }

    // Validate inputs
    if (n <= 0 || m < 0 || source < 0 || source >= n)
    {
        cerr << "Invalid graph parameters" << endl;
        return 1;
    }

    // Build adjacency list
    vector<vector<Edge>> graph(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        // Validate edge
        if (u < 0 || u >= n || v < 0 || v >= n || w < 0)
        {
            cerr << "Invalid edge: " << u << " " << v << " " << w << endl;
            continue;
        }

        graph[u].push_back({v, w});
    }

    // Run Dijkstra's algorithm
    vector<int> parent(n);
    vector<int> distances = dijkstra(n, graph, source, parent);

    // Output shortest distances
    cout << "Shortest distances from ambulance location " << source << ":" << endl;
    cout << "Hospital\tDistance\tPath" << endl;
    cout << "--------------------------------------------" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << i << "\t\t";
        if (distances[i] == INF)
        {
            cout << "INF\t\tNo path" << endl;
        }
        else
        {
            cout << distances[i] << "\t\t";

            // Print path
            vector<int> path = getPath(i, parent);
            for (size_t j = 0; j < path.size(); j++)
            {
                cout << path[j];
                if (j < path.size() - 1)
                    cout << " -> ";
            }
            cout << endl;
        }
    }

    return 0;
}
