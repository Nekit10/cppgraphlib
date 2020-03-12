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

#include "graph.h"

#include <vector>
#include <utility>
#include <optional>
#include <algorithm>
#include <queue>
#include <stack>

cgl::graph::graph() {
    edges = 0;
    connected = true;
    weighted = false;
    tree = true;
    complete = true;
    directed = false;
    loops = false;
    null = true;
    empty = true;
    integer = true;
}

void cgl::graph::set(const cgl::graph_t &g) {
    graph = g;
    weighted = true;
    null = g.empty();
    integer = false;
}

void cgl::graph::set(const cgl::intgraph_t &g) {
    size_t n = g.size();
    for (int i = 0; i < n; ++i) {
        size_t con = g[i].size();
        for (int j = 0; j < con; ++j) {
            graph[i].emplace_back(g[i][j].first, (double) g[i][j].second);
        }
    }

    weighted = true;
    null = n == 0;
    integer = true;
}

void cgl::graph::set(const cgl::nwgraph_t &g) {
    size_t n = g.size();
    for (int i = 0; i < n; ++i) {
        size_t con = g[i].size();
        for (int j = 0; j < con; ++j) {
            graph[i].emplace_back(g[i][j], 1.0);
        }
    }

    weighted = false;
    null = n == 0;
    integer = true;
}

cgl::graph::graph(const cgl::nwgraph_t &g) {
    set(g);
}

cgl::graph::graph(const cgl::graph_t &g) {
    set(g);
}

cgl::graph::graph(const cgl::intgraph_t &g) {
    set(g);
}

cgl::graph &cgl::graph::operator=(const cgl::nwgraph_t &g) {
    set(g);
    return *this;
}

cgl::graph &cgl::graph::operator=(const cgl::graph_t &g) {
    set(g);
    return *this;
}

cgl::graph &cgl::graph::operator=(const cgl::intgraph_t &g) {
    set(g);
    return *this;
}

cgl::graph_t cgl::graph::getGraph() const {
    return graph;
}

std::vector<std::pair<size_t, double>> cgl::graph::connectedWith(size_t n) const {
    return graph[n];
}

size_t cgl::graph::numberOfVertices() const {
    return graph.size();
}

size_t cgl::graph::numberOfEdges() const {
    if (edges) {
        return *edges;
    } else {
        int c = 0;
        for (auto i = std::begin(graph); i != std::end(graph); ++i) {
            int ver = i - std::begin(graph);
            for (auto j = std::begin(*i); j != std::end(*i); ++j) {
                if (j->first >= ver)
                    c++;
            }
        }
        return c;
    }
}

bool cgl::graph::isWeighted() {
    return weighted;
}

bool cgl::graph::isNull() {
    return null;
}

bool cgl::graph::isInteger() {
    return integer;
}

void cgl::graph::connect(size_t a, size_t b) {
    graph[a].emplace_back(b, 1);
    graph[b].emplace_back(a, 1);
    if (connected && !*connected)
        connected = std::nullopt;
    if (tree && *tree)
        tree = false;
    else if (tree)
        tree = std::nullopt;
    complete = std::nullopt;
    null = false;
    empty = false;
}

void cgl::graph::connect(size_t a, size_t b, double w) {
    graph[a].emplace_back(b, w);
    graph[b].emplace_back(a, w);
    if (connected && !*connected)
        connected = std::nullopt;
    if (tree && *tree)
        tree = false;
    else if (tree)
        tree = std::nullopt;
    complete = std::nullopt;
    weighted = true;
    integer = false;
    null = false;
    empty = false;
}

void cgl::graph::connect(size_t a, size_t b, int i) {
    graph[a].emplace_back(b, i);
    graph[b].emplace_back(a, i);
    if (connected && !*connected)
        connected = std::nullopt;
    if (tree && *tree)
        tree = false;
    else if (tree)
        tree = std::nullopt;
    complete = std::nullopt;
    weighted = true;
    null = false;
    empty = false;
}

void cgl::graph::connecto(size_t a, size_t b) {
    graph[a].emplace_back(b, 1);
    if (connected && !*connected)
        connected = std::nullopt;
    if (tree && *tree)
        tree = false;
    else if (tree)
        tree = std::nullopt;
    complete = std::nullopt;
    directed = true;
    null = false;
    empty = false;
}

void cgl::graph::connecto(size_t a, size_t b, double w) {
    graph[a].emplace_back(b, w);
    if (connected && !*connected)
        connected = std::nullopt;
    if (tree && *tree)
        tree = false;
    else if (tree)
        tree = std::nullopt;
    complete = std::nullopt;
    weighted = true;
    integer = false;
    directed = true;
    null = false;
    empty = false;
}

void cgl::graph::connecto(size_t a, size_t b, int i) {
    graph[a].emplace_back(b, i);
    if (connected && !*connected)
        connected = std::nullopt;
    if (tree && *tree)
        tree = false;
    else if (tree)
        tree = std::nullopt;
    complete = std::nullopt;
    weighted = true;
    directed = true;
    null = false;
    empty = false;
}

void cgl::graph::disconnect(size_t a, size_t b) {
    auto i = std::find_if(std::begin(graph[a]), std::end(graph[a]), [b](auto p) -> bool {
        return p.first == b;
    });
    if (i != std::end(graph[a]))
        graph[a].erase(i);

    i = std::find_if(std::begin(graph[b]), std::end(graph[b]), [a](auto p) -> bool {
        return p.first == a;
    });
    if (i != std::end(graph[a]))
        graph[a].erase(i);


    if (connected && *connected)
        connected = std::nullopt;
    if (tree && *tree)
        tree = false;
    else if (tree)
        tree = std::nullopt;
    complete = false;
    if (a == b)
        loops = std::nullopt;
    empty = std::nullopt;
}

void cgl::graph::addVertex() {
    addVertices(1);
}

void cgl::graph::addVertices(size_t n) {
    size_t gsize = graph.size() + n;
    graph.resize(gsize);

    connected = (gsize == 1) || (gsize == 0);
    tree = (gsize == 1) || (gsize == 0);
    complete = (gsize == 1) || (gsize == 0);
    null = gsize == 0;
}

void cgl::graph::removeVertex(size_t n) {
    graph.erase(graph.begin() + n);
    for (auto i = std::begin(graph); i != std::end(graph); ++i) {
        for (auto j = std::begin(*i); j != std::end(*i); ++j) {
            if (j->first == n)
                i->erase(j--);
            else if (j->first > n)
                --j->first;
        }
    }

    if (connected && !*connected)
        connected = std::nullopt;
    if (tree && !*tree)
        tree = std::nullopt;
    if (complete && !*complete)
        complete = std::nullopt;
    null = graph.empty();
    if (empty && !*empty)
        empty = std::nullopt;
    if (loops && *loops)
        loops = std::nullopt;
}

bool cgl::graph::isTree() {
    if (tree) {
        return *tree;
    } else {
        tree = (numberOfEdges() == numberOfVertices() - 1) && isConnected();
        return *tree;
    }
}

bool cgl::graph::isComplete() {
    if (complete) {
        return *complete;
    } else {
        size_t n = numberOfVertices();
        for (auto verts : graph) {
            std::vector<bool> checked(n, false);
            size_t nc = n;
            for (auto vertex : verts) {
                if (!checked[vertex.first]) {
                    checked[vertex.first] = true;
                    nc--;
                }
            }

            if (nc != 0) {
                complete = false;
                return false;
            }
        }
        complete = true;
        return true;
    }
}

bool cgl::graph::isEmpty() {
    if (empty) {
        return *empty;
    } else {
        for (auto verts : graph) {
            if (!verts.empty()) {
                empty = false;
                return false;
            }
        }
        empty = true;
        return true;
    }
}

bool cgl::graph::isDirected() {
    if (directed) {
        return *directed;
    } else {
        for (auto i = std::begin(graph); i != std::end(graph); ++i) {
            for (auto vertex : *i) {
                size_t iv = i - std::begin(graph);
                auto pos = std::find_if(std::begin(graph[vertex.first]), std::end(graph[vertex.first]), [iv](const auto &a) -> bool {
                    return a.first == iv;
                });
                if (pos == std::end(graph[vertex.first])) {
                    directed = true;
                    return true;
                }
            }
        }
        directed = false;
        return false;
    }
}

bool cgl::graph::isConnected() {
    if (!connected) {
        size_t s = 0;
        size_t n = numberOfVertices();
        std::vector<bool> v(n, false);
        v[s] = true;
        size_t nv = n - 1;


        std::queue<int> verts;
        verts.push(s);
        while (!verts.emplace()) {
            size_t vertex = verts.front();
            verts.pop();

            for (auto &edge : graph[vertex]) {
                if (!v[edge.first]) {
                    nv--;
                    v[edge.first] = true;
                }
            }
        }
        connected = n == 0;
    }
    return *connected;
}

bool cgl::graph::hasLoops() {
    if (!loops) {
        size_t n = numberOfVertices();
        std::vector<bool> color(n, false);

        std::stack<int> stack;
        for (size_t i = 0; i < n; ++i) {
            if (!color[i]) {
                stack.push(i);
                while (!stack.empty()) {
                    size_t vertex = stack.top();
                    stack.pop();

                    color[vertex] = true;
                    for (auto &ov : graph[vertex]) {
                        if (color[ov.first]) {
                            loops = true;
                            return true;
                        } else {
                            for (auto it = std::rbegin(graph[vertex]); it != std::rend(graph[vertex]); ++it) {
                                stack.push(it->first);
                            }
                        }
                    }
                }
            }
        }
        loops = false;
    }
    return *loops;
}

cgl::graph cgl::graphByAdjacencyMatrix(const std::vector<std::vector<double>>& m) {
    cgl::graph_t graph;
    size_t n = m.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (m[i][j] != 0)
                graph[i].emplace_back(j, m[i][j]);
        }
    }
    return cgl::graph(graph);
}

cgl::graph cgl::emptyGraph(size_t n) {
    cgl::graph graph;
    graph.addVertices(n);
    return graph;
}
