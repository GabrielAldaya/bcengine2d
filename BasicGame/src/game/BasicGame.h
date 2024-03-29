#ifndef BASIC_GAME_H
#define BASIC_GAME_H

#include "Engine.h"
#include "GameScene.h"

class BasicGame : public Game
{
public:

	// constructor / destructor
	BasicGame (HINSTANCE hInstance);
	~BasicGame ();

protected:

	bool OnStartUp();
	bool OnLoop();
	bool OnShutDown();

	void UpdateViewPortPos();

	//Escenas
	GameScene* m_pkGameScene;

};
#endif