#include <iostream>
#include <utility>
#include <vector>
#include <fstream>

using namespace std;
  
// Creating shortcut for an integer pair
typedef pair<int, int> iPair;

bool find_pair(vector<pair<int, int>> v, int a, int b)
{
    for(auto it = v.begin(); it!=v.end(); it++ )
    {
        if( (it->first == a && it->second == b) || (it->first == b && it->second == a))
            return true;
    }
        
    return false;
};
  
// Structure to represent a graph
struct Graph
{
    int V, E;
    vector< pair<int, iPair> > edges;
  
    // Constructor
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }
  
    // Utility function to add an edge
    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
        E ++;
    }
  
    // Function to find MST using Kruskal's
    // MST algorithm
    vector<int> SpacingKClusterings(int k);
};
  
// To represent Disjoint Sets
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
  
            //every element is parent of itself
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
        x = find(x);
        y = find(y);
  
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
  
vector<int> Graph::SpacingKClusterings(int k)
{
    int number_of_cluster = V;
  
    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());
  
    // Create disjoint sets
    DisjointSets ds(V);
    vector<int> min_spacings;
    vector<pair<int, int>> clusters;
  
    // Iterate through all sorted edges
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        if (number_of_cluster > k) // Make k-clustering
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
                // Merge two sets
                ds.merge(set_u, set_v);
                number_of_cluster --;
            }
        }
        else // Find spacing
        {
            
            int u = it->second.first;
            int v = it->second.second;
      
            int set_u = ds.find(u);
            int set_v = ds.find(v);
      
            // Check if the selected edge is from same cluster
            // Check if two cluster handling before
            if (set_u != set_v and find_pair(clusters, set_u, set_v) == false)
            {
                clusters.push_back({set_u, set_v});
                min_spacings.push_back(it->first);
            }
        }

    }
  
    return min_spacings;
}
  
int main()
{

    ifstream myfile;
    myfile.open("1.txt");
    int n;
    
    if ( myfile.is_open() )
    {
        myfile >> n;
        int V = n, E = 0;
        Graph g(V, E);
        while ( myfile )
        {
            int u, v, w;
            myfile >> u;
            myfile >> v;
            myfile >> w;
            g.addEdge(u, v, w);
        }
        
        vector<int> mst_wt = g.SpacingKClusterings(4);
        int max_spacing = -1;
        for (auto it=mst_wt.begin(); it!=mst_wt.end(); it++)
            max_spacing = max(max_spacing, *it);
        
        cout << max_spacing << endl;
        
    }
  
    return 0;
}


