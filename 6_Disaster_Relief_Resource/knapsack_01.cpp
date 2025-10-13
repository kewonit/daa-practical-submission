/*
 * File: knapsack_01.cpp
 * Author: 123B1F052

 * Description: Implements 0/1 Knapsack algorithm for disaster relief resource allocation.
 * Usage:
 *   Compile: g++ -O2 -std=c++17 knapsack_01.cpp -o knapsack_01
 *   Run:     ./knapsack_01 < input.txt > output.txt
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item
{
    int id;
    string name;
    int weight;
    int value;
    int priority; // 1=high (medicine), 2=medium (food), 3=low (others)
    bool selected;
};

// Solve 0/1 knapsack using dynamic programming
int knapsack01(vector<Item> &items, int capacity, vector<vector<int>> &dp)
{
    int n = items.size();

    // Build DP table
    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            // If current item weight exceeds capacity, skip it
            if (items[i - 1].weight > w)
            {
                dp[i][w] = dp[i - 1][w];
            }
            else
            {
                // Take maximum of including or excluding current item
                dp[i][w] = max(dp[i - 1][w],
                               dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            }
        }
    }

    return dp[n][capacity];
}

// Backtrack to find which items were selected
void findSelectedItems(vector<Item> &items, int capacity, const vector<vector<int>> &dp)
{
    int n = items.size();
    int w = capacity;

    // Trace back through DP table
    for (int i = n; i > 0 && w > 0; i--)
    {
        // If value differs from previous row, item was included
        if (dp[i][w] != dp[i - 1][w])
        {
            items[i - 1].selected = true;
            w -= items[i - 1].weight;
        }
    }
}

// Sort items by priority for better allocation
bool comparePriority(const Item &a, const Item &b)
{
    if (a.priority != b.priority)
        return a.priority < b.priority; // lower number = higher priority
    return a.value > b.value;           // if same priority, prefer higher value
}

// Entry point: read items and capacity, solve knapsack, output result
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, capacity;

    if (!(cin >> n >> capacity))
    {
        cerr << "Invalid input format" << endl;
        return 1;
    }

    // Validate inputs
    if (n <= 0 || capacity <= 0)
    {
        cout << "0" << endl;
        return 0;
    }

    vector<Item> items(n);

    // Read item details
    for (int i = 0; i < n; i++)
    {
        cin >> items[i].id;
        cin.ignore();
        getline(cin, items[i].name);
        cin >> items[i].weight >> items[i].value >> items[i].priority;
        cin.ignore();

        // Validate item data
        if (items[i].weight <= 0 || items[i].value < 0)
        {
            cerr << "Invalid item data for item " << items[i].id << endl;
            return 1;
        }

        items[i].selected = false;
    }

    // Sort by priority first (optional optimization)
    sort(items.begin(), items.end(), comparePriority);

    // Create DP table
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    // Solve 0/1 knapsack
    int max_value = knapsack01(items, capacity, dp);

    // Find which items were selected
    findSelectedItems(items, capacity, dp);

    // Calculate total weight used
    int total_weight = 0;
    for (const auto &item : items)
    {
        if (item.selected)
        {
            total_weight += item.weight;
        }
    }

    // Output results
    cout << "Maximum Utility Value: " << max_value << endl;
    cout << "Total Weight Used: " << total_weight << " kg (Capacity: " << capacity << " kg)" << endl;
    cout << "\nItems Selected:" << endl;
    cout << "ID\tName\t\t\tWeight\tValue\tPriority" << endl;
    cout << "-----------------------------------------------------------" << endl;

    for (const auto &item : items)
    {
        if (item.selected)
        {
            string priority_str;
            if (item.priority == 1)
                priority_str = "High";
            else if (item.priority == 2)
                priority_str = "Medium";
            else
                priority_str = "Low";

            cout << item.id << "\t" << item.name << "\t\t"
                 << item.weight << "\t" << item.value << "\t"
                 << priority_str << endl;
        }
    }

    // Additional analysis
    cout << "\nPriority-wise breakdown:" << endl;
    int high_count = 0, medium_count = 0, low_count = 0;
    for (const auto &item : items)
    {
        if (item.selected)
        {
            if (item.priority == 1)
                high_count++;
            else if (item.priority == 2)
                medium_count++;
            else
                low_count++;
        }
    }
    cout << "High priority items: " << high_count << endl;
    cout << "Medium priority items: " << medium_count << endl;
    cout << "Low priority items: " << low_count << endl;

    return 0;
}
