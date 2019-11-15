
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

        void create_density (const double graph_density = DEFAULT_DENSITY,
                             const int    max_weight    = DEFAULT_MAX_WGT) {

            // Before creating the edges, make sure all edge containers are empty.
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

                    cout << "    Density of 1: " << num_nodes * (num_nodes - 1) << " edges - tbg" << endl;
                    cout << "    Density of " << graph_density << ": " << num_edges << " edges - tbg" << endl;

            // Add random edges (and weights) to the graph.
            while (edge_cnt < num_edges) {

                // Set indexes to randomly select two nodes.
                int from_idx = rand() % num_nodes,
                      to_idx = rand() % num_nodes;

                // Check for loops.
                if (from_idx == to_idx) continue;

                // Get the strings associated with the two nodes.
                string from_node = node_names->at(from_idx),
                         to_node = node_names->at(to_idx);

                // Check that the 'from_node' doesn't already
                // have an edge to 'to_node.
                //
                if (graph->at(from_node)->contains(to_node)) continue;

                        cout << " tbg - from: " << from_node << ", to: " << to_node << endl;

                graph->at(from_node)->insert (make_pair (to_node, rand() % max_weight + 1));
            
                edge_cnt++;
            }
        }

        unordered_map<string, int>* operator[] (const string& node) const {
            return (graph->contains(node)) ? graph->at(node) : nullptr;
        }

        string operator[] (const int& idx) const {
            try {
                return node_names->at(idx);
            }
            catch (out_of_range& err) {
                cerr << err.what() << endl;
                throw;
            }
        }

        unsigned int size() const {
            return num_nodes;
        }


    private:

        unordered_map <string, unordered_map<string, int>* >* graph;
        const vector<string>*                                 node_names;
        unsigned int                                          num_nodes;
};


int main() {

    Graph graph1 {"zero", "one", "two", "three", "ohmy", "four", "five", "six", "ohno", "seven", "eight", "nine"};
    Graph graph2 { };
    Graph graph3;
    Graph graph4 { "four" };

    unordered_map<string, int>* mval = graph1["ohmy"];

    if (mval != nullptr)
        cout << "In main: " << mval->size() << endl; // tbg

    cout << "graph1 size = " << graph1.size() << endl;
    cout << "graph2 size = " << graph2.size() << endl;
    cout << "graph3 size = " << graph3.size() << endl;
    cout << "graph4 size = " << graph4.size() << endl;

    cout << "The names of the nodes in graph1: ";
    for (int i = 0; i < graph1.size(); i++) {
        cout << graph1[i] << " ";
    }
    cout << endl;

    cout << "The names of the nodes in graph2: ";
    for (int i = 0; i < graph2.size(); i++) {
        cout << graph2[i] << " ";
    }
    cout << endl;

    cout << "The names of the nodes in graph3: ";
    for (int i = 0; i < graph3.size(); i++) {
        cout << graph3[i] << " ";
    }
    cout << endl;

    cout << "The names of the nodes in graph4: ";
    for (int i = 0; i < graph4.size(); i++) {
        cout << graph4[i] << " ";
    }
    cout << endl;

    // Seed random number generator.
    srand (time(0));

    // Five random numbers with values 0 to graph1.size() - 1.
    for (int i = 0; i < 5; i++) {
        int idx = (rand() % graph1.size());
        cout << "idx: " << idx << ", node name: " << graph1[idx] << endl;
    }

    // Create default density for each graph.
    graph1.create_density();
    cout << "    In main: " << mval->size() << endl; // tbg

    graph2.create_density();
    graph3.create_density();
    graph4.create_density();

    char answer = 'n';
    cout << "Do you want to create new edges for graph1? (y/n)" << endl;
    cin >> answer;

    if (answer == 'y') {
        graph1.create_density();
        mval = graph1["ohmy"];
        cout << "    In main: " << mval->size() << endl; // tbg
    }

    // Create a density of 35% for graph1.
    // graph1.create_density(0.35);

}
