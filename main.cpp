
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

    string cur_node, end_node;

    // tbg Graph dg { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p" };
    Graph dg { "a", "b", "c", "d", "e" };

    cout << "dg size = " << dg.size() << endl;

    // Create random edges & weights for 'dg'.
    //
    dg.create_density(0.5);

    // Print 'dg'.
    //
    cout << "With density of 50%: (dg)" << endl;
    cout << dg << endl;

    // Create an open & a closed 'list' for implementing
    //  Dijkstra's algorithm.
    //
    unordered_map <string, traverse_info> closed;
    vector <traverse_info>                open;

    // Ask the user to enter a start node.  Make sure the
    // user entered a node that's in the graph.
    //
    cout << "Please enter a starting node: "s;
    cin  >> cur_node;
    if (!dg.contains(cur_node)) {
        cout << "The start node entered is not in the graph: "s << cur_node << endl;
        return 1;
    }

    // Ask the user to enter an end node.  Make sure the
    // user entered a node that's in the graph.
    //
    cout << "Please enter an end node: "s;
    cin  >> end_node;
    if (!dg.contains(end_node)) {
        cout << "The end node entered is not in the graph: "s << end_node << endl;
        return 1;
    }

    // Add the cur_node (start node) to the 'closed' list.
    //
    closed.insert( {cur_node, {cur_node, cur_node, 0}} );

    // Loop through the nodes in this Graph to determine if there's
    // a path from the start node to the 'end_node'.
    //
    while (!closed.contains(end_node)) {

        // Get the nodes/costs reachable from the cur_node.
        //
        unique_ptr< vector<reachable_node> > rn = dg.get_reachable_nodes (cur_node);

        // Add nodes reachable from the cur_node to the 'open list' if
        // they are not already in the 'closed list'.
        //
        for (auto& [name, cost] : *rn) {
            if (!closed.contains(name)) {
                open.push_back( {cur_node, name, cost + closed.at(cur_node).total_cost} );
            }
        }

        // If there are no entries in the open list break out of the loop.
        //
        if (open.empty()) break;

        // Use a lambda expression to sort the 'open' list in desending order
        //
        sort (open.begin(), open.end(), [](traverse_info& a, traverse_info& b) {
            return a.total_cost > b.total_cost;
        });

        // Get the next node that has the smallest cost (the last entry
        // on the open list). Remove it from the open list and set
        // cur_node to this 'next' node.
        //
        traverse_info next_node = open.back();
        open.pop_back();
        cur_node = next_node.node_id,

        // Add the 'current' node to the closed list.
        //
        closed.insert( {cur_node, {next_node.from_node, cur_node, next_node.total_cost}} );
    }

    if (closed.contains(end_node)) {
        cout << "Path found with cost: "s << closed.at(end_node).total_cost << endl;
        string node = end_node;
        cout << closed.at(node).node_id << " - "s << closed.at(node).total_cost << endl;
        while (closed.at(node).node_id != closed.at(node).from_node) {
            // tbg cout << closed.at(node).from_node << " - "s << closed.at(node).total_cost << endl;
            string from_node = closed.at(node).from_node;
            cout << from_node << " - "s << closed.at(from_node).total_cost << endl;
            node = closed.at(node).from_node;
        }
    }
    else {
        cout << "No path found"s << endl;
    }
}
