#include "screenbuffer.h"

ScreenBuffer::ScreenBuffer() : gSurface(nullptr){}

ScreenBuffer::ScreenBuffer(const ScreenBuffer& screenBuffer){
    gSurface = SDL_CreateRGBSurfaceWithFormat (0, screenBuffer.gSurface->w, screenBuffer.gSurface->h, 
                                               0, screenBuffer.gSurface->format->format);
    SDL_BlitSurface (screenBuffer.gSurface, nullptr, gSurface, nullptr);
}

ScreenBuffer &ScreenBuffer::operator=(const ScreenBuffer& screenBuffer)
{
    if (this == &screenBuffer)
    {
        return *this;
    }

    if (gSurface != nullptr)
    {
        SDL_FreeSurface(gSurface);
        gSurface = nullptr;
    }

    if (screenBuffer.gSurface != nullptr)
    {
        gSurface = SDL_CreateRGBSurfaceWithFormat (0, screenBuffer.gSurface->w, screenBuffer.gSurface->h, 
                                               0, screenBuffer.gSurface->format->format);
        SDL_BlitSurface (screenBuffer.gSurface, nullptr, gSurface, nullptr);
            
    }
    return *this;
}

void ScreenBuffer::Init(uint32_t format, uint32_t width, uint32_t height)
{
    gSurface = SDL_CreateRGBSurfaceWithFormat (0, width, height, 0, format);
    Clear();
}

void ScreenBuffer::Clear(const Color &c){
    
    assert(gSurface);
    if (gSurface){

        SDL_FillRect(gSurface, nullptr, c.GetPixelColor());
    }
}

void ScreenBuffer::SetPixel(const Color &color, int x, int y){
    
    assert(gSurface);

    if (gSurface && (y < gSurface->h && y>=0 && x >=0 && x<gSurface->w))
    {
        SDL_LockSurface(gSurface);

        uint32_t * pixels = (uint32_t*) gSurface->pixels;
        size_t index = GetIndex(y, x);
        pixels[index] = color.GetPixelColor();

        Color surfaceColor = Color(pixels[index]);
        pixels[index] = Color::Evaluate1MinusSourceAlpha(color, surfaceColor).GetPixelColor();

        SDL_UnlockSurface(gSurface);
    }
}

uint32_t ScreenBuffer::GetIndex(int r, int c){
    
    assert(gSurface);
    if (gSurface)
    {
        return r * gSurface->w + c;
    }
    return 0;
}

ScreenBuffer::~ScreenBuffer(){

    if (gSurface)
    {
        SDL_FreeSurface(gSurface);
    }
    
}
