/* Your code here! */
#pragma once
#include <vector>
//#include "dsets.cpp"


using namespace std;
class DisjointSets
{
    public:

        //Creates n unconnected root nodes at the end of the vector.
        void addelements(int num);

        //This function should compress paths and works as described in lecture.
        //Returns the index of the root of the up-tree in which the parameter element resides.
        int find(int elem);

        //This function should be implemented as union-by-size
        //Your setunion function SHOULD find the roots of its arguments before combining the trees. 
        //If the two sets are the same size, make the tree containing the second argument point to the tree containing the first.
        //a and b are the first and second elements to union
        void setunion(int a, int b);

        //This function should return the number of nodes in the up-tree containing the element.
        //returns the number of nodes in the up-tree containing the element
        int size(int elem);

        vector<int> output();

        void reset();

    private:

        vector<int> _elems;

};