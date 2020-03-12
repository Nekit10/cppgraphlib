#define CATCH_CONFIG_MAIN

#include "include/catch.hpp"

#include "graph.h"

TEST_CASE( "Graph class empty constructor generates null graph", "[constructors]" ) {
    cgl::graph graph;
    REQUIRE(graph.getGraph().empty());
}

TEST_CASE( "Graph can be created", "[constructors]" ) {
    cgl::nwgraph_t g1 {{1, 2}, {0, 2}, {0, 1, 3}};
    cgl::graph_t g1r {
            {{1, 1}, {2, 1}},
            {{0, 1}, {2, 1}},
            {{0, 1}, {1, 1}, {3, 1}}
    };

    cgl::intgraph_t g2 {
            {{1, 1}, {2, 4}},
            {{0, 1}, {2, 7}},
            {{0, 4}, {1, 7}, {3, 9}}
    };
    cgl::graph_t g2r {
            {{1, 1}, {2, 4}},
            {{0, 1}, {2, 7}},
            {{0, 4}, {1, 7}, {3, 9}}
    };

    cgl::graph_t g3 {
            {{1, 1.2}, {2, 4.8}},
            {{0, 1.2}, {2, 7}},
            {{0, 4.8}, {1, 7}, {3, 9}}
    };
    cgl::graph graph1(g1);
    cgl::graph graph2(g2);
    cgl::graph graph3(g3);
    REQUIRE(graph1.getGraph() == g1r);
    REQUIRE(graph2.getGraph() == g2r);
    REQUIRE(graph3.getGraph() == g3);
}

TEST_CASE( "Graph copy constructor generates copy of graph and changing copy does not change original", "[constructors]" ) {
    cgl::graph_t g {
            {{1, 1.2}, {2, 4.8}},
            {{0, 1.2}, {2, 7}},
            {{0, 4.8}, {1, 7}, {3, 9}}
    };
    cgl::graph graph(g);

    cgl::graph graph2(graph);
    REQUIRE(graph2.getGraph() == g);

    graph2.addVertex();

    REQUIRE(graph.getGraph() == g);
}