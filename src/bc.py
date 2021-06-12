import networkx as nx
from networkx.algorithms.centrality import betweenness_centrality
import sys
import time
from datetime import datetime


def read_graph():
    filepath = sys.argv[1]
    graph = nx.Graph()
    f = open(filepath, "r")
    lines = f.readlines()
    for line in lines:
        if '#' in line:
            continue
        left = int(line.split()[0])
        right = int(line.split()[1])
        if left == right:
            continue
        graph.add_edge(left, right)
        graph.add_edge(right, left)
    f.close()
    return graph


if __name__ == "__main__":
    start_datetime = datetime.today().strftime('%Y-%m-%d-%H:%M:%S')
    graph = read_graph()
    start = time.time()
    bcs = betweenness_centrality(graph, normalized=False)
    for i in bcs:
        print(str(i) + ": " + str(bcs[i]))
    end = time.time()
    print(end - start, "s")
