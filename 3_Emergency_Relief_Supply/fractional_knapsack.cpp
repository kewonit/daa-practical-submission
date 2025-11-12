#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item
{
    int item_id;
    string item_name;
    double item_weight;
    double item_value;
    double value_per_weight;
    double fraction_used;
};

// compare items by value per weight ratio
bool compareItems(const Item &first_item, const Item &second_item)
{
    return first_item.value_per_weight > second_item.value_per_weight;
}

// maximize value within weight limit
double fractionalKnapsack(vector<Item> &all_items, double max_capacity)
{
    if (max_capacity <= 0 || all_items.empty())
        return 0.0;

    sort(all_items.begin(), all_items.end(), compareItems);

    double total_value_collected = 0.0;
    double remaining_capacity = max_capacity;

    for (int i = 0; i < all_items.size(); i++)
    {
        if (remaining_capacity <= 0)
            break;

        if (all_items[i].item_weight <= remaining_capacity)
        {
            all_items[i].fraction_used = 1.0;
            total_value_collected += all_items[i].item_value;
            remaining_capacity -= all_items[i].item_weight;
        }
        else
        {
            all_items[i].fraction_used = remaining_capacity / all_items[i].item_weight;
            total_value_collected += all_items[i].item_value * all_items[i].fraction_used;
            remaining_capacity = 0;
        }
    }

    return total_value_collected;
}

int main()
{
    double bag_capacity = 50;
    vector<Item> supply_items = {
        {1, "Medicine Kit", 10, 60, 0, 0},
        {2, "Food Packets", 20, 100, 0, 0},
        {3, "Drinking Water", 30, 120, 0, 0},
        {4, "Blankets", 15, 45, 0, 0},
        {5, "First Aid", 5, 30, 0, 0}};

    for (int i = 0; i < supply_items.size(); i++)
    {
        if (supply_items[i].item_weight > 0)
            supply_items[i].value_per_weight = supply_items[i].item_value / supply_items[i].item_weight;
        else
            supply_items[i].value_per_weight = 0;
    }

    double maximum_value = fractionalKnapsack(supply_items, bag_capacity);

    cout << fixed << setprecision(2);
    cout << "Maximum Utility Value: " << maximum_value << endl;
    cout << "\nItems Selected:" << endl;
    cout << "ID\tName\t\t\tWeight\tValue\tFraction" << endl;
    cout << "------------------------------------------------------" << endl;

    for (int i = 0; i < supply_items.size(); i++)
    {
        if (supply_items[i].fraction_used > 0)
        {
            cout << supply_items[i].item_id << "\t" << supply_items[i].item_name << "\t\t"
                 << supply_items[i].item_weight << "\t" << supply_items[i].item_value << "\t"
                 << supply_items[i].fraction_used << endl;
        }
    }

    return 0;
}
