#include <iostream>
#include <vector>
using namespace std;

vector< int > dist;
class priorityQueue
{
private:
    int* key;
    int* location;
    int* label;
    int numItems;

    void bubble_up( int k )
    {
        int p = ( k - 1 ) / 2;
        if (p < 0) return;

        if (key[p] > key[k])
        {
            int temp = key[p];
            key[p] = key[k];
            key[k] = temp;

            int temp2 = label[p];
            label[p] = label[k];
            label[k] = temp2;

            location[label[p]] = p;
            location[label[k]] = k;

            bubble_up(p);
        }
    }

    void shift_down( int k )
    {
        int left_child = 2 * k + 1;
        int right_child = 2 * k + 2;
        int min_child;
        if (left_child >= numItems && right_child >= numItems )
        {
            return;
        }
        else if (right_child >= numItems)
        {
            min_child = left_child;
        }
        else if ( key[left_child] < key[right_child] )
        {
            min_child = left_child;
        }
        else min_child = right_child;

        if ( key[k] > key[min_child] )
        {
            int temp = key[k];
            key[k] = key[min_child];
            key[min_child] = temp;

            int temp2 = label[min_child];
            label[min_child] = label[k];
            label[k] = temp2;

            location[label[min_child]] = min_child;
            location[label[k]] = k;

            shift_down(min_child);
        }
    }

public:
    priorityQueue( int s )
    {
        key = new int[s];
        location = new int[s];
        label = new int[s];

        for (int i = 0; i < s; ++i)
        {
            key[i] = 5001;
        }

        for (int i = 0; i < s; ++i)
        {
            location[i] = i;
            label[i] = i;
        }
        numItems = 0;
    }

    ~priorityQueue()
    {
        delete [] key;
        delete [] label;
        delete [] location;
    }

    bool empty() const
    {
        if (numItems == 0) return true;
        else return false;
    }

    void insert( int x )
    {
        numItems++;
        key[numItems - 1] = x;
        bubble_up(numItems-1);
    }

    int find_min()
    {
        return label[0];
    }

    void delete_min()
    {
        key[0] = key[numItems - 1];
        label[0] = label[numItems - 1];

        int temp = key[0];
        key[0] = key[numItems - 1];
        key[numItems - 1] = temp;

        int temp2 = label[0];
        label[0] = label[numItems - 1];
        label[numItems - 1] = temp2;

        location[label[0]] = 0;
        location[label[numItems - 1]] = numItems - 1;

        numItems--;
        shift_down(0);
    }

    void decrease_key(int k, int new_key)
    {
        key[location[k]] = new_key;
        bubble_up(location[k]);
    }
};

void Dijkstra( vector< vector<int> > graph, vector< vector<int> > length, int s )
{
    dist.insert(dist.begin(), graph.size(), 5001);
    priorityQueue PQ( graph.size() );
    for (int i = 0; i < graph.size(); ++i)
    {
        PQ.insert(5001);
    }

    dist[s] = 0;

    PQ.decrease_key(s, 0);
    int u;
    while ( !PQ.empty() )
    {
        u = PQ.find_min();

        PQ.delete_min();

        for (auto i : graph[u])
        {
            if (dist[i] > dist[u] + length[u][i])
            {
                dist[i] = dist[u] + length[u][i];
                PQ.decrease_key( i, dist[i] );
            }
        }
    }
}

int main()
{
    int vertices;
    int edges;
    int source;
    vector< vector<int> > list;

    cin >> vertices;
    for( int i = 0; i < vertices; i++ )
    {
        vector< int > temp;
        list.push_back( temp );
    }

    cin >> edges;
    cin >> source;

    vector<int> temp(vertices, 5001);
    vector< vector<int> > matrix(vertices, temp);
    for( int i = 0; i < edges; i++ )
    {
        int temp1;
        int temp2;
        int temp3;
        cin >> temp1;
        cin >> temp2;
        cin >> temp3;
        list[temp1 - 1].push_back(temp2 - 1);
        matrix[temp1 - 1][temp2 - 1] = temp3;
    }

    Dijkstra( list, matrix, source-1 );

    for (int & i : dist)
    {
        if (i == 5001)
        {
            i = -1;
        }
        cout << i << endl;
    }
}
