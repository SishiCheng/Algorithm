#include <iostream>

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

int* merge_sort( int size, int* s )
{
    int* s2;
    if ( size <= 1 )
    {
        return s;
    }
    else
    {
        s2 = s + ( size/2 );
        int* sorted1 = merge_sort( size/2, s );
        int* sorted2 = merge_sort( size - (size/2), s2 );
        int* sorted = merge_two_sorted_arrays( size/2, sorted1, size - (size/2), sorted2 );
        return sorted;
    }
}


int main()
{
    int size;
    cin >> size;
    int* s = new int[size];
    for ( int i = 0; i < size; i++ )
    {
        cin >> s[i];
    }

    int* sorted = merge_sort( size, s );

    cout << sorted[0];
    for ( int i = 1; i < size; i++ )
    {
        cout << " " << sorted[i];
    }

    delete[] sorted;
    delete[] s;
    return 0;
}
