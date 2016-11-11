#ifndef GAMEBOSS_H_
#define GAMEBOSS_H_

#include <SDL.h>

#include <vector>

#include "GameState.h"
#include "System.h"
#include "Player.h"
#include "Missile.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Powerup.h"
#include "Boss.h"


class GameBoss : public GameState
{
    Texture*                mShuttleTex;
	Texture*				mShuttle2Tex;
	Texture*				mShuttle3Tex;
    Texture*                mShotTex;
	Texture*				mEnemyShotTex;
	Texture*				mEnemyTex;
	Texture*				mBossTex;
	Texture*				mBossHitTex;
	Texture*				mExplosionTex;
	Texture*				mPowerupTex;
	Texture*				mBgLayer0Tex;
	Texture*				mStartGameTex;
	Texture*				mLoseGameTex;
	bool					mPlayerAlive;
	bool					mGameStart;
	bool					mPowerupSpawn;
	bool					mIsActive;

	Boss*					mBoss;
	Player*				    mPlayer;

    std::vector<Missile*>   mMissiles;
	std::vector<Enemy*>		mEnemy;
	std::vector<Explosion*>	mExplosion;
	std::vector<Powerup*>	mPowerup;

	float					mMinSpawnDelay;
	float					mMaxSpawnDelay;
	float					mNextSpawnTime;

	float					mMinShotDelay;
	float					mMaxShotDelay;
	float					mNextShotTime;

public:
                            GameBoss(GameManager* game);
                            ~GameBoss() override;

	bool                    IsActive() const        { return mIsActive; }

    bool				    Initialize() override;
    void				    Shutdown() override;

    void				    Update(float dt) override;
    void				    Draw(SDL_Renderer* renderer) override;

	void					LoadLevel();
	void					ClearLevel();

	void					PlayerLogic(float dt, float worldLeft, float worldRight, float worldTop, float worldBottom);
	void					MissleLogic(float dt, float worldLeft, float worldRight, float worldTop, float worldBottom);
	void					EnemyLogic(float dt, float worldLeft, float worldRight, float worldTop, float worldBottom);
	void					BossLogic(float dt, float worldLeft, float worldRight, float worldTop, float worldBottom);
	void					ExplosionLogic(float dt, float worldLeft, float worldRight, float worldTop, float worldBottom);
	void					PowerUpLogic(float dt, float worldLeft, float worldRight, float worldTop, float worldBottom);
	void					SpawnLogic(float dt, float worldLeft, float worldRight, float worldTop, float worldBottom);
    void				    OnWindowResized(int w, int h);
    void				    OnKeyDown(const SDL_KeyboardEvent& kbe) override;
	//void				    OnKeyUp(const SDL_KeyboardEvent& kbe) override;
	//void				    OnMouseDown(const SDL_MouseButtonEvent& mbe) override;
	//void				    OnMouseUp(const SDL_MouseButtonEvent& mbe) override;
	//void				    OnMouseMotion(const SDL_MouseMotionEvent& mme) override;

    float                   WorldLeft() const       { return 0.0f; }
    float                   WorldRight() const      { return (float)System::GetWindowWidth(); }
    float                   WorldTop() const        { return 0.0f; }
    float                   WorldBottom() const     { return (float)System::GetWindowHeight(); }
};

#endif
