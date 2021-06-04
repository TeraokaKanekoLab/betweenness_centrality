#include "functions.hpp"

int main(int argc, char* argv[])
{
    assert(argc == 3);
    Graph g = read_graph(argv[1]);
    g.export_dist_impact(argv[2]);
    return 0;
}
