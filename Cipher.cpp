// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "Cipher.h"

//=============================================================================
// Constructor
//=============================================================================
Cipher::Cipher()
{}

//=============================================================================
// Destructor
//=============================================================================
Cipher::~Cipher()
{
	releaseAll();           // call onLostDevice() for every graphics item
	delete map1;
	for (std::vector<int>::size_type i = 0; i != characters.size(); i++) {
		delete characters[i];
	}
	map1 = NULL;
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Cipher::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
	cyrax = new Cyrax(this);
	cyrax->setType(1);
	necrid = new Necrid(this);
	necrid->setType(2);
	freid = new Freid(this);
	freid->setType(2);
	agent47 = new Agent47(this);
	agent47->setType(0);
	cyrax->setX(300);
	freid->setX(900);
	freid->setY(GAME_HEIGHT / 2 - necrid->getHeight()/2 );

	cyrax->setActive(true);
	//necrid->setActive(true);
	freid->setActive(true);
	agent47->setActive(true);

	characters.push_back(cyrax);
	characters.push_back(necrid);
	characters.push_back(freid);
	characters.push_back(agent47);
	
	if (typeid(characters[0]).name() == "class Cyrax")
	{
		cyrax = dynamic_cast<Cyrax*>(characters[0]);
	}
	else if (typeid(characters[0]).name() == "class Freid")
	{
		freid = dynamic_cast<Freid*>(characters[0]);
	}
	else if (typeid(characters[0]).name() == "class Agent47")
	{
		agent47 = dynamic_cast<Agent47*>(characters[0]);
	}
	else if (typeid(characters[0]).name() == "class Necrid")
	{
		necrid = dynamic_cast<Necrid*>(characters[0]);
	}
	if (typeid(characters[1]).name() == "class Cyrax")
	{
		cyrax = dynamic_cast<Cyrax*>(characters[1]);
	}
	else if (typeid(characters[1]).name() == "class Freid")
	{
		freid = dynamic_cast<Freid*>(characters[1]);
	}
	else if (typeid(characters[1]).name() == "class Agent47")
	{
		agent47 = dynamic_cast<Agent47*>(characters[1]);
	}
	else if (typeid(characters[1]).name() == "class Necrid")
	{
		necrid = dynamic_cast<Necrid*>(characters[1]);
	}
	//=============================================================================
	if (characters.size() > 2)
	{
		if (typeid(characters[2]).name() == "class Cyrax")
		{
			cyrax = dynamic_cast<Cyrax*>(characters[2]);
		}
		else if (typeid(characters[2]).name() == "class Freid")
		{
			freid = dynamic_cast<Freid*>(characters[2]);
		}
		else if (typeid(characters[2]).name() == "class Agent47")
		{
			agent47 = dynamic_cast<Agent47*>(characters[2]);
		}
		else if (typeid(characters[2]).name() == "class Necrid")
		{
			necrid = dynamic_cast<Necrid*>(characters[2]);
		}
	}
	//=============================================================================
	if (characters.size() > 3)
	{
		if (typeid(characters[3]).name() == "class Cyrax")
		{
			cyrax = dynamic_cast<Cyrax*>(characters[3]);
		}
		else if (typeid(characters[3]).name() == "class Freid")
		{
			freid = dynamic_cast<Freid*>(characters[3]);
		}
		else if (typeid(characters[3]).name() == "class Agent47")
		{
			agent47 = dynamic_cast<Agent47*>(characters[3]);
		}
		else if (typeid(characters[3]).name() == "class Necrid")
		{
			necrid = dynamic_cast<Necrid*>(characters[3]);
		}
	}
	

	map1 = new Map(0, this, characters);
	currentMode = 0;
	if (!instructionTexture.initialize(this->getGraphics(), INSTRUCTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instruction image"));
	if (!instruction.initialize(this, 1280, 720,1, &instructionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	return;
	
	if (audio.initialize() != S_OK) {
		throw (new GameError());
	}

	audio.playCue(BM_MUSIC);

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Cipher::update()
{
	if (currentMode == 0)
	{
		instruction.update(frameTime);
		if (input->getMouseLButton())
		{
			instruction.setActive(false);
			currentMode = 1;
		}
	}
	else if (currentMode == 1)
	{
		for (std::vector<int>::size_type i = 0; i != characters.size(); i++)
		{
			characters[i]->update(frameTime, this, &audio);
		}

		map1->update(frameTime, characters, &audio);
		audio.run();

		for (std::vector<int>::size_type i = 0; i != characters.size(); i++)
		{
			if (characters[i]->getHealthComponent()->getLives() <= 0 && characters[i]->getDeathConfirmed() == false)
			{
				if (fourthPos == NULL)
				{
					fourthPos = characters[i];
					characters[i]->setDeathConfirmed(true);
				}
				else if (thirdPos == NULL)
				{
					thirdPos = characters[i];
					characters[i]->setDeathConfirmed(true);
				}
				else if (secondPos == NULL)
				{
					secondPos = characters[i];
					characters[i]->setDeathConfirmed(true);
				}
				else if (firstPos == NULL)
				{
					firstPos = characters[i];
					characters[i]->setDeathConfirmed(true);
					currentMode = 2;
					winbackground.setActive(true);
					first.setActive(true);
					second.setActive(true);
					third.setActive(true);
					fourth.setActive(true);
					playerone.setActive(true);
					playertwo.setActive(true);
					ai1.setActive(true);
					ai2.setActive(true);
				}
			}
		}
	}
	else if (currentMode == 2)
	{
		winbackground.update(frameTime);
		first.update(frameTime);
		second.update(frameTime);
		third.update(frameTime);
		fourth.update(frameTime);
		playerone.update(frameTime);
		playertwo.update(frameTime);
		ai1.update(frameTime);
		ai2.update(frameTime);
		if (firstPos->getType() == 0)
		{
			if (ai1.getX() == 0 && ai1.getY()== 0)
			{
				ai1.setX(437.5 + 135 + 135);
				ai1.setY(180);
			}
			else
			{
				ai2.setX(437.5 + 135 + 135);
				ai2.setY(180);
			}
		}
		else if (firstPos->getType() == 1)
		{
			playerone.setX(437.5 + 135 + 135);
			playerone.setY(180);
		}
		else if (firstPos->getType() == 2)
		{
			playertwo.setX(437.5 + 135 + 135);
			playertwo.setY(180);
		}

		if (secondPos->getType() == 0)
		{
			if (ai1.getX() == 0 && ai1.getY() == 0)
			{
				ai1.setX(437.5 + 135 + 135);
				ai1.setY(180 + 2 * 45);
			}
			else
			{
				ai2.setX(437.5 + 135 + 135);
				ai2.setY(180 + 2 * 45);
			}
		}
		else if (secondPos->getType() == 1)
		{
			playerone.setX(437.5 + 135 + 135);
			playerone.setY(180 + 2 * 45);
		}
		else if (secondPos->getType() == 2)
		{
			playertwo.setX(437.5 + 135 + 135);
			playertwo.setY(180 + 2 * 45);
		}

		if (thirdPos->getType() == 0)
		{
			if (ai1.getX() == 0 && ai1.getY() == 0)
			{
				ai1.setX(437.5 + 135 + 135);
				ai1.setY(180 + 4 * 45);
			}
			else
			{
				ai2.setX(437.5 + 135 + 135);
				ai2.setY(180 + 4 * 45);
			}
		}
		else if (thirdPos->getType() == 1)
		{
			playerone.setX(437.5 + 135 + 135);
			playerone.setY(180 + 4 * 45);
		}
		else if (thirdPos->getType() == 2)
		{
			playertwo.setX(437.5 + 135 + 135);
			playertwo.setY(180 + 4 * 45);
		}

		if (fourthPos->getType() == 0)
		{
			if (ai1.getX() == 0 && ai1.getY() == 0)
			{
				ai1.setX(437.5 + 135 + 135);
				ai1.setY(180 + 6 * 45);
			}
			else
			{
				ai2.setX(437.5 + 135 + 135);
				ai2.setY(180 + 2 * 45);
			}
		}
		else if (fourthPos->getType() == 1)
		{
			playerone.setX(437.5 + 135 + 135);
			playerone.setY(180 + 6 * 45);
		}
		else if (fourthPos->getType() == 2)
		{
			playertwo.setX(437.5 + 135 + 135);
			playertwo.setY(180 + 6 * 45);
		}

		if (input->getMouseLButton())
		{
			currentMode = 3;
			credits.setActive(true);
		}

	}
	else if (currentMode == 3)
	{
		credits.update(frameTime);
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Cipher::ai()
{
	map1->ai(frameTime, characters);
}

//=============================================================================
// Handle collisions
//=============================================================================
void Cipher::collisions()
{
	map1->collisions(frameTime, characters);
	//=============================================================================
									//Cyrax//
	//=============================================================================
	//Cyrax Q
	for (std::vector<Bullet*>::iterator it = cyrax->getQcomponent()->getBulletList()->begin(); it != cyrax->getQcomponent()->getBulletList()->end();)
	{	
		VECTOR2 vec;
		if ((*it)->OldCollidesWith(*freid, vec))
		{
			delete (*it);
			it = cyrax->getQcomponent()->getBulletList()->erase(it);
			float damage = cyrax->getQcomponent()->getDamage();
			freid->knockback(damage, &audio);
			freid->setPassThroughWall(true);
			
		}
		else if ((*it)->OldCollidesWith(*agent47, vec))
		{
			delete (*it);
			it = cyrax->getQcomponent()->getBulletList()->erase(it);
			float damage = cyrax->getQcomponent()->getDamage();
			agent47->knockback(damage, &audio);
			agent47->setPassThroughWall(true);
		}
		else if ((*it)->OldCollidesWith(*necrid, vec))
		{
			delete (*it);
			it = cyrax->getQcomponent()->getBulletList()->erase(it);
			float damage = cyrax->getQcomponent()->getDamage();
			necrid->knockback(damage, &audio);
			necrid->setPassThroughWall(true);
		}
		else
		{
			it++;
		}
	}

	//Cyrax W
	for (std::vector<Bullet*>::iterator it = cyrax->getWcomponent()->getBulletList()->begin(); it != cyrax->getWcomponent()->getBulletList()->end();)
	{
		VECTOR2 vec;
		if ((*it)->OldCollidesWith(*freid, vec))
		{
			delete (*it);
			it = cyrax->getWcomponent()->getBulletList()->erase(it);
			float damage = cyrax->getWcomponent()->getDamage();
			freid->knockback(damage, &audio);
			freid->setPassThroughWall(true);
		}
		else if ((*it)->OldCollidesWith(*agent47, vec))
		{
			delete (*it);
			it = cyrax->getWcomponent()->getBulletList()->erase(it);
			float damage = cyrax->getWcomponent()->getDamage();
			agent47->knockback(damage, &audio);
			agent47->setPassThroughWall(true);
		}
		else if ((*it)->OldCollidesWith(*necrid, vec))
		{
			delete (*it);
			it = cyrax->getWcomponent()->getBulletList()->erase(it);
			float damage = cyrax->getWcomponent()->getDamage();
			necrid->knockback(damage, &audio);
			necrid->setPassThroughWall(true);
		}
		else
		{
			it++;
		}
	}
	//=============================================================================
									//Freid//
	//=============================================================================
	//Freid Q
	for (std::vector<Bullet*>::iterator it = freid->getQcomponent()->getArrowList()->begin(); it != freid->getQcomponent()->getArrowList()->end();)
	{
		VECTOR2 vec;
		if ((*it)->OldCollidesWith(*cyrax, vec))
		{
			delete (*it);
			it = freid->getQcomponent()->getArrowList()->erase(it);
			float damage = freid->getQcomponent()->getDamage();
			cyrax->knockback(damage, &audio);
			cyrax->setPassThroughWall(true);
		}
		else if ((*it)->OldCollidesWith(*agent47, vec))
		{
			delete (*it);
			it = freid->getQcomponent()->getArrowList()->erase(it);
			float damage = freid->getQcomponent()->getDamage();
			agent47->knockback(damage, &audio);
			agent47->setPassThroughWall(true);
		}
		else if ((*it)->OldCollidesWith(*necrid, vec))
		{
			delete (*it);
			it = freid->getQcomponent()->getArrowList()->erase(it);
			float damage = freid->getQcomponent()->getDamage();
			necrid->knockback(damage, &audio);
			necrid->setPassThroughWall(true);
		}
		else
		{
			it++;
		}
	}
	//Freid W
	for (std::vector<Bullet*>::iterator it = freid->getWcomponent()->getCometList()->begin(); it != freid->getWcomponent()->getCometList()->end();)
	{
		VECTOR2 vec;
		if ((*it)->OldCollidesWith(*cyrax, vec))
		{
			delete (*it);
			it = freid->getWcomponent()->getCometList()->erase(it);
			float damage = freid->getWcomponent()->getDamage();
			cyrax->knockback(damage, &audio);
			cyrax->setPassThroughWall(true);
		}
		else if ((*it)->OldCollidesWith(*agent47, vec))
		{
			delete (*it);
			it = freid->getWcomponent()->getCometList()->erase(it);
			float damage = freid->getWcomponent()->getDamage();
			agent47->knockback(damage, &audio);
			agent47->setPassThroughWall(true);
		}
		else if ((*it)->OldCollidesWith(*necrid, vec))
		{
			delete (*it);
			it = freid->getWcomponent()->getCometList()->erase(it);
			float damage = freid->getWcomponent()->getDamage();
			necrid->knockback(damage, &audio);
			necrid->setPassThroughWall(true);
		}
		else
		{
			it++;
		}
	}
	//=============================================================================
									//Agent 47//
	//=============================================================================
	
	//Agent 47 Q
	Bullet *punch = agent47->getQcomponent()->getPunch();
	if (punch->getActive())
	{ 
		VECTOR2 vec;
		if (punch->OldCollidesWith(*cyrax, vec))
		{
			float damage = agent47->getQcomponent()->hit();
			cyrax->knockback(damage, &audio);
			cyrax->setPassThroughWall(true);
		}
		if (punch->OldCollidesWith(*freid, vec))
		{
			float damage = agent47->getQcomponent()->hit();
			freid->knockback(damage, &audio);
			freid->setPassThroughWall(true);
		}
		if (punch->OldCollidesWith(*necrid, vec))
		{
			float damage = agent47->getQcomponent()->hit();
			necrid->knockback(damage, &audio);
			necrid->setPassThroughWall(true);
		}
	}

	//Agent 47 W
	Bullet *zap = agent47->getWcomponent()->getPunch();
	if (zap->getActive())
	{
		VECTOR2 vec;
		if (zap->OldCollidesWith(*cyrax, vec))
		{
			float damage = agent47->getWcomponent()->hit();
			cyrax->knockback(damage, &audio);
			cyrax->setPassThroughWall(true);
		}
		if (zap->OldCollidesWith(*freid, vec))
		{
			float damage = agent47->getWcomponent()->hit();
			freid->knockback(damage, &audio);
			freid->setPassThroughWall(true);
		}
		if (zap->OldCollidesWith(*necrid, vec))
		{
			float damage = agent47->getWcomponent()->hit();
			necrid->knockback(damage, &audio);
			necrid->setPassThroughWall(true);
		}
	}
	//=============================================================================
									//Necrid//
	//=============================================================================
	//Necrid Q
	for (std::vector<Bomb*>::iterator it = necrid->getQcomponent()->getBombList()->begin(); it != necrid->getQcomponent()->getBombList()->end();)
	{
		VECTOR2 vec;
		if ((*it)->OldCollidesWith(*cyrax, vec))
		{
			delete (*it);
			it = necrid->getQcomponent()->getBombList()->erase(it);
			float damage = necrid->getQcomponent()->getDamage();
			cyrax->knockback(damage, &audio);
			cyrax->setPassThroughWall(true);
		}
		else if ((*it)->OldCollidesWith(*freid, vec))
		{
			delete (*it);
			it = necrid->getQcomponent()->getBombList()->erase(it);
			float damage = necrid->getQcomponent()->getDamage();
			freid->knockback(damage, &audio);
			freid->setPassThroughWall(true);
		}
		else if ((*it)->OldCollidesWith(*agent47, vec))
		{
			delete (*it);
			it = necrid->getQcomponent()->getBombList()->erase(it);
			float damage = necrid->getQcomponent()->getDamage();
			agent47->knockback(damage, &audio);
			agent47->setPassThroughWall(true);
		}
		else
		{
			it++;
		}
	}

	//Necrid W
	for (std::vector<Bullet*>::iterator it = necrid->getWcomponent()->getRaindrops()->begin(); it != necrid->getWcomponent()->getRaindrops()->end();)
	{
		VECTOR2 vec;
		if ((*it)->OldCollidesWith(*cyrax, vec))
		{
			delete (*it);
			it = necrid->getWcomponent()->getRaindrops()->erase(it);
			float damage = necrid->getWcomponent()->getDamage();
			cyrax->knockback(damage, &audio);
			cyrax->setPassThroughWall(true);
		}
		else if ((*it)->OldCollidesWith(*freid, vec))
		{
			delete (*it);
			it = necrid->getWcomponent()->getRaindrops()->erase(it);
			float damage = necrid->getWcomponent()->getDamage();
			freid->knockback(damage, &audio);
			freid->setPassThroughWall(true);
		}
		else if ((*it)->OldCollidesWith(*agent47, vec))
		{
			delete (*it);
			it = necrid->getWcomponent()->getRaindrops()->erase(it);
			float damage = necrid->getWcomponent()->getDamage();
			agent47->knockback(damage, &audio);
			agent47->setPassThroughWall(true);
		}
		else
		{
			it++;
		}
	}
}

//=============================================================================
// Render game items
//=============================================================================
void Cipher::render()
{
	graphics->spriteBegin();                // begin 


	
	
	map1->draw();
	for (std::vector<int>::size_type i = 0; i != characters.size(); i++) {
		if (characters[i]->getActive())
		{
			characters[i]->draw();
		}
		
	}
	
	//draw here
	instruction.draw();
	winbackground.draw();
	first.draw();
	second.draw();
	third.draw();
	fourth.draw();
	playerone.draw();
	playertwo.draw();
	ai1.draw();
	ai2.draw();
	credits.draw();
	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Cipher::releaseAll()
{
	map1->releaseAll();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Cipher::resetAll()
{
	map1->resetAll();
	
	Game::resetAll();
	return;
}
