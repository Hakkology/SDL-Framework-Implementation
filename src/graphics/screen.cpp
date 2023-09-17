#include "screen.h"
#include "bmpfont.h"

Screen::Screen(): gWidth(0), gHeight(0), 
                    moptrWindow(nullptr), monoptrWindowSurface(nullptr),
                    bRenderer(nullptr), bPixelFormat(nullptr), bTexture(nullptr) {

}

SDL_Window *Screen::Init(uint32_t w, uint32_t h, uint32_t mag, bool fast){
    
    bFast = fast;

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
        uint8_t rClear = 0;
        uint8_t gClear = 0;
        uint8_t bClear = 0;
        uint8_t aClear = 255;

        if (bFast)
        {
            bRenderer = SDL_CreateRenderer(moptrWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (bRenderer == nullptr)
            {
                std::cout << "SDL_CreateRenderer failed." << std::endl;
                return nullptr;
            }
            SDL_SetRenderDrawColor(bRenderer, rClear, gClear, bClear, aClear);   
        }
        else
        {
            monoptrWindowSurface = SDL_GetWindowSurface(moptrWindow);
        }

        bPixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);
        //bPixelFormat = SDL_AllocFormat(SDL_GetWindowPixelFormat(moptrWindow));

        if (bFast)
        {
            bTexture = SDL_CreateTexture(bRenderer, bPixelFormat->format, SDL_TEXTUREACCESS_STREAMING, w, h);
        }
        
        // color and pixel format initializer
        Color::InitColorFormat(bPixelFormat);
        gClearColor = Color(rClear, gClear, bClear, aClear);

        gBackBuffer.Init(bPixelFormat -> format, gWidth, gHeight);
        gBackBuffer.Clear(gClearColor);
    }
    
    return moptrWindow;

}

void Screen::SwapBuffers(){
    
    assert(moptrWindow);
    if (moptrWindow)
    {
        ClearScreen();

        if (bFast)
        {
            uint8_t* textureData = nullptr;
            int texturePitch = 0;

            if (SDL_LockTexture(bTexture, nullptr, (void**)&textureData, &texturePitch) >= 0)
            {
                SDL_Surface* surface = gBackBuffer.GetSurface();
                memcpy(textureData, surface->pixels, surface->w* surface->h * bPixelFormat->BytesPerPixel);

                SDL_UnlockTexture(bTexture);
                SDL_RenderCopy(bRenderer, bTexture, nullptr, nullptr);
                SDL_RenderPresent(bRenderer);
            }
        }else
        {
            SDL_SetSurfaceBlendMode(gBackBuffer.GetSurface(), SDL_BLENDMODE_BLEND);  
            SDL_BlitScaled(gBackBuffer.GetSurface(), nullptr, monoptrWindowSurface, nullptr);
            SDL_UpdateWindowSurface(moptrWindow);
        }
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

void Screen::Draw(const Triangle& triangle, const Color& color, bool fill, const Color& fillColor){

    if (fill)
    {
        FillPoly(triangle.GetPoints(), [fillColor](uint32_t x, uint32_t y){return fillColor;});
    }
    
    Line2D p0p1 = Line2D (triangle.GetP0(), triangle.GetP1());
    Line2D p1p2 = Line2D (triangle.GetP1(), triangle.GetP2());
    Line2D p2p0 = Line2D (triangle.GetP2(), triangle.GetP0());

    Draw (p0p1, color);
    Draw (p1p2, color);
    Draw (p2p0, color);
}

void Screen::Draw(const Rectangle &rectangle, const Color &color, bool fill, const Color& fillColor){

    if (fill)
    {
        FillPoly(rectangle.GetPoints(), [fillColor](uint32_t x, uint32_t y){return fillColor;});
    }

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

void Screen::Draw(const Circle &circle, const Color &color, bool fill, const Color& fillColor){

    std::vector<Vector2D> circlePoints;
    std::vector<Line2D> lines;
    
    float angle = TAU / float(NUM_CIRCLE_SEGMENTS);

    Vector2D p0 = Vector2D(circle.GetCenterPoint().GetX() + circle.GetRadius(), circle.GetCenterPoint().GetY());
    Vector2D p1 = p0;
    Line2D nextLineToDraw;

    for (unsigned int i = 0; i < NUM_CIRCLE_SEGMENTS; ++i)
    {
        p1.Rotate(angle, circle.GetCenterPoint());
        nextLineToDraw.SetP1(p1);
        nextLineToDraw.SetP0(p0);

        lines.push_back(nextLineToDraw);
        //Draw(nextLineToDraw, color);
        circlePoints.push_back(p0);

        p0 = p1;
    }

    if (fill)
    {
        FillPoly(circlePoints, [fillColor](uint32_t x, uint32_t y){return fillColor;});
    }

    for (const Line2D& line: lines)
    {
        Draw(line, color);
    }
    
    
}

void Screen::Draw(const BMPImage &image, const Sprite& sprite, const Vector2D& pos, const Color& overlayColor, float rotation){

    float rVal = static_cast<float>(overlayColor.GetRed()) / 255.0f;
    float gVal = static_cast<float>(overlayColor.GetGreen()) / 255.0f;
    float bVal = static_cast<float>(overlayColor.GetBlue()) / 255.0f;
    float aVal = static_cast<float>(overlayColor.GetAlpha()) / 255.0f;
    
    uint32_t width = sprite.width;
    uint32_t height = sprite.height;

    const std::vector<Color>& pixels = image.GetPixels();

    Vector2D spritePos = Vector2D(sprite.xPos, sprite.yPos);

    auto topLeft = pos;
    auto topRight = pos + Vector2D(width, 0);
    auto bottomLeft = pos + Vector2D(0, height);
    auto bottomRight = pos + Vector2D(width, height);

    Vector2D centerPoint = Vector2D((topRight.GetX() - topLeft.GetX()) / 2, (bottomLeft.GetY() - topLeft.GetY()) / 2) + topLeft;
	float cosine = cosf(rotation);
	float sine = sinf(rotation);

    std::vector<Vector2D> points = {topLeft, bottomLeft, bottomRight, topRight};

    for (auto& point : points)
	{
		point.Rotate(rotation, centerPoint);
	}

    Vector2D xAxis = topRight - topLeft;
    Vector2D yAxis = bottomLeft - topLeft;

    const float invXAxisLengthSq = 1.0f / xAxis.MagnitudeSquare();
    const float invYAxisLengthSq = 1.0f / yAxis.MagnitudeSquare();

    FillPoly(points, [&](uint32_t px, uint32_t py){

        Vector2D p = {static_cast<float>(px), static_cast<float>(py)};
        Vector2D d = p - topLeft;

        float u = invXAxisLengthSq * d.Dot(xAxis);
        float v = invYAxisLengthSq * d.Dot(yAxis);

        u = Clamp(u, 0.0f, 1.0f);
        v = Clamp(v, 0.0f, 1.0f);

        float tx = roundf(u * static_cast<float>(sprite.width));
        float ty = roundf(v * static_cast<float>(sprite.height));

        Color imageColor = pixels[GetIndex(image.GetWidth(), ty + sprite.yPos, tx + sprite.xPos)];

        Color newColor = {static_cast<uint8_t>(imageColor.GetRed() * rVal), 
                          static_cast<uint8_t>(imageColor.GetGreen() * gVal), 
                          static_cast<uint8_t>(imageColor.GetBlue() * bVal), 
                          static_cast<uint8_t>(imageColor.GetAlpha() * aVal)};

        return newColor;
    });
}

void Screen::Draw(const SpriteSheet &ss, const std::string &spriteName, const Vector2D &pos, const Color& overlayColor, float rotation){
    
    Draw(ss.GetBMPImage(), ss.GetSprite(spriteName), pos, overlayColor, rotation);
}

void Screen::Draw(const BmpFont& font, const std::string& textLine, const Vector2D& pos, const Color& overlayColor){

    uint32_t xPos = pos.GetX();

    const SpriteSheet& ss = font.GetSpriteSheet();

    for( char c : textLine){

        if(c == ' '){

            xPos += font.GetFontSpacingBetweenWords();
            continue;
        }

        Sprite sprite = ss.GetSprite(std::string("") + c);

        Draw(ss.GetBMPImage(), sprite, Vector2D(xPos, pos.GetY()), overlayColor);

        xPos += sprite.width;
        xPos += font.GetFontSpacingBetweenLetters();
    }
}

void Screen::ClearScreen(){
    assert(moptrWindow);
    if (moptrWindow)
    {
        if (bFast)
        {
            SDL_RenderClear(bRenderer);
        }else
        {
            SDL_FillRect(monoptrWindowSurface, nullptr, gClearColor.GetPixelColor());
        }
    }
}

void Screen::FillPoly(const std::vector<Vector2D> &points, FillPolyFunc func){

    if (points.size() > 0)
    {
        float top = points[0].GetY();
        float bottom = points[0].GetY();
        float right = points[0].GetX();
        float left = points[0].GetX();

        for (size_t i = 0; i < points.size(); ++i)
        {
            if (points[i].GetY() < top)
            {
                top = points[i].GetY();
            }

            if (points[i].GetY() > bottom)
            {
                bottom = points[i].GetY();
            }

            if (points[i].GetX() < left)
            {
                left = points[i].GetX();
            }

            if (points[i].GetX() > right)
            {
                right = points[i].GetX();
            }
        }

        for (int pixelY = top; pixelY < bottom; ++pixelY)
        {
            std::vector<float> nodeXVector;

            size_t j = points.size() -1;

            for (size_t i = 0; i < points.size(); ++i)
            {
                float pointiY = points[i].GetY();
                float pointjY = points[j].GetY();

                if (pointiY <= (float) pixelY && pointjY > (float)pixelY || (pointjY) <= (float) pixelY && pointiY > (float) pixelY)
                { 
                    float denom = pointjY - pointiY;
                    if (IsEqual(denom, 0))
                    {
                        continue;
                    }
                    
                    float x = points[i].GetX() + (pixelY - pointiY)/denom * (points[j].GetX() - points[i].GetX());
                    nodeXVector.push_back(x);
                }
                
                j=i;
            }
            
            std::sort(nodeXVector.begin(), nodeXVector.end(), std::less<>());

            for (size_t k = 0; k < nodeXVector.size(); k+=2)
            {
                if (nodeXVector[k] > right)
                {
                    break;
                }

                if (nodeXVector[k+1] > left)
                {
                    if (nodeXVector[k] < left)
                    {
                        nodeXVector[k] = left;
                    }
                    if (nodeXVector[k+1] > right)
                    {
                        nodeXVector[k+1] = right;
                    }
                    
                    // Line2D line = {Vector2D(nodeXVector[k], pixelY), Vector2D(nodeXVector[k+1], pixelY)};
                    // Draw(line, color);

                    for (int pixelX = nodeXVector[k]; pixelX < nodeXVector[k+1]; ++pixelX)
                    {
                        Draw(pixelX, pixelY, func(pixelX, pixelY));
                    }
                    
                }
                
                
            }
            
        }
    }
}

Screen::~Screen(){

    if (bPixelFormat)
    {
        SDL_FreeFormat(bPixelFormat);
        bPixelFormat = nullptr;
    }
    
    if (bTexture)
    {
        SDL_DestroyTexture(bTexture);
        bTexture = nullptr;
    }
    
    if (bRenderer)
    {
        SDL_DestroyRenderer(bRenderer);
        bRenderer = nullptr;
    }
    
    if (moptrWindow)
    {
        SDL_DestroyWindow(moptrWindow);
        moptrWindow = nullptr;
    }
    SDL_Quit();
}

