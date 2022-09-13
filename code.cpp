// Author - Rahul Roy
// This file provides definitions and usage to graph theory algorithms.

#include <bits/stdc++.h>
using namespace std;

#define mod 1000000007
#define ll long long int
#define MAX_NODE 20
#define MAX_NO_OF_VERTICES 10

vector<vector<int>> adjacencyList(101);
set<int> vertices;
set<pair<int, int>> edges;
vector<int> visited;

// generate a random Graph
void generateRandomGraph()
{
    int v = (rand() % (MAX_NO_OF_VERTICES - 1 + 1)) + 1;
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

// nullify visited array
void nullifyVisitedArray()
{
    visited.resize(MAX_NODE + 1, 0);
    return;
}

// Function to carry out depth-first-search in the graph
void traverseDFS(int node, bool isPrint)
{
    visited[node] = 1;
    if (isPrint)
        cout << node << " ";
    for (int i = 0; i < adjacencyList[node].size(); i++)
    {
        if (visited[adjacencyList[node][i]] == 0)
        {
            traverseDFS(adjacencyList[node][i], isPrint);
        }
    }
    return;
}

// Depth-First-Search
void DFS(){
    for(auto it : vertices){
        if(visited[it]==0){
            traverseDFS(it, true);
        }
    }
}

// Function that finds and returns the number of connected components in the graph
int findNumberOfConnectedComponents()
{
    int count=0;
    for(auto it : vertices){
        if(visited[it]==0){
            traverseDFS(it, false);
            count++;
        }
    }
    return count;
}

// Function to determine if a graph is connected
bool isConnected(){
    return true ? findNumberOfConnectedComponents() == 1 : false;
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    srand(time(0));

    generateRandomGraph(); // generate random set of vertices and edges
    nullifyVisitedArray(); // nullify the visited array (no vertex is visited)

    // print the graph
    cout << "The graph looks as :\n";
    cout<<"The set of vertices are : \n";
    for(auto it : vertices){
        cout<<it<<"\n";
    }
    cout<<"The set of edges are: \n";
    for (auto it : vertices)
    {
        for (int i = 0; i < adjacencyList[it].size(); i++)
        {
            cout << it << " --> " << adjacencyList[it][i] << "\n";
        }
    }

    auto sourcePointer = vertices.begin();
    int source = *sourcePointer;

    // DFS();
    // cout<<"The number of connected components are "<< findNumberOfConnectedComponents();
    // if(isConnected())
    //     cout<<"The graph is connected";
    // else
    //     cout<<"The graph is not connected";
}