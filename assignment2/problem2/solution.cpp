#include <iostream>
using namespace std;

class point
{
public:
    float x;
    float y;
    static point first_point;

    bool operator < (point right) const
    {
        if ( (x != first_point.x) && (right.x != first_point.x) )
        {
            float left_slope = (y - first_point.y) / (x - first_point.x);
            float right_slope = (right.y - first_point.y) / (right.x - first_point.x);

            if ( left_slope * right_slope > 0 )
            {
                return ( left_slope < right_slope );
            }

            return ( left_slope > 0 );
        }
        else if ( (x == first_point.x) && (right.x == first_point.x) )
        {
            return false;
        }
        else if ( (x == first_point.x) )
        {
            float right_slope = (right.y - first_point.y) / (right.x - first_point.x);
            return ( right_slope < 0 );
        }
        else
        {
            float left_slope = (y - first_point.y) / (x - first_point.x);
            return ( left_slope > 0 );
        }
    }
};
point point::first_point;

class line
{
public:
    float a;
    float b;
};

template <class T>
T* merge_two_sorted_arrays(int size1, T* arr1, int size2, T* arr2 )
{
    T* sorted = new T[size1 + size2];

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

template <class T>
T* merge_sort(int size, T* s )
{
    T* s2;
    if ( size <= 1 )
    {
        return s;
    }
    else
    {
        s2 = s + ( size/2 );
        T* sorted1 = merge_sort(size / 2, s);
        T* sorted2 = merge_sort(size - (size / 2), s2);
        T* sorted = merge_two_sorted_arrays(size / 2, sorted1, size - (size / 2), sorted2);
        return sorted;
    }
}

int graham_scan( point* p, int size, point* convex_hull )
{
    int miny = 0;
    for ( int i = 1; i < size; i++ )
    {
        if (p[miny].y > p[i].y )
        {
            miny = i;
        }
    }

    point* temp1 = new point[size - 1];
    int count = 0;
    for ( int i = 0; i < size; i++ )
    {
        if ( i != miny )
        {
            temp1[count] = p[i];
            count++;
        }
    }
    point::first_point = p[miny];

    point* temp2 = merge_sort(size-1, temp1);
    delete[] temp1;

    point* p_sorted = new point[size];
    p_sorted[0] = p[miny];
    for (int i = 1; i < size; i++ )
    {
        p_sorted[i] = temp2[i-1];
    }
    delete[] temp2;

    convex_hull[0] = p_sorted[0];
    convex_hull[1] = p_sorted[1];
    convex_hull[2] = p_sorted[2];
    int stack_size = 3;
    for (int i = 3; i < size; i++ )
    {
        while ( stack_size > 0 )
        {
            float vector_a_x = convex_hull[stack_size - 1].x - convex_hull[stack_size - 2].x;
            float vector_a_y = convex_hull[stack_size - 1].y - convex_hull[stack_size - 2].y;
            float vector_b_x = p_sorted[i].x - convex_hull[stack_size - 1].x;
            float vector_b_y = p_sorted[i].y - convex_hull[stack_size - 1].y;

            if ( vector_a_x * vector_b_y - vector_b_x * vector_a_y >= 0 )
            {
                convex_hull[stack_size] = p_sorted[i];
                stack_size++;
                break;
            }
            else
            {
                stack_size--;
            }
        }
    }
    delete[] p_sorted;
    return stack_size;
}

int lower_half_size(int ch_size, point* convex_hull )
{
    int low_size = 1;
    for ( int i = 1; i < ch_size; i++ )
    {
        if ( convex_hull[i].x > convex_hull[i-1].x )
        {
            low_size++;
        }
        else
        {
            break;
        }
    }

    for ( int i = ch_size - 2; i > -1; i-- )
    {
        if ( convex_hull[i].x < convex_hull[i+1].x )
        {
            low_size++;
        }
        else
        {
            break;
        }
    }

    if ( convex_hull[ch_size-1].x < convex_hull[0].x )
    {
        low_size++;
    }

    return low_size;
}

int main()
{
    int size;
    cin >> size;
    line* l = new line[size];
    for ( int i = 0; i < size; i++ )
    {
        cin >> l[i].a >> l[i].b;
    }

    point* p = new point[size];
    for ( int i = 0; i < size; i++ )
    {
        p[i].x = l[i].a;
        p[i].y = -l[i].b;
    }
    delete[] l;

    point* convex_hull = new point[size];
    int ch_size = graham_scan( p, size, convex_hull );
    delete[] p;

    int low_size = lower_half_size(ch_size, convex_hull);
    delete[] convex_hull;
    cout << low_size << ' ' << ch_size - low_size + 2;
    return 0;
}
