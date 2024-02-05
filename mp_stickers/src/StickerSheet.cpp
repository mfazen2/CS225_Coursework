#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image& picture) {
    Image pic = Image(picture);
    Sticker temp = {pic,0,0};
    stickers.push_back(temp);
}
int StickerSheet::addSticker(Image& sticker, int x, int y) {
    Image pic = Image(sticker);
    Sticker temp = {pic, x,y};
    stickers.push_back(temp);
    return (stickers.size() - 1);
}
int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y) {
    if (layer > stickers.size() - 1) {
        Image pic = Image(sticker);
        Sticker temp = {pic, x,y};
        stickers.push_back(temp);
        return stickers.size()-1;
    }
    Image pic = Image(sticker);
    Sticker temp = {pic, x,y};
    stickers.insert(stickers.begin()+layer,temp);
    return layer;
}
bool StickerSheet::translate(unsigned index, int x, int y) {
    return false;
}
void StickerSheet::removeSticker(unsigned index) {
    stickers.erase(stickers.begin()+index);
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index < 0 || index >= stickers.size()) {
        return NULL;
    }
    return &stickers.at(index).img;
    
}
int StickerSheet::layers() const{
    return stickers.size();
}
Image StickerSheet::render() const{
    Image temp = Image();
    return temp;
}