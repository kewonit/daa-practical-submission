/*
 * File: merge_sort.cpp
 * Author: 123B1F052

 * Description: Implements Merge Sort algorithm to sort customer orders by timestamp.
 * Usage:
 *   Compile: g++ -O2 -std=c++17 merge_sort.cpp -o merge_sort
 *   Run:     ./merge_sort < input.txt > output.txt
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Order
{
    int id;
    long long timestamp;
};

// Merge two sorted segments of the orders array into a single sorted segment by timestamp
void merge(vector<Order> &a, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Order> L(a.begin() + left, a.begin() + mid + 1);
    vector<Order> R(a.begin() + mid + 1, a.begin() + right + 1);
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].timestamp <= R[j].timestamp)
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    while (i < n1)
        a[k++] = L[i++];
    while (j < n2)
        a[k++] = R[j++];
}

// Recursively divide the orders array and sort each half using merge sort
void mergeSort(vector<Order> &a, int left, int right)
{
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    merge(a, left, mid, right);
}

// Entry point: read orders, sort by timestamp, and output sorted list
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n))
        return 0;

    vector<Order> orders(n);
    for (int i = 0; i < n; ++i)
        cin >> orders[i].id >> orders[i].timestamp;

    mergeSort(orders, 0, n - 1);

    for (const auto &o : orders)
        cout << o.id << ' ' << o.timestamp << '\n';

    return 0;
}
