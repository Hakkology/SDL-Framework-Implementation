#include "screen.h"

Screen::Screen(): gWidth(0), gHeight(0), 
                    moptrWindow(nullptr), monoptrWindowSurface(nullptr){

}

SDL_Window *Screen::Init(uint32_t w, uint32_t h, uint32_t mag){
    
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "Error SDL_Init Failed" << std::endl;
        return nullptr;
    }

    gWidth = w;
    gHeight = h;

    // window initializer
    moptrWindow = SDL_CreateWindow("Bilqe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gWidth*mag, gHeight*mag, 0);
    
    if (moptrWindow == nullptr)
    {
        std::cout << "Window could not be created with error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // window surface initializer
    if (moptrWindow)
    {
        monoptrWindowSurface = SDL_GetWindowSurface(moptrWindow);

        // color and pixel format initializer
        SDL_PixelFormat *pixelFormat = monoptrWindowSurface->format;
        Color::InitColorFormat(pixelFormat);
        gClearColor = Black();
        gBackBuffer.Init(pixelFormat -> format, gWidth, gHeight);
        gBackBuffer.Clear(gClearColor);
    }
    
    return moptrWindow;

}

void Screen::SwapBuffers(){
    
    assert(moptrWindow);
    if (moptrWindow)
    {
        ClearScreen();

        SDL_BlitScaled(gBackBuffer.GetSurface(), nullptr, monoptrWindowSurface, nullptr);
        SDL_UpdateWindowSurface(moptrWindow);

        gBackBuffer.Clear(gClearColor);
    }
}

void Screen::Draw(int x, int y, const Color &color){

    assert(moptrWindow);
    if (moptrWindow) {gBackBuffer.SetPixel(color, x, y);}

}

void Screen::Draw(const Vector2D &point, const Color &color){
    
    assert(moptrWindow);
    if (moptrWindow) {gBackBuffer.SetPixel(color, point.GetX(), point.GetY());}
}

void Screen::Draw(const Line2D &line, const Color &color) {

    assert(moptrWindow);
    if (moptrWindow)
    {
        int dx, dy;

        int x0 = roundf(line.GetP0().GetX());
        int y0 = roundf(line.GetP0().GetY());
        int x1 = roundf(line.GetP1().GetX());
        int y1 = roundf(line.GetP1().GetY());

        dx = x1 - x0;
        dy = y1 - y0;

        // boolean expressions are either 1 or -1 in c++, so these expressions are just -1, 0 or 1, which defines the direction.
        signed const char ix((dx>0)-(dx<0));
        signed const char iy((dy>0)-(dy<0));

        // to avoid floating point math, shall be divided by two.
        dx = abs (dx) * 2;
        dy = abs (dy) * 2;

        Draw (x0, y0, color);
        if (dx >= dy)
        {
            int d = dy - dx/2;
            while (x0 != x1){
                if (d >=0)
                {
                    d -= dx;
                    y0 += iy;
                }
                d += dy;
                x0 += ix;

                Draw(x0, y0, color);
            }
        }
        else
        {
            int d = dx - dy/2;
            while (y0 != y1){
                if (d >= 0)
                {
                    d -= dy;
                    x0 += ix;
                }
                d += dx;
                y0 += iy;

                Draw(x0, y0, color);
            }
        }
    }

}

void Screen::Draw(const Triangle& triangle, const Color& color){

    Line2D p0p1 = Line2D (triangle.GetP0(), triangle.GetP1());
    Line2D p1p2 = Line2D (triangle.GetP1(), triangle.GetP2());
    Line2D p2p0 = Line2D (triangle.GetP2(), triangle.GetP0());

    Draw (p0p1, color);
    Draw (p1p2, color);
    Draw (p2p0, color);
}

void Screen::Draw(const Rectangle &rectangle, const Color &color){

    std::vector <Vector2D> points = rectangle.GetPoints();

    Line2D p0p1 = Line2D(points[0], points[1]);
    Line2D p1p2 = Line2D(points[1], points[2]);
    Line2D p2p3 = Line2D(points[2], points[3]);
    Line2D p3p0 = Line2D(points[3], points[0]);

    Draw(p0p1, color);
    Draw(p1p2, color);
    Draw(p2p3, color);
    Draw(p3p0, color);
}

void Screen::Draw(const Circle &circle, const Color &color){

    float angle = TAU / float(NUM_CIRCLE_SEGMENTS);

    Vector2D p0 = Vector2D(circle.GetCenterPoint().GetX() + circle.GetRadius(), circle.GetCenterPoint().GetY());
    Vector2D p1 = p0;
    Line2D nextLineToDraw;

    for (unsigned int i = 0; i < NUM_CIRCLE_SEGMENTS; ++i)
    {
        p1.Rotate(angle, circle.GetCenterPoint());
        nextLineToDraw.SetP1(p1);
        nextLineToDraw.SetP0(p0);

        Draw(nextLineToDraw, color);
        p0 = p1;
    }
}

void Screen::ClearScreen(){
    assert(moptrWindow);
    if (moptrWindow)
    {
        SDL_FillRect(monoptrWindowSurface, nullptr, gClearColor.GetPixelColor());
    }
}

Screen::~Screen(){

    if (moptrWindow)
    {
        SDL_DestroyWindow(moptrWindow);
        moptrWindow = nullptr;
    }
    SDL_Quit();
}

