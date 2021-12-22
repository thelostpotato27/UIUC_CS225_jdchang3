/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include <string>
#include <iostream>
#include "Image.h"
#include "cs225/PNG.h"
#include <vector>

class StickerSheet
{
    public:
        StickerSheet (const Image &picture, unsigned max);
        //Initializes this StickerSheet with a deep copy of the base picture 
        //and the ability to hold a max number of stickers (Images) with indices 0 through max - 1.

        // ~StickerSheet ();
        //Frees all space that was dynamically allocated by this StickerSheet

        // StickerSheet (const StickerSheet & other);
        //The copy constructor makes this StickerSheet an independent copy of the source.

        // const StickerSheet & operator= (const StickerSheet &other);
 	    //The assignment operator for the StickerSheet class
        ~StickerSheet();
        
        void changeMaxStickers (unsigned max);
 	    //Modifies the maximum number of stickers that can be stored on 
        //this StickerSheet without changing existing stickers' indices.

        int addSticker (Image &sticker, unsigned x, unsigned y);
 	    //Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.
 
        bool translate (unsigned index, unsigned x, unsigned y);
 	    //Changes the x and y coordinates of the Image in the specified layer.
 
        void removeSticker (unsigned index);
 	    //Removes the sticker at the given zero-based layer index. 
 
        Image * getSticker (unsigned index);
 	    //Returns a pointer to the sticker at the specified index, not a copy of it.
 
        Image render () const;
 	    //Renders the whole StickerSheet on one Image and returns that Image. 

        struct vectObject {
            int x_;
            int y_;
            Image sticker_;
        };

        std::vector<vectObject> vect;
        std::vector<Image*> to_delete;
        Image baseImg;

        unsigned int maximum;
        unsigned int counter = 0;
};



