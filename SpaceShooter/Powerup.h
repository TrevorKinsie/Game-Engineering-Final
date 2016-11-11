#ifndef POWERUP_H_
#define POWERUP_H_

#include "Texture.h"
#include "Vec2.h"
#include <string>


enum PowerType {
	//This is just the regular type of shot that the player has
	NONE,

	// A powerup which will give the player a shot which shoots 3 bullets
	//each going in a different direction
	WIDESHOT,

	// Will shoot two missles instead of just one
	MULTI,
};

class Powerup
{
    const Texture*          mTex;
    Vec2                    mCenter;
    Vec2                    mVelocity;
	PowerType				mPower;

public:
                            Powerup(const Vec2& pos, const Texture* tex);
                            ~Powerup();

    const Vec2&             Center() const                  { return mCenter; }
    void                    SetCenter(const Vec2& pos)      { mCenter = pos; }
    void                    SetCenter(float x, float y)     { mCenter = Vec2(x, y); }

    const Vec2&             Velocity() const                { return mVelocity; }
    void                    SetVelocity(const Vec2& vel)    { mVelocity = vel; }
    void                    SetVelocity(float x, float y)   { mVelocity = Vec2(x, y); }

	PowerType				GetPowerType() const			{ return mPower; }
	void					SetPowerType(PowerType power)	{ mPower = power; }

    float                   Width() const                   { return (float)mTex->GetWidth(); }
    float                   Height() const                  { return (float)mTex->GetHeight(); }

    float                   Left() const                    { return mCenter.x - 0.5f * Width(); }
    float                   Right() const                   { return mCenter.x + 0.5f * Width(); }
    float                   Top() const                     { return mCenter.y - 0.5f * Height(); }
    float                   Bottom() const                  { return mCenter.y + 0.5f * Height(); }

    void                    SetLeft(float x)                { mCenter.x = x + 0.5f * Width(); }
    void                    SetRight(float x)               { mCenter.x = x - 0.5f * Width(); }
    void                    SetTop(float y)                 { mCenter.y = y + 0.5f * Height(); }
    void                    SetBottom(float y)              { mCenter.y = y - 0.5f * Height(); }

    void					Update(float dt);

    void					Draw(SDL_Renderer* renderer) const;
};

#endif
