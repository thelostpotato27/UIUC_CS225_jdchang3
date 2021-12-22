#include "Image.h"
#include <string>
#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <algorithm>

void Image::parse (double hChange, double sChange, double lChange){
    using cs225::HSLAPixel;
    unsigned width = this->width();
    unsigned height = this->height();
    for (unsigned x = 0; x < width; x++) {
        for (unsigned y = 0; y < height; y++) {
            HSLAPixel & pixel = this -> getPixel(x, y);

            pixel.h = ((pixel.h + hChange) < 0) ? pixel.h + hChange + 360 : pixel.h + hChange;
            pixel.h = ((pixel.h) >= 360) ? pixel.h - 360 : pixel.h;
            pixel.s = ((pixel.s + sChange) < 0) ? 0 : pixel.s + sChange;
            pixel.s = ((pixel.s) > 1) ? 1 : pixel.s;
            pixel.l = ((pixel.l + lChange) < 0) ? 0 : pixel.l + lChange;
            pixel.l = ((pixel.l) > 1) ? 1 : pixel.l;
        }
    }
}

void Image::darken(){
    parse(0, 0, -.1);
}

void Image::darken(double amount){
    parse(0, 0, -1 * amount);
}

void Image::desaturate(){
    parse(0, -.1, 0);
}

void Image::desaturate(double amount){
    parse(0, -1 * amount, 0);
}

void Image::grayscale(){
    parse(0, -1, 0);
}

void Image::illinify(){
    using cs225::HSLAPixel;
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.h < 11 || pixel.h > 293){
                pixel.h = 11;
            }else if (pixel.h > 216){
                pixel.h = 216;
            } else {
                pixel.h = pixel.h >= 114 ? pixel.h = 216 : pixel.h = 11;
            }
        }
    } 
}

void Image::lighten(){
    parse(0, 0, .1);
}

void Image::lighten(double amount){
    parse(0, 0, amount);
}

void Image::rotateColor(double degrees){
    this->parse(degrees, 0, 0);
}

void Image::saturate(){
    parse(0, .1, 0);
}

void Image::saturate(double amount){
    parse(0, amount, 0);
}

void Image::scale(double factor){
    using cs225::HSLAPixel;
    unsigned width = this->width();
    unsigned height = this->height();
    
    if (factor != 1){

        Image old = Image(*this);
        this->resize(width * factor, height * factor);

        for(unsigned i = 0; i < width * factor; i++){
            for(unsigned j = 0; j < height * factor; j++){
                HSLAPixel & current = getPixel(i, j);
                current = old.getPixel(i/factor, j/factor);
            }
        }
    }

}
    

void Image::scale(unsigned w, unsigned h){
    unsigned width = this->width();
    unsigned height = this->height();
    double factor = 0;
    if((w * 1.0)/width < (h * 1.0)/height){
        factor = (w * 1.0)/width;
    }else{
        factor = (h * 1.0)/height;
    }
    scale(factor);
}