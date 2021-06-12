#include "header.hpp"

class Graph {
private:
    typedef pair<int, int> edge;
    unordered_map<int, int> original_to_renumbered;
    vector<int> renumbered_to_original;
    vector<vector<int>> neighbors;
    vector<int> node_to_community;
    vector<double> betweenness_centrality;
    vector<vector<int>> communities;
    unordered_map<int, long long> dist_to_num_pairs;
    int num_nodes;
    int num_edges;
    int num_communities;
    int diameter;
    bool has_computed_bc;

    void add_vertex(int original_id)
    {
        if (original_to_renumbered.find(original_id) != original_to_renumbered.end())
            return;
        original_to_renumbered[original_id] = num_nodes;
        neighbors.push_back(vector<int>());
        betweenness_centrality.push_back(0);
        renumbered_to_original.push_back(original_id);
        node_to_community.push_back(-1);
        ++num_nodes;
    }

public:
    Graph()
    {
        num_nodes = 0;
        num_edges = 0;
        num_communities = 0;
        has_computed_bc = false;
    }

    // getter
    // We assume v is a valid node
    // Otherwise an exception will be triggered
    int get_degree(int v)
    {
        assert(0 <= v && v < num_nodes);
        return neighbors[v].size();
    }
    vector<int> get_degrees()
    {
        vector<int> degrees = vector<int>(num_nodes, 0);
        for (int i = 0; i < num_nodes; ++i)
            degrees[i] = get_degree(i);
        return degrees;
    }

    int get_num_vertices()
    {
        return num_nodes;
    }

    int get_num_edges()
    {
        return num_edges;
    }

    // We assume v is a valid node
    // Otherwise an exception will be triggered
    vector<int> get_neighbors(int v)
    {
        return neighbors[v];
    }

    vector<int> get_vertices()
    {
        vector<int> vertices;
        for (int i = 0; i < num_nodes; ++i) {
            vertices.push_back(renumbered_to_original[i]);
        }
        return vertices;
    }

    int get_diameter()
    {
        if (!has_computed_bc)
            compute_bc();
        return diameter;
    }

    void print_graph()
    {
        for (int i = 0; i < num_nodes; ++i) {
            cout << renumbered_to_original[i] << ":";
            for (auto v : neighbors[i]) {
                cout << " " << renumbered_to_original[v];
            }
            cout << endl;
        }
    }

    // compute
    vector<double> compute_bc()
    {
        if (has_computed_bc)
            return betweenness_centrality;
        has_computed_bc = true;
        long long sum_bc = 0;
        for (int s = 0; s < num_nodes; ++s) {
            stack<int> stack;
            vector<vector<int>> direct_predecessors = vector<vector<int>>(num_nodes, vector<int>());
            vector<int> num_paths = vector<int>(num_nodes, 0);
            num_paths[s] = 1;
            vector<int> d = vector<int>(num_nodes, -1);
            d[s] = 0;
            queue<int> visited;
            visited.push(s);

            while (!visited.empty()) {
                int v = visited.front();
                visited.pop();
                stack.push(v);
                for (int nbr : neighbors[v]) {
                    if (d[nbr] < 0) {
                        visited.push(nbr);
                        d[nbr] = d[v] + 1;
                    }
                    if (d[nbr] == d[v] + 1) {
                        num_paths[nbr] += num_paths[v];
                        direct_predecessors[nbr].push_back(v);
                    }
                }
            }
            vector<double> delta = vector<double>(num_nodes, 0);
            while (!stack.empty()) {
                int w = stack.top();
                stack.pop();
                for (int pred : direct_predecessors[w])
                    delta[pred] += (double)num_paths[pred] / num_paths[w] * (1 + delta[w]);

                if (w == s)
                    continue;
                betweenness_centrality[w] += delta[w];
                if (dist_to_num_pairs.find(d[w]) == dist_to_num_pairs.end())
                    dist_to_num_pairs[d[w]] = 1;
                else
                    dist_to_num_pairs[d[w]]++;
                sum_bc += d[w] - 1;
            }

            for (int eachd : d)
                diameter = max(diameter, eachd);
        }

        return betweenness_centrality;
    }

    // compute
    vector<double> compute_limited_bc(int max_dist)
    {
        vector<double> limited_bc = vector<double>(num_nodes, 0);
        long long sum_bc = 0;
        for (int s = 0; s < num_nodes; ++s) {
            stack<int> stack;
            vector<vector<int>> direct_predecessors = vector<vector<int>>(num_nodes, vector<int>());
            vector<int> num_paths = vector<int>(num_nodes, 0);
            num_paths[s] = 1;
            vector<int> d = vector<int>(num_nodes, -1);
            d[s] = 0;
            queue<int> visited;
            visited.push(s);

            while (!visited.empty()) {
                int v = visited.front();
                visited.pop();
                stack.push(v);
                if (d[v] >= max_dist)
                    continue;
                for (int nbr : neighbors[v]) {
                    if (d[nbr] < 0) {
                        visited.push(nbr);
                        d[nbr] = d[v] + 1;
                    }
                    if (d[nbr] == d[v] + 1) {
                        num_paths[nbr] += num_paths[v];
                        direct_predecessors[nbr].push_back(v);
                    }
                }
            }

            vector<double> delta = vector<double>(num_nodes, 0);

            while (!stack.empty()) {
                int w = stack.top();
                stack.pop();
                for (int pred : direct_predecessors[w])
                    delta[pred] += (double)num_paths[pred] / num_paths[w] * (1 + delta[w]);

                if (w == s)
                    continue;
                limited_bc[w] += delta[w];
                if (dist_to_num_pairs.find(d[w]) == dist_to_num_pairs.end())
                    dist_to_num_pairs[d[w]] = 1;
                else
                    dist_to_num_pairs[d[w]]++;
                sum_bc += d[w] - 1;
            }
        }
        return limited_bc;
    }

    double compute_clustering_coefficient(int nd, unordered_map<int, unordered_set<int>>& neighbors_of)
    {
        vector<int> nbs = get_neighbors(nd);
        int d = nbs.size(); // degree of nd
        if (d < 2)
            return 0;
        int cnt = 0; // # of edges in any pairs of neighbors
        for (int nb1 : nbs)
            for (int nb2 : nbs)
                if (neighbors_of[nb1].find(nb2) != neighbors_of[nb1].end())
                    cnt++;
        return (double)cnt / (d * (d - 1));
    }

    vector<double> compute_all_clustering_coefficient()
    {
        vector<double> cc = vector<double>(num_nodes, 0);
        unordered_map<int, unordered_set<int>> neighbors_of;
        for (int nd = 0; nd < num_nodes; nd++) {
            neighbors_of[nd] = unordered_set<int>();
            for (int nbr : get_neighbors(nd))
                neighbors_of[nd].insert(nbr);
        }
        for (int nd = 0; nd < num_nodes; nd++)
            cc[nd] = compute_clustering_coefficient(nd, neighbors_of);
        return cc;
    }

    // setter
    void add_edge(int u, int v)
    {
        add_vertex(u);
        add_vertex(v);
        u = original_to_renumbered[u];
        v = original_to_renumbered[v];
        neighbors[u].push_back(v);
        neighbors[v].push_back(u);
        ++num_edges;
    }

    void print_betweeness_centrality()
    {
        if (!has_computed_bc)
            compute_bc();
        double sum = 0;
        // for (int i = 0; i < num_nodes; ++i)
        //     sum += betweenness_centrality[i];
        // for (int i = 0; i < num_nodes; ++i)
        //     cout << renumbered_to_original[i] << ": " << betweenness_centrality[i] / sum << endl;
        for (int i = 0; i < num_nodes; ++i)
            cout << renumbered_to_original[i] << ": " << betweenness_centrality[i] << endl;
    }

    void add_to_community(int original_id, int community)
    {
        int renumbered = original_to_renumbered[original_id];
        node_to_community[renumbered] = community;
        if (num_communities <= community) {
            num_communities = community + 1;
            communities.resize(num_communities, vector<int>());
        }
        communities[community].push_back(renumbered);
    }

    bool is_border_node(int nd)
    {
        int community = node_to_community[nd];
        for (int nbr : neighbors[nd])
            if (node_to_community[nbr] != community)
                return true;
        return false;
    }

    void print_community()
    {
        int all_borderes = 0;
        for (int i = 0; i < num_communities; ++i) {
            cout << "community " << i << "; ";
            int num_borders = 0;
            for (int j = 0; j < communities[i].size(); ++j)
                if (is_border_node(communities[i][j]))
                    ++num_borders;
            cout << "size: " << communities[i].size() << ", border: " << num_borders << endl;
            all_borderes += num_borders;
        }
        cout << "# nodes: " << num_nodes << ", # border nodes: " << all_borderes << endl;
    }

    double sum_of_bc()
    {
        if (!has_computed_bc)
            compute_bc();
        double sum_bc = 0;
        for (auto bc : betweenness_centrality) {
            sum_bc += bc;
        }
        return sum_bc;
    }

    void export_dist_impact(string filepath)
    {
        if (!has_computed_bc)
            compute_bc();
        ofstream output(filepath);
        vector<pair<int, long long>> dist_num_pairs;
        for (auto kv : dist_to_num_pairs)
            dist_num_pairs.push_back(kv);
        sort(dist_num_pairs.begin(), dist_num_pairs.end());
        for (auto [dist, num_pairs] : dist_num_pairs)
            output << dist << " " << num_pairs << " " << (long long)(dist - 1) * num_pairs << endl;
    }
};