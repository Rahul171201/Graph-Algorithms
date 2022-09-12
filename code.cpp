// Author - Rahul Roy
// This file provides definitions and usage to graph theory algorithms.

#include <bits/stdc++.h>
using namespace std;

#define mod 1000000007
#define ll long long int

vector<vector<int>> adjacencyList(101);
set<int> vertices;
set<pair<int, int>> edges;

// generate a random Graph
void generateRandomGraph()
{
    int v = (rand() % (10 - 1 + 1)) + 1;
    int e = (rand() % ((v-1) - 1 + 1)) + 1;
    for (int i = 0; i < v; i++)
    {
        int x = (rand() % (20 - 1 + 1)) + 1;
        vertices.insert(x);
    }
    int count = 0;
    for (auto currentVertex : vertices)
    {
        if (count == e)
            break;
        for (auto newVertex : vertices)
        {
            if (count == e)
                break;
            if (newVertex != currentVertex && edges.count({newVertex, currentVertex})==0)
            {
                edges.insert({currentVertex, newVertex});
                adjacencyList[currentVertex].push_back(newVertex);
                count++;
            }
        }
    }
    return;
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    srand(time(0));

    generateRandomGraph();

    // print the graph
    cout<<"The graph looks as :\n";
    for(auto it : vertices){       
        for(int i=0;i<adjacencyList[it].size();i++){
            cout<<it<<" --> "<<adjacencyList[it][i]<<"\n";
        }
    }
}