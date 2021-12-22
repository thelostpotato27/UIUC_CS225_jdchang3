#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  start_ = start;
  point_list_.push(start);
  int height = png.height();
  int width = png.width();

  //std::cout << height << std::endl;
  //std::cout << width << std::endl;

  visited_points_.resize(height);
  for (int i = 0; i < height; i++){
    visited_points_[i].resize(width);
  }

  while(!point_list_.empty()){
    Point check_point = point_list_.top();
    x_ = check_point.x;
    y_ = check_point.y;

    if(visited_points_[y_][x_] == 1){
      point_list_.pop();
      continue;
    }

    point_list_final_.push(check_point);
    point_list_.pop();

    visited_points_[y_][x_] = 1;
    
    HSLAPixel p1 = png.getPixel(start_.x, start_.y);

    //std::cout << x_ + 1 << std::endl;
    //std::cout << y_ + 1 << std::endl;

    if(x_+1 < width){
      if (tolerance > calculateDelta(p1, png.getPixel(x_ + 1, y_))){
        point_list_.push(Point(x_ + 1, y_));
      }
    }

    //std::cout << "first" << std::endl;

    if(y_+1 < height){
      if (tolerance > calculateDelta(p1, png.getPixel(x_, y_ + 1))){
        point_list_.push(Point(x_, y_ + 1));
      }
    }

    //std::cout << "second" << std::endl;

    if(x_- 1 >= 0){
      if (tolerance > calculateDelta(p1, png.getPixel(x_ - 1, y_))){
        point_list_.push(Point(x_ - 1, y_));
      }
    }

    //std::cout << "third" << std::endl;
    
    if(y_-1 >= 0){
      if (tolerance > calculateDelta(p1, png.getPixel(x_, y_ - 1))){
        point_list_.push(Point(x_, y_ - 1));
      }
    }

    //std::cout << "fourth" << std::endl;
  }
  point_list_.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(point_list_final_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(std::queue<Point> ());
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  point_list_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point holder = point_list_.top();
  point_list_.pop();
  return holder;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return point_list_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  if(point_list_.empty()){return true;}
  return false;
}

double DFS::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}