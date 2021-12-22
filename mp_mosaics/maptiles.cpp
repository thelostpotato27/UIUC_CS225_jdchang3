    /**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* Mosaic = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> pixel_info;
    for(unsigned i = 0; i < theTiles.size(); i++){
        Point<3> pixel_vector = convertToXYZ(theTiles[i].getAverageColor());
        pixel_info.push_back(pixel_vector);
    }
    KDTree<3> mosaic_tree = KDTree<3>(pixel_info);
    unsigned rows = theSource.getRows();
    unsigned cols = theSource.getColumns();
    for(unsigned i = 0; i < rows; i++){
        for(unsigned j = 0; j < cols; j++){
            Point<3> source_avg = convertToXYZ(theSource.getRegionColor(i,j));
            Point<3> closest_col = mosaic_tree.findNearestNeighbor(source_avg);
            int counter = 0;
            while(pixel_info[counter] != closest_col){
                counter++;
            }
            TileImage * temp = &theTiles[counter];
            Mosaic->setTile(i,j,temp);
        }
    }

    return Mosaic;
}

