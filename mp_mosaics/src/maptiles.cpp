/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    //make new canvas
    MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    //make new vector of points and a map that links the points and TileImage pointers
    vector<Point<3>> node_points;
    map<Point<3>, TileImage*> conversion;
    //iterate over the vector of tiles
    auto iter = theTiles.begin();
    while (iter != theTiles.end()) {
        //get average color of each tile, insert into map, and push back to vector of points
        Point<3> AvColPoint = convertToXYZ(iter->getAverageColor());
        //pass address of the dereferenced iterator to the map
        conversion[AvColPoint] = &(*iter);
        node_points.push_back(AvColPoint);
        iter++;
    }
    //construct new tree with our vector
    KDTree<3> kdtree(node_points);
    for (int i = 0; i < canvas->getRows(); ++i) {
        for (int j = 0; j < canvas->getColumns(); ++j) {
            //decide which tile image to chose using the FNN function to find whichever point has the closest color 
            //to the average color of the region
            Point<3> AvColRegion = convertToXYZ(theSource.getRegionColor(i, j));
            Point<3> nearestColor = kdtree.findNearestNeighbor(AvColRegion);
            canvas->setTile(i, j, conversion[nearestColor]);
        }
    }
    return canvas;
}

