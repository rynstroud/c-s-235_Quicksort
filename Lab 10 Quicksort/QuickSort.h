//
//  QuickSort.h
//  Lab 10 QuickSort
//
//  Created by C/R
//

#ifndef QuickSort_h
#define QuickSort_h
#include <string>
#include <sstream>
#include <iostream>
#include "QSInterface.h"

template<typename T>
class QuickSort: public QSInterface<T>
{
private:
    size_t threshold;
    size_t num_items;
    T* the_data;
    int front_index;
    int rear_index;
public:
    QuickSort() : front_index(0), rear_index(0), num_items(0), threshold(0), the_data(new T[0]) {}
    ~QuickSort() { delete [] the_data; }

    /** Add an element to the QuickSort array. Dynamically grow array as needed. */
    bool addElement(T element)
    {
        if (rear_index == threshold - 1) reallocate();
        ++num_items;
        the_data[rear_index] = element;
        ++rear_index;
        return true;
    }

    /** Gives more space to the array */
    void reallocate()
    {
        size_t new_capacity = 2 * threshold;
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < num_items; ++i) new_data[i] = the_data[i]; 
        front_index = 0;
        rear_index = num_items;
        threshold = new_capacity;
    
        std::swap(the_data, new_data);
        delete[] new_data;
    }
    
    /** Sort the elements of a QuickSort subarray using median and partition functions. */
    bool sort(size_t left, size_t right)
    {
        int middle = medianOfThree(left, right - 1);
        if (middle == -1) return false;
        if (right - left > 1)
        {
            size_t pivot = partition(left, right, middle);
            sort(left, pivot);
            sort(pivot+1, right);
        }
        return true;
    }

    /** Sort all elements of the QuickSort array using median and partition functions. */
    bool sortAll() { return sort(front_index, rear_index); }

    /** Removes all items from the QuickSort array. */
    bool clear()
    {
        T* new_data = new T[threshold];
        std::swap(the_data, new_data);
        delete[] new_data;
        num_items = 0;
        rear_index = 0;
        return true;
    }
    
    /** Resets the object to default */
    void reset()
    {
        rear_index = 0;
        num_items = 0;
        threshold = 0;
        delete[] the_data;
        the_data = new T[0];
    }

    /** Return size of the QuickSort array. */
    size_t capacity() const { return threshold; }
    
    void setCapacity(size_t c)
    {
        threshold = c;
        T* new_data = new T[threshold];
        std::swap(the_data, new_data);
        delete[] new_data;
    }

    /** Return number of elements in the QuickSort array. */
    size_t size() const { return num_items; }

    /** The median of three pivot selection has two parts:
    1) Calculates the middle index by averaging the given left and right indices:
       middle = (left + right)/2
    2) Then bubble-sorts the values at the left, middle, and right indices.

    After this method is called, data[left] <= data[middle] <= data[right].

    @param left - the left boundary for the subarray from which to find a pivot
    @param right - the right + 1 boundary for the subarray from which to find a pivot
    @return the index of the pivot (middle index).
    Return -1 if  1) the array is empty,
                  2) if either of the given integers is out of bounds,
                  3) or if the left index is not less than the right index.
     */
   
     int medianOfThree(size_t left, size_t right)
    {
        if ((size() == 0) || (right < 0) || (left < 0) || (right > num_items) || (left > num_items) || !(left < right)) return -1; //We changed l & r to be -1
        int middle = 0;
        middle = (right + left) / 2;
        bubble_sort3(the_data[left], the_data[right - 1], the_data[middle]);
        return middle;
    }
    
    void bubble_sort3(int& first, int& last, int& middle)
    {
        if (middle < first) std::swap(first, middle);
        if (last < middle) std::swap(middle, last);
        if (middle < first) std::swap(first, middle);
    }

    /** Partitions a subarray around a pivot value selected according
    to median-of-three pivot selection. Because there are multiple ways
    to partition a list, follow the algorithm on page 611.

    The values less than or equal to the pivot should be placed to the left of the pivot;
    the values greater than the pivot should be placed to the right of the pivot.

    @param left - left index for the subarray to partition.
    @param right - right index + 1 for the subarray to partition.
    @param pivotIndex - index of the pivot in the subarray.
    @return the pivot's ending index after the partition completes:
    Return -1 if  1) the array is empty,
                  2) if any of the given indexes are out of bounds,
                  3) if the left index is not less than the right index.
    *///FIXME: finish
     int partition(size_t left, size_t right, size_t pivotIndex)
    {
        if ((size() == 0) || (right < 0) || (left < 0) || (right - 1 > num_items) || (left > num_items) || !(left < right - 1) || (pivotIndex < left) || (pivotIndex > right)) return -1;
        std::swap(the_data[left], the_data[pivotIndex]);
        int up = left + 1;
        int down = right - 1;
        do
        {
            while ((up != right -1) && !(the_data[left] < the_data[up])) ++up;
            while (the_data[left] < the_data[down]) --down;
            if (up < down)
            {
                std::swap(the_data[up], the_data[down]);
            }
        } while (up < down);
        std::swap(the_data[left], the_data[down]);
        return down;
    }


    /** @return: comma delimited string representation of the array. */
    std::string toString() const
    {
        std::ostringstream os;
        for (int i = 0; i < num_items; ++i) os << the_data[i]  << ",";
        return os.str().substr(0, os.str().size() - 1);
    }
    
    /** Overrides the extraction operator */
    friend std::ostream& operator<<(std::ostream& os, QuickSort& myClass) { return os << myClass.toString(); }
};

#endif /* QuickSort_h */
