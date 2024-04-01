#pragma once

#include "ColorPicker.h"
#include "cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
/*solid color to white(?) idk this might suck*/
class MyColorPicker : public ColorPicker {
public:
  HSLAPixel getColor(unsigned x, unsigned y);
  MyColorPicker(HSLAPixel color, Point height,unsigned dist);

private:
  HSLAPixel color_;
  HSLAPixel white = HSLAPixel(0,0,100);
  Point height_;
  unsigned dist_;
};
