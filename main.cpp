
#include <iostream>
#include "Graph.h"

using namespace std;

int main() {

    Graph graph1 {"zero", "one", "two", "three", "ohmy", "four", "five", "six", "ohno", "seven", "eight", "nine"};
    Graph graph2 { };
    Graph graph3;
    Graph graph4 { "four" };

    cout << "graph1 size = " << graph1.size() << endl;
    cout << "graph2 size = " << graph2.size() << endl;
    cout << "graph3 size = " << graph3.size() << endl;
    cout << "graph4 size = " << graph4.size() << endl;

    // Create default density for each graph.
    graph1.create_density();

    cout << "With default density (graph1):" << endl;
    cout << graph1 << endl;

    graph2.create_density();

    cout << "With default density: (graph2)" << endl;
    cout << graph2 << endl;

    graph3.create_density();
    graph4.create_density();

    // Create a density of 35% for graph1.
    graph1.create_density(0.35);

    cout << "With density 0.35 (graph1):" << endl;
    cout << graph1.to_string() << endl;

    cout << "With density 0.35 (graph1) (using <<):" << endl;
    cout << graph1 << "okay" << 4 << "\n" << graph4 << endl;
}
