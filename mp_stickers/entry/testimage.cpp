#include "Image.h"

#include <iostream>

int main() {
  Image alma;

  std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  alma.readFromFile("../data/alma.png");
  alma.lighten(0.2);
  alma.writeToFile("lighten.png");

  std::cout << "Using Image::saturate to create `saturate.png`..." << std::endl;
  alma.readFromFile("../data/alma.png");
  alma.saturate(0.2);
  alma.writeToFile("saturate.png");

  std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  alma.readFromFile("../data/alma.png");
  alma.scale(100,200);
  alma.writeToFile("lighten.png");

  std::cout << "Using Image::illinify to create 'illinify.png..." << std::endl;
  alma.readFromFile("../data/alma.png");
  alma.illinify();
  alma.writeToFile("illinify.png");

  alma.readFromFile("../data/alma.png");
  alma.resize(2000,2000);
  alma.writeToFile("resizedemo.png");
  return 0;
  
}
