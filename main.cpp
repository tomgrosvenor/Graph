
#include <iostream>
#include <memory>

#include "Graph.h"

using namespace std;

struct traverse_info {
    string  from_node;
    string  node_id;
    int     total_cost;

    bool operator< (const traverse_info& rhs) {
        return total_cost < rhs.total_cost;
    }
};


int main() {

    string input, cur_node, end_node;

    // tbg Graph dg { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p" };
    Graph dg { "a", "b", "c", "d", "e" };

    cout << "dg size = " << dg.size() << endl;

    // Create random edges & weights for 'dg'.
    //
    dg.create_density(0.5);

    // Print 'dg'.
    cout << "With density of 50%: (dg)" << endl;
    cout << dg << endl;

    // Create an open & a closed 'list' for implementing
    //  Dijkstra's algorithm.
    //
    unordered_map <string, traverse_info> closed;
    vector <traverse_info>                open;

    // Ask the user to enter a start node.
    cout << "Please enter a starting node: "s;
    cin >> cur_node;

    // Make sure the user entered a cur_node that's in the graph.
    if (!dg.contains(cur_node)) {
        cout << "The start node entered is not in the graph: "s << cur_node << endl;
        return 1;
    }

    // Ask the user to enter an end node.
    cout << "Please enter an end node: "s;
    cin >> end_node;

    // Make sure the user entered a end_node that's in the graph.
    if (!dg.contains(end_node)) {
        cout << "The end node entered is not in the graph: "s << end_node << endl;
        return 1;
    }

    // Add the cur_node to the 'closed' list.
    //
    closed.insert( {cur_node, {cur_node, cur_node, 0}} );

    // Get the nodes/costs reachable from the cur_node.
    unique_ptr< vector<reachable_node> > rn = dg.get_reachable_nodes (cur_node);

    // Add nodes reachable from the cur_node to the 'open list'
    // if they are not already in the 'closed list'.
    //
    for (auto& [name, cost] : *rn) {
            cout << "name: " << name << ", cost: " << cost << endl; // tbg
        if (!closed.contains(name)) {
            cout << "    put on open list: name: " << name << ", cost: " << cost << endl; // tbg
            open.push_back( {cur_node, name, cost} );
        }
    }

    cout << endl; // tbg

    // Use a lambda expression to sort the 'open' list in desending order
    //
    sort (open.begin(), open.end(), [](traverse_info& a, traverse_info& b) {
        return a.total_cost > b.total_cost;
    });

    while (!closed.contains(end_node) && !open.empty()) {

        // Get the next node that has the smallest total cost.
        traverse_info next_node = open.back();
        open.pop_back();

        // Add this 'next' node to the closed list. Determine what
        // nodes are reachable from this 'next' node and add them to
        // the open list.  Continue checking to see if the end_node
        // has been added to the closed list.
        //
        closed.insert( {next_node.node_id, {next_node.from_node,
                                            next_node.node_id,
                                            next_node.total_cost + closed.at(next_node.from_node).total_cost}} );

        // Get the nodes/costs reachable from this next_node.
        unique_ptr< vector<reachable_node> > rn = dg.get_reachable_nodes (next_node.node_id);

        // Add nodes reachable from this next_node to the 'open list'
        // if they are not already in the 'closed list'.
        //
        for (auto& [name, cost] : *rn) {
                cout << "name: " << name << ", cost: " << cost << endl; // tbg
            if (!closed.contains(name)) {
                cout << "    put on open list: name: " << name << ", cost: " << cost << endl; // tbg
                open.push_back( {next_node.node_id, name, cost} );
            }
        }

    cout << endl; // tbg

        // Use a lambda expression to sort the 'open' list in desending order
        //
        sort (open.begin(), open.end(), [](traverse_info& a, traverse_info& b) {
            return a.total_cost > b.total_cost;
        });
    }

    if (closed.contains(end_node)) {
        cout << "Path found with cost: "s << closed.at(end_node).total_cost << endl;
        string node = end_node;
        cout << closed.at(node).node_id << " - "s << closed.at(node).total_cost << endl;
        while (closed.at(node).node_id != closed.at(node).from_node) {
            cout << closed.at(node).from_node << " - "s << closed.at(node).total_cost << endl;
            node = closed.at(node).from_node;
        }
    }
    else {
        cout << "No path found"s << endl;
    }

}
