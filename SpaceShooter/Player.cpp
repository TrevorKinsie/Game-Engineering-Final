#include <iostream>

#include "Player.h"
#include "Powerup.h"
#include "System.h"

Player::Player(const Vec2& pos, const Texture* tex)
    : mTex(tex)
    , mCenter(pos)
    , mSpeed(100.0f)        // pixels/second
	, mPower(NONE)
{
}

Player::~Player()
{
    //std::cout << "Destroying Player" << std::endl;
}

void Player::Update(float dt)
{
    const Uint8* keys = System::GetKeyStates();

    if (keys[SDL_SCANCODE_D]) {
        mCenter.x += mSpeed * dt;
    }
    if (keys[SDL_SCANCODE_A]) {
        mCenter.x -= mSpeed * dt;
    }
    if (keys[SDL_SCANCODE_W]) {
        mCenter.y -= mSpeed * dt;
    }
    if (keys[SDL_SCANCODE_S]) {
        mCenter.y += mSpeed * dt;
    }
}

void Player::Draw(SDL_Renderer* renderer) const
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
