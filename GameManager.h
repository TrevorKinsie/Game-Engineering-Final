#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <vector>

#include "System.h"

#include "Game.h"
#include "GameBoss.h"
#include "MainMenu.h"

class GameManager
{
    Game*					mGameplayState;
	GameBoss*				mGameBossState;

    MainMenu*				mMainMenuState;

    GameState*              mCurrentState;

public:
                            GameManager();
                            ~GameManager();

    bool				    Initialize();
    void				    Shutdown();

    void				    Update(float dt);
    void				    Draw(SDL_Renderer* renderer);
    
    void				    OnWindowResized(int w, int h);
    void				    OnKeyDown(const SDL_KeyboardEvent& kbe);
    void				    OnKeyUp(const SDL_KeyboardEvent& kbe);
    void				    OnMouseDown(const SDL_MouseButtonEvent& mbe);
    void				    OnMouseUp(const SDL_MouseButtonEvent& mbe);
    void				    OnMouseMotion(const SDL_MouseMotionEvent& mme);

    Game*				    GetGameplayState() const    { return mGameplayState; }
	GameBoss*				GetGameBossState() const	{ return mGameBossState; }
    MainMenu*				GetMainMenuState() const    { return mMainMenuState; }

    void                    EnterMainMenu();
    void                    EnterGameplay();
	void					EnterGameBoss();
};

#endif
