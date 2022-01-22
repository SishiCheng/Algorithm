#include <iostream>

using namespace std;

int* Merge_and_Count( int size1, int* arr1, int size2, int* arr2, int* count )
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
            (*count) = *count + size1-k1;
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

int* Sort_and_Count( int size, int* s, int* count )
{
    int* s2;
    if ( size <= 1 )
    {
        return s;
    }
    else
    {
        s2 = s + ( size/2 );
        int* sorted1 = Sort_and_Count( size/2, s, count );
        int* sorted2 = Sort_and_Count( size - (size/2), s2, count );
        int* sorted = Merge_and_Count( size/2, sorted1, size - (size/2), sorted2, count );
        return sorted;
    }
}


int main()
{
    int size;
    int count = 0;
    cin >> size;
    int* s = new int[size];
    for ( int i = 0; i < size; i++ )
    {
        cin >> s[i];
    }

    int* sorted = Sort_and_Count( size, s, &count );

    cout << count;

    delete[] sorted;
    delete[] s;
    return 0;
}
