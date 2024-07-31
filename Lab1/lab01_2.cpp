#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;  

typedef pair<int, int> iPair; 

// Structure to represent a graph 
struct Graph 
{ 
    int V, E; 
    vector< pair<iPair, iPair> > edges; 
    int sum_p, sum_w;

    // Constructor 
    Graph(int V, int E) 
    {   
        this->V = V; 
        this->E = E; 
    } 

    // Utility function to add an edge 
    void addEdge(int u, int v, int p, int w) 
    {   
        edges.push_back({{p, w}, {u, v}}); 
    } 
  
    // Function to find MST using Kruskal's 
    // MST algorithm 
    double kruskalMST(double c); 
}; 
  
struct DisjointSets 
{ 
    int *parent, *rnk; 
    int n; 
  
    // Constructor. 
    DisjointSets(int n) 
    { 
        // Allocate memory 
        this->n = n; 
        parent = new int[n+1]; 
        rnk = new int[n+1]; 
  
        // Initially, all vertices are in 
        // different sets and have rank 0. 
        for (int i = 0; i <= n; i++) 
        { 
            rnk[i] = 0; 
            parent[i] = i; 
        } 
    } 
  
    // Find the parent of a node 'u' 
    // Path Compression 
    int find(int u) 
    { 
        /* Make the parent of the nodes in the path 
        from u--> parent[u] point to parent[u] */
        if (u != parent[u]) 
            parent[u] = find(parent[u]); 
        return parent[u]; 
    } 
  
    // Union by rank 
    void merge(int x, int y) 
    { 
        x = find(x), y = find(y); 
  
        /* Make tree with smaller height 
        a subtree of the other tree */
        if (rnk[x] > rnk[y]) 
            parent[y] = x; 
        else // If rnk[x] <= rnk[y] 
            parent[x] = y; 
  
        if (rnk[x] == rnk[y]) 
            rnk[y]++; 
    } 
}; 

double Graph::kruskalMST(double c) 
{ 
    double mst_wt = 0; // Initialize result 
    sum_p = 0, sum_w = 0; // Initialize result-sums
  
    // Sort edges in increasing order by: (w - c*p)
    sort(edges.begin(), edges.end(), [c](const pair<iPair, iPair> &e1, const pair<iPair, iPair> &e2) {
        return (e1.first.second - c * e1.first.first) < (e2.first.second - c * e2.first.first);
    });
    
    // Create disjoint sets 
    DisjointSets ds(V); 
  
    // Iterate through all sorted edges 
    vector< pair<iPair, iPair> >::iterator it; 
    for (it=edges.begin(); it!=edges.end(); it++) 
    { 
        int u = it->second.first; 
        int v = it->second.second; 
  
        int set_u = ds.find(u); 
        int set_v = ds.find(v); 
  
        // Check if the selected edge is creating 
        // a cycle or not (Cycle is created if u 
        // and v belong to same set)         
        if (set_u != set_v) 
        { 
            // Update MST weight 
            mst_wt += it->first.second - c * it->first.first; 
  
            // Merge two sets 
            ds.merge(set_u, set_v); 

            // Add current p,w to sums
            sum_p += it->first.first;
            sum_w += it->first.second;
        } 
    } 
  
    return mst_wt; 
}

void BinarySearch(Graph &g, int max_p, int max_w){
    // double low = 0, high = 10.01, e = 1.92*1e-5;
    double low = 0, high = 1.0*max_p/max_w, e = 1e-5;

    while(low <= high){
        double mid = (low + high) / 2.0;
        double mst_wt = g.kruskalMST(mid);

        if(mst_wt == 0) break;
        if(mst_wt > 0) low = mid + e; 
        else high = mid - e;
    }
}

int main(){

    int N, M, u, v, p, w;

        cin >> N >> M;

        Graph g(N,M);
        int max_p = 0, max_w = 0;

        for(int i = 0; i<M; i++){
            cin >> u >> v >> p >> w;
            max_p = max(p, max_p);
            max_w = max(w, max_p);
            g.addEdge(u, v, p, w);
        }
        
        BinarySearch(g, max_p, max_w);

        int res1 = g.sum_p / __gcd(g.sum_p, g.sum_w);
        int res2 = g.sum_w / __gcd(g.sum_p, g.sum_w);

        cout << res1 << " " << res2 << endl;

    return 0;
}
