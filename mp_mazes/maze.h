/* Your code here! */
#pragma once
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include <iostream>

using namespace std;
class SquareMaze
{
    private:
        struct _cell{
            bool down = 1;
            bool right = 1;

        };
        
        DisjointSets _elem_sets;
        vector<_cell> _maze_frame;

        int _width;
        int _height;
    
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        cs225::PNG* drawMaze() const;
        cs225::PNG* drawMazeWithSolution();
};