#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Order
{
    int id;
    long long timestamp;
};

// Combines two sorted subarrays into one sorted array
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

// Divide and conquer approach to sort orders by timestamp
void mergeSort(vector<Order> &a, int left, int right)
{
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    merge(a, left, mid, right);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Hardcoded input data
    vector<Order> orders = {
        {101, 1609459200},
        {102, 1609455600},
        {103, 1609462800},
        {104, 1609457400},
        {105, 1609460000}};

    int n = orders.size();
    mergeSort(orders, 0, n - 1);

    for (const auto &o : orders)
        cout << o.id << ' ' << o.timestamp << '\n';

    return 0;
}
