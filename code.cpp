// Author - Rahul Roy
// This file provides definitions and usage to graph theory algorithms.

#include <bits/stdc++.h>
using namespace std;

#define mod 1000000007
#define ll long long int
#define MAX_NODE 20           // maximum value of a node
#define MAX_NO_OF_VERTICES 10 // maximum number of nodes

vector<vector<int>> adjacencyList(101); // adjacency list of the graph G
set<int> vertices;                      // set of vertices V(G)
set<pair<int, int>> edges;              // set of edges E(G)
vector<int> visited;                    // array to store if a node is visited or not (0 represents not visited while 1 represents visited)
vector<int> color;                      // array to store the color of every node in the graph
bool isBipartite;                       // to store if the graph is bipartite
int n_of_components;                    // to store the number of components in a single connected component of the graph
int no_of_edges_visited;                // to keep track of number of edges visited
int final_point;                        // to keep track of any point at any point of traversal
map<pair<int, int>, int> visited_edges; // map to store if an edge is visited or not
bool isEulerian = false;
int no_of_eulerian_paths = 0;
int number_of_vertices;
int number_of_edges;
vector<int> parent;
vector<int> rank_parent;

// generate a random Graph
void generateRandomGraph()
{
    int v = (rand() % (MAX_NO_OF_VERTICES - 2 + 1)) + 2;
    int e = (rand() % ((((v - 1) * (v - 2)) / 2) - 1 + 1)) + 1;
    for (int i = 0; i < v; i++)
    {
        int x = (rand() % (MAX_NODE - 1 + 1)) + 1;
        if (vertices.count(x) == 0)
            vertices.insert(x);
        else
            i--;
    }
    int count = 0;
    while (count < e)
    {
        int firstVertex = (rand() % (MAX_NODE - 1 + 1)) + 1;
        int secondVertex = (rand() % (MAX_NODE - 1 + 1)) + 1;
        if (firstVertex != secondVertex && vertices.count(firstVertex) != 0 && vertices.count(secondVertex) != 0 && edges.count({firstVertex, secondVertex}) == 0)
        {
            edges.insert({firstVertex, secondVertex});
            adjacencyList[firstVertex].push_back(secondVertex);
            count++;
        }
    }
    return;
}

// Function to read graph from file
void readGraphFromFile(vector<vector<int>> &adjacencyMatrix)
{
    ifstream file("input.txt");

    file >> number_of_vertices;
    file >> number_of_edges;
    cout << number_of_vertices << " " << number_of_edges << "\n";

    for (int i = 0; i < number_of_edges; i++)
    {
        int u, v, w;
        file >> u;
        file >> v;
        file >> w;
        cout << u << " " << v << " " << w << "\n";
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
        edges.insert({u, v});
        adjacencyMatrix[u][v] = w;
        adjacencyMatrix[v][u] = w;
        if (vertices.count(u) == 0)
            vertices.insert(u);
        if (vertices.count(v) == 0)
            vertices.insert(v);
    }
}

// nullify visited array
void nullifyVisitedArray()
{
    visited.resize(MAX_NODE + 1, 0);
    for (int i = 0; i < MAX_NODE + 1; i++)
    {
        visited[i] = 0;
    }
    return;
}

// nullify parent array
void nullifyParentArray()
{
    parent.resize(101, -1);
    rank_parent.resize(101, 0);
    for (int i = 0; i <= 100; i++)
    {
        parent[i] = -1;
        rank_parent[i] = i;
    }
    return;
}

// nullify color array
void nullifyColorArray()
{
    color.resize(MAX_NODE + 1, 0);
    for (int i = 0; i < MAX_NODE + 1; i++)
    {
        color[i] = 0;
    }
    return;
}

// nullify edges map
void nullifyEdgesMap()
{
    for (auto it : vertices)
    {
        for (auto jt : adjacencyList[it])
        {
            visited_edges[{it, jt}] = 0;
        }
    }
}

// Function to carry out depth-first-search in the graph
void traverseDFS(int node, bool isPrint)
{
    visited[node] = 1;
    n_of_components++;
    if (isPrint)
        cout << node << " ";
    for (int i = 0; i < adjacencyList[node].size(); i++)
    {
        if (visited[adjacencyList[node][i]] == 0)
            traverseDFS(adjacencyList[node][i], isPrint);
    }
    return;
}

// Depth-First-Search
void DFS()
{
    for (auto it : vertices)
    {
        if (visited[it] == 0)
        {
            traverseDFS(it, true);
        }
    }
}

// Function that finds and returns the number of connected components in the graph
int findNumberOfConnectedComponents()
{
    int count = 0;
    for (auto it : vertices)
    {
        if (visited[it] == 0)
        {
            traverseDFS(it, false);
            count++;
        }
    }
    return count;
}

// Function to determine if a graph is connected
bool isConnected()
{
    return true ? findNumberOfConnectedComponents() == 1 : false;
}

// Function to calculate the size of the largest component
int sizeOfLargestComponent()
{
    nullifyVisitedArray();
    int max_size = 0;
    for (auto it : vertices)
    {
        n_of_components = 0;
        if (visited[it] == 0)
        {
            traverseDFS(it, false);
            max_size = max(max_size, n_of_components);
        }
    }
    return max_size;
}

// Function to check if a graph is bipartite
void checkBipartite(int node)
{
    visited[node] = 1;
    for (int i = 0; i < adjacencyList[node].size(); i++)
    {
        if (visited[adjacencyList[node][1]] == 0)
        {
            color[adjacencyList[node][i]] = 1 ? color[node] == 0 : 1;
            checkBipartite(i);
        }
        else
        {
            int chosenColor = 0 ? color[node] == 1 : 1;
            if (color[adjacencyList[node][i]] ^ chosenColor == 1)
                isBipartite = false;
        }
    }
    return;
}

// Function to apply eulerian traversel
void eulerianTraversal(int start_node, int node)
{
    final_point = node;
    if (no_of_edges_visited == edges.size())
    {
        no_of_eulerian_paths++;
    }
    if (final_point == start_node && no_of_edges_visited == edges.size())
    {
        isEulerian = true;
    }
    for (auto it : adjacencyList[node])
    {
        if (visited_edges[{it, node}] == 0)
        {
            visited_edges[{it, node}] = 1;
            visited_edges[{node, it}] = 1;
            no_of_edges_visited++;

            eulerianTraversal(start_node, node);

            visited_edges[{it, node}] = 0;
            visited_edges[{node, it}] = 0;
            no_of_edges_visited--;
        }
    }
}

// Function to find the number of Euler paths
int getNumberOfEulerPaths()
{
    if (!isConnected())
    {
        return 0;
    }
    no_of_eulerian_paths = 0;
    for (auto it : vertices)
    {
        no_of_edges_visited = 0;
        eulerianTraversal(it, it);
    }
    return no_of_eulerian_paths;
}

bool checkIfEulerian()
{
    if (!isConnected())
    {
        return false;
    }
    for (auto it : vertices)
    {
        no_of_edges_visited = 0;
        eulerianTraversal(it, it);
    }
    return isEulerian;
}

vector<pair<int, pair<int, int>>> sort_edges(vector<vector<int>> &adjacencyMatrix)
{
    vector<pair<int, pair<int, int>>> ans;
    for (auto it : edges)
    {
        ans.push_back({adjacencyMatrix[it.first][it.second], {it.first, it.second}});
    }
    sort(ans.begin(), ans.end());
    return ans;
}

int Kruskal_MST(vector<vector<int>> &adjacencyMatrix)
{
    // if(!isConnected()){
    //     return -1;
    // }
    vector<pair<int, pair<int, int>>> res = sort_edges(adjacencyMatrix);
    int ans = 0;
    set<int> parsed_vertices;
    for (int i = 0; i < res.size(); i++)
    {
        if (vertices.size() == parsed_vertices.size())
            break;

        if (rank_parent[res[i].second.first] != rank_parent[res[i].second.second] || (rank_parent[res[i].second.first] == -1 && rank_parent[res[i].second.second] == -1))
        {
            parent[res[i].second.first] = res[i].second.second;
            rank_parent[res[i].second.first] = rank_parent[res[i].second.second];
            ans = ans + res[i].first;
            parsed_vertices.insert(res[i].second.first);
            parsed_vertices.insert(res[i].second.second);
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // srand(time(0));

    vector<vector<int>> adjacencyMatrix(101, vector<int>(101, -1));
    // reading graph from input file
    readGraphFromFile(adjacencyMatrix);
    // generate random set of vertices and edges
    // generateRandomGraph(); 
    nullifyVisitedArray(); // nullify the visited array (no vertex is visited)
    nullifyColorArray();   // nullify the color array (no vertex is colored)
    nullifyEdgesMap();     // nullify the edges map (no edge is visited)
    nullifyParentArray();
    no_of_edges_visited = 0;
    final_point = 0;

    // print the graph
    cout << "The graph looks as :\n";
    cout << "The set of vertices are : \n";
    for (auto it : vertices)
    {
        cout << it << "\n";
    }
    cout << "The set of edges are: \n";
    for (auto it : edges)
    {
        cout << it.first << " --> " << it.second << " with weight = " << adjacencyMatrix[it.first][it.second] << "\n";
    }

    auto sourcePointer = vertices.begin();
    int source = *sourcePointer;

    // For DFS Traversal
    // DFS();

    // To count the number of connected components
    // cout<<"The number of connected components are\n"<< findNumberOfConnectedComponents();

    // To check if the graph is connected
    // isConnected() ? cout<<"The graph is connected\n" : cout<<"The graph is disconnected\n";

    // To get the size of the largest connected component
    // cout << "The size of the largest component = " << sizeOfLargestComponent() << "\n";

    // To check if the graph is Bipartite
    // isBipartite = true;
    // for (auto it : vertices)
    // {
    //     if (visited[it] == 0)
    //         checkBipartite(it);
    // }
    // isBipartite ? cout<<"The graph is bipartite\n" : cout<<"The graph is not bipartite\n";

    // To find number of Euler paths
    cout << "The number of eularian paths = " << getNumberOfEulerPaths() << "\n";

    // To check if the graph is Eulerian
    isEulerian ? cout << "The graph is eulerian\n" : cout << "The graph is not eulerian\n";

    // MST using Kruskal's Algorithm
    cout << "The MST Cost using Kruskal is equal to  = " << Kruskal_MST(adjacencyMatrix) << "\n";
}