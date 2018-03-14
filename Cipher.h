// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 spacewar.h v1.0

#ifndef _CIPHER_H             // Prevent multiple definitions if this 
#define _CIPHER_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "map.h"
#include "Cyrax.h"
#include "Freid.h"
#include "Agent47.h"
#include "Necrid.h"
#include <vector>
#include "characters.h"
#include "audio.h"
#include "instruction.h"
#include "first.h"
#include "second.h"
#include "third.h"
#include "fourth.h"
#include "WinBackground.h"
#include "ai.h"
#include "playerone.h"
#include "playertwo.h"
#include "credit.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class Cipher : public Game
{
private:
	// game items
	//TextureManager
	//Object
	Map *map1;
	
	Characters* firstPos;
	Characters* secondPos;
	Characters* thirdPos;
	Characters* fourthPos;


	Audio audio;
	TextureManager characterTexture;     // player texture
	TextureManager instructionTexture;
	TextureManager winbackgroundTexture;
	TextureManager firstTexture;
	TextureManager secondTexture;
	TextureManager thirdTexture;
	TextureManager fourthTexture;
	TextureManager playeroneTexture;
	TextureManager playertwoTexture;
	TextureManager aiTexture;
	TextureManager creditTexture;

	Credit credits;
	WinBackground winbackground;
	First first;
	Second second;
	Third third;
	Fourth fourth;
	Playerone playerone;
	Playertwo playertwo;
	AI ai1, ai2;

	Instruction instruction;
	Cyrax *cyrax;
	Freid *freid;
	Agent47 *agent47;
	Necrid *necrid;
	int currentMode;

	std::vector<Characters*> characters;

public:
	// Constructor
	Cipher();

	// Destructor
	virtual ~Cipher();

	// Initialize the game
	void initialize(HWND hwnd);
	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();
};

#endif
