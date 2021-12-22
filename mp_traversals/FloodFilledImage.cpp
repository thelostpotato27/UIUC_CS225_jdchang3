#include "cs225/PNG.h"
#include <list>
#include <iostream>
#include <vector>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  img_flood = png;
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  //put queues into another queue, then in the animate just take from that queue
  vector<Point> point_holder;
  ColorPicker* color = &colorPicker;
  colors.push_back(color);
  for (const Point & p : traversal) {
    point_holder.push_back(p);
  }
  animation_iterate.push_back(point_holder);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  PNG img_copy = PNG(img_flood);
  unsigned i = 0;
  unsigned counter = 0;
  
  for (vector<Point> v : animation_iterate){
    animation.addFrame(img_copy);
    for (const Point & p : v) {
      ColorPicker* color = colors[i];
      if(counter == frameInterval){
        counter = 0;
        animation.addFrame(img_copy);
      } else {
        counter++;
      }

      img_copy.getPixel(p.x, p.y) = color -> getColor(p.x, p.y);
    }
    if(counter != 0){
      animation.addFrame(img_copy);
    }
    counter = 0;
  }
  return animation;
}
