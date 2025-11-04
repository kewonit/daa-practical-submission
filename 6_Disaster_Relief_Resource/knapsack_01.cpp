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
    int priority;
    bool selected;
};

// Dynamic programming table-building approach for optimal item selection
int knapsack01(vector<Item> &items, int capacity, vector<vector<int>> &dp)
{
    int n = items.size();

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (items[i - 1].weight > w)
            {
                dp[i][w] = dp[i - 1][w];
            }
            else
            {
                dp[i][w] = max(dp[i - 1][w],
                               dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            }
        }
    }

    return dp[n][capacity];
}

// Traces back through DP table to identify which items were included
void findSelectedItems(vector<Item> &items, int capacity, const vector<vector<int>> &dp)
{
    int n = items.size();
    int w = capacity;

    for (int i = n; i > 0 && w > 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            items[i - 1].selected = true;
            w -= items[i - 1].weight;
        }
    }
}

// Prioritizes high-value items within the same priority level
bool comparePriority(const Item &a, const Item &b)
{
    if (a.priority != b.priority)
        return a.priority < b.priority;
    return a.value > b.value;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Hardcoded input data
    int capacity = 50;
    vector<Item> items = {
        {1, "Medicine Kit", 15, 100, 1, false},
        {2, "Antibiotics", 8, 80, 1, false},
        {3, "Food Packets", 20, 60, 2, false},
        {4, "Drinking Water", 12, 40, 2, false},
        {5, "Blankets", 10, 30, 3, false},
        {6, "Tents", 25, 70, 3, false},
        {7, "First Aid", 5, 50, 1, false}};

    int n = items.size();
    sort(items.begin(), items.end(), comparePriority);

    // Build DP table for knapsack solution
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    int max_value = knapsack01(items, capacity, dp);

    findSelectedItems(items, capacity, dp);

    // Calculate total weight of selected items
    int total_weight = 0;
    for (const auto &item : items)
    {
        if (item.selected)
        {
            total_weight += item.weight;
        }
    }

    // Display results
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

    // Summary breakdown by priority
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
