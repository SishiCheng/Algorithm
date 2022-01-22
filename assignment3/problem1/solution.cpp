#include <iostream>
#include <vector>
using namespace std;

int vertices;
int edges;
vector< int > visited;
vector< int > postlist;
vector< int > magic_order;
int num_cc;

void explore( const vector< vector<int> >& graph, const int vertex )
{
    visited[vertex] = 1;
    for( int i : graph[vertex] )
    {
        if( visited[i] == 0)
        {
            explore( graph, i );
        }
    }
    postlist.push_back( vertex );
}

void DFS( const vector< vector<int> >& graph )
{
    num_cc = 0;
    auto it = visited.begin();
    visited.insert( it, vertices, 0 );
    for(int i : magic_order)
    {
        if( visited[ i ] == 0 )
        {
            num_cc++;
            explore( graph, i );
        }
    }
}

int main()
{
    vector< vector<int> > adjacency;
    vector< vector<int> > reverse_adjacency;
    cin >> vertices;
    for( int i = 0; i < vertices; i++ )
    {
        vector< int > temp;
        adjacency.push_back( temp );
        reverse_adjacency.push_back( temp );
    }

    cin >> edges;
    for( int i = 0; i < edges; i++ )
    {
        int temp1;
        int temp2;
        cin >> temp1;
        cin >> temp2;
        adjacency[ temp1 - 1 ].push_back( temp2 - 1 );
        reverse_adjacency[ temp2 - 1 ].push_back( temp1 - 1 );
    }

    for( int i = 0; i < vertices; i++ )
    {
        magic_order.push_back( i );
    }

    DFS( reverse_adjacency );

    for( int i = vertices - 1; i >= 0; i-- )
    {
        magic_order[vertices - 1 - i] = postlist[i];
    }

    visited.clear();
    DFS( adjacency );

    cout << num_cc;
}
