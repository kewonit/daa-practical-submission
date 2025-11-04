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

// Dynamic programming approach to find minimum cost path through all stages
pair<int, vector<int>> multistageGraph(int n, int stages, const vector<Edge> &edges, const vector<int> &stage_map)
{
    vector<int> dist(n, INF);
    vector<int> parent(n, -1);

    dist[0] = 0;

    vector<vector<Edge>> graph(n);
    for (const Edge &e : edges)
    {
        graph[e.from].push_back(e);
    }

    for (int node = 0; node < n; node++)
    {
        if (dist[node] == INF)
            continue;

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

    // Build path from source to destination
    vector<int> path;
    int current = n - 1;

    if (dist[current] == INF)
    {
        return {-1, path};
    }

    while (current != -1)
    {
        path.push_back(current);
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    return {dist[n - 1], path};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Hardcoded input data
    int n = 8, m = 13, stages = 4;
    vector<int> stage_map = {0, 1, 1, 2, 2, 2, 3, 3};

    vector<Edge> edges = {
        {0, 1, 2}, {0, 2, 3}, {0, 3, 6}, {1, 4, 4}, {1, 5, 5}, {2, 4, 2}, {2, 5, 4}, {3, 5, 3}, {4, 6, 3}, {4, 7, 6}, {5, 6, 5}, {5, 7, 2}, {6, 7, 4}};

    // Find optimal delivery route
    auto result = multistageGraph(n, stages, edges, stage_map);
    int min_cost = result.first;
    vector<int> path = result.second;

    // Display results
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
