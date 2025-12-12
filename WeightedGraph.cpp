#include "WeightedGraph.h"
#include <iostream>
#include <stack>
#include <algorithm>

WeightedGraph::WeightedGraph(int size) {
    numVertices = 0;
    adjList.resize(size);
}

void WeightedGraph::addVertex(Vertex* v) {
    vertices.push_back(v);
    numVertices++;
}

void WeightedGraph::addEdge(int src, int dest, int weight) {
    adjList[src].push_back({dest, weight});
}

int WeightedGraph::getIndex(Vertex* v) {
    for (int i = 0; i < vertices.size(); i++)
        if (vertices[i] == v)
            return i;
    return -1;
}

void WeightedGraph::DFSUtil(int v, vector<bool>& visited, int& cost) {
    visited[v] = true;
    cout << vertices[v]->getName() << " ";

    for (auto& edge : adjList[v]) {
        if (!visited[edge.dest]) {
            cost += edge.weight;
            DFSUtil(edge.dest, visited, cost);
        }
    }
}

void WeightedGraph::DFS(Vertex* start) {
    int startIndex = getIndex(start);
    vector<bool> visited(numVertices, false);
    int cost = 0;

    cout << "DFS order: ";
    DFSUtil(startIndex, visited, cost);
    cout << endl << "Total cost = " << cost << endl;
}

void WeightedGraph::BFS(Vertex* start) {
    int startIndex = getIndex(start);

    vector<bool> visited(numVertices, false);
    vector<int> cost(numVertices, 0);

    queue<int> q;
    visited[startIndex] = true;
    q.push(startIndex);

    cout << "BFS order: ";

    while (!q.empty()) {
        int v = q.front(); 
        q.pop();

        cout << vertices[v]->getName() << " ";

        for (auto& edge : adjList[v]) {
            if (!visited[edge.dest]) {
                visited[edge.dest] = true;
                cost[edge.dest] = cost[v] + edge.weight;
                q.push(edge.dest);
            }
        }
    }

    cout << endl;

    cout << "BFS accumulated costs:" << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << vertices[i]->getName() 
             << " cost = " << cost[i] << endl;
    }
}

bool WeightedGraph::findPath(int srcIndex, int dstIndex) {
    vector<bool> visited(numVertices, false);
    vector<int> parent(numVertices, -1);
    vector<int> cost(numVertices, 0);

    queue<int> q;
    q.push(srcIndex);
    visited[srcIndex] = true;

    while (!q.empty()) {
        int v = q.front(); 
        q.pop();

        if (v == dstIndex)
            break;

        for (auto& edge : adjList[v]) {
            int w = edge.dest;
            int wCost = edge.weight;

            if (!visited[w]) {
                visited[w] = true;
                parent[w] = v;
                cost[w] = cost[v] + wCost;
                q.push(w);
            }
        }
    }

    if (!visited[dstIndex]) {
        cout << "No path from "
             << vertices[srcIndex]->getName()
             << " to "
             << vertices[dstIndex]->getName()
             << "." << endl;
        return false;
    }

    // Reconstruct path
    vector<int> path;
    for (int v = dstIndex; v != -1; v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    cout << "Path from "
         << vertices[srcIndex]->getName()
         << " to "
         << vertices[dstIndex]->getName()
         << ": ";

    for (int i = 0; i < path.size(); i++) {
        cout << vertices[path[i]]->getName();
        if (i != path.size() - 1) cout << " -> ";
    }

    cout << "   Cost = " << cost[dstIndex] << endl;

    return true;
}
