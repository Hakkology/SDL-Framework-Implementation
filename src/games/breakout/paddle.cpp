#include "paddle.h"

void Paddle::Init(const Rectangle &rect, const Rectangle& boundary){

    Excluder::Init(rect);
    bBoundary = boundary;
    bPaddleDirection = 0;
}

void Paddle::Update(uint32_t dt, Ball& ball){

    if (GetRectangle().ContainsPoint(ball.GetPosition()))
    {
        Vector2D pointOnEdge;

        ball.MakeFlushWithEdge(GetEdge(BOTTOM_EDGE), pointOnEdge, true);
    }
    
     
    if (bPaddleDirection != 0)
    {
        Vector2D direction;

        if ((bPaddleDirection & PaddleDirection::LEFT) == PaddleDirection::LEFT && (bPaddleDirection & PaddleDirection::RIGHT) == PaddleDirection::RIGHT)
        {
            direction = Vector2D::Zero;
        }
        else if (bPaddleDirection == PaddleDirection::LEFT){
            direction = LEFT_DIR;
        }
        else{
            direction = RIGHT_DIR;
        }
        
        Vector2D dx = direction * paddleVelocity * MillisecondstoSeconds(dt);

        MoveBy(dx);

        const Rectangle& bRect = GetRectangle();

        if (IsGreaterThanOrEqual(bBoundary.GetTopLeftPoint().GetX(), bRect.GetTopLeftPoint().GetX()))
        {
            MoveTo(Vector2D(bBoundary.GetTopLeftPoint().GetX(), bRect.GetTopLeftPoint().GetY()));
        }
        else if (IsGreaterThanOrEqual(bRect.GetBottomRightPoint().GetX(), bBoundary.GetBottomRightPoint().GetX()))
        {
            MoveTo(Vector2D(bBoundary.GetBottomRightPoint().GetX() - bRect.GetWidth(), bRect.GetTopLeftPoint().GetY()));
        }
        
        
    } 
}

void Paddle::Draw(Screen &screen){

    screen.Draw(GetRectangle(), Blue(), true, Blue());
}

bool Paddle::Bounce(Ball &ball){

    BoundaryEdge edge;

    if (HasCollided(ball.GetBoundingRect(), edge))
    {
        Vector2D pointOnEdge;

        ball.MakeFlushWithEdge(edge, pointOnEdge, true);

        if (edge.edge == GetEdge(TOP_EDGE).edge)
        {
            float edgeLength = edge.edge.Length();
            assert(!IsEqual(edgeLength, 0));

            float tx = (pointOnEdge.GetX() - edge.edge.GetP0().GetX())/edgeLength;

            if (tx <= corner_bounce_amt && ball.GetVelocity().GetX() > 0 ||
                tx >= (1.0f - corner_bounce_amt) && ball.GetVelocity().GetX() < 0)
            {
                ball.SetVelocity(-ball.GetVelocity());
                return true;
            }
            
        }

        ball.SetVelocity(ball.GetVelocity().Reflect(edge.normal));
        return true;
    }
    
    return false;
}
