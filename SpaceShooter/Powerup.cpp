#include <iostream>

#include "Powerup.h"
#include "System.h"

Powerup::Powerup(const Vec2& pos, const Texture* tex)
    : mTex(tex)
    , mCenter(pos)
    , mVelocity()        // pixels/second
	, mPower(NONE)		
{
}

Powerup::~Powerup()
{
    //std::cout << "Destroying Missile" << std::endl;
}

void Powerup::Update(float dt)
{
    mCenter.x += mVelocity.x * dt;
    mCenter.y += mVelocity.y * dt;
}

void Powerup::Draw(SDL_Renderer* renderer) const
{
    // check if we have a valid texture
    if (mTex) {

        // compute rectangle on screen
        SDL_Rect screenRect;
        screenRect.w = mTex->GetWidth();
        screenRect.h = mTex->GetHeight();
        screenRect.x = (int)(mCenter.x - mTex->GetWidth() / 2);
        screenRect.y = (int)(mCenter.y - mTex->GetHeight() / 2);

        // draw textured rectangle
        SDL_RenderCopy(renderer, mTex->GetSDLTexture(), NULL, &screenRect);

    } else {
        // draw a placeholder
        SDL_Rect screenRect;
        screenRect.w = 64;
        screenRect.h = 64;
        screenRect.x = (int)(mCenter.x - screenRect.w / 2);
        screenRect.y = (int)(mCenter.y - screenRect.h / 2);

        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &screenRect);
    }
}
