#include "global.h"




Hero CreateHero(LONG posX, LONG posY, LONG sizeX, LONG sizeY, HBITMAP hBmp, int curFrameIndex, int maxFrameSize)
{
	Hero hero;
	hero.hBmp = hBmp;
	hero.pos.x = posX;
	hero.pos.y = posY;
	hero.vel.x = 0;
	hero.vel.y = 0;
	hero.size.cx = sizeX;
	hero.size.cy = sizeY;
	hero.curFrameIndex = curFrameIndex;
	hero.maxFrameSize = maxFrameSize;
	return hero;
}

GameButton CreateGameButton(LONG posX, LONG posY, LONG sizeX, LONG sizeY, HBITMAP hBmp, int status)
{
	GameButton gameButton;
	gameButton.pos.x = posX;
	gameButton.pos.y = posY;
	gameButton.size.cx = sizeX;
	gameButton.size.cy = sizeY;
	gameButton.hBmp = hBmp;
	gameButton.status = status;
	return gameButton;
}

Terrian CreateTerrian(LONG posX, LONG posY, LONG sizeX, LONG sizeY,
	HBITMAP hBlockBmp)
{
	Terrian terrian;
	terrian.pos.x = posX;
	terrian.pos.y = posY;
	terrian.size.cx = sizeX;
	terrian.size.cy = sizeY;
	terrian.hBmp = hBlockBmp;
	return terrian;
}

Bang CreateBang (LONG posX, LONG posY, LONG sizeX, LONG sizeY, HBITMAP hBmp, int curFrameIndex, int maxFrameSize)
{
	Bang bang;
	bang.hBmp = hBmp;
	bang.pos.x = posX;
	bang.pos.y = posY;
	bang.vel.x = 0;
	bang.vel.y = 0;
	bang.size.cx = sizeX;
	bang.size.cy = sizeY;
	bang.curFrameIndex = curFrameIndex;
	bang.maxFrameSize = maxFrameSize;
	return bang;
	
}


Gunsight CreateGunsight(LONG posX, LONG posY, LONG sizeX, LONG sizeY, HBITMAP hBmp)
{
	Gunsight gunsight;
	gunsight.pos.x = posX;
	gunsight.pos.y = posY;
	gunsight.size.cx = sizeX;
	gunsight.size.cy = sizeY;
	gunsight.hBmp = hBmp;
	return gunsight;
}

Herolife Createherolife(LONG posX, LONG posY, LONG sizeX,LONG sizeY)
{
	Herolife herolife;
	herolife.size.cx = sizeX;
	herolife.size.cy = sizeY;
	herolife.pos.x = posX;
	herolife.pos.y = posY;
	return herolife;
}

Force Createforce(LONG posX, LONG posY, LONG sizeX,LONG sizeY)
{
	Force force;
	force.size.cx = sizeX;
	force.size.cy = sizeY;
	force.pos.x = posX;
	force.pos.y = posY;
	return force;
}

Weapon Createweapon(LONG posX, LONG posY, LONG sizeX,LONG sizeY, HBITMAP hBmp)
{
	Weapon weapon;
	weapon.size.cx = sizeX;
	weapon.size.cy = sizeY;
	weapon.pos.x = posX;
	weapon.pos.y = posY;
	weapon.hBmp = hBmp;
	return weapon;
}

VirtialButton CreatVirtialButton(LONG sizex, LONG sizey, LONG posX, LONG posY)
{
	VirtialButton VButton;
	VButton.size.cx = sizex;
	VButton.size.cy = sizey;
	VButton.pos.x = posX;
	VButton.pos.y = posY;
	return VButton;
}

Aid CreatAid(LONG sizex, LONG sizey, LONG posX, LONG posY)
{
	Aid aid;
	aid.size.cx = sizex;
	aid.size.cy = sizey;
	aid.pos.x = posX;
	aid.pos.y = posY;
	return aid;
}