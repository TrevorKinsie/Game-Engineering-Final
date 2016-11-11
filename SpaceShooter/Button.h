#ifndef BUTTON_H_
#define BUTTON_H_

#include "Texture.h"

class Button
{
	SDL_Rect				mRect;
    Texture*                mTex;

public:
                            Button(Texture* tex);
                            Button(Texture* tex, int x, int y);

                            ~Button();

	int						Width() const		{ return mRect.w; }
	int						Height() const		{ return mRect.h; }

	int						Left() const		{ return mRect.x; }
	int						Top() const			{ return mRect.y; }
	int						Right() const		{ return mRect.x + mRect.w; }
	int						Bottom() const		{ return mRect.y + mRect.h; }

	SDL_Point				Center() const;

	void					SetLeft(int x)		{ mRect.x = x; }
	void					SetRight(int x)		{ mRect.x = x - mRect.w; }
	void					SetTop(int y)		{ mRect.y = y; }
	void					SetBottom(int y)	{ mRect.y = y - mRect.h; }

	void					SetWidth(int w)		{ mRect.w = w; }
	void					SetHeight(int h)	{ mRect.h = h; }

	void					SetCenter(int x, int y);

	void					Draw(SDL_Renderer* renderer) const;

    bool                    Contains(int x, int y) const;
};

#endif
