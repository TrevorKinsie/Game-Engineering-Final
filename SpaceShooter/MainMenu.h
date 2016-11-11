#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include "GameState.h"
#include "Button.h"
#include "Texture.h"

class MainMenu : public GameState
{
    Texture*            mBtnNewTex;
    Texture*            mBtnResumeTex;
    Texture*            mBtnExitTex;
	Texture*			mBtnBossTex;

    Button*             mBtnNew;
	Button*				mBtnBoss;
    Button*             mBtnResume;
    Button*             mBtnExit;

public:
                        MainMenu(GameManager* game);
                        ~MainMenu() override;

    bool                Initialize() override;
    void                Shutdown() override;

    void                Update(float dt) override;
    void                Draw(SDL_Renderer* renderer) override;

    void		        OnKeyDown(const SDL_KeyboardEvent& kbe) override;
    void		        OnMouseDown(const SDL_MouseButtonEvent& mbe) override;
};

#endif
