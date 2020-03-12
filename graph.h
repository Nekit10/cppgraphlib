/**
 * This file is part of cppgraphlib.
 *
 *  cppgraphlib is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of
 *  the License, or (at your option) any later version.
 *
 *  cppgraphlib is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  and GNU Lesser General Public License along with cppgraphlib.  If not,
 *  see <https://www.gnu.org/licenses/>.
 */

#ifndef CPPGRAPHLIB_GRAPH_H
#define CPPGRAPHLIB_GRAPH_H

#include <vector>
#include <utility>
#include <optional>

namespace cgl {

    typedef std::vector< std::vector< std::pair<size_t, double> > > graph_t;
    typedef std::vector< std::vector< std::pair<size_t, int> > > intgraph_t;
    typedef std::vector< std::vector< size_t > > nwgraph_t;  // Not weighted graph

    class graph {

    public:

        graph();
        graph(const graph &g) = default;
        graph(const nwgraph_t &g);
        graph(const graph_t &g);
        graph(const intgraph_t &g);

        void set(const graph_t &g);
        void set(const intgraph_t &g);
        void set(const nwgraph_t &g);

        void connect(size_t a, size_t b);
        void connect(size_t a, size_t b, double w);
        void connect(size_t a, size_t b, int i);
        void connecto(size_t a, size_t b);
        void connecto(size_t a, size_t b, double w);
        void connecto(size_t a, size_t b, int i);
        void disconnect(size_t a, size_t b);  // Complexity: O(m)
        void addVertex();
        void addVertices(size_t n);
        void removeVertex(size_t n);  // Complexity: O(n*m)

        graph& operator=(const graph &g) = default;
        graph& operator=(const nwgraph_t &g);
        graph& operator=(const graph_t &g);
        graph& operator=(const intgraph_t &g);

        [[nodiscard]] size_t numberOfVertices() const;
        [[nodiscard]] size_t numberOfEdges() const;  // Complexity: O(n*m)

        [[nodiscard]] graph_t getGraph() const;
        [[nodiscard]] graph_t::value_type connectedWith(size_t n) const;

        [[nodiscard]] bool isConnected();  // Complexity: O(n + m)
        [[nodiscard]] bool isWeighted();  // Complexity: O(1)
        [[nodiscard]] bool isTree();  // Complexity: O(n + m)
        [[nodiscard]] bool isComplete();  // Complexity: O(n*m)
        [[nodiscard]] bool isNull();  // Complexity: O(1)
        [[nodiscard]] bool isEmpty();  // Complexity: O(n)
        [[nodiscard]] bool isDirected();  // Complexity: O(n*m^2)
        [[nodiscard]] bool hasLoops();  // Complexity: O(n + m)
        [[nodiscard]] bool isInteger();   // Complexity: O(1) ; Does it have double-typed weights of edges

    protected:

        graph_t graph;

        std::optional<size_t> edges;

        std::optional<bool> connected;
        bool weighted;
        std::optional<bool> tree;
        std::optional<bool> complete;
        std::optional<bool> directed;
        std::optional<bool> loops;
        bool null;
        std::optional<bool> empty;
        bool integer;

    };

    graph graphByAdjacencyMatrix(const std::vector< std::vector<double> >& m);
    graph emptyGraph(size_t n);

}

#endif //CPPGRAPHLIB_GRAPH_H
