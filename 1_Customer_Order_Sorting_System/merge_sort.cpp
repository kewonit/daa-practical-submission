#include <iostream>
#include <vector>

using namespace std;

struct Order
{
    int order_id;
    long long order_timestamp;
};

// merge two sorted halves into one sorted array
void merge(vector<Order> &orders, int start_index, int middle_index, int end_index)
{
    int left_size = middle_index - start_index + 1;
    int right_size = end_index - middle_index;

    vector<Order> left_orders(orders.begin() + start_index, orders.begin() + middle_index + 1);
    vector<Order> right_orders(orders.begin() + middle_index + 1, orders.begin() + end_index + 1);

    int left_pointer = 0;
    int right_pointer = 0;
    int main_pointer = start_index;

    while (left_pointer < left_size && right_pointer < right_size)
    {
        if (left_orders[left_pointer].order_timestamp <= right_orders[right_pointer].order_timestamp)
        {
            orders[main_pointer] = left_orders[left_pointer];
            left_pointer++;
        }
        else
        {
            orders[main_pointer] = right_orders[right_pointer];
            right_pointer++;
        }
        main_pointer++;
    }

    while (left_pointer < left_size)
    {
        orders[main_pointer] = left_orders[left_pointer];
        left_pointer++;
        main_pointer++;
    }

    while (right_pointer < right_size)
    {
        orders[main_pointer] = right_orders[right_pointer];
        right_pointer++;
        main_pointer++;
    }
}

// sort orders by timestamp using merge sort
void mergeSort(vector<Order> &orders, int start_index, int end_index)
{
    if (start_index >= end_index)
        return;

    int middle_index = start_index + (end_index - start_index) / 2;
    mergeSort(orders, start_index, middle_index);
    mergeSort(orders, middle_index + 1, end_index);
    merge(orders, start_index, middle_index, end_index);
}

int main()
{
    vector<Order> all_orders = {
        {101, 1609459200},
        {102, 1609455600},
        {103, 1609462800},
        {104, 1609457400},
        {105, 1609460000}};

    int total_orders = all_orders.size();
    mergeSort(all_orders, 0, total_orders - 1);

    for (int i = 0; i < total_orders; i++)
    {
        cout << all_orders[i].order_id << ' ' << all_orders[i].order_timestamp << '\n';
    }

    return 0;
}
