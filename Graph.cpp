
#include <iostream>
#include <unordered_map>
#include <vector>

#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constants for Graph density (valid values: 0.0 - 1.0) and the
// maximum weight that can be associated with an edge (valid
// values: 1 - DEFAULT_MAX_WGT).
//
constexpr double DEFAULT_DENSITY { 0.20 };
constexpr int    DEFAULT_MAX_WGT { 10 };

class Graph {

    public:

        Graph ()
            :graph { new unordered_map <string, unordered_map<string, int>* > },
             node_names { new vector <string> }
        {
            // Set how many nodes are in this graph.
            num_nodes = graph->size();
        }

        Graph (const initializer_list <string>& lst)
            :graph { new unordered_map <string, unordered_map<string, int>* > },
             node_names { new vector <string> {lst} }
        {
            // Add the names in the 'lst' to this graph. The names in the 'lst'
            // become the names of the nodes in this graph. Create and associate
            // an empty map for each node before inserting into the graph.
            //
            for (const auto& node_name : lst) {
                graph->insert (make_pair (node_name, new unordered_map<string, int>));
            }

            // Set how many nodes are in this graph.
            num_nodes = graph->size();
        }

        ~Graph () {
            // Free the memory associated with the vector;
            delete node_names;

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
        void create_density (const double graph_density = DEFAULT_DENSITY,
                             const int    max_weight    = DEFAULT_MAX_WGT) {

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

                // Get the strings associated with the two nodes.
                string from_node = node_names->at(from_idx),
                         to_node = node_names->at(to_idx);

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
        unsigned int size() const {
            return num_nodes;
        }

        // Returns a string representation of this Graph.
        //
        string to_string() const {
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


    private:

        unordered_map <string, unordered_map<string, int>* >* graph;
        const vector<string>*                                 node_names;
        unsigned int                                          num_nodes;
};


// Overload the '<<' operator so it can be used with a Graph.
//
ostream& operator<< (ostream& os, const Graph& g) {
    return os << g.to_string();
}


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
    cout << "With default density:" << endl;
    cout << graph1 << endl;
    graph2.create_density();
    graph3.create_density();
    graph4.create_density();

    // Create a density of 35% for graph1.
    graph1.create_density(0.35);

    cout << "With density 0.35:" << endl;
    cout << graph1.to_string() << endl;

    cout << "With density 0.35 (using <<):" << endl;
    cout << graph1 << "okay" << 4 << "\n" << graph4 << endl;
}
