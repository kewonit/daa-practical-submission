/*
 * File: fractional_knapsack.cpp
 * Author: 123B1F052

 * Description: Implements Fractional Knapsack algorithm for relief supply distribution.
 * Usage:
 *   Compile: g++ -O2 -std=c++17 fractional_knapsack.cpp -o fractional_knapsack
 *   Run:     ./fractional_knapsack < input.txt > output.txt
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
    double weight;
    double value;
    double value_per_weight;
    double fraction_taken;
};

// Compare items by value per weight ratio in descending order
bool compareItems(const Item &a, const Item &b)
{
    return a.value_per_weight > b.value_per_weight;
}

// Solve fractional knapsack problem and return maximum value
double fractionalKnapsack(vector<Item> &items, double capacity)
{
    // Handle edge cases
    if (capacity <= 0 || items.empty())
        return 0.0;

    // Sort items by value per weight ratio
    sort(items.begin(), items.end(), compareItems);

    double total_value = 0.0;
    double remaining_capacity = capacity;

    // Greedily select items
    for (auto &item : items)
    {
        if (remaining_capacity <= 0)
            break;

        // If item can be fully taken
        if (item.weight <= remaining_capacity)
        {
            item.fraction_taken = 1.0;
            total_value += item.value;
            remaining_capacity -= item.weight;
        }
        else
        {
            // Take fraction of the item
            item.fraction_taken = remaining_capacity / item.weight;
            total_value += item.value * item.fraction_taken;
            remaining_capacity = 0;
        }
    }

    return total_value;
}

// Entry point: read items and capacity, solve knapsack, output result
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    double capacity;

    if (!(cin >> n >> capacity))
    {
        cerr << "Invalid input format" << endl;
        return 1;
    }

    // Validate inputs
    if (n <= 0 || capacity <= 0)
    {
        cout << "0.00" << endl;
        return 0;
    }

    vector<Item> items(n);

    // Read item details
    for (int i = 0; i < n; i++)
    {
        cin >> items[i].id;
        cin.ignore();
        getline(cin, items[i].name);
        cin >> items[i].weight >> items[i].value;
        cin.ignore();

        // Calculate value per weight ratio
        if (items[i].weight > 0)
        {
            items[i].value_per_weight = items[i].value / items[i].weight;
        }
        else
        {
            items[i].value_per_weight = 0;
        }
        items[i].fraction_taken = 0.0;
    }

    // Solve fractional knapsack
    double max_value = fractionalKnapsack(items, capacity);

    // Output results
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
