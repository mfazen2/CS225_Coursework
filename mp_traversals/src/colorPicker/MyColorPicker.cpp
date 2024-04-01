#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(HSLAPixel color, Point height,unsigned dist){
  dist_ = dist;
  height_ = height;
  color_=color;
}
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  double h = y - height_.y;
  double pct = h / dist_;
  if (pct >= 1){return white;}
  double pixel_h = color_.h - (color_.h*pct);
  double pixel_s = color_.s - (color_.s*pct);
  double pixel_l = color_.l - (color_.l*pct);

  return HSLAPixel(pixel_h,pixel_s,pixel_l);
}
