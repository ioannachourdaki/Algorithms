#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX_VALUE 9223372036854775807

typedef pair<int, int> iPair;

// Structure to represent a graph
struct Graph {
    int V;
    vector<pair<iPair, int>> edges;
    int *parent, *P, *S;
    bool *visited;
    long long *distance, *duration, *min_duration;

    // Constructor
    Graph(int V) {
        this->V = V;
        this->visited = new bool[V];
        this->distance = new long long[V];
        this->duration = new long long[V];
        this->min_duration = new long long[V];
        this->parent = new int[V];
        this->P = new int[V];
        this->S = new int[V];

        // Initializations
        for (int i = 0; i < V; ++i) this->visited[i] = false;
        distance[0] = 0;
        duration[0] = 0;
        min_duration[0] = 0;
        for (int i = 0; i < V; ++i) parent[i] = -1;
        P[0] = S[0] = 0;
    }

    // Utility function to add an edge
    void addEdge(int u, int v, int d) {
        edges.push_back({{u, v}, d});
    }

    void findRootDistance();
    void findTripDuration();
};

// Modified Breadth-First Function
void Graph::findRootDistance() {
    // Create a queue of {child, parent}
    queue<int> qu;

    // Push root node in the front of
    qu.push(0);
    visited[0] = true;

    while (!qu.empty()) {
        int p = qu.front();

        // Dequeue a vertex from queue
        qu.pop();

        // Get all adjacent vertices of the dequeued
        // vertex s. If any adjacent has not
        // been visited then enqueue it
        for (pair<iPair, int> edge : edges) {
            int u = edge.first.first;
            int v = edge.first.second;
            int d = edge.second;

            if (u == p && !visited[v]) {
                distance[v] = distance[u] + d;
                qu.push(v);
                visited[v] = true;
                parent[v] = u;
            } 
            else if (v == p && !visited[u]) {
                distance[u] = distance[v] + d;
                qu.push(u);
                visited[u] = true;
                parent[u] = v;
            }
        }
    }
}

void Graph::findTripDuration() {
    for (int i = 1; i < V; i++) {
        int current_parent = parent[i];
        long long alternative = MAX_VALUE;
        while (current_parent != 0 && current_parent != -1) {
            alternative = min(alternative, P[i] + S[i] * (distance[i] - distance[current_parent]) + min_duration[current_parent]);
            current_parent = parent[current_parent];
        }
        min_duration[i] = min(duration[i], alternative);
    }
}

int main() {
    int N, V1, V2, d;

    cin >> N;

    Graph g(N);

    for (int i = 0; i < N-1; i++) {
        cin >> V1 >> V2 >> d;
        g.addEdge(V1-1, V2-1, d);
    }

    // Calculate distance from root
    g.findRootDistance();

    for (int i = 1; i < N; i++) {
        cin >> g.P[i] >> g.S[i];
        // Calculate duration of trip (V-V1)
        g.duration[i] = g.P[i] + g.S[i] * g.distance[i];
    }

    // Calculate minimum trip duration
    g.findTripDuration();

    for (int i = 1; i < N-1; i++) {
        cout << g.min_duration[i] << " ";
    }
    cout << g.min_duration[N-1] << endl;

    return 0;
}
