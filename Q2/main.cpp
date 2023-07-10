#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <cmath>
#include <stdlib.h>

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

int hamming_distance32(unsigned int x, unsigned int y)
{
    return __builtin_popcount(x ^ y);
}
  
// Structure to represent a graph
struct Graph
{
    int V, E;
    unsigned int* vertex;
    vector< pair<int, iPair> > edges;
  
    // Constructor
    Graph(int V)
    {
        this->V = V;
        vertex = new unsigned int[V];
        this->E = 0;
    }
    
    void addVertex(unsigned int u, int i)
    {
        
        vertex[i] = u;
    }
  
    // Utility function to add an edge
    void addEdge()
    {
        for (int i=0; i<V; i++)
        {
            for(int j=i+1; j<V; j++)
            {
                if (hamming_distance32(vertex[i], vertex[j]) <= 2)
                {
    //                cout << it->first << " " << u << endl;
                    edges.push_back({1, {i, j}});
                    
                }
            }
            cout << i << endl;
        }
        
        E ++;
    }
  
    // Function to find MST using Kruskal's
    // MST algorithm
    int MST();
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
  
int Graph::MST()
{
    int number_of_cluster = V;
  
    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());
  
    // Create disjoint sets
    DisjointSets ds(V);
  
    // Iterate through all sorted edges
    vector< pair<int, iPair> >::iterator it;
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
                // Merge two sets
                ds.merge(set_u, set_v);
                number_of_cluster --;
        }

    }
  
    return number_of_cluster;
}
  
int main()
{
    unsigned int* input;

    ifstream myfile;
    myfile.open("2.txt");
    int n;
    int l;

    if ( myfile.is_open() )
    {
        myfile >> n;
        myfile >> l;
        input = new unsigned int[n];
        Graph g(n);
        int c = 0;
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<l; j++)
            {
                int a;
                myfile >> a;
                
                input[i] += a*pow(2, (l-j-1));
            }
            
            g.addVertex(input[i], i);
        }
        
        g.addEdge();
        int k = g.MST();
        cout << k << endl;
        
    }

  
    return 0;
}
