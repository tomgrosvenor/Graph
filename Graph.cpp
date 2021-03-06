
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Graph.h"

using namespace std;


Graph::Graph ()
    :graph { new unordered_map <string, unordered_map<string, int>* > },
     nodes { new vector <string> },
     num_nodes { 0 }
{
}


Graph::Graph (const initializer_list <string>& lst)
    :graph { new unordered_map <string, unordered_map<string, int>* > },
     nodes { new vector <string> {lst} }
{
    // Add the nodes (lst) to this graph. Create and associate an
    // empty map for each node before inserting into the graph.
    //
    for (const auto& node : lst) {
        graph->insert (make_pair (node, new unordered_map<string, int>));
    }

    // Set how many nodes are in this graph.
    num_nodes = graph->size();
}


Graph::Graph (const Graph& copyGraph)
    :graph { new unordered_map <string, unordered_map<string, int>* > },
     nodes { new vector <string> { *(copyGraph.nodes) } },
     num_nodes { copyGraph.num_nodes }
{
    for (const auto& [node, edges] : *(copyGraph.graph)) {
        graph->insert (make_pair ( node, new unordered_map<string, int> { *edges } ));
    }
}


Graph::Graph (Graph&& moveGraph)
    :graph { moveGraph.graph },
     nodes { moveGraph.nodes },
     num_nodes { moveGraph.num_nodes }
{
    moveGraph.graph = new unordered_map <string, unordered_map<string, int>* >;
    moveGraph.nodes = new vector <string>;
    moveGraph.num_nodes = 0;
}


Graph& Graph::operator= (const Graph& copyGraph)
{
    // Before assigning the 'new' values (from copyGraph) to the member
    // variables, free the memory associated with the 'current' values.
    //
    for (auto& [node, edges] : *graph) {
        delete edges;
    }
    delete graph;
    delete nodes;

    // Assign the 'new' values from copyGraph to this Graph.
    //
    graph = new unordered_map <string, unordered_map<string, int>* >;
    nodes = new vector <string> { *(copyGraph.nodes) };
    num_nodes = copyGraph.num_nodes;

    for (const auto& [node, edges] : *(copyGraph.graph)) {
        graph->insert (make_pair ( node, new unordered_map<string, int> { *edges } ));
    }

    // Return this Graph.
    //
    return *this;
}


Graph& Graph::operator= (Graph&& moveGraph)
{
    // Before assigning the 'new' values (from moveGraph) to the member
    // variables, free the memory associated with the 'current' values.
    //
    for (auto& [node, edges] : *graph) {
        delete edges;
    }
    delete graph;
    delete nodes;

    // Assign the 'new' values from moveGraph to this Graph.
    //
    graph = moveGraph.graph;
    nodes = moveGraph.nodes;
    num_nodes = moveGraph.num_nodes;

    moveGraph.graph = new unordered_map <string, unordered_map<string, int>* >;
    moveGraph.nodes = new vector <string>;
    moveGraph.num_nodes = 0;

    // Return this Graph.
    //
    return *this;
}


Graph::~Graph ()
{
    // Free the memory associated with the vector.
    delete nodes;

    // Free the memory for each value (edges) associated with each key (node).
    for (auto& [node, edges] : *graph) {
        delete edges;
    }

    // Free the memory associated with this graph.
    delete graph;
}


// Set this Graph up with random edges (and weights for these edges).
// The number of edges that willl be added will be determined by the
// number of nodes this Graph has and the value of 'graph_density'.
//
void Graph::create_density (const double graph_density,
                            const int    max_weight)
{
    // Before creating the edges, make sure all edge containers are empty.
    //
    for (auto& [node, edges] : *graph) {
        if (!edges->empty()) {
            delete edges;
            edges = new unordered_map<string, int>;
        }
    }

    // Set 'num_edges' to the number of edges a Graph needs in order to have
    // a graph density of 'graph_density'. Initialize 'edge_cnt'. As edges
    // are added increment 'edge_cnt'.
    //
    const unsigned int num_edges = floorf(num_nodes * (num_nodes - 1) * graph_density);
    unsigned int       edge_cnt  = 0;

    // Seed random number generator.
    srand (time(0));

    // Add random edges (and weights) to the graph.
    //
    while (edge_cnt < num_edges) {

        // Set indexes to two randomly selected nodes.
        int from_idx = rand() % num_nodes,
              to_idx = rand() % num_nodes;

        // Check for loops.
        if (from_idx == to_idx) continue;

        // 'Get' the two nodes.
        string from_node = nodes->at(from_idx),
                 to_node = nodes->at(to_idx);

        // Check that the 'from_node' doesn't already
        // have an edge to the 'to_node.
        //
        if (graph->at(from_node)->contains(to_node)) continue;

        // Add the edge to the 'to_node' to the 'from_node'.
        // Give this edge a random weight.
        //
        graph->at(from_node)->insert (make_pair (to_node, rand() % max_weight + 1));
            
        edge_cnt++;
    }
}


// Return the number of nodes this Graph has.
//
unsigned int Graph::size() const
{
    return num_nodes;
}


// Indicate whether this Graph contain a given node.
//
bool Graph::contains (const string& node) const
{
    return graph->contains(node);
}


// Returns a string representation of this Graph.
//
string Graph::to_string() const
{
    string retStr = "";
    for (auto& [node, edges] : *graph) {
        retStr += "Node: " + node + " -> ";
        for (auto& [node, weight] : *edges) {
            retStr += node + " (" + std::to_string(weight) + ") -> ";
        }
        retStr.replace(retStr.size() - 4, 4, "\n");
    }
    return retStr;
}


// Given a node that's in this graph, return a pointer to a vector that contains all
// the nodes that are reachable from this given node along with the cost associated
// with traversal to a reachable node.
//
unique_ptr <vector <Graph::reachable_node> > Graph::get_reachable_nodes (const string& node) const
{
    unique_ptr <vector <Graph::reachable_node> > vec { new vector<Graph::reachable_node> };

    // If the node is in this graph, add all its reachable
    // nodes and the cost of traversal to that node.
    //
    if (graph->contains(node)) {
        for (auto& [to_node, cost] : *graph->at(node)) {
            vec->push_back( {to_node, cost} );
        }
    }

    // Return the pointer to the 'reachable' nodes.
    return vec;
}


// Overload the '<<' operator so it can be used with a Graph.
//
ostream& operator<< (ostream& os, const Graph& g)
{
    return os << g.to_string();
}

