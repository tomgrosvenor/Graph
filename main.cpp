
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

    string input;

    // tbg Graph dg { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p" };
    Graph dg { "a", "b", "c", "d" };

    cout << "dg size = " << dg.size() << endl;

    // Create random edges & weights for 'dg'.
    //
    dg.create_density(0.5);

    // Print 'dg'.
    cout << "With density of 50%: (dg)" << endl;
    cout << dg << endl;

    // Copy dg using the copy constructor and print 'dgc'.
    Graph dgc { dg };
    cout << "dgc size = " << dgc.size() << endl;
    cout << "Print: (dgc)" << endl;
    cout << dgc << endl;
      cout << "Pause for randomness ... "s;
      cin >> input;

      dg.create_density(0.25);
      cout << "With density of 25%: (dg)" << endl;
      cout << dg << endl;
        cout << "Print: (dgc)" << endl;
        cout << dgc << endl;

    // Assign dg using the copy assignment and print 'dgc2'.
    Graph dgc2;
    dgc2 = dgc;
      cout << "Pause for randomness ... "s;
      cin >> input;
      dgc.create_density(0.15);
    cout << "dgc2 size = " << dgc2.size() << endl;
    cout << "Print: (dgc2)" << endl;
    cout << dgc2 << endl;
      cout << "With density of 15%: (dgc)" << endl;
      cout << dgc << endl;
        cout << "Print: (dgc2)" << endl;
        cout << dgc2 << endl;

/* tbg
    // Create an open & closed 'list' for implementing
    //  Dijkstra's algorithm.
    //
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

tbg */

}
