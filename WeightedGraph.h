#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include "Vertex.h"
using namespace std;

class WeightedGraph {
private:
    struct Edge {
        int dest;
        int weight;
    };

    vector<Vertex*> vertices;
    vector<vector<Edge>> adjList;
    int numVertices;

public:
    WeightedGraph(int size);

    void addVertex(Vertex* v);
    void addEdge(int src, int dest, int weight);

    void DFS(Vertex* start);
    void BFS(Vertex* start);

    bool findPath(int srcIndex, int dstIndex);

private:
    void DFSUtil(int v, vector<bool>& visited, int& cost);
    int getIndex(Vertex* v);
};

#endif
