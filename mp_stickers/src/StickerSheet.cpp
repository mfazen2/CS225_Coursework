#include "StickerSheet.h"
using namespace cs225;
StickerSheet::StickerSheet(const Image& picture) {
    pic = picture;
}
int StickerSheet::addSticker(Image& sticker, int x, int y) {
    Image *s = &sticker;
    std::pair<int,int> c = {x,y};
    stickers.push_back(s);
    positions.push_back(c);
    return (stickers.size() - 1);
}
int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y) {
    if (layer > stickers.size()-1) {
        Image *s = new Image(sticker);
        std::pair<int,int> c = {x,y};
        stickers.push_back(s);
        positions.push_back(c);
        return stickers.size()-1;
    }
    std::pair<int,int> c = {x,y};
    stickers[layer] = &sticker;
    positions[layer] = c;  
    return layer;
}
bool StickerSheet::translate(unsigned index, int x, int y) {
    if (index >= stickers.size()){
        return false;
    }
    positions[index].first = x;
    positions[index].second = y;
    return true;
}
void StickerSheet::removeSticker(unsigned index) {
    if(index < 0 || index >= stickers.size()) {
        throw std::exception();
    }
    stickers.erase(stickers.begin()+index);
    positions.erase(positions.begin()+index);
    std::cout << "stickersize updated " << stickers.size() << std::endl;
    
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index < 0 || index >= stickers.size()) {
        return NULL;
    }
    return stickers.at(index);
    
}
int StickerSheet::layers() const{
    return stickers.size();
}

Image StickerSheet::render() const{
    Image *out = new Image(pic);
    int xmax = pic.width();
    int ymax = pic.height();
    for (size_t i = 0 ; i < stickers.size();i++){
        auto current = positions[i];
        auto curpic = stickers[i];
        int xstick = current.first + curpic->width();
        int ystick= current.second + curpic->height();
        if (xmax < xstick)  xmax = xstick;
        if (ymax < ystick)  ymax = ystick;
    }
    out->resize(xmax,ymax);
    for(size_t index =  0; index < stickers.size(); index++) {
        for(unsigned int i = 0; i < stickers[index]->width();i++) {
            for (unsigned int j = 0; j < stickers[index]->height();j++) {
                HSLAPixel& temp = stickers[index]->getPixel(i,j);
                HSLAPixel& curpix = out->getPixel(i+positions[index].first,j+positions[index].second);
                if (temp.a != 0){
                    curpix.h = temp.h;
                    curpix.s = temp.s;
                    curpix.l = temp.l;
                }
            }
        }
    }
    
    Image output = *out;
    delete out;
    return output;
}
