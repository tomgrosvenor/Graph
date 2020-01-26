# Graph
A representation of a Graph with random, directional edges (with random weights).

The main() routine implements Dijkstra's shortest path algorithm using this Graph class.

To build under MacOS (from a command line):

    g++-9 -std=c++2a -O2 Graph.cpp main.cpp

To run (in the directory the above build was done):

    a.out

The program will create a graph with directed edges and a density of 50%.

It prints the graph showing the edges connect to a node and each edge's weight/cost.

The user is asked to enter a start node and an end node.

The program then searches for the shortest (least cost) path between the two nodes.

If a path is found it prints the nodes in the path and the cumulative cost.

If no path is found, a message is printed saying not path was found.
