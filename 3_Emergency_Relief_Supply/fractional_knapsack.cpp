#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item
{
    int id;
    string name;
    double weight;
    double value;
    double value_per_weight;
    double fraction_taken;
};

// Sorts items by their value-to-weight ratio in descending order
bool compareItems(const Item &a, const Item &b)
{
    return a.value_per_weight > b.value_per_weight;
}

// Greedy algorithm to maximize value within weight capacity constraints
double fractionalKnapsack(vector<Item> &items, double capacity)
{
    if (capacity <= 0 || items.empty())
        return 0.0;

    sort(items.begin(), items.end(), compareItems);

    double total_value = 0.0;
    double remaining_capacity = capacity;

    for (auto &item : items)
    {
        if (remaining_capacity <= 0)
            break;

        if (item.weight <= remaining_capacity)
        {
            item.fraction_taken = 1.0;
            total_value += item.value;
            remaining_capacity -= item.weight;
        }
        else
        {
            item.fraction_taken = remaining_capacity / item.weight;
            total_value += item.value * item.fraction_taken;
            remaining_capacity = 0;
        }
    }

    return total_value;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Hardcoded input data
    double capacity = 50;
    vector<Item> items = {
        {1, "Medicine Kit", 10, 60, 0, 0},
        {2, "Food Packets", 20, 100, 0, 0},
        {3, "Drinking Water", 30, 120, 0, 0},
        {4, "Blankets", 15, 45, 0, 0},
        {5, "First Aid", 5, 30, 0, 0}};

    // Calculate value per weight ratio
    for (auto &item : items)
    {
        if (item.weight > 0)
            item.value_per_weight = item.value / item.weight;
        else
            item.value_per_weight = 0;
    }

    double max_value = fractionalKnapsack(items, capacity);

    // Display results
    cout << fixed << setprecision(2);
    cout << "Maximum Utility Value: " << max_value << endl;
    cout << "\nItems Selected:" << endl;
    cout << "ID\tName\t\t\tWeight\tValue\tFraction" << endl;
    cout << "------------------------------------------------------" << endl;

    for (const auto &item : items)
    {
        if (item.fraction_taken > 0)
        {
            cout << item.id << "\t" << item.name << "\t\t"
                 << item.weight << "\t" << item.value << "\t"
                 << item.fraction_taken << endl;
        }
    }

    return 0;
}
