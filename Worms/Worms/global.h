#ifndef GLOBAL_H
#define GLOBAL_H

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <math.h>
#include "resource.h"
#include <time.h>

// 定义宏变量，WNDWIDTH、WNDHEIGHT为窗口的宽和高
#define TIMER_ID             1		//计时器ID
#define TIMER_ELAPSE         10  	//计时器间隔(ms)
#define WNDWIDTH             1200	//窗口的宽
#define WNDHEIGHT            740	//窗口的高
#define TITLEBARHEIGHT       32		//标题栏高

// 定义资源的尺寸
#define SCENE_SIZE_X        1821  //场景的宽度
#define HERO_SIZE_X         40
#define HERO_SIZE_Y          40
#define HERO_MAX_FRAME_NUM   3
#define GAME_START_BUTTON_SIZE_X   120
#define GAME_START_BUTTON_SIZE_Y   120
#define BANG_SIZE_X			20
#define BANG_SIZE_Y			20
#define MAX_BANG_NUM		2
#define BANG_MAX_FRAME_NUM   3
#define GUNSIGHT_SIZE_X     20
#define GUNSIGHT_SIZE_Y     20
#define GAME_RESTART_BUTTON_SIZE_X  108
#define GAME_RESTART_BUTTON_SIZE_Y  111
#define BANG_GIF_SIZE_X     120
#define BANG_GIF_SIZE_Y     87
#define CLOUD_SIZE_X        200
#define CLOUD_SIZE_Y        100
#define BALL_SIZE_X         25
#define BALL_SIZE_Y         25
#define WEAPON_SIZE_X       50
#define WEAPON_SIZE_Y       50
#define BALL_EFFECT_SIZE_X  120
#define BALL_EFFECT_SIZE_Y	150
//定义游戏常量
#define INIT_SEALEVEL		 80		//起始海水高度
#define MAX_TERRIAN_NUM      1500	//最大地块数量
#define GRAVITY				 15		//重力
#define HERO_VEL_X			 2		//英雄水平速度
#define HERO_VEL_Y			 5  	//英雄竖直速度
#define MAX_HERO_NUM         6		//英雄最多数目
#define MAX_BANG_VEL         15     //最大炮弹速度
#define MAX_BANG_RANGE       60     //最大杀伤半径
#define MAX_ALLOWED_HEIGHT   1      //允许可通过最大高度差
#define MAX_LIFE_DROP        40   //最大杀伤值
#define TERRIAN_START_POS    100    //地形起始位置
#define GRAVITYX             10    //风引起的加速度
// 英雄结构体，英雄位图、位置、大小*/
typedef struct
{
	HBITMAP	hBmp;	//英雄图片
	POINT	pos;	//英雄
	POINT   vel;
	SIZE	size;
	int     curFrameIndex;
	int     maxFrameSize;
} Hero;

//炮弹结构体
typedef struct
{
	HBITMAP	hBmp;
	POINT	pos;
	POINT   vel;
	SIZE	size;
	int     curFrameIndex;
	int     maxFrameSize;
} Bang;

/*地形结构体，地形方块位置、大小*/
typedef struct
{
	HBITMAP hBmp;
	POINT	pos;
	SIZE    size;
} Terrian;

/*按钮结构体*/
typedef struct
{
	HBITMAP	hBmp;	//按钮图片
	POINT   pos;	//按钮位置
	SIZE	size;	//按钮尺寸
	int	status;	//按钮状态
}  GameButton;

/*游戏状态结构体*/
typedef struct
{
	HBITMAP	hBmp;	//背景图片
	int	status;	//游戏状态
}  GameStatus;

//鼠标位置结构体
/*typedef struct
{
	int x;
	int y;
} POINT;*/

//瞄准器结构体
typedef struct
{
	HBITMAP	hBmp;	//瞄准器图片
	POINT   pos;	//瞄准器位置
	SIZE	size;	//瞄准器尺寸
} Gunsight;

//血条结构体
typedef struct
{
	SIZE size;
	POINT pos;
} Herolife;

//蓄力条结构体
typedef struct
{
	SIZE size;
	POINT pos; 
} Force;
//武器列表结构体
typedef struct
{
	HBITMAP	hBmp;
	SIZE size;
	POINT pos;
} Weapon;

typedef struct
{
	SIZE size;
	POINT pos;
}VirtialButton;

typedef struct
{
	SIZE size;
	POINT pos;
}Aid;
// 全局函数

/*************************************************
Fucntion : 创建英雄人物
Parameter:
posX、posY表示矩形左上角的坐标
sizeX、sizeY表示矩形的size
hBmp表示位图句柄
curFrameIndex当前帧
maxFrameSize最大帧率
*************************************************/
Hero CreateHero(LONG posX, LONG posY, LONG sizeX, LONG sizeY, HBITMAP hBmp, int curFrameIndex, int maxFrameSize);

/*************************************************
Fucntion : 创建游戏状态
Parameter:
posX、posY表示矩形左上角的坐标
sizeX、sizeY表示矩形的size
hBmp表示位图句柄
*************************************************/
GameButton CreateGameButton(LONG posX, LONG posY, LONG sizeX, LONG sizeY, HBITMAP hBmp, int status);

/*************************************************
Fucntion : 创建单个地形
Parameter:
posX、posY表示矩形左上角的坐标
sizeX、sizeY表示矩形的size
*************************************************/
Terrian CreateTerrian(LONG posX, LONG posY, LONG sizeX, LONG sizeY, HBITMAP hBmp);

Bang CreateBang(LONG posX, LONG posY, LONG sizeX, LONG sizeY, HBITMAP hBmp, int curFrameIndex, int maxFrameSize);

Gunsight CreateGunsight(LONG posX, LONG posY, LONG sizeX, LONG sizeY, HBITMAP hBmp);

Herolife Createherolife(LONG posX, LONG posY, LONG sizeX,LONG sizeY);

Force Createforce(LONG posX, LONG posY, LONG sizeX,LONG sizeY);

Weapon Createweapon(LONG posX, LONG posY, LONG sizeX,LONG sizeY, HBITMAP hBmp);

VirtialButton CreatVirtialButton(LONG sizex, LONG sizey, LONG posX, LONG posY);

Aid CreatAid(LONG sizex, LONG sizey, LONG posX, LONG posY);
#endif // !GLOBAL_H
