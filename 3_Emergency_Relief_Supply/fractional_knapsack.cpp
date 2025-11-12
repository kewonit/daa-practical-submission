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
    vector<Item> supply_items;
    
    Item item1; item1.item_id = 1; item1.item_name = "Medicine Kit"; item1.item_weight = 10; item1.item_value = 60; item1.value_per_weight = 0; item1.fraction_used = 0;
    Item item2; item2.item_id = 2; item2.item_name = "Food Packets"; item2.item_weight = 20; item2.item_value = 100; item2.value_per_weight = 0; item2.fraction_used = 0;
    Item item3; item3.item_id = 3; item3.item_name = "Drinking Water"; item3.item_weight = 30; item3.item_value = 120; item3.value_per_weight = 0; item3.fraction_used = 0;
    Item item4; item4.item_id = 4; item4.item_name = "Blankets"; item4.item_weight = 15; item4.item_value = 45; item4.value_per_weight = 0; item4.fraction_used = 0;
    Item item5; item5.item_id = 5; item5.item_name = "First Aid"; item5.item_weight = 5; item5.item_value = 30; item5.value_per_weight = 0; item5.fraction_used = 0;
    
    supply_items.push_back(item1);
    supply_items.push_back(item2);
    supply_items.push_back(item3);
    supply_items.push_back(item4);
    supply_items.push_back(item5);

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
