//////////////////////////////////////////////////////////
// Name 1:Sishi Cheng     
// Name 2:Leran Ma        
// Name 3:Ivy Chen        

#include <iostream>
#include <vector>
using namespace std;

int vertices;
int edges;
int source;
vector< vector<int> > dist;

void DP_shortest_path( const vector< vector<int> > reverse_list,
                       const vector< vector<int> > matrix, const int source )
{
    dist[0][source] = 0;
    for ( int k = 1; k <= vertices; k++ )
    {
        for ( int i = 0; i < vertices; ++i )
        {
            dist[k][i] = dist[k - 1][i];
            for ( int j = 0; j < reverse_list[i].size(); ++j )
            {
                if( dist[k][i] > dist[k-1][ reverse_list[i][j] ] + matrix[ reverse_list[i][j] ][i] )
                {
                    dist[k][i] = dist[k-1][ reverse_list[i][j] ] + matrix[ reverse_list[i][j] ][i];
                }
            }
        }
    }
}

int main()
{
    cin >> vertices;
    cin >> edges;
    cin >> source;
    source--;

    vector<int> temp( vertices, 5001 );
    vector< vector<int> > reverse_list( vertices );
    vector< vector<int> > matrix( vertices, temp );
    dist.resize( vertices + 1, temp );

    int temp1;
    int temp2;
    int temp3;
    for( int i = 0; i < edges; i++ )
    {
        cin >> temp1;
        cin >> temp2;
        cin >> temp3;
        reverse_list[temp2 - 1].push_back(temp1 - 1);
        matrix[temp1 - 1][temp2 - 1] = temp3;
    }

    DP_shortest_path( reverse_list, matrix, source );

    string hasNegCycle = "False";
    for ( int i = 0; i < vertices; i++ )
    {
        if ( dist[vertices][i] != dist[vertices - 1][i] )
        {
            hasNegCycle = "True";
            break;
        }
    }
    cout << hasNegCycle;
    return 0;
}
