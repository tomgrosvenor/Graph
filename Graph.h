
#include <unordered_map>
#include <vector>

using namespace std;

// Constants for Graph density (valid values: 0.0 - 1.0) and the
// maximum weight that can be associated with an edge (valid
// values: 1 - DEFAULT_MAX_WGT).
//
constexpr double DEFAULT_DENSITY { 0.20 };
constexpr int    DEFAULT_MAX_WGT { 10 };

class Graph {
    public:
        Graph ();
        Graph (const initializer_list <string>&);
        ~Graph ();
        void create_density (const double graph_density = DEFAULT_DENSITY,
                             const int    max_weight    = DEFAULT_MAX_WGT);
        unsigned int size() const;
        string to_string() const;
    private:
        unordered_map <string, unordered_map<string, int>* >* graph;
        const vector<string>*                                 node_names;
        unsigned int                                          num_nodes;
};

ostream& operator<< (ostream&, const Graph&);
