#ifndef GRAPHICS_COLOR_H
#define GRAPHICS_COLOR_H

#include <stdint.h>

#include <SDL2/SDL.h>

struct SDL_PixelFormat;

class Color{

    uint32_t gColor;

public:

    static const SDL_PixelFormat* gFormat;
    static void InitColorFormat(const SDL_PixelFormat *format);

    Color(): gColor(0){}
    Color (uint32_t color): gColor(color){};
    Color (uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    inline bool operator ==(const Color& c) const{return gColor == c.gColor;}
    inline bool operator !=(const Color& c) const{return (*this == c);}
    inline uint32_t GetPixelColor() const {return gColor;}

    void SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void SetRed(uint8_t r);
    void SetGreen(uint8_t g);
    void SetBlue(uint8_t b);
    void SetAlpha(uint8_t a);

    uint8_t GetRed() const;
    uint8_t GetGreen() const;
    uint8_t GetBlue() const;
    uint8_t GetAlpha() const;


private:


};

#endif