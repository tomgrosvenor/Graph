
#include <iostream>
#include <memory>

#include "Graph.h"

using namespace std;

struct traverse_info {
    string  from_node;
    string  node;
    int     accum_cost;

    bool operator< (const traverse_info& rhs) {
        return accum_cost < rhs.accum_cost;
    }
};


int main() {

    Graph graph1 {"zero", "one", "two", "three", "ohmy", "four", "five", "six", "ohno", "seven", "eight", "nine"};
    Graph graph2 { };
    Graph graph3;
    Graph graph4 { "four" };
    Graph dg     { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p" };

    cout << "graph1 size = " << graph1.size() << endl;
    cout << "graph2 size = " << graph2.size() << endl;
    cout << "graph3 size = " << graph3.size() << endl;
    cout << "graph4 size = " << graph4.size() << endl;

/* tbg

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

tbg */

    dg.create_density(0.35);
    cout << "With density of 35%: (dg)" << endl;
    cout << dg << endl;



    unordered_map <string, pair <string, int> > closed;
    vector <traverse_info>                      open;


    // Get the nodes/costs reachable from node 'g'
    unique_ptr< vector<reachable_node> > rn = dg.get_reachable_nodes ("g");

    // Add the reachable nodes to the 'open list' if they are
    // not already in the 'closed list'.
    //
    for (auto& [name, cost] : *rn) {
            cout << "name: " << name << ", cost: " << cost << endl; // tbg
        if (!closed.contains(name)) {
            open.push_back( {"g", name, cost} );
        }
    }

    for (auto& [from, node, cost] : open) {
        cout << "from: " << from << ", to node: " << node << ", cost: " << cost << endl;
    }

    sort (open.begin(), open.end());

    cout << "   after sort():" << endl;
    for (auto& [from, node, cost] : open) {
        cout << "from: " << from << ", to node: " << node << ", cost: " << cost << endl;
    }

    // Use a lambda expression to sort 'open' in desending order
    //
    sort (open.begin(), open.end(), [](traverse_info& a, traverse_info& b) {
        return a.accum_cost > b.accum_cost;
    });

    cout << "   after lambda expression sort():" << endl;
    for (auto& [from, node, cost] : open) {
        cout << "from: " << from << ", to node: " << node << ", cost: " << cost << endl;
    }

    // Get the last element
    //
    traverse_info ti = open.back();
    cout << "The last element:" << endl;
    cout << "   from: " << ti.from_node << endl;
    cout << "   node: " << ti.node << endl;
    cout << "   cost: " << ti.accum_cost << endl;

    // Remove the last element
    //
    open.pop_back();

    // Get the last element
    //
    ti = open.back();
    cout << "The last element:" << endl;
    cout << "   from: " << ti.from_node << endl;
    cout << "   node: " << ti.node << endl;
    cout << "   cost: " << ti.accum_cost << endl;

    // Remove the last element
    //
    open.pop_back();

    // Get the last element
    //
    ti = open.back();
    cout << "The last element:" << endl;
    cout << "   from: " << ti.from_node << endl;
    cout << "   node: " << ti.node << endl;
    cout << "   cost: " << ti.accum_cost << endl;

    // Remove the last element
    //
    open.pop_back();
}
