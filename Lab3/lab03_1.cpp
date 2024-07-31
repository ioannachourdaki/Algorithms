#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/* Kruskal’s Minimum Spanning Tree used in this project is taken from: 
   https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/
*/

// Creating shortcut for an integer pair 
typedef pair<int, int> iPair; 

// Structure to represent a graph 
struct Graph{ 
	int V, E, K; 
	vector< pair<int, iPair> > edges; 

	// Constructor 
	Graph(int V, int E, int K){ 
		this->V = V; 
		this->E = E; 
        this->K = K;
	} 

	// Utility function to add an edge 
	void addEdge(int u, int v, int w){ 
		edges.push_back({w, {u, v}}); 
	} 

	int modifiedKruskalMST(); 
}; 

// To represent Disjoint Sets 
struct DisjointSets{ 
	int *parent, *rnk; 
	int n; 

	// Constructor. 
	DisjointSets(int n){ 
		this->n = n; 
		parent = new int[n+1]; 
		rnk = new int[n+1]; 

		for (int i = 0; i <= n; i++){ 
			rnk[i] = 0;  
			parent[i] = i; 
		} 
	} 

	int find(int u){ 
		if (u != parent[u]) 
			parent[u] = find(parent[u]); 
		return parent[u]; 
	} 

	// Union by rank 
	void merge(int x, int y){ 
		x = find(x), y = find(y); 

		if (rnk[x] > rnk[y]) 
			parent[y] = x; 
		else 
			parent[x] = y; 

		if (rnk[x] == rnk[y]) 
			rnk[y]++; 
	} 
}; 

bool compare(const pair<int, pair<int, int>>& a, const pair<int, pair<int, int>>& b){
    return a.first > b.first; 
}

/* Function that (1) caclulates the MST with Kruskal's algorithm with maximum weights (t values)
                 (2) returns the (K+1)-th value of MST as it is the smallest of the values remaining
                     to the MST if we delete the first K values
*/
int Graph::modifiedKruskalMST(){ 
    vector<int> weightsMST;

	// Sort edges in increasing order on basis of cost 
	sort(edges.begin(), edges.end(), compare); 

	// Create disjoint sets 
	DisjointSets ds(V); 

	// Iterate through all sorted edges 
	vector< pair<int, iPair> >::iterator it; 
	for (it=edges.begin(); it!=edges.end(); it++){ 
		int u = it->second.first; 
		int v = it->second.second; 

		int set_u = ds.find(u); 
		int set_v = ds.find(v); 

		if (set_u != set_v){ 
            weightsMST.push_back(it->first);
			ds.merge(set_u, set_v); 
		} 
	}

    // Sort vector values and take the K-th element if 
    // it exists
    sort(weightsMST.begin(), weightsMST.end());

    if (K < weightsMST.size()) {
        return weightsMST[K];
    }

    return -1;
} 

// Driver program to test above functions 
int main(){ 
	int N, M, K, u, v, t;
	
  cin >> N >> M >> K;
	Graph g(N, M, K); 

	for(int i = 0; i < M; i++){
        cin >> u >> v >> t;
        g.addEdge(u,v,t); 
    }

    int result = g.modifiedKruskalMST();
    if(result == -1){
        cout << "infinity" << endl;
    }
    else {
        cout << result << endl;
    }
    
	return 0; 
} 
