#pragma once
#ifndef _NECRIDRCOMPONENT_H               // Prevent multiple definitions if this 
#define _NECRIDRCOMPONENT_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "input.h"
#include "game.h"
#include "entity.h"


namespace NecridRComponentNS
{

}

class NecridRComponent
{
private:


public:
	NecridRComponent();
	void update(float frameTime, Entity &ent);
};
#endif