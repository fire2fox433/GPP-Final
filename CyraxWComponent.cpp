#include "CyraxWComponent.h"
#include <vector>
#include "bullet.h"

CyraxWComponent::CyraxWComponent(Game *cipher)
{
	bulletList.reserve(10);
	if (!WbulletTexture.initialize(cipher->getGraphics(), CYRAXW_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cyrax W image"));
}
CyraxWComponent::~CyraxWComponent()
{
	bulletList.clear();
}
void CyraxWComponent::update(float frameTime)
{
	for (int i = 0; i < bulletList.size(); i++)
	{
		bulletList[i]->update(frameTime);
		if (bulletList[i]->getActive())
		{
			if (bulletList[i]->getCurrRange() == 30)
			{
				bulletList[i]->setCurrentFrame(CyraxWComponentNS::WBULLET_END_FRAME);
				VECTOR2 newSpeed;
				if (bulletList[i]->getMotion()->getVelocity().x >= 0)
				{
					newSpeed.x = -CyraxWComponentNS::WBULLET_MAX_SPEED;
					newSpeed.y = 0;
				}
				else
				{
					newSpeed.x = CyraxWComponentNS::WBULLET_MAX_SPEED;
					newSpeed.y = 0;
				}
				bulletList[i]->setDirection(newSpeed);
			}
			if (bulletList[i]->getCurrRange() == CyraxWComponentNS::WBULLET_MAX_RANGE)
			{
				bulletList.erase(bulletList.begin() + i);
			}
		}
	}
}
void CyraxWComponent::draw()
{
	for (int i = 0; i < bulletList.size(); i++)
	{
		bulletList[i]->draw();

	}
}
void CyraxWComponent::releaseAll()
{
	WbulletTexture.onLostDevice();
}
void CyraxWComponent::resetAll()
{
	WbulletTexture.onResetDevice();
}

void CyraxWComponent::activate(bool facingRight, float x, float y, Game *cipher)
{
	Bullet *newBullet = new Bullet();
	newBullet->setBulletSprite(CyraxWComponentNS::WIDTH, CyraxWComponentNS::HEIGHT, CyraxWComponentNS::WBULLET_START_FRAME, CyraxWComponentNS::WBULLET_END_FRAME, 100);
	newBullet->setCurrentFrame(CyraxWComponentNS::WBULLET_START_FRAME);
	if (!newBullet->initialize(cipher, CyraxWComponentNS::WIDTH, CyraxWComponentNS::HEIGHT, CyraxWComponentNS::TEXTURE_COLS, &WbulletTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cyrax W"));
	}
	newBullet->setX(x);
	newBullet->setY(y);
	newBullet->setActive(true);	
	VECTOR2 direction;
	if (facingRight) //shoot right
	{
		direction.x = CyraxWComponentNS::WBULLET_MIN_SPEED;
		direction.y = CyraxWComponentNS::WBULLET_MIN_SPEED;
		newBullet->flipHorizontal(true);
		newBullet->setDirection(direction);
	}
	else if (!facingRight) //shoot left
	{
		direction.x = -CyraxWComponentNS::WBULLET_MIN_SPEED;
		direction.y = CyraxWComponentNS::WBULLET_MIN_SPEED;		
		newBullet->setDirection(direction);
	}
	bulletList.push_back(newBullet);
}