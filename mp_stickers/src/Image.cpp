#include "Image.h"
using namespace cs225;
    void Image::lighten(){
        auto w = width();
        auto h = height();
        for(unsigned int  x = 0; x < w; x++){
            for(unsigned int y = 0; y < h; y++) {
                HSLAPixel& temp = getPixel(x,y);
                if (temp.l +.1 > 1){
                    temp.l = 1;
                } else {
                    temp.l+=.1;
                }
            }
        }

    }
    void Image::lighten(double amount){
        auto w = width();
        auto h = height();
        for(unsigned int x = 0; x < w; x++){
            for(unsigned int y = 0; y < h; y++) {
                HSLAPixel& temp = getPixel(x,y);
                if (temp.l + amount > 1){
                    temp.l = 1;
                } else {
                    temp.l+=amount;
                }
            }
        }

    }
    void Image::darken(double amount){
        auto w = width();
        auto h = height();
        for(unsigned int x = 0; x < w; x++){
            for(unsigned int y = 0; y < h; y++) {
                HSLAPixel& temp = getPixel(x,y);
                if (temp.l - amount < 0){
                    temp.l = 0;
                } else {
                    temp.l-=amount;
                }
            }
        }

    }
    void Image::darken(){
        auto w = width();
        auto h = height();
        for(unsigned int x = 0; x < w; x++){
            for(unsigned int y = 0; y < h; y++) {
                HSLAPixel& temp = getPixel(x,y);
                if (temp.l - .1 < 0){
                    temp.l = 0;
                } else {
                    temp.l-=.1;
                }
            }
        }

    }

    void Image::grayscale(){
        auto w = width();
        auto h = height();
        for(unsigned int x = 0; x < w; x++){
            for(unsigned int y = 0; y < h; y++) {
                HSLAPixel& temp = getPixel(x,y);
                temp.s = 0;
            }
        }
    }
    void Image::saturate(){
        auto w = width();
        auto h = height();
        for(unsigned int x = 0; x < w; x++){
            for(unsigned int y = 0; y < h; y++) {
                HSLAPixel& temp = getPixel(x,y);
                if ((temp.s + .1) > 1){
                    temp.s = 1;
                } else {
                    temp.s+=.1;
                }
            }
        } 
    }
    void Image::saturate(double amount) {
        auto w = width();
        auto h = height();
        for(unsigned int x = 0; x < w; x++){
            for(unsigned int y = 0; y < h; y++) {
                HSLAPixel& temp = getPixel(x,y);
                if ((temp.s + amount) > 1){
                    temp.s = 1;
                } else {
                    temp.s +=amount;
                }
            }
        }  
    }
    void Image::desaturate(){
    auto w = width();
        auto h = height();
        for(unsigned int x = 0; x < w; x++){
            for(unsigned int y = 0; y < h; y++) {
                HSLAPixel& temp = getPixel(x,y);
                if ((temp.s - .1) < 0){
                    temp.s = 0;
                } else {
                    temp.s-=.1;
                }
            }
        }  
    }
    void Image::desaturate(double amount){
        auto w = width();
        auto h = height();
        for(unsigned int x = 0; x < w; x++){
            for(unsigned int y = 0; y < h; y++) {
                HSLAPixel& temp = getPixel(x,y);
                if ((temp.s - amount) < 0){
                    temp.s = 0;
                } else {
                    temp.s-=amount;
                }
            }
        }  
    }
    void Image::rotateColor(double degrees) {
        auto w = width();
        auto h = height();
        for(unsigned int x = 0; x < w; x++){
            for(unsigned int y = 0; y < h; y++) {
                HSLAPixel& temp = getPixel(x,y);
                if (temp.h + degrees > 360) {
                    temp.h = (temp.h + degrees) - 360;
                } else if (temp.h + degrees < 0) {
                    temp.h = 360 + (temp.h + degrees);
                } else {
                    temp.h+=degrees;
                }
            }
        } 
    }

    void Image::illinify(){
        auto w = width();
        auto h = height();
        for(unsigned int x = 0; x < w; x++){
            for(unsigned int y = 0; y < h; y++) {
                HSLAPixel& temp = getPixel(x,y);
                if ((temp.h >= 114) && (temp.h <= 296)) {
                    temp.h = 216;
                } else {
                    temp. h = 11;
                }
            }
        } 
    }
    void Image::scale(unsigned w, unsigned h){
        resize(w,h);
    }
    void Image::scale(double factor){
        int w = static_cast<int>(factor*width());
        int h = static_cast<int>(factor*height());
        resize(w,h);
    }
    
