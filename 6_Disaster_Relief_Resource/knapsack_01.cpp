#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item
{
    int item_id;
    string item_name;
    int item_weight;
    int item_value;
    int priority_level;
    bool is_selected;
};

// build table to find maximum value combination
int knapsack01(vector<Item> &all_items, int bag_capacity, vector<vector<int>> &value_table)
{
    int total_items = all_items.size();

    for (int item_index = 1; item_index <= total_items; item_index++)
    {
        for (int current_weight = 0; current_weight <= bag_capacity; current_weight++)
        {
            if (all_items[item_index - 1].item_weight > current_weight)
            {
                value_table[item_index][current_weight] = value_table[item_index - 1][current_weight];
            }
            else
            {
                int without_item = value_table[item_index - 1][current_weight];
                int with_item = value_table[item_index - 1][current_weight - all_items[item_index - 1].item_weight] + all_items[item_index - 1].item_value;
                value_table[item_index][current_weight] = max(without_item, with_item);
            }
        }
    }

    return value_table[total_items][bag_capacity];
}

// figure out which items were picked
void findSelectedItems(vector<Item> &all_items, int bag_capacity, const vector<vector<int>> &value_table)
{
    int total_items = all_items.size();
    int remaining_weight = bag_capacity;

    for (int item_index = total_items; item_index > 0 && remaining_weight > 0; item_index--)
    {
        if (value_table[item_index][remaining_weight] != value_table[item_index - 1][remaining_weight])
        {
            all_items[item_index - 1].is_selected = true;
            remaining_weight -= all_items[item_index - 1].item_weight;
        }
    }
}

// sort items by priority and value
bool comparePriority(const Item &first_item, const Item &second_item)
{
    if (first_item.priority_level != second_item.priority_level)
        return first_item.priority_level < second_item.priority_level;
    return first_item.item_value > second_item.item_value;
}

int main()
{
    int bag_capacity = 50;
    vector<Item> relief_items = {
        {1, "Medicine Kit", 15, 100, 1, false},
        {2, "Antibiotics", 8, 80, 1, false},
        {3, "Food Packets", 20, 60, 2, false},
        {4, "Drinking Water", 12, 40, 2, false},
        {5, "Blankets", 10, 30, 3, false},
        {6, "Tents", 25, 70, 3, false},
        {7, "First Aid", 5, 50, 1, false}};

    int total_items = relief_items.size();
    sort(relief_items.begin(), relief_items.end(), comparePriority);

    vector<vector<int>> value_table(total_items + 1, vector<int>(bag_capacity + 1, 0));
    int maximum_value = knapsack01(relief_items, bag_capacity, value_table);

    findSelectedItems(relief_items, bag_capacity, value_table);

    int total_weight_used = 0;
    for (int i = 0; i < relief_items.size(); i++)
    {
        if (relief_items[i].is_selected)
        {
            total_weight_used += relief_items[i].item_weight;
        }
    }

    cout << "Maximum Utility Value: " << maximum_value << endl;
    cout << "Total Weight Used: " << total_weight_used << " kg (Capacity: " << bag_capacity << " kg)" << endl;
    cout << "\nItems Selected:" << endl;
    cout << "ID\tName\t\t\tWeight\tValue\tPriority" << endl;
    cout << "-----------------------------------------------------------" << endl;

    for (int i = 0; i < relief_items.size(); i++)
    {
        if (relief_items[i].is_selected)
        {
            string priority_name;
            if (relief_items[i].priority_level == 1)
                priority_name = "High";
            else if (relief_items[i].priority_level == 2)
                priority_name = "Medium";
            else
                priority_name = "Low";

            cout << relief_items[i].item_id << "\t" << relief_items[i].item_name << "\t\t"
                 << relief_items[i].item_weight << "\t" << relief_items[i].item_value << "\t"
                 << priority_name << endl;
        }
    }

    cout << "\nPriority-wise breakdown:" << endl;
    int high_priority_count = 0;
    int medium_priority_count = 0;
    int low_priority_count = 0;

    for (int i = 0; i < relief_items.size(); i++)
    {
        if (relief_items[i].is_selected)
        {
            if (relief_items[i].priority_level == 1)
                high_priority_count++;
            else if (relief_items[i].priority_level == 2)
                medium_priority_count++;
            else
                low_priority_count++;
        }
    }

    cout << "High priority items: " << high_priority_count << endl;
    cout << "Medium priority items: " << medium_priority_count << endl;
    cout << "Low priority items: " << low_priority_count << endl;

    return 0;
}
