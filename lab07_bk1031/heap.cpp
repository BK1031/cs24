// heap.cpp
// Bharat Kathi (5938444)

#include "heap.h"
#include <iostream>
using std::cout;

// Pushes a value into the heap, then ensures
// the heap is correctly arranged
void Heap::push(int value) {
    vdata.push_back(value);
    percolateUp(vdata.size()-1);
}

// Pops the minimum value off the heap
// (but does not return it), then ensures
// the heap is correctly arranged
void Heap::pop() {
    if (vdata.size() == 0) return;
    if (vdata.size() == 1) {
        vdata.erase(vdata.begin());
        return;
    }
    int popVal = vdata[vdata.size() - 1];
    vdata[0] = popVal;
    vdata.pop_back();
    percolateDown(0);
}

// Returns the minimum element in the heap
int Heap::top() {
    if(vdata.size() == 0) return -1;
    return vdata[0];
}

// Returns true if the heap is empty, false otherwise
bool Heap::empty(){
    return vdata.size() == 0;
}

/*
    Examples of min heap

             10                      10
         /      \               /       \
       20        100          15         30
      /                      /  \        /  \
    30                     40    50    100   40

    Root element (min) at 0 index

    For element at index i:
        Parent node at [(i-1)/2] index
        Left child node at [2i+1] index
        Right child node at [2i+2] index
 */

void Heap::percolateUp(int i) {
    while (i > 0) {
        int parInd = (i - 1) / 2;
        if (vdata[i] >= vdata[parInd]) return;
        else {
            int temp = vdata[i];
            vdata[i] = vdata[parInd];
            vdata[parInd] = temp;
            i = parInd;
        }
    }
}

void Heap::percolateDown(int i) {
    int newIndex = 2 * i + 1;
    int value = vdata[i];
    while (newIndex < vdata.size()) {
        int minValue = value;
        int minIndex = -1;
        int j = 0;
        while (j < 2 && j + newIndex < vdata.size()) {
            if (vdata[j + newIndex] < minValue) {
                minValue = vdata[j + newIndex];
                minIndex = j + newIndex;
            }
            j++;
        }
        if (minValue == value) return;
        else {
            int temp = vdata[i];
            vdata[i] = vdata[minIndex];
            vdata[minIndex] = temp;
            i = minIndex;
            newIndex = 2 * i + 1;
        }
    }
}