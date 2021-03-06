# Louvain
## General
Git repository for understanding [A Clustered Approach for Fast Computation of Betweenness Centrality in Social Networks](https://ieeexplore.ieee.org/document/7207201/).

## Version History
| Version | Date  | Commit | Notes |
| :-----: | :-: | :-: | :-: |
| 0.0 | April 28, 2021 | [ec01299](https://github.com/TeraokaKanekoLab/betweenness_centrality/commit/ec01299186fe6aa64cb318f26836dc78ab2e4e34) | first commit |
| 0.1 | April 28, 2021 | [84d59e7](https://github.com/TeraokaKanekoLab/betweenness_centrality/commit/84d59e78c2f8e900a6dbe0d5ba1ecd0d95c7177d) | Check border nodes |
| 0.2 | June 4, 2021 | [1351dcb](https://github.com/TeraokaKanekoLab/betweenness_centrality/commit/1351dcbfccaffa19b23f2968e5bb7d45b4a8f069) | dist of two nodes to impact |
| 0.3 | June 6, 2021 | [55d5e59](https://github.com/TeraokaKanekoLab/betweenness_centrality/commit/55d5e594957f9aa5b67755c19448b183f6a337aa) | error ratio and computation time |
| 0.4 | June 6, 2021 | [3f8d100](https://github.com/TeraokaKanekoLab/betweenness_centrality/commit/3f8d100c7e3c0ef65ea2cb7cceb5f2e830a7b831) | modified sorting order from ascending to descending |
| 0.5 | June 12, 2021 | [eaaffb4](https://github.com/TeraokaKanekoLab/betweenness_centrality/commit/eaaffb4c9f8c453fb20b878b9607fd961a75f48e) | calculate clustering coefficient |

## Graph Data File Format
The graph data files need to follow the rule below. `<endpoint n>` needs to be an int (node id)

```
<endpoint 1> <endpoint 2>
<endpoint 3> <endpoint 4>
.
.
.
```

Let's say there is a graph like this.
![](https://i.ibb.co/g6F8pfv/images-dragged.jpg)

The following data (`graph/simple_graph.gr`) represents this simple graph with 9 nodes and 12 edges, which are <0, 1>, ..., <7, 8>.

```
0 1
0 2
1 2
1 3
2 3
2 7
3 4
3 5
4 6
5 6
5 8
7 8
```

## How to Run the Program
Try the following command to get an instant result.

```
sh run.sh all graph/simple_graph.gr output/simple_graph.gr
```

## References
1. P. Suppa and E. Zimeo, [A Clustered Approach for Fast Computation of Betweenness Centrality in Social Networks](https://ieeexplore.ieee.org/document/7207201/), *2015 IEEE International Congress on Big Data*, 2015, pp. 47-54, doi: 10.1109/BigDataCongress.2015.17.