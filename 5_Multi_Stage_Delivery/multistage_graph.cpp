/*
 * File: multistage_graph.cpp
 * Author: 123B1F052

 * Description: Implements dynamic programming for optimal delivery routes in multistage graph.
 * Usage:
 *   Compile: g++ -O2 -std=c++17 multistage_graph.cpp -o multistage_graph
 *   Run:     ./multistage_graph < input.txt > output.txt
 */

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge
{
    int from;
    int to;
    int cost;
};

// Find shortest path in multistage graph using dynamic programming
pair<int, vector<int>> multistageGraph(int n, int stages, const vector<Edge> &edges, const vector<int> &stage_map)
{
    // Initialize distance array
    vector<int> dist(n, INF);
    vector<int> parent(n, -1);

    // Source node has distance 0
    dist[0] = 0;

    // Build adjacency list for efficient edge lookup
    vector<vector<Edge>> graph(n);
    for (const Edge &e : edges)
    {
        graph[e.from].push_back(e);
    }

    // Process nodes in topological order (stage by stage)
    for (int node = 0; node < n; node++)
    {
        if (dist[node] == INF)
            continue;

        // Relax all outgoing edges
        for (const Edge &edge : graph[node])
        {
            int new_cost = dist[node] + edge.cost;
            if (new_cost < dist[edge.to])
            {
                dist[edge.to] = new_cost;
                parent[edge.to] = node;
            }
        }
    }

    // Reconstruct path
    vector<int> path;
    int current = n - 1; // destination is last node

    // Check if destination is reachable
    if (dist[current] == INF)
    {
        return {-1, path};
    }

    // Backtrack to find path
    while (current != -1)
    {
        path.push_back(current);
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    return {dist[n - 1], path};
}

// Entry point: read multistage graph, find optimal path, output result
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, stages;

    if (!(cin >> n >> m >> stages))
    {
        cerr << "Invalid input format" << endl;
        return 1;
    }

    // Validate inputs
    if (n <= 0 || m < 0 || stages <= 0)
    {
        cerr << "Invalid graph parameters" << endl;
        return 1;
    }

    // Read stage mapping for each node
    vector<int> stage_map(n);
    for (int i = 0; i < n; i++)
    {
        cin >> stage_map[i];
        if (stage_map[i] < 0 || stage_map[i] >= stages)
        {
            cerr << "Invalid stage for node " << i << endl;
            return 1;
        }
    }

    // Read edges
    vector<Edge> edges;
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

        // Ensure edge goes forward in stages
        if (stage_map[u] >= stage_map[v])
        {
            cerr << "Edge does not go forward: " << u << " -> " << v << endl;
            continue;
        }

        edges.push_back({u, v, w});
    }

    // Find optimal path
    auto result = multistageGraph(n, stages, edges, stage_map);
    int min_cost = result.first;
    vector<int> path = result.second;

    // Output results
    if (min_cost == -1)
    {
        cout << "No path exists from source to destination" << endl;
    }
    else
    {
        cout << "Minimum delivery cost: " << min_cost << endl;
        cout << "Optimal route: ";
        for (size_t i = 0; i < path.size(); i++)
        {
            cout << path[i];
            if (i < path.size() - 1)
                cout << " -> ";
        }
        cout << endl;

        // Print stage information
        cout << "\nStage breakdown:" << endl;
        for (size_t i = 0; i < path.size(); i++)
        {
            cout << "Node " << path[i] << " (Stage " << stage_map[path[i]] << ")";
            if (i < path.size() - 1)
                cout << " -> ";
        }
        cout << endl;
    }

    return 0;
}
