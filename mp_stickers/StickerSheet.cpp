#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <iostream>
#include <vector>


StickerSheet::StickerSheet	(const Image & picture, unsigned max){
    using cs225::PNG;
    baseImg = picture;
    vect.reserve(max);
    maximum = max;
}



StickerSheet::~StickerSheet() {
    for(Image* elem : to_delete){
        delete elem;
    }
}


int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){
    unsigned int vectSize = vect.size();
    if (vectSize == maximum){
        return -1;
    }


    vectObject newObject;
    newObject.x_ = x;
    newObject.y_ = y;
    newObject.sticker_ = sticker;
    vect.insert(vect.begin() + counter, newObject);
    counter++;
    return (vect.size() -1);
}

void StickerSheet::changeMaxStickers(unsigned max){
    vect.resize(max);
    if (max < counter && max != 0){
        counter = max - 1;
    }else if (max == 0){
        counter = 0;
    }
}

Image * StickerSheet::getSticker(unsigned index){
    if (vect.size() < index + 1){
        return NULL;
    }
    Image *ptr = new Image(vect[index].sticker_);
    to_delete.push_back(ptr);
    return ptr;
}



void StickerSheet::removeSticker(unsigned index){
    vect.erase(vect.begin() + index);
    counter--;
}

Image StickerSheet::render()const{
    using cs225::HSLAPixel;
    Image output = baseImg;
    int size = vect.size();
    for (int i = 0; i < size; i++){
        Image sticker = vect[i].sticker_;
        unsigned int stickerWidth = sticker.width();
        unsigned int stickerHeight = sticker.height();

        if ((vect[i].x_ + stickerWidth ) > output.width()){
            output.resize(vect[i].x_ + stickerWidth , output.height());
        }
        if ((vect[i].y_ + stickerHeight ) > output.height()){
            output.resize(output.width(), vect[i].y_ + stickerHeight);
        }

        for (unsigned int x = vect[i].x_; x < (vect[i].x_ + stickerWidth); x++){
            for (unsigned int y = vect[i].y_; y < (vect[i].y_ + stickerHeight); y++){
                HSLAPixel & pixel = sticker.getPixel(x - vect[i].x_, y - vect[i].y_);
                if (pixel.a == 0){
                    continue;
                }
                HSLAPixel & outPixel = output.getPixel(x,y);
                outPixel.h = pixel.h;
                outPixel.s = pixel.s;
                outPixel.l = pixel.l;
                outPixel.a = pixel.a;
            }
        }
    }
    return output;
}

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){
    if ( vect.size() < index + 1){
        return false;
    }
    vect[index].x_ = x;
    vect[index].y_ = y;

    return true;
}