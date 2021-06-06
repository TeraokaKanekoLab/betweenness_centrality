#include <algorithm>
#include <cassert>
#include <chrono>
#include <climits>
#include <deque>
#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

void print_vector(vector<int> nums)
{
    cout << "[" << nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        cout << ", " << nums[i];
    }
    cout << "]" << endl;
}

void print_double_vector(vector<double> nums)
{
    cout << "[" << nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        cout << ", " << nums[i];
    }
    cout << "]" << endl;
}

void print_set(unordered_set<int>& nums)
{
    cout << "set:";
    for (auto num : nums) {
        cout << " " << num;
    }
    cout << endl;
}

void print_nodes_in_community(unordered_map<int, unordered_set<int>> nodes_in_communities)
{
    for (auto [c, nodes] : nodes_in_communities) {
        cout << c << ":";
        for (auto node : nodes)
            cout << " " << node;
        cout << endl;
    }
}

long double print_sum_vectror(vector<double> values)
{
    long double sum = 0;
    for (double v : values)
        sum += v;
    cout << sum << endl;

    return sum;
}

double compute_error_ratio(vector<pair<double, int>> bc_index, vector<pair<double, int>> limited_bc_index, double k)
{
    unordered_set<int> indices, limited_indices;
    if (k < 0 || k > 100) {
        cout << "k must be [0, 100]" << endl;
        return -1;
    }

    int num_checked_nodes = bc_index.size() * k / 100;
    for (int i = 0; i < num_checked_nodes; ++i) {
        indices.insert(bc_index[i].second);
        limited_indices.insert(limited_bc_index[i].second);
    }

    int num_error = 0;
    for (auto index : limited_indices)
        if (indices.find(index) == indices.end())
            ++num_error;

    return (double)num_error * 100 / num_checked_nodes;
}
