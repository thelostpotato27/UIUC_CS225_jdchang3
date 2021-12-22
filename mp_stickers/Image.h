/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include <string>
#include <iostream>
#include "cs225/PNG.h"

class Image: public cs225::PNG
{
    public:
        //darkens every pixel by .1, make sure it doesnt go under 0
        void darken();

        //darkens every pixel by amount, doesnt go uner 0
        void darken(double amount);

        //desaturates image by lowering saturation by .1, doesnt go uner 0
        void desaturate();

        //desaturates image by lowering saturation by amount, doesnt go under 0
        void desaturate(double amount);

        //grayscales img
        void grayscale();

        //illinifys img
        void illinify();

        //lighten every pixel by .1, make sure it doesnt go over 1
        void lighten();

        //lighten every pixel by certain amount
        void lighten(double amount);

        //rotates the color wheel by degrees, makes sure that the color 
        //wheel stays in [0, 360]
        void rotateColor(double degrees);

        //saturates by increasing s by .1, makes sure to stay in [0,1]
        void saturate();

        void saturate(double amount);

        //scale the image by factor, for ex scale of .5 reduces width and
        //height by half
        void scale(double factor);

        //scales image to fit wxh. preserves function aspect ration, so
        //will scale either by w or by h, depending on what fits. for 
        //example, a 10,20 img wants to scale to 100,100 will turn into
        //a 50,100 img
        void scale(unsigned w, unsigned h);

        void parse(double hChange, double sChange, double lChange);
};