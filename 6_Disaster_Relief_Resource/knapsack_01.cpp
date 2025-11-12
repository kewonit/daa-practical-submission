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
int knapsack01(vector<Item> &all_items, int bag_capacity, vector<vector<int> > &value_table)
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
void findSelectedItems(vector<Item> &all_items, int bag_capacity, const vector<vector<int> > &value_table)
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
    vector<Item> relief_items;
    
    Item item1; item1.item_id = 1; item1.item_name = "Medicine Kit"; item1.item_weight = 15; item1.item_value = 100; item1.priority_level = 1; item1.is_selected = false; relief_items.push_back(item1);
    Item item2; item2.item_id = 2; item2.item_name = "Antibiotics"; item2.item_weight = 8; item2.item_value = 80; item2.priority_level = 1; item2.is_selected = false; relief_items.push_back(item2);
    Item item3; item3.item_id = 3; item3.item_name = "Food Packets"; item3.item_weight = 20; item3.item_value = 60; item3.priority_level = 2; item3.is_selected = false; relief_items.push_back(item3);
    Item item4; item4.item_id = 4; item4.item_name = "Drinking Water"; item4.item_weight = 12; item4.item_value = 40; item4.priority_level = 2; item4.is_selected = false; relief_items.push_back(item4);
    Item item5; item5.item_id = 5; item5.item_name = "Blankets"; item5.item_weight = 10; item5.item_value = 30; item5.priority_level = 3; item5.is_selected = false; relief_items.push_back(item5);
    Item item6; item6.item_id = 6; item6.item_name = "Tents"; item6.item_weight = 25; item6.item_value = 70; item6.priority_level = 3; item6.is_selected = false; relief_items.push_back(item6);
    Item item7; item7.item_id = 7; item7.item_name = "First Aid"; item7.item_weight = 5; item7.item_value = 50; item7.priority_level = 1; item7.is_selected = false; relief_items.push_back(item7);

    int total_items = relief_items.size();
    sort(relief_items.begin(), relief_items.end(), comparePriority);

    vector<vector<int> > value_table(total_items + 1, vector<int>(bag_capacity + 1, 0));
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
