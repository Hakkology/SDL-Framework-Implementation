#ifndef GRAPHICS_BMPIMAGE_H
#define GRAPHICS_BMPIMAGE_H

#include <vector>
#include <string>
#include <stdint.h>

#include "bmpimage.h"

#include "color.h"

class BMPImage{

public:

    BMPImage();
    
    bool Load (const std::string& path);

    inline const std::vector<Color>& GetPixels() const {return mPixels;}
    inline uint32_t GetWidth() const {return mWidth;}
    inline uint32_t GetHeight() const {return mHeight;}

private:

    std::vector<Color> mPixels;
    uint32_t mWidth, mHeight;
};

#endif  