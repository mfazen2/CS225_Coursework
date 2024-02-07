#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;  i.readFromFile("../data/i.png");
  StickerSheet sheet(alma);
  sheet.addSticker(i,900,1000);
  sheet.render().writeToFile("stickertest.png");


  return 0;
}
