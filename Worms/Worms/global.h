#ifndef GLOBAL_H
#define GLOBAL_H

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <math.h>
#include "resource.h"
#include <time.h>

// ����������WNDWIDTH��WNDHEIGHTΪ���ڵĿ�͸�
#define TIMER_ID             1		//��ʱ��ID
#define TIMER_ELAPSE         10  	//��ʱ�����(ms)
#define WNDWIDTH             1200	//���ڵĿ�
#define WNDHEIGHT            740	//���ڵĸ�
#define TITLEBARHEIGHT       32		//��������

// ������Դ�ĳߴ�
#define SCENE_SIZE_X        1821  //�����Ŀ��
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
//������Ϸ����
#define INIT_SEALEVEL		 80		//��ʼ��ˮ�߶�
#define MAX_TERRIAN_NUM      1500	//���ؿ�����
#define GRAVITY				 15		//����
#define HERO_VEL_X			 2		//Ӣ��ˮƽ�ٶ�
#define HERO_VEL_Y			 5  	//Ӣ����ֱ�ٶ�
#define MAX_HERO_NUM         6		//Ӣ�������Ŀ
#define MAX_BANG_VEL         15     //����ڵ��ٶ�
#define MAX_BANG_RANGE       60     //���ɱ�˰뾶
#define MAX_ALLOWED_HEIGHT   1      //�����ͨ�����߶Ȳ�
#define MAX_LIFE_DROP        40   //���ɱ��ֵ
#define TERRIAN_START_POS    100    //������ʼλ��
#define GRAVITYX             10    //������ļ��ٶ�
// Ӣ�۽ṹ�壬Ӣ��λͼ��λ�á���С*/
typedef struct
{
	HBITMAP	hBmp;	//Ӣ��ͼƬ
	POINT	pos;	//Ӣ��
	POINT   vel;
	SIZE	size;
	int     curFrameIndex;
	int     maxFrameSize;
} Hero;

//�ڵ��ṹ��
typedef struct
{
	HBITMAP	hBmp;
	POINT	pos;
	POINT   vel;
	SIZE	size;
	int     curFrameIndex;
	int     maxFrameSize;
} Bang;

/*���νṹ�壬���η���λ�á���С*/
typedef struct
{
	HBITMAP hBmp;
	POINT	pos;
	SIZE    size;
} Terrian;

/*��ť�ṹ��*/
typedef struct
{
	HBITMAP	hBmp;	//��ťͼƬ
	POINT   pos;	//��ťλ��
	SIZE	size;	//��ť�ߴ�
	int	status;	//��ť״̬
}  GameButton;

/*��Ϸ״̬�ṹ��*/
typedef struct
{
	HBITMAP	hBmp;	//����ͼƬ
	int	status;	//��Ϸ״̬
}  GameStatus;

//���λ�ýṹ��
/*typedef struct
{
	int x;
	int y;
} POINT;*/

//��׼���ṹ��
typedef struct
{
	HBITMAP	hBmp;	//��׼��ͼƬ
	POINT   pos;	//��׼��λ��
	SIZE	size;	//��׼���ߴ�
} Gunsight;

//Ѫ���ṹ��
typedef struct
{
	SIZE size;
	POINT pos;
} Herolife;

//�������ṹ��
typedef struct
{
	SIZE size;
	POINT pos; 
} Force;
//�����б�ṹ��
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
// ȫ�ֺ���

/*************************************************
Fucntion : ����Ӣ������
Parameter:
posX��posY��ʾ�������Ͻǵ�����
sizeX��sizeY��ʾ���ε�size
hBmp��ʾλͼ���
curFrameIndex��ǰ֡
maxFrameSize���֡��
*************************************************/
Hero CreateHero(LONG posX, LONG posY, LONG sizeX, LONG sizeY, HBITMAP hBmp, int curFrameIndex, int maxFrameSize);

/*************************************************
Fucntion : ������Ϸ״̬
Parameter:
posX��posY��ʾ�������Ͻǵ�����
sizeX��sizeY��ʾ���ε�size
hBmp��ʾλͼ���
*************************************************/
GameButton CreateGameButton(LONG posX, LONG posY, LONG sizeX, LONG sizeY, HBITMAP hBmp, int status);

/*************************************************
Fucntion : ������������
Parameter:
posX��posY��ʾ�������Ͻǵ�����
sizeX��sizeY��ʾ���ε�size
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
