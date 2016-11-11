#include <iostream>

#include "Button.h"

Button::Button(Texture* tex)
    : Button(tex, 0, 0)
{
}

Button::Button(Texture* tex, int x, int y)
	: mRect()
    , mTex(tex)
{
    mRect.x = x;
    mRect.y = y;
    mRect.w = tex->GetWidth();
	mRect.h = tex->GetHeight();
}

Button::~Button()
{
    //std::cout << "Button destroyed" << std::endl;
}

SDL_Point Button::Center() const
{
	SDL_Point p;
	p.x = Left() + Width() / 2;
	p.y = Top() + Height() / 2;
	return p;
}

void Button::SetCenter(int x, int y)
{
	SetLeft(x - Width() / 2);
	SetTop(y - Height() / 2);
}

void Button::Draw(SDL_Renderer* renderer) const
{
    // check if we have a valid texture
    if (mTex) {
        // draw textured rectangle
        SDL_RenderCopy(renderer, mTex->GetSDLTexture(), NULL, &mRect);
    } else {
        // draw solid rectangle
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &mRect);
    }
}

bool Button::Contains(int x, int y) const
{
    return x >= Left() && x < Right() && y >= Top() && y < Bottom();
}
