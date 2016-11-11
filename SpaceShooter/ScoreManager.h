#ifndef SCOREMANAGER_H_
#define SCOREMANAGER_H_

#include <SDL.h>
#include <iostream>

class ScoreManager
{
	int				mScore;

public:
	ScoreManager();
	~ScoreManager();

	int			GetScore() const	{ return mScore; }
	void		SetScore(int score)	{ mScore = score; }
	void		PrintScore()		{ std::cout << "Score: " << mScore <<std::endl; }
};

#endif