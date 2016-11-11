#include <iostream>
#include <cmath>

#include "GameManager.h"
#include "GameBoss.h"
#include "Random.h"
#include "Vec2.h"

using namespace std;

GameBoss::GameBoss(GameManager* game)
	: GameState(game)
	, mShuttleTex(NULL)
	, mShuttle2Tex(NULL)
	, mShuttle3Tex(NULL)
    , mShotTex(NULL)
	, mEnemyTex(NULL)
	, mEnemyShotTex(NULL)
	, mBossTex(NULL)
	, mBossHitTex(NULL)
	, mExplosionTex(NULL)
	, mPowerupTex(NULL)
	, mBgLayer0Tex(NULL)
	, mStartGameTex(NULL)
	, mLoseGameTex(NULL)
	, mPlayer(NULL)
	, mBoss(NULL)
	, mPlayerAlive(true)
	, mGameStart(true)
	, mPowerupSpawn(false)
	, mIsActive(false)
	, mEnemy()
    , mMissiles()
	, mExplosion()
	, mPowerup()
	, mMinSpawnDelay(0.0f)
	, mMaxSpawnDelay(0.0f)
	, mNextSpawnTime(0.0f)
	, mMinShotDelay(0.0f)
	, mMaxShotDelay(0.0f)
	, mNextShotTime(0.0f)
{
    // nothing to do: all setup should be done in Initialize method
}

GameBoss::~GameBoss()
{
    // nothing to do: all cleanup should be done in Shutdown method
}

bool GameBoss::Initialize()
{
    std::cout << "Initializing game" << std::endl;

    // set some window properties
    System::SetWindowSize(480, 640);
    System::SetWindowTitle("Space Shootah!");

    // get renderer
    SDL_Renderer* renderer = System::GetRenderer();

    //
    // load all textures
    //
	mShuttleTex = Texture::Load("media/shuttle.png", renderer);
    if (!mShuttleTex) {
        std::cerr << "*** Failed to load shuttle texture" << std::endl;
        return false;
    }
	
	mShuttle2Tex = Texture::Load("media/shuttle2.png", renderer);
	if (!mShuttle2Tex) {
		std::cerr << "*** Failed to load shuttle 3 texture" << std::endl;
		return false;
	}

	mShuttle3Tex = Texture::Load("media/shuttle3.png", renderer);
	if (!mShuttle3Tex) {
		std::cerr << "*** Failed to load shuttle 3 texture" << std::endl;
		return false;
	}

    mShotTex = Texture::Load("media/shot.png", renderer);
    if (!mShotTex) {
        std::cerr << "*** Failed to load shot texture" << std::endl;
        return false;
    }

	mBossTex = Texture::Load("media/boss.png", renderer);
	if (!mBossTex) {
		std::cerr << "*** Failed to load boss texture" << std::endl;
		return false;
	}

	mBossHitTex = Texture::Load("media/bossflash.png", renderer);
	if (!mBossHitTex) {
		std::cerr << "*** Failed to load bosshit texture" << std::endl;
		return false;
	}

	mEnemyTex = Texture::Load("media/alien2.png", renderer);
	if (!mEnemyTex) {
		std::cerr << "*** Failed to load alien texture" << std::endl;
		return false;
	}

	mEnemyShotTex = Texture::Load("media/shot2.png", renderer);
	if (!mEnemyShotTex) {
		std::cerr << "*** Failed to load shot2 texture" << std::endl;
		return false;
	}

	mExplosionTex = Texture::Load("media/explosion.tga", renderer);
	if (!mExplosionTex) {
		std::cerr << "*** Failed to load explosion texture" << std::endl;
		return false;
	}

	mPowerupTex = Texture::Load("media/powerup.png", renderer);
	if (!mPowerupTex){
		std::cerr << "**Failed to load powerup texture" << std::endl;
	}

	mBgLayer0Tex = Texture::Load("media/space.png", renderer);
	if (!mBgLayer0Tex) {
		std::cerr << "*** Failed to load background texture" << std::endl;
		return false;
	}
	mLoseGameTex = Texture::Load("media/lose.png", renderer);
	if (!mLoseGameTex) {
		std::cerr << "*** Failed to load lose game texture" << std::endl;
		return false;
	}

	mStartGameTex = Texture::Load("media/start.png", renderer);
	if (!mStartGameTex) {
		std::cerr << "*** Failed to load start game texture" << std::endl;
		return false;
	}
	//initialize rand

	InitRandom();

	//iniitalize spawner

	mMinSpawnDelay = 0.5f;
	mMaxSpawnDelay = 2.0;
	mNextSpawnTime = System::GetTime() + 1.0f;

	mMinShotDelay = 1.0f;
	mMaxShotDelay = 3.0f;
	mNextShotTime = System::GetTime() + 1.0f;

    //
    // spawn player
    //

    Vec2 spawnPos;
    spawnPos.x = 0.5f * System::GetWindowWidth();
    spawnPos.y = 0.75f * System::GetWindowHeight();

    mPlayer = new Player(spawnPos, mShuttleTex);
    mPlayer->SetSpeed(150.0f);

	spawnPos.y = 0;
	mBoss = new Boss(spawnPos, mBossTex);

	return true;
}

void GameBoss::Shutdown()
{
    std::cout << "Shutting down game" << std::endl;

    //
    // delete all entities
    //

    // delete player
    delete mPlayer;

	if (mBoss)
	{
		delete mBoss;
	}

    // delete missiles
    for (unsigned i = 0; i < mMissiles.size(); i++) {
        delete mMissiles[i];
    }
    mMissiles.clear();

	// delete enemies
	for (unsigned i = 0; i < mEnemy.size(); i++){
		delete mEnemy[i];
	}
	mEnemy.clear();
	
	// delete explosions
	for (unsigned i = 0; i < mExplosion.size(); i++) {
		delete mExplosion[i];
	}
	mExplosion.clear();

	//delete powerups
	for (unsigned i = 0; i < mPowerup.size(); i++) {
		delete mPowerup[i];
	}
	mPowerup.clear();
    //
    // destroy all textures
    //
    Texture::Destroy(mShuttleTex);
    Texture::Destroy(mShotTex);
	Texture::Destroy(mEnemyTex);
	Texture::Destroy(mExplosionTex);
	Texture::Destroy(mBgLayer0Tex);
	Texture::Destroy(mEnemyShotTex);
	Texture::Destroy(mLoseGameTex);
	Texture::Destroy(mStartGameTex);
	Texture::Destroy(mPowerupTex);

}

void GameBoss::LoadLevel()
{
	ClearLevel();

	Vec2 spawnPos;
	spawnPos.x = 0.5f * System::GetWindowWidth();
	spawnPos.y = 0.75f * System::GetWindowHeight();

	mPlayer = new Player(spawnPos, mShuttleTex);

	spawnPos.y = 0;

	mBoss = new Boss(spawnPos, mBossTex);


	mPlayer->SetSpeed(150.0f);
}

void GameBoss::ClearLevel()
{
	delete mPlayer;
	mPlayer = NULL;

	for (auto it = mMissiles.begin(); it != mMissiles.end(); it++) {
		Missile* m = *it;
		delete m;
	}
	mMissiles.clear();
}

void GameBoss::Draw(SDL_Renderer* renderer)
{
		// clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	if (mBgLayer0Tex)
	{
		SDL_RenderCopy(renderer, mBgLayer0Tex->GetSDLTexture(), NULL, NULL);
	}

	if (mBoss != NULL)
	{
		if (mBoss->Life() <= 0)
		{
			std::cout << "still here" << std::endl;
		}
		mBoss->Draw(renderer);
	}

	// draw missiles
	for (unsigned i = 0; i < mMissiles.size(); i++) {
		mMissiles[i]->Draw(renderer);
	}

	//draw enemies
	for (unsigned i = 0; i < mEnemy.size(); i++){
		mEnemy[i]->Draw(renderer);
	}

	for (unsigned i = 0; i < mExplosion.size(); i++) {
		mExplosion[i]->Draw(renderer);
	}

	for (unsigned i = 0; i < mPowerup.size(); i++) {
		mPowerup[i]->Draw(renderer);
	}
	
	mPlayer->Draw(renderer);
}

void GameBoss::Update(float dt)
{
    // get world bounds
    float worldLeft = WorldLeft();
    float worldRight = WorldRight();
    float worldTop = WorldTop();
    float worldBottom = WorldBottom();

    // update player

	PlayerLogic(dt, worldLeft, worldRight, worldTop, worldBottom);
	
    // update missiles

	MissleLogic(dt, worldLeft, worldRight, worldTop, worldBottom);

	// update enemies
    
	//EnemyLogic(dt, worldLeft, worldRight, worldTop, worldBottom);
		
	//update the explosions
	
	ExplosionLogic(dt, worldLeft, worldRight, worldTop, worldBottom);

	// update the powerup

	PowerUpLogic(dt, worldLeft, worldRight, worldTop, worldBottom);

	// update the boss

	if (mBoss != NULL)
	{
		BossLogic(dt, worldLeft, worldRight, worldTop, worldBottom);
	}

	// update spawner
	//get current time
	float t = System::GetTime();
	float time = System::GetTime();

	int timeInt = System::GetTime();
	int modTime = timeInt % 30;
	
	if (modTime == 3){mPowerupSpawn = true;}

	if ((modTime == 4) && mPowerupSpawn && mPlayer->GetPower() != WIDESHOT){
		float x = RandomFloat(WorldLeft() + 40.0f, WorldRight() - 40.0f);
		float y = 0;
		Powerup* powerup = new Powerup(Vec2(x, y), mPowerupTex);
		powerup->SetVelocity(0.0f, 50.0f);
		mPowerup.push_back(powerup);
		
		std::cout << "spawned" << std::endl;
		mPowerupSpawn = false;
	}

}

void GameBoss::PlayerLogic(float dt, float worldLeft, float worldRight, float worldTop, float worldBottom)
{
	mPlayer->Update(dt);

	// keep the player within world bounds
	if (mPlayer->Left() < worldLeft) {
		mPlayer->SetLeft(worldLeft);
	}
	else if (mPlayer->Right() > worldRight) {
		mPlayer->SetRight(worldRight);
	}
	if (mPlayer->Top() < worldTop) {
		mPlayer->SetTop(worldTop);
	}
	else if (mPlayer->Bottom() > worldBottom) {
		mPlayer->SetBottom(worldBottom);
	}
}

void GameBoss::MissleLogic(float dt, float worldLeft, float worldRight, float worldTop, float worldBottom)
{
	for (unsigned i = 0; i < mMissiles.size();) {
		Missile* m = mMissiles[i];
		bool deleted = false;
		// update missile
		m->Update(dt);
		for (unsigned k = 0; k < mMissiles.size();){
			if (i != k){
				Missile* m2 = mMissiles[k];
				bool mis1 = m->GetWho();
				bool mis2 = m2->GetWho();

				if (((mis1 == true) && (mis2 == false)) || ((mis1 == false) && (mis2 == true))){
					//this is checking to make sure that we are only comparing missles that are enemy vs player
					float distanceBetweenMissles = Distance(m2->Center(), m->Center());
					if (distanceBetweenMissles < 20.0f){

						float scale = 1.0f;
						float duration = 1.0f;
						Explosion* ex1 = new Explosion(m->Center(), mExplosionTex, scale, duration);
						mExplosion.push_back(ex1);
						Explosion* ex2 = new Explosion(m2->Center(), mExplosionTex, scale, duration);
						mExplosion.push_back(ex2);

						if (k > i){ //need to delete in array order
							delete m2;
							mMissiles[k] = mMissiles.back();
							mMissiles.pop_back();
							delete m;
							mMissiles[i] = mMissiles.back();
							mMissiles.pop_back();
						}
						else {
							delete m;
							mMissiles[i] = mMissiles.back();
							mMissiles.pop_back();
							delete m2;
							mMissiles[k] = mMissiles.back();
							mMissiles.pop_back();
						}

						deleted = true;
						break;
					}
					++k;
				}
				else {
					++k;
				}
			}
			else {

				++k;
			}
		}

		if (deleted){
			++i;
		}
		else {
			// remove the missile if it went off screen
			if (m->Left() > worldRight || m->Right() < worldLeft || m->Top() > worldBottom || m->Bottom() < worldTop) {
				// missile is out of world bounds: remove it
				delete m;
				mMissiles[i] = mMissiles.back();
				mMissiles.pop_back();
			}
			else {
				// missile is still within world bounds: keep it and move on to the next one
				float distMissilePlayer = Distance(m->Center(), mPlayer->Center());
				if (mPlayerAlive){
					if (m->GetWho() == false){
						if (distMissilePlayer < 25.0f){
							if (mPlayer->GetPower() == NONE)
							{
								std::cout << "how" << std::endl;
								mPlayerAlive = false;
							}
							else if (mPlayer->GetPower() == MULTI)
							{
								std::cout << "huh?" << std::endl;
								mPlayer->SetPower(NONE);
								mPlayer->SetTex(mShuttleTex);
							}
							else if (mPlayer->GetPower() == WIDESHOT)
							{
								mPlayer->SetPower(MULTI);
								mPlayer->SetTex(mShuttle2Tex);
							}
							delete m;
							mMissiles[i] = mMissiles.back();
							mMissiles.pop_back();

							float scale = 3.0f;
							float duration = 1.0f;
							Explosion* ex = new Explosion(mPlayer->Center(), mExplosionTex, scale, duration);
							mExplosion.push_back(ex);
						}
					}
				}


				++i;
			}
		}
	}
}

void GameBoss::BossLogic(float dt, float worldLeft, float worldRight, float worldTop, float worldBottom)
{
	mBoss->SetTex(mBossTex);
	mBoss->Update(dt);
	for (unsigned i = 0; i < mMissiles.size();) {
		Missile* m = mMissiles[i];
		if (m->GetWho()){
			float distanceMissle = Distance(mBoss->Center(), m->Center());
			if (distanceMissle < 100.0f) {
				mBoss->SetTex(mBossHitTex);
				int life = mBoss->Life();
				--life;
				mBoss->SetLife(life);
				delete m;
				mMissiles[i] = mMissiles.back();
				mMissiles.pop_back();

				std::cout << "Boss life: " << life << std::endl;
				break;
			}
			else {
				++i;
			}
		}
		else {
			++i;
		}
	}

	if (mBoss->Life() <= 0)
	{
		float scale = 10.0f;
		float duration = 2.0f;
		Explosion* ex = new Explosion(mBoss->Center(), mExplosionTex, scale, duration);
		mExplosion.push_back(ex);

		delete mBoss;
		mBoss = NULL;
	}
}

void GameBoss::EnemyLogic(float dt, float worldLeft, float worldRight, float worldTop, float worldBottom)
{
	float t = System::GetTime();
	bool shoot = false;
	/*if (t >= mNextShotTime){
		shoot = true;
		mNextShotTime = t + RandomFloat(mMinShotDelay, mMaxShotDelay);
	}*/
	for (unsigned i = 0; i < mEnemy.size();){
		Enemy* e = mEnemy[i];
		bool deadMissle = false;
		bool deadEnemy = false;
		bool createExplosion = false;

		//update enemy
		e->Update(dt);

		//enemies shoot back!
		// is it time to shoot?

		int randInt = (rand() % 100);

		if (randInt < 3){
			Missile* missile = new Missile(mEnemy[i]->Center(), mEnemyShotTex);
			missile->SetVelocity(0.0f, 400.0f);
			missile->SetWho(false);
			mMissiles.push_back(missile);
		}




		// remove the enemy if it went off screen
		if (e->Left() > worldRight || e->Right() < worldLeft || e->Top() > worldBottom){
			//enemy is out of world bounds: remove it
			delete e;
			mEnemy[i] = mEnemy.back();
			mEnemy.pop_back();
		}
		else {
			float distancePlayer = Distance(e->Center(), mPlayer->Center());
			//std::cout << "enemy" << distancePlayer << std::endl;
			if (mPlayerAlive){
				if (distancePlayer < 50.0f){
					mPlayerAlive = false;
					deadEnemy = true;
					createExplosion = true;

					float scale = 3.0f;
					float duration = 1.0f;
					Explosion* ex = new Explosion(mPlayer->Center(), mExplosionTex, scale, duration);
					mExplosion.push_back(ex);

				}
			}
			for (unsigned i = 0; i < mMissiles.size();) {
				Missile* m = mMissiles[i];
				if (m->GetWho()){
					float distanceMissle = Distance(e->Center(), m->Center());
					if (distanceMissle < 50.0f) {
						delete m;
						mMissiles[i] = mMissiles.back();
						mMissiles.pop_back();
						deadEnemy = true;
						createExplosion = true;
						break;
					}
					else {
						++i;
					}
				}
				else {
					++i;
				}
			}
			if (createExplosion){
				float scale = 2.0f;
				float duration = 1.0f;
				Explosion* ex = new Explosion(e->Center(), mExplosionTex, scale, duration);
				mExplosion.push_back(ex);
			}
			if (deadEnemy){
				delete e;
				mEnemy[i] = mEnemy.back();
				mEnemy.pop_back();
			}
			++i;
		}
	}
}

void GameBoss::ExplosionLogic(float dt, float worldLeft, float worldRight, float worldTop, float worldBottom)
{
	for (unsigned i = 0; i < mExplosion.size();) {
		Explosion* e = mExplosion[i];

		// update explosion
		e->Update(dt);

		// remove the explosion if it is finished
		if (e->IsFinished()) {
			delete e;
			mExplosion[i] = mExplosion.back();
			mExplosion.pop_back();
		}
		else {
			// keep current effect and move on to the next one
			++i;
		}
	}
}

void GameBoss::PowerUpLogic(float dt, float worldLeft, float worldRight, float worldTop, float worldBottom)
{
	for (unsigned i = 0; i < mPowerup.size();) {
		Powerup* p = mPowerup[i];
		// update powerup
		p->Update(dt);
		if (p->Left() > worldRight || p->Right() < worldLeft || p->Top() > worldBottom){
			//enemy is out of world bounds: remove it
			delete p;
			mPowerup[i] = mPowerup.back();
			mPowerup.pop_back();
			++i;
		}
		else
		{
			float distancePlayer = Distance(p->Center(), mPlayer->Center());
			//std::cout << "enemy" << distancePlayer << std::endl;
			if (mPlayerAlive){
				if (distancePlayer < 50.0f){
					if (mPlayer->GetPower() == NONE)
					{
						mPlayer->SetTex(mShuttle2Tex);
						mPlayer->SetPower(MULTI);
					}
					else
					{
						mPlayer->SetTex(mShuttle3Tex);
						mPlayer->SetPower(WIDESHOT);
					}
					delete p;
					mPowerup[i] = mPowerup.back();
					mPowerup.pop_back();
					++i;
					break;
				}
			}
			++i;
		}
	}
}

void GameBoss::OnKeyDown(const SDL_KeyboardEvent& kbe)
{
    switch (kbe.keysym.sym) {
    case SDLK_ESCAPE:
        // tell the system that we want to quit
        System::Quit();
        break;

	case SDLK_UP:
		// fire a missile
		if (mGameStart){
			if (mPlayer->GetPower() == NONE)
			{
				Missile* missile = new Missile(mPlayer->Center(), mShotTex);
				missile->SetVelocity(0.0f, -400.0f);
				missile->SetWho(true);
				mMissiles.push_back(missile);
			}
			else if (mPlayer->GetPower() == MULTI)
			{
				Vec2 shotPos = mPlayer->Center(); 
				shotPos.x -= 15;
				Missile* missile = new Missile(shotPos, mShotTex);
				missile->SetVelocity(0.0f, -400.0f);
				missile->SetWho(true);
				mMissiles.push_back(missile);
				shotPos.x += 30;

				Missile* missile2 = new Missile(shotPos, mShotTex);
				missile2->SetVelocity(0.0f, -400.0f);
				missile2->SetWho(true);
				mMissiles.push_back(missile2);
			}
			else if (mPlayer->GetPower() == WIDESHOT)
			{
				Vec2 shotPos = mPlayer->Center();
				Missile* missile = new Missile(shotPos, mShotTex);
				missile->SetVelocity(0.0f, -400.0f);
				missile->SetWho(true);
				mMissiles.push_back(missile);

				shotPos.x -= 15;
				Missile* missile2 = new Missile(shotPos, mShotTex);
				missile2->SetVelocity(-30.0f, -400.0f);
				missile2->SetWho(true);
				mMissiles.push_back(missile2);
				shotPos.x += 30;

				Missile* missile3 = new Missile(shotPos, mShotTex);
				missile3->SetVelocity(30.0f, -400.0f);
				missile3->SetWho(true);
				mMissiles.push_back(missile3);

			}
		}
		break;
	case SDLK_r:
		// reset the world
		mPlayerAlive = true;
		Shutdown();
		Initialize();
		std::cout << "Reset the Game" << std::endl;
		break;
	case SDLK_SPACE:
		if (mGameStart == false){
			mPlayerAlive = true;;
			mGameStart = true;
			Shutdown();
			Initialize();
		}
		break;
    }
}

void GameBoss::OnWindowResized(int w, int h)
{
    std::cout << "Window resized to " << w << 'x' << h << std::endl;
}
