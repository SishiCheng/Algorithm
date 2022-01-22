//////////////////////////////////////////////////////////
// Name 1:Sishi Cheng     
// Name 2:Leran Ma       
// Name 3:Ivy Chen        

#include <iostream>
#include <vector>
using namespace std;

int verticeNum, edgeNum, flowValue;

void explore( const vector< vector<int> > &list, vector<int> &visit, vector<int> &pre, int v )
{
    visit[v] = 1;
    for ( int i = 0; i < list[v].size(); ++i )
    {
        if ( visit[ list[v][i] ] == 0 )
        {
            pre[ list[v][i] ] = v;
            if ( list[v][i] == verticeNum - 1 )
            {
                visit[verticeNum - 1] = 1;
                return;
            }
            else
                explore( list, visit, pre, list[v][i] );
        }
    }
}

void Ford_Fulkson( const vector< vector<int> > &list,
                   const vector< vector<int> > &matrix,
                   vector< vector<int> > &flow )
{
    flowValue = 0;
    while ( true )
    {
        vector< vector<int> > list_residual(verticeNum);
        vector< vector<int> > matrix_residual(matrix);
        for (int i = 0; i < verticeNum; ++i)
        {
            for (int j = 0; j < list[i].size(); ++j)
            {
                matrix_residual[i][ list[i][j] ] -= flow[i][ list[i][j] ];
                if ( matrix_residual[i][ list[i][j] ] != 0 )
                    list_residual[i].push_back( list[i][j] );

                matrix_residual[ list[i][j] ][i] += flow[i][ list[i][j] ];
                if ( matrix_residual[ list[i][j] ][i] != 0 )
                    list_residual[list[i][j]].push_back( i );
            }
        }

        //////////////////////////////////////////////////////////////////////

        vector<int> visit(verticeNum, 0);
        vector<int> pre(verticeNum, -1);
        explore( list_residual, visit, pre, 0 );

        if ( visit[verticeNum - 1] == 0 )
            return;

        ///////////////////////////////////////////////////////////////////////

        int current_vertex = verticeNum - 1;
        int smallest = 2147483647;
        while ( pre[current_vertex] != -1 )
        {
            if ( smallest > matrix_residual[ pre[current_vertex] ][current_vertex] )
                smallest = matrix_residual[ pre[current_vertex] ][current_vertex];

            current_vertex = pre[current_vertex];
        }

        /////////////////////////////////////////////////////////////////////////
        flowValue += smallest;
        current_vertex = verticeNum - 1;
        while ( pre[current_vertex] != -1 )
        {
            if ( matrix[current_vertex][ pre[current_vertex] ] != 0 )
                flow[ pre[current_vertex] ][current_vertex] -= smallest;
            else
                flow[ pre[current_vertex] ][current_vertex] += smallest;

            current_vertex = pre[current_vertex];
        }
    }
}

int main()
{
    cin >> verticeNum >> edgeNum;

    vector< vector<int> > list(verticeNum);
    vector<int> temp_vector(verticeNum, 0);
    vector< vector<int> > matrix(verticeNum, temp_vector);
    vector< vector<int> > flow(verticeNum, temp_vector);

    int temp_int1, temp_int2, temp_int3;
    for (int i = 0; i < edgeNum; ++i)
    {
        cin >> temp_int1 >> temp_int2 >> temp_int3;
        if ( matrix[temp_int1 - 1][temp_int2 - 1] == 0 )
            list[temp_int1 - 1].push_back( temp_int2 - 1 );
        matrix[temp_int1 - 1][temp_int2 - 1] += temp_int3;
    }

    Ford_Fulkson( list, matrix, flow );
    cout << flowValue;

    return 0;
}
