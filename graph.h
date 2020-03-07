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

namespace cgl {

    typedef std::vector< std::vector< std::pair<size_t, double> > > graph_t;
    typedef std::vector< std::vector< std::pair<size_t, int> > > intgraph_t;
    typedef std::vector< std::vector< size_t > > ndgraph_t;  // Not weighted graph

    class Graph {

    public:

        Graph();
        Graph(const Graph &g);
        Graph(const ndgraph_t &g);
        Graph(const graph_t &g);
        Graph(const intgraph_t &g);

        void set(const graph_t &g);
        void set(const intgraph_t &g);
        void set(const ndgraph_t &g);

        void connect(size_t a, size_t b);
        void disconnect(size_t a, size_t b);
        void addVertex();
        void addVertices(size_t n);
        void removeVertex(size_t n);

        Graph& operator=(const Graph &g);
        Graph& operator=(const ndgraph_t &g);
        Graph& operator=(const graph_t &g);
        Graph& operator=(const intgraph_t &g);

        size_t numberOfVertices() const;
        size_t numberOfEdges() const;

        graph_t getGraph() const;
        graph_t::value_type connectedWith(size_t n);

        bool isConnected() const;
        bool isWeighted() const;
        bool isTree() const;
        bool isComplete() const;
        bool isNull() const;
        bool isEmpty() const;
        bool isDirected() const;
        bool hasLoops() const;

    protected:

        graph_t graph;

        bool connected;
        bool weighted;
        bool tree;
        bool complete;
        bool directed;
        bool loops;
        bool null;
        bool empty;

    };

    Graph graphByAdjacencyMatrix(std::vector< std::vector<int> > m);
    Graph emptyGraph(size_t n);

}

#endif //CPPGRAPHLIB_GRAPH_H
