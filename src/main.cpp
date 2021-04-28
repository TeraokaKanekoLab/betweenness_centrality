#include "functions.hpp"

int main(int argc, char* argv[])
{
    assert(argc == 3);
    Graph g = read_graph(argv[1]);
    read_community(argv[2], g);
    g.print_community();
    return 0;
}
