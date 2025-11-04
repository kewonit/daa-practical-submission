#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <tuple>

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

    bool operator>(const Node &other) const
    {
        return distance > other.distance;
    }
};

// Finds shortest paths from source vertex to all other vertices using priority queue
vector<int> dijkstra(int n, vector<vector<Edge>> &graph, int source, vector<int> &parent)
{
    vector<int> dist(n, INF);
    vector<bool> visited(n, false);
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[source] = 0;
    parent[source] = -1;
    pq.push({source, 0});

    while (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();

        int u = current.vertex;

        if (visited[u])
            continue;

        visited[u] = true;

        for (const Edge &edge : graph[u])
        {
            int v = edge.to;
            int weight = edge.weight;

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

// Traces back the path from destination to source using parent pointers
vector<int> getPath(int dest, const vector<int> &parent)
{
    vector<int> path;
    int current = dest;

    if (parent[current] == -1 && current != 0)
        return path;

    while (current != -1)
    {
        path.push_back(current);
        current = parent[current];
    }

    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Hardcoded input data
    int n = 6, m = 9, source = 0;
    vector<vector<Edge>> graph(n);

    vector<tuple<int, int, int>> edges = {
        {0, 1, 4}, {0, 2, 2}, {1, 2, 1}, {1, 3, 5}, {2, 3, 8}, {2, 4, 10}, {3, 4, 2}, {3, 5, 6}, {4, 5, 3}};

    for (const auto &e : edges)
    {
        int u = get<0>(e);
        int v = get<1>(e);
        int w = get<2>(e);
        graph[u].push_back({v, w});
    }

    // Execute Dijkstra's algorithm
    vector<int> parent(n);
    vector<int> distances = dijkstra(n, graph, source, parent);

    // Display shortest paths
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
