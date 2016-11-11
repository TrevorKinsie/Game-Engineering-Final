#include <iostream>

#include "Boss.h"
#include "System.h"

Boss::Boss(const Vec2& pos, const Texture* tex)
	: mTex(tex)
	, mCenter(pos)
	, mVelocity(0.0f, 25.0f)
	, mLife(100)
	, mSpawned(false)
	, mJitter(0)
	, mMove(true)
{
}

Boss::~Boss()
{

}

void Boss::Update(float dt)
{
	Vec2 bossTarget;
	bossTarget.x = 0.5f * System::GetWindowWidth();
	bossTarget.y = 0.25f * System::GetWindowHeight();

	if (mCenter.y <= bossTarget.y && mSpawned == false)
	{
		mCenter.y += mVelocity.y * dt;
	}
	else 
	{
		mSpawned = true;
	}

	if (mMove && mSpawned)
	{
		mCenter.y -= mVelocity.y * dt;
		mJitter++;
	}
	else if (mMove == false && mSpawned)
	{
		mCenter.y += mVelocity.y * dt;
		mJitter--;
	}

	if (mJitter == 0)
	{
		mMove = true;
	}
	else if (mJitter == 25)
	{
		mMove = false;
	}
}

void Boss::Draw(SDL_Renderer* renderer) const
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

	}
	else {
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