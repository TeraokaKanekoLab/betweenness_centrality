#include "graph.hpp"

Graph read_graph(string filepath)
{
    std::ifstream file(filepath);
    if (!file.good()) {
        cout << "file not found" << endl;
        exit(-1);
    }

    Graph graph;

    int u, v;
    // エッジの追加
    while (file >> u >> v)
        graph.add_edge(u, v);

    file.close();

    return graph;
}

void read_community(string filepath, Graph& g)
{
    std::ifstream file(filepath);
    if (!file.good()) {
        cout << "file not found" << endl;
        exit(-1);
    }

    Graph graph;

    int u, v;
    // エッジの追加
    while (file >> u >> v)
        g.add_to_community(u, v);

    file.close();
}