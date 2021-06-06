#include "functions.hpp"

void error_rate(string inpath, string outpath)
{

    Graph g = read_graph(inpath);
    ofstream output(outpath);

    auto start1 = chrono::high_resolution_clock::now();
    vector<double> bc = g.compute_bc();
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1);
    vector<pair<double, int>> bc_index;
    for (int i = 0; i < bc.size(); ++i) {
        bc_index.push_back(make_pair(bc[i], i));
    }
    sort(bc_index.begin(), bc_index.end(), greater<pair<double, int>>());
    cout << "exact bc: " << (double)duration1.count() / 1000000 << " sec" << endl;
    print_sum_vectror(bc);
    cout << "diameter = " << g.get_diameter() << endl;

    for (int limit = 2; limit <= g.get_diameter(); ++limit) {
        auto start2 = chrono::high_resolution_clock::now();
        vector<double> limited_bc = g.compute_limited_bc(limit);
        auto end2 = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2);
        vector<pair<double, int>> limited_bc_index;
        for (int i = 0; i < bc.size(); ++i) {
            limited_bc_index.push_back(make_pair(limited_bc[i], i));
        }
        sort(limited_bc_index.begin(), limited_bc_index.end(), greater<pair<double, int>>());
        cout << "limit = " << limit << endl;
        output << limit << " ";
        double time = (double)duration2.count() / 1000000;
        cout << "limited bc: " << time << " sec" << endl;
        output << time;
        for (int k = 1; k <= 100; ++k) {
            double ratio = compute_error_ratio(bc_index, limited_bc_index, k);
            cout << "top " << k << "% error ratio = " << ratio << "%" << endl;
            output << " " << ratio;
        }
        output << endl;
        print_sum_vectror(limited_bc);
    }
}

void top10(string inpath)
{

    Graph g = read_graph(inpath);

    vector<double> bc = g.compute_bc();
    vector<pair<double, int>> bc_index;
    for (int i = 0; i < bc.size(); ++i) {
        bc_index.push_back(make_pair(bc[i], i));
    }
    sort(bc_index.begin(), bc_index.end(), greater<pair<double, int>>());

    vector<double> limited_bc = g.compute_limited_bc(2);
    vector<pair<double, int>> limited_bc_index;
    for (int i = 0; i < bc.size(); ++i) {
        limited_bc_index.push_back(make_pair(limited_bc[i], i));
    }
    sort(limited_bc_index.begin(), limited_bc_index.end(), greater<pair<double, int>>());

    for (int i = 0; i < bc_index.size(); ++i) {
        cout << "|" << i + 1 << "|" << bc_index[i].second << "|" << limited_bc_index[i].second << "|" << bc_index[i].first << "|" << limited_bc_index[i].first << "|" << endl;
    }
}

int main(int argc, char* argv[])
{
    error_rate(argv[1], argv[2]);
    // top10(argv[1]);
    return 0;
}