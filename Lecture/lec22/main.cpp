#include "basicgraph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int get_followers(BasicGraph& graph, Vertex* node) { // without & the pointer has the zddress which not fits the copied struct
    Set<Vertex*> followersOfFollowers;
    for (Vertex* followerNode : graph.getNeighbors(node)) {
        for (Vertex* secondFollower
                    : graph.getNeighbors(followerNode)) {
                followersOfFollowers.add(secondFollower);
            }
    }
    return followersOfFollowers.size();
}

string coolest(const string& fname) {
    BasicGraph graph;
    ifstream input;
    input.open(fname);
    string line;
    while (getline(input, line)) {
        istringstream ipts(line.c_str());
        string start, end;
        ipts >> start >> end;
        graph.addVertex(start); graph.addVertex(end);
        // a follows b means b -> a
        graph.addEdge(graph.getVertex(end), graph.getVertex(start));
    }
    int max_neighbor = 0;
    string s;
    for (Vertex* node : graph.getVertexSet()) {
        if (get_followers(graph, node) >= max_neighbor) {
            max_neighbor = get_followers(graph, node);
            s = node->name;
        }
    }
    return s;
}