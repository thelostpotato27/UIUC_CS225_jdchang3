/* Your code here! */
#include <vector>
#include "maze.h"
#include <stack>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include <iostream>
#include <stdlib.h>



using namespace std;
using namespace cs225;
SquareMaze::SquareMaze(){
}


using namespace std;
using namespace cs225;
void SquareMaze::makeMaze(int width, int height){
    _width = width;
    _height = height;
    _maze_frame.clear();
    for(int i = 0; i < width * height; i++){
        _maze_frame.push_back(_cell());
    }
    _elem_sets.reset();
    _elem_sets.addelements(width * height);

    while(_elem_sets.size(0) < width * height){
        int randx = rand() % width;
        int randy = rand() % height;

        int check_right = rand() % 2;
        if(randy == height -1 && check_right == 0){
            continue;
        }else if (randx == width-1 && check_right == 1){
            continue;
        }
        
        if(check_right == 1){
            if(_elem_sets.find((randy * width) + randx) == _elem_sets.find((randy * width) + randx + 1) ){
                continue;
            }    
            _maze_frame[(randy * width) + randx].right = 0;
            _elem_sets.setunion((randy * width) + randx, (randy * width) + randx + 1);
        }else if(check_right == 0){
            if(_elem_sets.find((randy * width) + randx) == _elem_sets.find(((randy + 1) * width) + randx)){
                continue;
            }
            _maze_frame[(randy * width) + randx].down = 0;
            _elem_sets.setunion((randy * width) + randx, ((randy + 1) * width) + randx);
        }
        
    }
    
}

using namespace std;
using namespace cs225;
bool SquareMaze::canTravel(int x, int y, int dir) const{
    if(x == 0 && dir == 2){
        return 0;
    }else if(x == (_width - 1) && dir == 0){
        return 0;
    }else if(y == 0 && dir == 3){
        return 0;
    }else if(y == (_height - 1) && dir == 1){
        return 0;
    }

    if(dir == 2){
        dir = 0;
        x -= 1;
    }else if(dir == 3){
        dir = 1;
        y -= 1;
    }
    if(dir == 0){
        if(_maze_frame[(y * _width) + x].right == 0){
            return 1;
        }
    }else{
        if(_maze_frame[(y * _width) + x].down == 0){
            return 1;
        }
    }
    return 0;
}

using namespace std;
using namespace cs225;
void SquareMaze::setWall(int x, int y, int dir, bool exists){

    if(dir == 0){
        _maze_frame[(y * _width) + x].right = exists;

    }else if(dir == 1){
        _maze_frame[(y * _width) + x].down = exists;
    }
}

using namespace std;
using namespace cs225;
vector<int> SquareMaze::solveMaze(){
    vector<int> longest;
    vector<int> second;
    vector<bool> visited;
    stack<pair<int, int>> backtrack_stack;
    visited.assign(_width * _height, 0);

    int x = 0;
    int y = 0;
    pair<int,int> longest_final (0,0);
    pair<int,int> current_coord (x,y);
    int bot_row = 1;
    backtrack_stack.push(current_coord);
    while(bot_row > 0){

        
        visited[y*_width + x] = 1;
        if(canTravel(x,y,0) && !visited[y*_width + x + 1]){
            x += 1;
            current_coord.first = x;
            current_coord.second = y;
            backtrack_stack.push(current_coord);
            second.push_back(0);
        }else if(canTravel(x,y,1) && !visited[(y + 1)*_width + x]){
            y += 1;
            current_coord.first = x;
            current_coord.second = y;
            backtrack_stack.push(current_coord);
            
            second.push_back(1);
        }else if(canTravel(x,y,2) && !visited[y*_width + x - 1]){
            x -= 1;
            current_coord.first = x;
            current_coord.second = y;
            backtrack_stack.push(current_coord);
            
            second.push_back(2);
        }else if(canTravel(x,y,3) && !visited[(y - 1)*_width + x]){
            y -= 1;
            current_coord.first = x;
            current_coord.second = y;
            backtrack_stack.push(current_coord);
            
            second.push_back(3);
        }else{

            if(y == _height - 1 && second.size() > longest.size()){
                for(unsigned i = 0; i < second.size(); i++){
                    longest[i] = second[i];
                }
                longest_final.first = backtrack_stack.top().first;
                longest_final.second = backtrack_stack.top().second;
            }
            if(y == _height - 1 && second.size() == longest.size()){
                if(backtrack_stack.top().first < longest_final.first){
                    for(unsigned i = 0; i < second.size(); i++){
                        longest[i] = second[i];
                    }
                }
                longest_final.first = backtrack_stack.top().first;
                longest_final.second = backtrack_stack.top().second;
            }
            second.pop_back();
            backtrack_stack.pop();
            current_coord = backtrack_stack.top();
            
            x = current_coord.first;
            y = current_coord.second;
        }
        if(y == _height - 1 && second.size() > longest.size()){
            longest = second;
        }
        bot_row = _width;
        for(int i = 0; i < _width; i++){
            if(visited[(_width * (_height - 1)) + i]){
                bot_row--;
            }
        }
    }
    return longest;
}

using namespace std;
using namespace cs225;
PNG* SquareMaze::drawMaze() const {
    PNG * maze_pic = new PNG(_width*10 + 1, _height*10 + 1);
    for(int i = 0; i < _height*10 + 1; i++){
		HSLAPixel & pixel = maze_pic->getPixel(0,i);
		pixel.h = 0;
		pixel.s = 0;
		pixel.l = 0;
        pixel.a = 1;
	}

    for(int i = 10; i < _width*10 + 1; i++){
		HSLAPixel & pixel = maze_pic->getPixel(i,0);
		pixel.h = 0;
		pixel.s = 0;
		pixel.l = 0;
        pixel.a = 1;
	}

    for(int i = 0; i < _height; i++){
        for(int j = 0; j < _width; j++){
            bool right = _maze_frame[(i * _width) + j].right;
            bool down = _maze_frame[(i * _width) + j].down;
            if(right){
                for(int k = 0; k <= 10; k++){
                    HSLAPixel & pixel = maze_pic->getPixel((j + 1)*10,(i*10)+k);
		            pixel.h = 0;
		            pixel.s = 0;
		            pixel.l = 0;
                    pixel.a = 1;
                }
            }
            if(down){
                for(int k = 0; k <= 10; k++){
                    HSLAPixel & pixel = maze_pic->getPixel((j*10)+k, (i + 1)*10);
		            pixel.h = 0;
		            pixel.s = 0;
		            pixel.l = 0;
                    pixel.a = 1;
                }
            }
        }
    }
    return maze_pic;
}

using namespace std;
using namespace cs225;
PNG* SquareMaze::drawMazeWithSolution(){
    PNG *maze_pic = drawMaze();
	vector<int> solution = solveMaze();
	int x = 5;
	int y = 5;

    for(unsigned i = 0; i < solution.size(); i++){
        if(solution[i]==0){
			for(int j = 0; j <= 10; j++){
				HSLAPixel &pixel = maze_pic->getPixel(x + j,y);
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
                pixel.a = 1;
            }
            x += 10;
        }else if(solution[i]==1){
			for(int j = 0; j <= 10; j++){
				HSLAPixel &pixel = maze_pic->getPixel(x,y + j);
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
                pixel.a = 1;
            }
            y += 10;
        }else if(solution[i]==2){
			for(int j = 0; j <= 10; j++){
				HSLAPixel &pixel = maze_pic->getPixel(x - j,y);
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
                pixel.a = 1;
            }
            x -= 10;
        }else if(solution[i]==3){
			for(int j = 0; j <= 10; j++){
				HSLAPixel &pixel = maze_pic->getPixel(x,y - j);
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
                pixel.a = 1;
            }
            y -= 10;
        }
    }
    x -= 5;
    y += 5;
    for(int k = 1; k <10; k++){
		HSLAPixel &pixel = maze_pic->getPixel(x+k, y);
		pixel.h = 0;
		pixel.s = 0;
		pixel.l = 1;
        pixel.a = 1;
	}

    return maze_pic;
}