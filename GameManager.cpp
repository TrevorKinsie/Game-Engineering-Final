#include <iostream>

#include "GameManager.h"

GameManager::GameManager()
    : mGameplayState(NULL)
    , mMainMenuState(NULL)
    , mCurrentState(NULL)
{
    // nothing to do: all setup should be done in Initialize method
}

GameManager::~GameManager()
{
    // nothing to do: all cleanup should be done in Shutdown method
}

bool GameManager::Initialize()
{
    std::cout << "Initializing game" << std::endl;

    // set some window properties
    System::SetWindowSize(480, 640);
    System::SetWindowTitle("Space Shootah!");

    //
    // create all game states
    //
    mGameplayState = new Game(this);
    if (!mGameplayState->Initialize()) {
        return false;
    }

    mMainMenuState = new MainMenu(this);
    if (!mMainMenuState->Initialize()) {
        return false;
    }

	mGameBossState = new GameBoss(this);
	if (!mGameBossState->Initialize()){
		return false;
	}

    // set initial state
    mCurrentState = mMainMenuState;

	return true;
}

void GameManager::Shutdown()
{
    std::cout << "Shutting down game" << std::endl;

    mGameplayState->Shutdown();
    mMainMenuState->Shutdown();


    delete mGameplayState;
    delete mMainMenuState;
}

void GameManager::Draw(SDL_Renderer* renderer)
{
    mCurrentState->Draw(renderer);
}

void GameManager::Update(float dt)
{
    mCurrentState->Update(dt);
}

void GameManager::OnKeyDown(const SDL_KeyboardEvent& kbe)
{
    mCurrentState->OnKeyDown(kbe);
}

void GameManager::OnKeyUp(const SDL_KeyboardEvent& kbe)
{
    mCurrentState->OnKeyUp(kbe);
}

void GameManager::OnMouseDown(const SDL_MouseButtonEvent& mbe)
{
    mCurrentState->OnMouseDown(mbe);
}

void GameManager::OnMouseUp(const SDL_MouseButtonEvent& mbe)
{
    mCurrentState->OnMouseUp(mbe);
}

void GameManager::OnMouseMotion(const SDL_MouseMotionEvent& mme)
{
    mCurrentState->OnMouseMotion(mme);
}

void GameManager::OnWindowResized(int w, int h)
{
    //std::cout << "Window resized to " << w << 'x' << h << std::endl;

    mCurrentState->OnWindowResized(w, h);
}

void GameManager::EnterMainMenu()
{
    mCurrentState = mMainMenuState;
}

void GameManager::EnterGameplay()
{
    mCurrentState = mGameplayState;
}

void GameManager::EnterGameBoss()
{
	mCurrentState = mGameBossState;
}
