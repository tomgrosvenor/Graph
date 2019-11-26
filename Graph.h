
#include <unordered_map>
#include <vector>
#include <memory>

using namespace std;

// Constants for Graph density (valid values: 0.0 - 1.0) and the
// maximum weight that can be associated with an edge (valid
// values: 1 - DEFAULT_MAX_WGT).
//
constexpr double DEFAULT_DENSITY { 0.20 };
constexpr int    DEFAULT_MAX_WGT { 10 };

// Information about a reachable node. There is a directed
// edge from a node to the node named in this structure. The
// 'cost' of traversing to this named node is 'cost_to_node'.
//
struct reachable_node {
    string  node_name;
    int     cost_to_node;
};

// A class that respresents a graph. This class contains a
// graph's nodes. A call to create_density() creates a random
// number of directed edges. Each edge has a random weight/cost
// associated with it.
//
class Graph {
    public:
        Graph ();
        explicit Graph (const initializer_list <string>&);
        Graph (const Graph&);
        Graph (Graph&&);
        Graph& operator= (const Graph&);
        Graph& operator= (Graph&&);
        ~Graph ();

        void create_density (const double graph_density = DEFAULT_DENSITY,
                             const int    max_weight    = DEFAULT_MAX_WGT);
        unsigned int size() const;
        string to_string() const;
        unique_ptr< vector<reachable_node> > get_reachable_nodes (const string&) const;
    private:
        unordered_map <string, unordered_map<string, int>* > *graph;
        const vector<string>                                 *node_names;
        unsigned int                                          num_nodes;
};

// Overload the output operatator for the Graph class.
//
ostream& operator<< (ostream&, const Graph&);
