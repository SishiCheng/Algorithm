//////////////////////////////////////////////////////////
// Name 1:Sishi Cheng     Access ID:smc6823
// Name 2:Leran Ma        Access ID:lkm5463
// Name 3:Ivy Chen        Access ID:ikc5058

#include <iostream>
using namespace std;

struct node
{
    int data;
    int height;
    node *parent;
};

void make_set( node *x )
{
    x->height = 1;
    x->parent = x;
}

node *find( node *x )
{
    if ( x->parent != x )
    {
        return find( x->parent );
    }
    else
    {
        return x;
    }
}

void unionSets( node *x, node *y )
{
    node *rx = find( x );
    node *ry = find( y );
    if ( rx == ry ) return;
    if ( rx->height < ry->height )
    {
        rx->parent = ry;
    }
    else if ( rx->height > ry->height )
    {
        ry->parent = rx;
    }
    else
    {
        rx->parent = ry;
        ry->height = ry->height + 1;
    }
}

struct edge
{
    int start;
    int end;
    int weight;
};

edge* merge_two_sorted_arrays( int size1, edge* arr1, int size2, edge* arr2 )
{
    edge* sorted = new edge[size1 + size2];

    int k1, k2;
    k1 = k2 = 0;

    for ( int i = 0; i < size1 + size2; i++ )
    {
        if ( arr1[k1].weight < arr2[k2].weight )
        {
            sorted[i] = arr1[k1];
            k1++;
            if ( k1 == size1 )
            {
                for ( int j = i + 1; j < size1 + size2; j++ )
                {
                    sorted[j] = arr2[k2];
                    k2++;
                }
                break;
            }
        }
        else
        {
            sorted[i] = arr2[k2];
            k2++;
            if ( k2 == size2 )
            {
                for ( int j = i + 1; j < size1 + size2; j++ )
                {
                    sorted[j] = arr1[k1];
                    k1++;
                }
                break;
            }
        }
    }

    if ( size1 > 1 )
    {
        delete[] arr1;
    }
    if ( size2 > 1 )
    {
        delete[] arr2;
    }
    return sorted;
}

edge* merge_sort( int size, edge* s )
{
    edge* s2;
    if ( size <= 1 )
    {
        return s;
    }
    else
    {
        s2 = s + ( size/2 );
        edge* sorted1 = merge_sort( size/2, s );
        edge* sorted2 = merge_sort( size - (size/2), s2 );
        edge* sorted = merge_two_sorted_arrays( size/2, sorted1, size - (size/2), sorted2 );
        return sorted;
    }
}

int main()
{
    int vertices;
    int edges;
    cin >> vertices;
    cin >> edges;

    edge E[edges];
    for (int i = 0; i < edges; ++i)
    {
        cin >> E[i].start;
        E[i].start--;
        cin >> E[i].end;
        E[i].end--;
        cin >> E[i].weight;
    }

    edge *E_sorted = merge_sort( edges, E );

    node V[vertices];
    for (int i = 0; i < vertices; ++i)
    {
        V[i].data = i;
        make_set( &V[i] );
    }

    int sum = 0;
    for (int i = 0; i < edges; ++i)
    {
        node *ru;
        node *rv;
        ru = find( &V[ E_sorted[i].start ] );
        rv = find( &V[ E_sorted[i].end ] );
        if ( ru != rv )
        {
            sum += E_sorted[i].weight;
            unionSets( ru, rv );
        }
    }
    cout << sum;

    delete [] E_sorted;
    return 0;
}
