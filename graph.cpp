#include <iostream>
#include <vector>

using namespace std;

class Vertex {
public:
    int id;

    Vertex(int _id) : id(_id) {}
};

class Edge {
public:
    Vertex* startVertex;
    Vertex* endVertex;

    Edge(Vertex* start, Vertex* end) : startVertex(start), endVertex(end) {}
};

class Graph {
private:
    vector<Vertex*> vertices;
    vector<Edge*> edges;

public:
    void addVertex(int id) {
        Vertex* newVertex = new Vertex(id);
        vertices.push_back(newVertex);
    }

    void addEdge(int startId, int endId) {
        Vertex* startVertex = nullptr;
        Vertex* endVertex = nullptr;

        for (Vertex* v : vertices) {
            if (v->id == startId)
                startVertex = v;
            if (v->id == endId)
                endVertex = v;
        }

        if (startVertex == nullptr || endVertex == nullptr) {
            cout << "Error: Vertices not found." << endl;
            return;
        }

        Edge* newEdge = new Edge(startVertex, endVertex);
        edges.push_back(newEdge);
    }

    void removeVertex(int id) {
        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i]->id == id) {
                vertices.erase(vertices.begin() + i);
                break;
            }
        }

        for (int i = edges.size() - 1; i >= 0; --i) {
            if (edges[i]->startVertex->id == id || edges[i]->endVertex->id == id) {
                delete edges[i];
                edges.erase(edges.begin() + i);
            }
        }
    }

    void removeEdge(int startId, int endId) {
        for (int i = 0; i < edges.size(); ++i) {
            if ((edges[i]->startVertex->id == startId && edges[i]->endVertex->id == endId) ||
                (edges[i]->startVertex->id == endId && edges[i]->endVertex->id == startId)) {
                delete edges[i];
                edges.erase(edges.begin() + i);
                break;
            }
        }
    }

    int countVertices() {
        return vertices.size();
    }

    int countEdges() {
        return edges.size();
    }

    ~Graph() {
        for (Vertex* v : vertices)
            delete v;
        for (Edge* e : edges)
            delete e;
    }
};

int main() {
    Graph g;

    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);

    g.addEdge(1, 2);
    g.addEdge(2, 3);

    cout << "Number of vertices: " << g.countVertices() << endl;
    cout << "Number of edges: " << g.countEdges() << endl;

    g.removeEdge(1, 2);
    g.removeVertex(2);

    cout << "Number of vertices after removal: " << g.countVertices() << endl;
    cout << "Number of edges after removal: " << g.countEdges() << endl;

    return 0;
}
