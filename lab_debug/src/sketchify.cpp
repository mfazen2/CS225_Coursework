/**
 * @file sketchify.cpp
 * Implementation of the sketchify function.
 */
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wreturn-stack-address"
#include <string>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

/**
 * Creates a new output image.

 * @param w width of the image
 * @param h height of the image

 * @return a pointer to the newly-created image
 */
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

/**
 * Used to customize the color of the sketchified image.

 * @return a pointer to the color to use when sketchifying
 */
HSLAPixel* myFavoriteColor() {
    return new HSLAPixel (280, 0.8, 0.5);
    
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    std::cout << "line 40" << std::endl;
    PNG* original = new PNG();
    std::cout << "png current null" << std::endl;
    original->readFromFile(inputFile);
    std::cout << "original data -> readfromfile" << std::endl;
    unsigned width = original->width();
    std::cout << "original width" << width << std::endl;
    unsigned height = original->height();
    std::cout << "original height" << std::endl;

    // Create out.png
    PNG* output = NULL;
    std::cout << "output = null" << std::endl;
    output = setupOutput(width, height);
    std::cout << "output h & w" << output->width() << " " << output->width() << std::endl;
    std::cout << "setupout" << std::endl;
    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor();
    std::cout << "pixel = myfavcol" << std::endl;
    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (unsigned y = 1; y < height; y++) {
        for (unsigned x = 1; x < width; x++) {
            // Calculate the pixel difference
            HSLAPixel& prev = original->getPixel(x - 1, y - 1);
            HSLAPixel& curr = original->getPixel(x, y);
            double diff = std::fabs(curr.h - prev.h);

            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            HSLAPixel currOutPixel = output->getPixel(x, y);
            if (diff > 20) {
                std::cout << "assign currout to *mypixel" << std::endl;
                currOutPixel = *myPixel;
                output->getPixel(x,y) = currOutPixel;
            }
            
        }
    }
    std::cout << "about to save" << std::endl;
    // Save the output file
    output->writeToFile(outputFile);
    std::cout << "savesuccess" << std::endl;
    // Clean up memory
    delete myPixel;
    delete output;
    delete original;
}
