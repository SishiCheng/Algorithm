//////////////////////////////////////////////////////////
// Name 1:Sishi Cheng     
// Name 2:Leran Ma        
// Name 3:Ivy Chen       

#include <iostream>
using namespace std;

struct interval
{
    int start;
    int end;
    int weight;
};

interval* merge_two_sorted_arrays( int size1, interval* arr1, int size2, interval* arr2 )
{
    interval* sorted = new interval[size1 + size2];

    int k1, k2;
    k1 = k2 = 0;

    for ( int i = 0; i < size1 + size2; i++ )
    {
        if ( arr1[k1].end < arr2[k2].end )
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

interval* merge_sort( int size, interval* s )
{
    interval* s2;
    if ( size <= 1 )
    {
        return s;
    }
    else
    {
        s2 = s + ( size/2 );
        interval* sorted1 = merge_sort( size/2, s );
        interval* sorted2 = merge_sort( size - (size/2), s2 );
        interval* sorted = merge_two_sorted_arrays( size/2, sorted1, size - (size/2), sorted2 );
        return sorted;
    }
}

int binary_search( interval *jobs, int a, int start, int end )
{
    if ( jobs[a].start < jobs[0].end )
    {
        return -1;
    }

    int median = ( start + end ) / 2;

    if ( jobs[median].end <= jobs[a].start && jobs[a].start <= jobs[median + 1].end )
    {
        if ( jobs[a].start < jobs[median + 1].end )
            return median;
        if ( jobs[median].end == jobs[a].start )
            return median;
        if ( jobs[median+1].end == jobs[a].start )
            return median + 1;
        return median;
    }
    else if ( jobs[median].end >= jobs[a].start )
    {
        return binary_search( jobs, a, start, median );
    }
    else if ( jobs[a].start >= jobs[median + 1].end )
    {
        return binary_search( jobs, a, median + 1, end );
    }
}

int DP_weighted( interval *jobs, int num_of_jobs )
{
    int sum[num_of_jobs];
    int pre[num_of_jobs];

    for (int i = 0; i < num_of_jobs; ++i)
    {
        sum[i] = 0;
    }

    sum[0] = jobs[0].weight;
    pre[0] = -1;
    for (int i = 1; i < num_of_jobs; ++i)
    {
        pre[i] = binary_search( jobs, i, 0, i-1 );

        if ( pre[i] != -1 )
        {
            if (sum[i - 1] < sum[pre[i]] + jobs[i].weight)
            {
                sum[i] = sum[pre[i]] + jobs[i].weight;
            }
            else
            {
                sum[i] = sum[i - 1];
            }
            while ( jobs[ pre[i] ].end == jobs[ pre[i] + 1 ].end )
            {
                pre[i]++;
                if (sum[i - 1] < sum[pre[i]] + jobs[i].weight && sum[i] < sum[pre[i]] + jobs[i].weight)
                {
                    sum[i] = sum[pre[i]] + jobs[i].weight;
                }
                else if ( sum[i] < sum[i - 1] )
                {
                    sum[i] = sum[i - 1];
                }
            }
        }
        else
        {
            if (sum[i - 1] < jobs[i].weight)
            {
                sum[i] = jobs[i].weight;
            }
            else
            {
                sum[i] = sum[i - 1];
            }
        }
    }


    return sum[num_of_jobs-1];
}

int main()
{
    int num_of_jobs;
    cin >> num_of_jobs;

    interval jobs[num_of_jobs];
    for (int i = 0; i < num_of_jobs; ++i)
    {
        cin >> jobs[i].start;
        cin >> jobs[i].end;
        cin >> jobs[i].weight;
    }

    interval *jobs_sorted = merge_sort( num_of_jobs, jobs );

    cout << DP_weighted( jobs_sorted, num_of_jobs );

    cout << endl;

//    for (int i = 0; i < num_of_jobs; ++i) {
//        cout << jobs_sorted[i].start << " "
//             << jobs_sorted[i].end << " "
//             << jobs_sorted[i].weight << " "
//             << sum[i] << endl;
//    }

    delete [] jobs_sorted;
    return 0;
}
