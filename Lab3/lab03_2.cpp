#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 0x3f3f3f3f

/* Dijkstra’s Shortest Path Algorithm using priority_queueused in this project is 
   taken from: 
   https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
*/

typedef pair<int,int> iPair;
typedef pair<iPair,iPair> iPairs;

// Structure to represent a graph 
struct Graph{ 
	int V, E;
	vector<iPairs>* edges; 

	// Constructor 
	Graph(int V, int E){ 
		this->V = V; 
		this->E = E; 
        this->edges = new vector<iPairs>[V+1];
	} 

	/* Add edges to the adjacency list representation:
	   Each edge is represented as a pair containing:
	    - The destination vertex and the weight of the edge
	    - A pair of starting and ending times indicating when the president will attend that edge
	*/
	void addEdge(int u, int v, int w){ 
		edges[u].push_back({{v,w},{}});
        edges[v].push_back({{u,w},{}});
	} 

    void addSchedule(int K, int* president){
        int startPresident = 0;
        for(int i=0; i < K-1; i++){
            for(iPairs& edge : edges[president[i]]){
                if(edge.first.first == president[i+1]){
                    // Add time (start, end) when the street is occupied
                    edge.second.first = startPresident;
                    edge.second.second = startPresident + edge.first.second;
                    break;
                }
            }
			// Update both vertices
            for(iPairs& edge : edges[president[i+1]]){
                if(edge.first.first == president[i]){
                    // Add time (start, end) when the street is occupied
                    edge.second.first = startPresident;
                    edge.second.second = startPresident + edge.first.second;
                    startPresident = edge.second.second;
                    break;
                }
            }
        }
    }

	int modifiedDijkstra(int start, int finish, int T){

        priority_queue<iPair, vector<iPair>, greater<iPair> > pq;
        vector<int> dist(V+1, INF);

        pq.push(make_pair(0, start));
        dist[start] = T;
    
        while (!pq.empty()) {

            int u = pq.top().second;
			int u_dist = pq.top().first;
            pq.pop();

			if(u_dist > dist[u]) continue;

            for(iPairs& edge : edges[u]) {
                int v = edge.first.first;
                int weight = edge.first.second;
                int startPresident = edge.second.first;
                int endPresident = edge.second.second;

                // Add president schedule restrictions by renewing the weight
                if(dist[u] >=  startPresident && dist[u] < endPresident){
                    weight += endPresident - dist[u];
                }
    
                if(dist[v] > dist[u] + weight){
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            } 
            if(u == finish) break;
        }
        return dist[finish] - T;
    }
}; 

int main(){ 
	int N, M, K, A, B, T, u, v, w;
	
    cin >> N >> M >> A >> B >> T >> K;

	Graph g(N,M); 
    int president[K];
    
    for(int i=0; i < K; i++){
        cin >> president[i];
    }

	for(int i = 0; i < M; i++){
        cin >> u >> v >> w;
        g.addEdge(u,v,w); 
    }

    g.addSchedule(K, president);

    cout << g.modifiedDijkstra(A,B,T) << endl;

    return 0;
}