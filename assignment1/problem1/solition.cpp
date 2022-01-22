#include <iostream>
#include <fstream>
using namespace std;

int* merge_two_sorted_arrays( int size1, int* arr1, int size2, int* arr2 )
{
    int* sorted = new int[size1 + size2];

    int k1, k2;
    k1 = k2 = 0;

    for ( int i = 0; i < size1 + size2; i++ )
    {
        if ( arr1[k1] < arr2[k2] )
        {
            sorted[i] = arr1[k1];
            k1++;
        }
        else
        {
            sorted[i] = arr2[k2];
            k2++;
        }
    }

    return sorted;
}

int main( )
{
    int size1;
    cin >> size1;
    int* arr1 = new int[size1 + 1];
    for ( int i = 0; i < size1; i++ )
    {
        cin >> arr1[i];
    }
    arr1[size1] = 2147483647;

    int size2;
    cin >> size2;
    int* arr2 = new int[size2 + 1];
    for ( int i = 0; i < size2; i++ )
    {
        cin >> arr2[i];
    }
    arr2[size2] = 2147483647;

    int *sorted1 = merge_two_sorted_arrays( size1, arr1, size2, arr2 );
    cout << size1 + size2;
    for ( int i = 0; i < size1 + size2; i++ )
    {
        cout << " " << sorted1[i];
    }

    delete [] arr1;
    delete [] arr2;
    delete [] sorted1;
    return 0;
}
