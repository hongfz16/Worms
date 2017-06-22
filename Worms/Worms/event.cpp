#include "event.h"
#include "global.h"
#include "item.h"
int movex=0;
int sealevel=INIT_SEALEVEL;
int sealevelcount=0;
int here=0;
int herojumptimer[MAX_HERO_NUM]={0};
int h[MAX_TERRIAN_NUM];
int heronum=0;
int bangstatus=0;
int bangtimer=0;
int currentpointx=0;
int	currentpointy=0;
int have_banged=0;
int currentposx;
int currentposy;
int winner;
int force=0;
int force_status=0;
int fly[MAX_HERO_NUM]={0};
int herolife[MAX_HERO_NUM];
int flytst=0;
int bang_gif_count=0;
int bang_gif_status=0;
int gravityx=0;
int windcounter=0;
int herodead_team_a[MAX_HERO_NUM/2];  //hero编号为偶数的
int herodead_team_b[MAX_HERO_NUM/2];  //hero编号为奇数的
int herodead_all[MAX_HERO_NUM];
int hero01counter=0;
int hero01counter_status=0;
int hero02counter=0;
int hero02counter_status=0;
int hero03counter=0;
int hero03counter_status=0;
int wizard01counter=0;
int wizard02counter=0;
int wizard03counter=0;
int vkstatus=0;
int cloudposx=0;
int bangnum=1;
int banggif=0;
int ballgif=0;
int wizard_caught[3];
int text01status=0;
int text01count=0;
int text02status=0;
int text02count=0;
int text03status=0;
int text03count=0;
int text04status=1;
int text04count=0;
int text05status=0;
int text05count=0;
int move_status=0;
int movejudge=0;
int background_choose=0;
int aid_status=0;
int aidtimer=0;
int aid_vel=0;
//实时鼠标位置结构体
POINT point;

/*void crandt(int l,int r,int MOD)
{
	int mid=(l+r)>>1;
	h[mid]=(h[l]+h[r])>>1;
	if(r-l<=5)
	{
		for(int i=l+1;i<=r-1;++i)
		{
			h[i]=(h[r]-h[l])*(i-l+1)/(r-l+1)+h[l];
			//h[i]=(h[l]+h[r])>>1;
		}
		return ;
	}
	else
	{
		h[mid]+=rand()%MOD-(MOD>>1);
		crandt(l,mid,(int)((double)MOD*0.618));
		crandt(mid,r,(int)((double)MOD*0.618));
	}
}*/

VOID Init(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//加载急救箱位图
	m_aidBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_AID));
	//加载选择背景页面
	m_pick_background = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_PICKBACKGROUND));
	//加载hero头像
	m_heroicon[0] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HERO1ICON));
	m_heroicon[1] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HERO2ICON));
	m_heroicon[2] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HERO3ICON));
	//加载wizard头像
	m_wizardicon[0] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_WIZARD1ICON));
	m_wizardicon[1] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_WIZARD2ICON));
	m_wizardicon[2] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_WIZARD3ICON));
	//加载岩石位图
	m_rocket = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_ROCKET));
	//加载游戏结束界面背景图
	m_overbackground = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_OVER_BACKGROUND));
	//加载七张结果图片
	m_result[0] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HEROWIN0));
	m_result[1] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HEROWIN1));
	m_result[2] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HEROWIN2));
	m_result[3] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HEROWIN3));
	m_result[4] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_WIZARDWIN0));
	m_result[5] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_WIZARDWIN1));
	m_result[6] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_WIZARDWIN2));

	//加载pause页面
	m_pause_page = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_PAUSE_PAGE));
	//加载pause位图
	m_pause = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_PAUSE));
	//加载reload位图
	m_reload = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_RELOAD));
	//加载菜单界面
	m_menu = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_MENU));
	//加载帮助界面位图
	m_helppage = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HELPPAGE));
	//加载帮助按钮位图
	m_help = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HELP));
	//加载墓碑
	m_tomb = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_TOMB));
	//加载text4：精灵回合
	m_text05 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_TEXT05));
	//加载text4：hero回合
	m_text04 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_TEXT04));
	//加载text3：一个精灵死亡
	m_text03 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_TEXT03));
	//加载text2：一名hero死亡
	m_text02 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_TEXT02));
	//加载精灵球效果
	m_balleffect =  LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BALLEFFECT));
	//加载精灵球位图
	m_ball =  LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BALL));
	//加载云朵
	m_cloudBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_CLOUD));
	//加载大海
	m_seaBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_SEA));
	// 加载背景1位图
	m_hBackground01Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BACKGROUND01));

	// 加载背景2位图
	m_hBackground02Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BACKGROUND02));

	// 加载背景3位图
	m_hBackground03Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BACKGROUND03));

	// 加载背景4位图
	m_hBackground04Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BACKGROUND04));

	//加载指针位图
	m_pointerBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_POINTER));

	//加载wizard01右方向位图
	m_hWizard01Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_WIZARD01));

	//加载wizard01左方向位图
	m_hWizard01BmpRe = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_WIZARD01REVERSE));
	m_hWizard01replaceBmpRe = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_WIZARD01REVERSE));
	//加载wizard02右方向位图
	m_hWizard02Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_WIZARD02));

	//加载wizard02左方向位图
	m_hWizard02BmpRe = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_WIZARD02REVERSE));
	m_hWizard02replaceBmpRe = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_WIZARD02REVERSE));
	//加载wizard03位图
	m_hWizard03Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_WIZARD03));
	
	//加载文字1：hero捕获一只精灵
	m_text01 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_TEXT01));

	//加载hero01右方向位图
	m_hHero01Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HERO01));

	//加载hero01左方向位图
	m_hHero01BmpRe =  LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HERO01REVERSE));

	//加载hero02右方向位图
	m_hHero02Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HERO02));

	//加载hero02左方向位图
	m_hHero02BmpRe =  LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HERO02REVERSE));

	//加载hero03右方向位图
	m_hHero03Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HERO03));

	//加载hero03左方向位图
	m_hHero03BmpRe =  LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HERO03REVERSE));

	m_hHero03replaceBmpRe =   LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HERO03REVERSE));

	//加载hero04右方向位图
	m_hHero04Bmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HERO04));

	//加载hero04左方向位图
	m_hHero04BmpRe =  LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HERO04REVERSE));

	//加载爆炸动图位图
	m_hBangGif =  LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BANG_GIF));

	//加载restart位图
	m_hRestartButtonBmp =  LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_RESTART));

	//加载瞄准器位图
	m_hGunsightBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_GUNSIGHT));
	
	// 加载背景位图
	m_hBackgroundBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BACKGROUND));

	// 加载Hero位图
	m_hHeroBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HERO));

	//加载Hero反转位图
	m_hHeroBmpRe = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_HEROREVERSE));

	// 加载开始游戏按钮位图
	m_hGameStartButtonBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_START));

	// 加载炮弹视图
	m_hBangreplaceBmp = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
		MAKEINTRESOURCE(IDB_BANG01));

	for(int i=0;i<MAX_HERO_NUM;i++)
	herolife[i]=100;
	//创建血条
	int herolife_posx=75;
	for (int i=0;i<MAX_HERO_NUM;i+=2)
	{
		m_herolife[i]= Createherolife(herolife_posx , 30 , herolife[i] , 20);
		herolife_posx += 230;
	}
	herolife_posx=75;
	for (int i=1;i<MAX_HERO_NUM;i+=2)
	{
		m_herolife[i]= Createherolife(herolife_posx , 100 , herolife[i] , 20);
		herolife_posx += 230;
	}
	//创建蓄力条
	m_force=Createforce(m_hero[heronum].pos.x, m_hero[heronum].pos.y- m_hero[heronum].size.cy -10, force*HERO_SIZE_X/100, 5);

	// 创建英雄
	int heroposx=200;
	m_hero[0] = CreateHero(heroposx, 400, HERO_SIZE_X, HERO_SIZE_Y, m_hHero01Bmp, 0, HERO_MAX_FRAME_NUM);	
	heroposx+=100;
	m_hero[2] = CreateHero(heroposx, 400, HERO_SIZE_X, HERO_SIZE_Y, m_hHero02Bmp, 0, HERO_MAX_FRAME_NUM);	
	heroposx+=100;
	m_hero[4] = CreateHero(heroposx, 400, HERO_SIZE_X, HERO_SIZE_Y, m_hHero03Bmp, 0, HERO_MAX_FRAME_NUM);
	int wizardposx=1600;
	wizardposx-=100;
	m_hero[1] = CreateHero(wizardposx, 400, HERO_SIZE_X, HERO_SIZE_Y, m_hWizard01BmpRe, 0, HERO_MAX_FRAME_NUM);
	wizardposx-=100;
	m_hero[3] = CreateHero(wizardposx, 400, HERO_SIZE_X, HERO_SIZE_Y, m_hWizard02BmpRe, 0, HERO_MAX_FRAME_NUM);
	wizardposx-=100;
	m_hero[5] = CreateHero(wizardposx, 400, HERO_SIZE_X, HERO_SIZE_Y, m_hWizard03Bmp, 0, HERO_MAX_FRAME_NUM);
	// 创建地形
	srand((unsigned)time(NULL));
	int posx=TERRIAN_START_POS;
	int sizex=2;
	int sizey;
	h[0]=20;
	h[0]=h[MAX_TERRIAN_NUM-1]=70;
//	crandt(0,MAX_TERRIAN_NUM-1,120);
	int terriansinT;
	int terriansinH;
	int Tcount=0;
	int binary=1;
	/*int basehight;
	basehight = rand() % 400;*/
	terriansinT = rand() % 400;
	terriansinH = rand() % 100;
	int hight=500;
	for (int i=0;i<=MAX_TERRIAN_NUM-1;i++)
	{
		while(terriansinT<=200) terriansinT = rand() % 400;
		while(terriansinH<=25)	terriansinH = rand() % 100;
		if(i<=MAX_TERRIAN_NUM/2 && i%2==0)
			hight--;
		if(i>MAX_TERRIAN_NUM/2 && i%2==0)
			hight++;
		if(Tcount<terriansinT/2)
		{
			sizey= binary * terriansinH * (double)(sin(double(2*3.14/terriansinT)*Tcount)) + hight;
			posx++;
			m_terrian[i] = CreateTerrian(posx , 740-sizey , sizex, sizey, NULL);
			Tcount++;
		}
		else
		{
			/*do{
			basehight = rand() % 400;
			}while (basehight<=350);*/
			binary=-binary;
			terriansinT = rand() % 400;
			terriansinH = rand() % 100;
			Tcount=0;
			i--;
		}

	}
	// 创建武器列表
	m_weapon[0] = Createweapon(700,50,WEAPON_SIZE_X,WEAPON_SIZE_Y, m_hBangreplaceBmp);
	m_weapon[1] = Createweapon(700 + WEAPON_SIZE_X + 20 , 50 , WEAPON_SIZE_X,WEAPON_SIZE_Y, m_ball);
	// 创建游戏开始按钮
	m_gameStartButton = CreateGameButton(525, 500, GAME_START_BUTTON_SIZE_X, GAME_START_BUTTON_SIZE_Y, m_hGameStartButtonBmp, 0);
	//创建游戏RESTART按钮
	m_gamgRestartButton = CreateGameButton(650,500, GAME_RESTART_BUTTON_SIZE_X, GAME_RESTART_BUTTON_SIZE_Y, m_reload, 0);
	m_gamgRestartButton2 = CreateGameButton(650,500, GAME_START_BUTTON_SIZE_X,GAME_START_BUTTON_SIZE_Y, m_reload, 0);
	//创建游戏帮助按钮
	m_helpButton = CreateGameButton(650, 500, GAME_START_BUTTON_SIZE_X, GAME_START_BUTTON_SIZE_Y, m_help, 0);
	//创建从帮助界面开始游戏的按钮
	m_help_startButton = CreateGameButton(100, 480, GAME_START_BUTTON_SIZE_X, GAME_START_BUTTON_SIZE_Y, m_hGameStartButtonBmp, 0);
	//创建菜单按钮
	m_menuButton = CreateGameButton(525, 500,  GAME_START_BUTTON_SIZE_X, GAME_START_BUTTON_SIZE_Y, m_menu, 0);
	//创建pause按钮
	m_pauseButton = CreateGameButton(1000, 0,  GAME_START_BUTTON_SIZE_X, GAME_START_BUTTON_SIZE_Y, m_pause, 0);
	//创建暂停界面虚拟按键-返回游戏
	m_VB01 = CreatVirtialButton (271,81,441,266);
	//创建暂停界面虚拟按键-残忍离开
	m_VB02 = CreatVirtialButton (271,81,441,501);
	//创建瞄准器
	m_gunsight= CreateGunsight(0,0, GUNSIGHT_SIZE_X , GUNSIGHT_SIZE_Y ,m_hGunsightBmp);
	//创建急救箱
	m_aid = CreatAid(25, 25, 0, 0);
	//创建选择图片界面的按钮
	m_background01 = CreatVirtialButton(554,246,0,0);
	m_background02 = CreatVirtialButton(554,246,649,0);
	m_background03 = CreatVirtialButton(554,246,0,492);
	m_background04 = CreatVirtialButton(554,246,649,492);



	//设定初始游戏状态
	gameStatus.status=0;
	gameStatus.hBmp = m_hBackgroundBmp;

	//mciSendString(TEXT("open a.wav alias Mysong"), NULL, 0,NULL);  
  
	mciSendString(TEXT("play a.wav"), NULL, 0, NULL);  

}
VOID initial(HWND hWnd)
{	
	aid_vel=0;
	aidtimer=0;
	aid_status=0;
	background_choose=0;
	movejudge=0;
	move_status=0;
	text01status=0;
	text01count=0;
	text02status=0;
	text02count=0;
	text03status=0;
	text03count=0;
	text04status=0;
	text04count=0;
	text05status=0;
	text05count=0;
	wizard_caught[0]=0;
	wizard_caught[1]=0;
	wizard_caught[2]=0;
	movex=0;
	hero01counter=0;
	hero01counter_status=0;
	hero02counter=0;
	hero02counter_status=0;
	hero03counter=0;
	hero03counter_status=0;
	wizard01counter=0;
	wizard02counter=0;
	wizard03counter=0;
	srand((unsigned)time(NULL));
	for(int i=0;i<MAX_HERO_NUM/2;i++)
	{
		herodead_team_a[i]=0;  //hero编号为偶数的
		herodead_team_b[i]=0;  //hero编号为奇数的
	}
	for(int i=0;i<MAX_HERO_NUM;i++)
	{
		herodead_all[i]=0;
		herolife[i]=100;
	}
		gravityx=0;
	bang_gif_status=0;
	bang_gif_count=0;
	sealevel=INIT_SEALEVEL;
	sealevelcount=0;
	here=0;
	for (int i=0;i<MAX_HERO_NUM;i++)
	fly[i]=0;
	flytst=0;

	for(int i=0;i<MAX_HERO_NUM;i++)
	herolife[i]=100;
	//创建血条
	int herolife_posx=75;
	for (int i=0;i<MAX_HERO_NUM;i+=2)
	{
		m_herolife[i]= Createherolife(herolife_posx , 30 , herolife[i] , 20);
		herolife_posx += 230;
	}
	herolife_posx=75;
	for (int i=1;i<MAX_HERO_NUM;i+=2)
	{
		m_herolife[i]= Createherolife(herolife_posx , 100 , herolife[i] , 20);
		herolife_posx += 230;
	}
	//创建蓄力条
	m_force=Createforce(m_hero[heronum].pos.x, m_hero[heronum].pos.y- m_hero[heronum].size.cy -10, force*HERO_SIZE_X/100, 5);

	// 创建英雄
	int heroposx=200;
	m_hero[0] = CreateHero(heroposx, 400, HERO_SIZE_X, HERO_SIZE_Y, m_hHero01Bmp, 0, HERO_MAX_FRAME_NUM);	
	heroposx+=100;
	m_hero[2] = CreateHero(heroposx, 400, HERO_SIZE_X, HERO_SIZE_Y, m_hHero02Bmp, 0, HERO_MAX_FRAME_NUM);	
	heroposx+=100;
	m_hero[4] = CreateHero(heroposx, 400, HERO_SIZE_X, HERO_SIZE_Y, m_hHero03Bmp, 0, HERO_MAX_FRAME_NUM);
	int wizardposx=1600;
	wizardposx-=100;
	m_hero[1] = CreateHero(wizardposx, 400, HERO_SIZE_X, HERO_SIZE_Y, m_hWizard01BmpRe, 0, HERO_MAX_FRAME_NUM);
	wizardposx-=100;
	m_hero[3] = CreateHero(wizardposx, 400, HERO_SIZE_X, HERO_SIZE_Y, m_hWizard02BmpRe, 0, HERO_MAX_FRAME_NUM);
	wizardposx-=100;
	m_hero[5] = CreateHero(wizardposx, 400, HERO_SIZE_X, HERO_SIZE_Y, m_hWizard03Bmp, 0, HERO_MAX_FRAME_NUM);
	// 创建地形
	srand((unsigned)time(NULL));
	int posx=TERRIAN_START_POS;
	int sizex=2;
	int sizey;
	h[0]=20;
	h[0]=h[MAX_TERRIAN_NUM-1]=70;
//	crandt(0,MAX_TERRIAN_NUM-1,120);
	int terriansinT;
	int terriansinH;
	int Tcount=0;
	int binary=1;
	/*int basehight;
	basehight = rand() % 400;*/
	terriansinT = rand() % 400;
	terriansinH = rand() % 100;
	int hight=500;
	for (int i=0;i<=MAX_TERRIAN_NUM-1;i++)
	{
		while(terriansinT<=200) terriansinT = rand() % 400;
		while(terriansinH<=25)	terriansinH = rand() % 100;
		if(i<=MAX_TERRIAN_NUM/2 && i%2==0)
			hight--;
		if(i>MAX_TERRIAN_NUM/2 && i%2==0)
			hight++;
		if(Tcount<terriansinT/2)
		{
			sizey= binary * terriansinH * (double)(sin(double(2*3.14/terriansinT)*Tcount)) + hight;
			posx++;
			m_terrian[i] = CreateTerrian(posx , 740-sizey , sizex, sizey, NULL);
			Tcount++;
		}
		else
		{
			/*do{
			basehight = rand() % 400;
			}while (basehight<=350);*/
			binary=-binary;
			terriansinT = rand() % 400;
			terriansinH = rand() % 100;
			Tcount=0;
			i--;
		}

	}
	// 创建武器列表
	m_weapon[0] = Createweapon(700,50,WEAPON_SIZE_X,WEAPON_SIZE_Y, m_hBangreplaceBmp);
	m_weapon[1] = Createweapon(700 + WEAPON_SIZE_X + 20 , 50 , WEAPON_SIZE_X,WEAPON_SIZE_Y, m_ball);
	// 创建游戏开始按钮
	m_gameStartButton = CreateGameButton(525, 500, GAME_START_BUTTON_SIZE_X, GAME_START_BUTTON_SIZE_Y, m_hGameStartButtonBmp, 0);
	//创建游戏RESTART按钮
	m_gamgRestartButton = CreateGameButton(650,500, GAME_RESTART_BUTTON_SIZE_X, GAME_RESTART_BUTTON_SIZE_Y, m_reload, 0);
	m_gamgRestartButton2 = CreateGameButton(650,500, GAME_START_BUTTON_SIZE_X,GAME_START_BUTTON_SIZE_Y, m_reload, 0);
	//创建游戏帮助按钮
	m_helpButton = CreateGameButton(650, 500, GAME_START_BUTTON_SIZE_X, GAME_START_BUTTON_SIZE_Y, m_help, 0);
	//创建从帮助界面开始游戏的按钮
	m_help_startButton = CreateGameButton(100, 480, GAME_START_BUTTON_SIZE_X, GAME_START_BUTTON_SIZE_Y, m_hGameStartButtonBmp, 0);
	//创建菜单按钮
	m_menuButton = CreateGameButton(525, 500,  GAME_START_BUTTON_SIZE_X, GAME_START_BUTTON_SIZE_Y, m_menu, 0);
	//创建pause按钮
	m_pauseButton = CreateGameButton(1000, 0,  GAME_START_BUTTON_SIZE_X, GAME_START_BUTTON_SIZE_Y, m_pause, 0);
	//创建暂停界面虚拟按键-返回游戏
	m_VB01 = CreatVirtialButton (271,81,441,266);
	//创建暂停界面虚拟按键-残忍离开
	m_VB02 = CreatVirtialButton (271,81,441,501);
	//创建瞄准器
	m_gunsight= CreateGunsight(0,0, GUNSIGHT_SIZE_X , GUNSIGHT_SIZE_Y ,m_hGunsightBmp);
	//创建选择图片界面的按钮
	m_background01 = CreatVirtialButton(554,246,0,0);
	m_background02 = CreatVirtialButton(554,246,649,0);
	m_background03 = CreatVirtialButton(554,246,0,492);
	m_background04 = CreatVirtialButton(554,246,649,492);
	//创建急救箱
	m_aid = CreatAid(25, 25, 0, 0);
	heronum=0;
}
VOID Render(HWND hWnd)
{
	//判断游戏状态
	switch(gameStatus.status)
	{
	case 0:
		//绘制开始界面
		Render_Start(hWnd);
		break;
	case 1:
		//绘制游戏界面
		Render_Game(hWnd);
		break;
	case 2:
		KillTimer(hWnd, TIMER_ID);
		Render_Over(hWnd);
		break;
	case 3: //帮助界面
		Render_help(hWnd);
		break;
	case 4: //暂停界面
		Render_Pause(hWnd);
		break;
	case 5:
		Render_pick(hWnd);
		break;
	default:
		break;
	}
}

VOID Render_pick(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	// 开始绘制
	hdc = BeginPaint(hWnd, &ps);

	HDC	hdcBmp, hdcBuffer;
	HBITMAP	cptBmp;

	cptBmp = CreateCompatibleBitmap(hdc, WNDWIDTH, WNDHEIGHT);
	hdcBmp = CreateCompatibleDC(hdc);
	hdcBuffer = CreateCompatibleDC(hdc);
	


	// 绘制背景到缓存
	SelectObject(hdcBuffer, cptBmp);
	SelectObject(hdcBmp, m_pick_background);
	BitBlt(hdcBuffer, 0, 0, WNDWIDTH, WNDHEIGHT,
		hdcBmp, 0, 0, SRCCOPY);

	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc, 0, 0, WNDWIDTH, WNDHEIGHT, hdcBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存
	DeleteObject(cptBmp);
	DeleteDC(hdcBuffer);
	DeleteDC(hdcBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);
}
VOID Render_Pause(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	// 开始绘制
	hdc = BeginPaint(hWnd, &ps);

	HDC	hdcBmp, hdcBuffer;
	HBITMAP	cptBmp;

	cptBmp = CreateCompatibleBitmap(hdc, WNDWIDTH, WNDHEIGHT);
	hdcBmp = CreateCompatibleDC(hdc);
	hdcBuffer = CreateCompatibleDC(hdc);
	


	// 绘制背景到缓存
	SelectObject(hdcBuffer, cptBmp);
	SelectObject(hdcBmp, m_pause_page);
	BitBlt(hdcBuffer, 0, 0, WNDWIDTH, WNDHEIGHT,
		hdcBmp, 0, 0, SRCCOPY);

	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc, 0, 0, WNDWIDTH, WNDHEIGHT, hdcBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存
	DeleteObject(cptBmp);
	DeleteDC(hdcBuffer);
	DeleteDC(hdcBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);
}
VOID Render_Start(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	// 开始绘制
	hdc = BeginPaint(hWnd, &ps);

	HDC	hdcBmp, hdcBuffer;
	HBITMAP	cptBmp;

	cptBmp = CreateCompatibleBitmap(hdc, WNDWIDTH, WNDHEIGHT);
	hdcBmp = CreateCompatibleDC(hdc);
	hdcBuffer = CreateCompatibleDC(hdc);
	


	// 绘制背景到缓存
	SelectObject(hdcBuffer, cptBmp);
	SelectObject(hdcBmp, gameStatus.hBmp);
	BitBlt(hdcBuffer, 0, 0, WNDWIDTH, WNDHEIGHT,
		hdcBmp, 0, 0, SRCCOPY);

	// 绘制开始按钮
	SelectObject(hdcBmp, m_gameStartButton.hBmp);
	TransparentBlt(hdcBuffer, m_gameStartButton.pos.x, m_gameStartButton.pos.y, m_gameStartButton.size.cx, m_gameStartButton.size.cy,
		hdcBmp, 0, 0,
		108, 109, RGB(255, 255, 255));
	//绘制帮助按钮
	SelectObject(hdcBmp, m_helpButton.hBmp);
	TransparentBlt(hdcBuffer, m_helpButton.pos.x, m_helpButton.pos.y, m_helpButton.size.cx, m_helpButton.size.cy,
		hdcBmp, 0, 0,
		108, 111, RGB(255, 255, 255));

	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc, 0, 0, WNDWIDTH, WNDHEIGHT, hdcBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存
	DeleteObject(cptBmp);
	DeleteDC(hdcBuffer);
	DeleteDC(hdcBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);
}

VOID Render_help(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	// 开始绘制
	hdc = BeginPaint(hWnd, &ps);

	HDC	hdcBmp, hdcBuffer;
	HBITMAP	cptBmp;

	cptBmp = CreateCompatibleBitmap(hdc, WNDWIDTH, WNDHEIGHT);
	hdcBmp = CreateCompatibleDC(hdc);
	hdcBuffer = CreateCompatibleDC(hdc);
	


	// 绘制背景到缓存
	SelectObject(hdcBuffer, cptBmp);
	SelectObject(hdcBmp, m_helppage);
	BitBlt(hdcBuffer, 0, 0, WNDWIDTH, WNDHEIGHT,
		hdcBmp, 0, 0, SRCCOPY);

	// 绘制开始按钮
	SelectObject(hdcBmp, m_help_startButton.hBmp);
	TransparentBlt(hdcBuffer,m_help_startButton.pos.x, m_help_startButton.pos.y, m_help_startButton.size.cx, m_help_startButton.size.cy,
		hdcBmp, 0, 0,
		108, 109, RGB(255, 255, 255));

	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc, 0, 0, WNDWIDTH, WNDHEIGHT, hdcBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存
	DeleteObject(cptBmp);
	DeleteDC(hdcBuffer);
	DeleteDC(hdcBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);
}

VOID Render_Game(HWND hWnd)
{
	if(bangstatus!=0)
	{
		if( m_bang[bangstatus-1].pos.x - WNDWIDTH / 2 >= 0 &&  m_bang[bangstatus-1].pos.x + WNDWIDTH / 2 <= SCENE_SIZE_X  )
		movex = m_bang[bangstatus-1].pos.x - WNDWIDTH / 2;
		if( m_bang[bangstatus-1].pos.x - WNDWIDTH / 2 < 0)
		{
			movex = 0;
		}
		if(m_bang[bangstatus-1].pos.x + WNDWIDTH / 2 > SCENE_SIZE_X)
		{
			movex = 621;
		}
	}
	else
	{
	if(abs(movex + WNDWIDTH/2 - m_hero[heronum].pos.x) > 10)
	{
	if(move_status==1 && movex <= 1821-WNDWIDTH)
		movex+=10;
	if(move_status==-1 && movex >= 0)
		movex-=10;
	if(m_hero[heronum].pos.x - WNDWIDTH / 2 >= 0 &&  m_hero[heronum].pos.x + WNDWIDTH / 2 <= SCENE_SIZE_X  )
	{
		if(m_hero[heronum].pos.x >= movex + WNDWIDTH/2 - 6 && m_hero[heronum].pos.x <= movex + WNDWIDTH/2 + 6)
		{
			move_status=0;
			movejudge=0;
		}
	}
	if( m_hero[heronum].pos.x - WNDWIDTH / 2 < 0)
	{
		if(movex < 5)
		{
			move_status=0;
			movejudge=0;
		}
	}
	if(m_hero[heronum].pos.x + WNDWIDTH / 2 > SCENE_SIZE_X)
	{
		if(movex > 616)
		{
			move_status=0;
			movejudge=0;
		}
	}
	if(movejudge==0)
	{
	if(vkstatus==0)
	{
		if(flytst==0 && bang_gif_status==0)
		{
			if( m_hero[heronum].pos.x - WNDWIDTH / 2 >= 0 && m_hero[heronum].pos.x + WNDWIDTH /2 <= SCENE_SIZE_X && m_hero[heronum].pos.x < movex + WNDWIDTH/2 - 6 )
			{move_status = -1; 	movejudge=1;}
			if( m_hero[heronum].pos.x - WNDWIDTH / 2 >= 0 && m_hero[heronum].pos.x + WNDWIDTH /2 <= SCENE_SIZE_X && m_hero[heronum].pos.x > movex + WNDWIDTH/2 + 6 )
			{move_status = 1; 	movejudge=1;}
			if( m_hero[heronum].pos.x - WNDWIDTH / 2 < 0 && movex>=5)
			{move_status = -1; 	movejudge=1;}
			if(m_hero[heronum].pos.x + WNDWIDTH / 2 > SCENE_SIZE_X && movex <= 616)
			{move_status = 1; 	movejudge=1;}
		}
	}
	}
	}
		else
		{
			if(vkstatus==0)
			{
				if(flytst==0 && bang_gif_status==0)
				{
					if( m_hero[heronum].pos.x - WNDWIDTH / 2 >= 0 &&  m_hero[heronum].pos.x + WNDWIDTH / 2 <= SCENE_SIZE_X  )
						movex = m_hero[heronum].pos.x - WNDWIDTH / 2;
					if( m_hero[heronum].pos.x - WNDWIDTH / 2 < 0)
					{
						movex = 0;
					}
					if(m_hero[heronum].pos.x + WNDWIDTH / 2 > SCENE_SIZE_X)
					{
						movex = 621;
					}
				}
			}
		}
	}

	PAINTSTRUCT ps;
	HDC hdc;
	// 开始绘制
	hdc = BeginPaint(hWnd, &ps);

	HDC	hdcBmp, hdcBuffer;
	HBITMAP	cptBmp;

	cptBmp = CreateCompatibleBitmap(hdc, SCENE_SIZE_X , WNDHEIGHT);
	hdcBmp = CreateCompatibleDC(hdc);
	hdcBuffer = CreateCompatibleDC(hdc);
	
	// 绘制背景到缓存
	SelectObject(hdcBuffer, cptBmp);
	if(background_choose==1)
		SelectObject(hdcBmp, m_hBackground01Bmp);
	if(background_choose==3)
		SelectObject(hdcBmp, m_hBackground02Bmp);
	if(background_choose==2)
		SelectObject(hdcBmp, m_hBackground03Bmp);
	if(background_choose==4)
		SelectObject(hdcBmp, m_hBackground04Bmp);
	BitBlt(hdcBuffer, 0, 0, SCENE_SIZE_X , WNDHEIGHT,
		hdcBmp, 0, 0, SRCCOPY);
	
	//绘制墓碑
	for (int i=0;i<MAX_HERO_NUM;i++)
	{
		if(i%2==1 && wizard_caught[i/2]==1) continue;
		if(herodead_all[i]==1)
		{
		SelectObject(hdcBmp, m_tomb);
			TransparentBlt(
				hdcBuffer,m_hero[i].pos.x - HERO_SIZE_X/2  , m_hero[i].pos.y - HERO_SIZE_Y/2 ,
				HERO_SIZE_X*3/2, HERO_SIZE_Y*3/2,
				hdcBmp, 0, 0, 175, 220,
					RGB(255, 255, 255)	
				);
		}
	}
	//绘制武器图标
	for(int i=0;i<=1;i++)
	{
		SelectObject(hdcBmp, m_weapon[i].hBmp);
		TransparentBlt(
			hdcBuffer,m_weapon[i].pos.x +movex , m_weapon[i].pos.y ,
			WEAPON_SIZE_X, WEAPON_SIZE_Y,
			hdcBmp, 0, 0, 540, 518,
			RGB(255, 255, 255)
	
			);
	}
	//绘制云朵
	if(windcounter/1000==0)
		cloudposx++;
	else if(windcounter/1000==2)
		cloudposx--;
	SelectObject(hdcBmp, m_cloudBmp);
		TransparentBlt(
			hdcBuffer, cloudposx, 100,
			CLOUD_SIZE_X, CLOUD_SIZE_Y,
			hdcBmp, 0, 0, 996, 599,
			RGB(255, 255, 255)
	
			);
	// 绘制Hero到缓存
	if(herodead_all[0]==0)
	{
		if(hero01counter_status==1)
		{
			hero01counter++;
			if(hero01counter==8)
				hero01counter=0;
		}
		SelectObject(hdcBmp, m_hero[0].hBmp);
		TransparentBlt(
			hdcBuffer, m_hero[0].pos.x, m_hero[0].pos.y,
			m_hero[0].size.cx, m_hero[0].size.cy,
			hdcBmp, 63*(hero01counter/2), 0, 63, 67,
			RGB(255, 255, 255)
	
			);
	}
	if(herodead_all[1]==0)
	{
		wizard01counter++;
		if(wizard01counter==24)
			wizard01counter=0;
		SelectObject(hdcBmp, m_hero[1].hBmp);
		TransparentBlt(
			hdcBuffer, m_hero[1].pos.x, m_hero[1].pos.y,
			m_hero[1].size.cx, m_hero[1].size.cy,
			hdcBmp,0,118*(wizard01counter/4), 100, 118,
			RGB(255, 255, 255)
		);
	}
	if(herodead_all[2]==0)
	{
		if(hero02counter_status==1)
		{
			hero02counter++;
			if(hero02counter==6)
				hero02counter=0;
		}
		SelectObject(hdcBmp, m_hero[2].hBmp);
		TransparentBlt(
			hdcBuffer, m_hero[2].pos.x, m_hero[2].pos.y,
			m_hero[2].size.cx, m_hero[2].size.cy,
			hdcBmp, 63*(hero02counter/2), 0, 63, 63,
			RGB(255, 255, 255)
		);
	}
	if(herodead_all[3]==0)
	{
		wizard02counter++;
		if(wizard02counter==24)
			wizard02counter=0;
		SelectObject(hdcBmp, m_hero[3].hBmp);
		TransparentBlt(
			hdcBuffer, m_hero[3].pos.x, m_hero[3].pos.y,
			m_hero[3].size.cx, m_hero[3].size.cy,
			hdcBmp,0,82*(wizard02counter/4), 70, 82,
			RGB(255, 255, 255)
		);
	}
	if(herodead_all[4]==0)
	{
		if(hero03counter_status==1)
		{
			hero03counter++;
			if(hero03counter==8)
				hero03counter=0;
		}
		SelectObject(hdcBmp, m_hero[4].hBmp);
		TransparentBlt(
			hdcBuffer, m_hero[4].pos.x, m_hero[4].pos.y,
			m_hero[4].size.cx, m_hero[4].size.cy,
			hdcBmp, 63*(hero03counter/2), 0, 63, 70,
			RGB(255, 255, 255)
		);
	}
	if(herodead_all[5]==0)
	{
		wizard03counter++;
		if(wizard03counter==16)
			wizard03counter=0;
		SelectObject(hdcBmp, m_hero[5].hBmp);
		TransparentBlt(
			hdcBuffer, m_hero[5].pos.x, m_hero[5].pos.y,
			m_hero[5].size.cx, m_hero[5].size.cy,
			hdcBmp,0,50*(wizard03counter/4), 50, 50,
			RGB(255, 255, 255)
		);
	}

	//绘制指针
	SelectObject(hdcBmp, m_pointerBmp);
		TransparentBlt(
			hdcBuffer,m_hero[heronum].pos.x, m_hero[heronum].pos.y - m_hero[heronum].size.cy,
			m_hero[heronum].size.cx, m_hero[heronum].size.cy,
			hdcBmp, 0, 0, 130, 130,
			RGB(255, 255, 255));
	//绘制指向武器的小箭头
		if(bangnum!=0)
		{
	SelectObject(hdcBmp, m_pointerBmp);
	TransparentBlt(
		hdcBuffer,m_weapon[bangnum-1].pos.x + 5 + movex, m_weapon[bangnum-1].pos.y - 20,
		m_hero[heronum].size.cx, m_hero[heronum].size.cy,
		hdcBmp, 0, 0, 130, 130,
		RGB(255, 255, 255));
		}
	//绘制炮弹
	if(bangstatus!=0 )
	{
		SelectObject(hdcBmp, m_bang[bangstatus-1].hBmp);
		TransparentBlt(
			hdcBuffer,m_bang[bangstatus-1].pos.x, m_bang[bangstatus-1].pos.y,
			m_bang[bangstatus-1].size.cx, m_bang[bangstatus-1].size.cy,
			hdcBmp, 0, 0,540, 518,
			RGB(255, 255, 255));
	}

	//绘制爆炸动图
	if(banggif==1)
	{
	if(bang_gif_status == 1 && bang_gif_count < 50 )
	{
		SelectObject(hdcBmp,m_hBangGif);
		TransparentBlt(
			hdcBuffer,m_bang[0].pos.x - BANG_GIF_SIZE_X/2, m_bang[0].pos.y ,
			BANG_GIF_SIZE_X, BANG_GIF_SIZE_Y,
			hdcBmp, 130, 296*(bang_gif_count/5) + 100, 109, 96 ,
			RGB(255, 255, 255 ));
		bang_gif_count++;
	}
	}

	if(ballgif==1)
	{
	if(bang_gif_status == 1 && bang_gif_count < 50 )
	{
		SelectObject(hdcBmp,m_balleffect);
		TransparentBlt(
			hdcBuffer,m_bang[1].pos.x - BALL_EFFECT_SIZE_X/2, m_bang[1].pos.y -BALL_EFFECT_SIZE_Y / 2,
			BALL_EFFECT_SIZE_X, BALL_EFFECT_SIZE_Y,
			hdcBmp, 192* (bang_gif_count/10), 0, 192, 192 ,
			RGB(255, 255, 255 ));
		bang_gif_count++;
	}
	}
	

	//绘制瞄准器	 
	//if (bangstatus!=0)
	
	GetCursorPos(&point);
	ScreenToClient(hWnd,&point);
	SelectObject(hdcBmp, m_gunsight.hBmp);
	point.x += movex;
	double point_to_hero = sqrt(double(((point.x - m_hero[heronum].pos.x)*(point.x - m_hero[heronum].pos.x))+
		((point.y - m_hero[heronum].pos.y)*(point.y - m_hero[heronum].pos.y))));
		TransparentBlt(
			hdcBuffer ,m_hero[heronum].pos.x + (point.x - m_hero[heronum].pos.x) / point_to_hero * 70 - m_gunsight.size.cx / 2, 
			m_hero[heronum].pos.y + (point.y - m_hero[heronum].pos.y) / point_to_hero * 70 - m_gunsight.size.cy / 2,
			m_gunsight.size.cx , m_gunsight.size.cy,
			hdcBmp, 0, 0, 500, 500,
			RGB(255, 255, 255));
	

	//绘制海洋
	SelectObject(hdcBuffer, GetStockObject(NULL_PEN));
	HBRUSH seaBrush = CreateSolidBrush(RGB(40, 150, 200));
	SelectObject(hdcBuffer, seaBrush);
	Rectangle(hdcBuffer, 0, WNDHEIGHT-sealevel ,SCENE_SIZE_X   ,WNDHEIGHT );
	DeleteObject(seaBrush);
	/*_BLENDFUNCTION blend;
	blend.AlphaFormat=AC_SRC_ALPHA;
	blend.BlendFlags=0;
	blend.BlendOp=AC_SRC_OVER;
	blend.SourceConstantAlpha=255;
	SelectObject(hdcBmp, m_seaBmp);
	GdiAlphaBlend(
		hdcBuffer , 0 , WNDHEIGHT - sealevel , WNDWIDTH , WNDHEIGHT ,
		hdcBmp , 0 , 0 ,1821 , 740 ,blend );*/


	
	// 绘制地形
	SelectObject(hdcBuffer, GetStockObject(NULL_PEN));
	HBRUSH terrianBrush = CreatePatternBrush(m_rocket);//CreateSolidBrush(RGB(223, 169, 103));
	SelectObject(hdcBuffer, terrianBrush);
	int k;
	for (k = 0; k < MAX_TERRIAN_NUM; ++k)
	{
		Terrian *terrian = &m_terrian[k];
		Rectangle(hdcBuffer, terrian->pos.x, terrian->pos.y,
			terrian->pos.x + terrian->size.cx, terrian->pos.y + terrian->size.cy);
	}
	DeleteObject(terrianBrush);

	//绘制血条
	SelectObject(hdcBuffer, GetStockObject(NULL_PEN));
	HBRUSH herolifeBrush = CreateSolidBrush(RGB(240, 0, 0));
	SelectObject(hdcBuffer, herolifeBrush);
	int kj;
	for (kj = 0; kj < MAX_HERO_NUM; kj+=2)
	{
		Herolife *herolife = &m_herolife[kj];
		Rectangle(hdcBuffer, herolife->pos.x + movex, herolife->pos.y,
			herolife->pos.x + herolife->size.cx + movex, herolife->pos.y + herolife->size.cy);
		SelectObject(hdcBmp, m_heroicon[kj/2]);
		TransparentBlt(
			hdcBuffer, herolife->pos.x + movex - 60, herolife->pos.y - 27,
			60, 75,
				hdcBmp, 0, 0, 60, 75,
			RGB(255, 255, 255));
	}
	DeleteObject(herolifeBrush);

	SelectObject(hdcBuffer, GetStockObject(NULL_PEN));
	HBRUSH herolifeBrush2 = CreateSolidBrush(RGB(255, 209, 43));
	SelectObject(hdcBuffer, herolifeBrush2);
	for (kj = 1; kj < MAX_HERO_NUM; kj+=2)
	{
		Herolife *herolife = &m_herolife[kj];
		Rectangle(hdcBuffer, herolife->pos.x + movex, herolife->pos.y,
			herolife->pos.x + herolife->size.cx + movex, herolife->pos.y + herolife->size.cy);
		SelectObject(hdcBmp, m_wizardicon[kj/2]);
		TransparentBlt(
			hdcBuffer, herolife->pos.x + movex - 60, herolife->pos.y - 27,
			60, 75,
				hdcBmp, 0, 0, 60, 75,
			RGB(255, 255, 255));
	}
	DeleteObject(herolifeBrush2);

	//绘制蓄力条
	SelectObject(hdcBuffer, GetStockObject(NULL_PEN));
	HBRUSH forceBrush = CreateSolidBrush(RGB(0, 0, 240));
	SelectObject(hdcBuffer, forceBrush);
	m_force.pos.x=m_hero[heronum].pos.x;
	m_force.pos.y=m_hero[heronum].pos.y - m_hero[heronum].size.cy -10;
	Force *force = &m_force;
	Rectangle(hdcBuffer, force->pos.x, force->pos.y,
		force->pos.x + force->size.cx * HERO_SIZE_X /100, force->pos.y + force->size.cy);
	DeleteObject(forceBrush);

	// 绘制分数
	/*TCHAR	szDist[20];
	szDist[0]=herodead_all[0]+'0';
	szDist[1]=herodead_all[1]+'0';
	szDist[2]=herodead_all[2]+'0';
	szDist[3]=herodead_all[3]+'0';
	szDist[4]=herodead_all[4]+'0';
	szDist[5]=herodead_all[5]+'0';
	szDist[6]=' ';
	szDist[7]=herodead_team_a[0]+'0';
	szDist[8]=herodead_team_a[1]+'0';
	szDist[9]=herodead_team_a[2]+'0';
	szDist[10]=' ';
	szDist[11]=herodead_team_b[0]+'0';
	szDist[12]=herodead_team_b[1]+'0';
	szDist[13]=herodead_team_b[2]+'0';
	szDist[14]=' ';
	szDist[15]=move_status+'0';
	szDist[16]=' ';
	szDist[17]=movejudge+'0';
	szDist[18]='\0';
	SetTextColor(hdcBuffer, RGB(0, 0, 0));
	SetBkMode(hdcBuffer, TRANSPARENT);
	//wsprintf(szDist, );
	TextOut(hdcBuffer, WNDWIDTH - 400 + movex, 15, szDist, _tcslen(szDist));*/

	//绘制‘weapon list’
	TCHAR	szDist[13];
	SetTextColor(hdcBuffer, RGB(0, 0, 0));
	SetBkMode(hdcBuffer, TRANSPARENT);
	wsprintf(szDist, _T("Weapon List"));
	TextOut(hdcBuffer, m_weapon[0].pos.x + 20 + movex, 15, szDist, _tcslen(szDist));

	//绘制文字1内容
	if(text01status==1&&text01count<=100)
	{
		text01count++;
		SelectObject(hdcBmp, m_text01);
		TransparentBlt(
			hdcBuffer,20 + movex, 200,
			270, 30,
				hdcBmp, 0, 0, 917, 111,
			RGB(255, 255, 255));
	}
	else
	{
		text01status=0;
		text01count=0;
	}
	//绘制文字2内容
	if(text02status==1&&text02count<=100)
	{
		text02count++;
		SelectObject(hdcBmp, m_text02);
		TransparentBlt(
			hdcBuffer,20 + movex, 300,
			160, 30,
				hdcBmp, 0, 0, 603, 114,
			RGB(255, 255, 255));
	}
	else
	{
		text02status=0;
		text02count=0;
	}
	//绘制文字3内容
	if(text03status==1&&text03count<=100)
	{
		text03count++;
		SelectObject(hdcBmp, m_text03);
		TransparentBlt(
			hdcBuffer,20 + movex, 400,
			150, 30,
				hdcBmp, 0, 0, 552, 125,
			RGB(255, 255, 255));
	}
	else
	{
		text03status=0;
		text03count=0;
	}
	//绘制文字4内容
	if(text04status==1&&text04count<=100)
	{
		text04count++;
		SelectObject(hdcBmp, m_text04);
		TransparentBlt(
			hdcBuffer,500 + movex, 150,
			200, 50,
				hdcBmp, 0, 0, 404, 110,
			RGB(255, 255, 255));
	}
	else
	{
		text04status=0;
		text04count=0;
	}
	//绘制文字5内容
	if(text05status==1&&text05count<=100)
	{
		text05count++;
		SelectObject(hdcBmp, m_text05);
		TransparentBlt(
			hdcBuffer,500 + movex, 150,
			200, 50,
				hdcBmp, 0, 0, 397, 116,
			RGB(255, 255, 255));
	}
	else
	{
		text05status=0;
		text05count=0;
	}

	//绘制pause按钮
	SelectObject(hdcBmp, m_pauseButton.hBmp);
		TransparentBlt(
			hdcBuffer,m_pauseButton.pos.x + movex ,m_pauseButton.pos.y,
			m_pauseButton.size.cx, m_pauseButton.size.cy,
				hdcBmp, 0, 0, 108, 111,
			RGB(255, 255, 255));

	//绘制急救箱
		if(aid_status==1)
		{
		SelectObject(hdcBmp, m_aidBmp);
		TransparentBlt(
			hdcBuffer, m_aid.pos.x , m_aid.pos.y,
			m_aid.size.cx, m_aid.size.cy,
				hdcBmp, 0, 0, 100, 100,
			RGB(255, 255, 255));
		}
	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc, 0, 0, WNDWIDTH, WNDHEIGHT, hdcBuffer,movex, 0, SRCCOPY);

	// 回收资源所占的内存
	DeleteObject(cptBmp);
	DeleteDC(hdcBuffer);
	DeleteDC(hdcBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);
}

VOID Render_Over(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	// 开始绘制
	hdc = BeginPaint(hWnd, &ps);

	HDC	hdcBmp, hdcBuffer;
	HBITMAP	cptBmp;

	cptBmp = CreateCompatibleBitmap(hdc, WNDWIDTH, WNDHEIGHT);
	hdcBmp = CreateCompatibleDC(hdc);
	hdcBuffer = CreateCompatibleDC(hdc);
	
	// 绘制背景到缓存
	SelectObject(hdcBuffer, cptBmp);
	SelectObject(hdcBmp,m_overbackground);
	BitBlt(hdcBuffer, 0, 0, WNDWIDTH, WNDHEIGHT,
		hdcBmp, 0, 0, SRCCOPY);

	// 绘制RESTART按钮
	SelectObject(hdcBmp, m_gamgRestartButton2.hBmp);
	TransparentBlt(hdcBuffer, m_gamgRestartButton2.pos.x, m_gamgRestartButton2.pos.y, 120,120,//m_gamgRestartButton2.size.cx, m_gamgRestartButton2.size.cy,
		hdcBmp, 0, 0,
		108, 111, RGB(255, 255, 255));

	//绘制menu按钮
	SelectObject(hdcBmp, m_menuButton.hBmp);
	TransparentBlt(hdcBuffer, m_menuButton.pos.x, m_menuButton.pos.y, 120,120,//m_menuButton.size.cx, m_menuButton.size.cy,
		hdcBmp, 0, 0,
		108,111, RGB(255, 255, 255));

	//绘制赢家信息
	TCHAR	szDist[100];
	SetTextColor(hdcBuffer, RGB(0, 0, 0));
	SetBkMode(hdcBuffer, TRANSPARENT);
	int wizard_caught_count=0;
	for(int i =0;i<3;i++)
	{
		if(wizard_caught[i]==1)
			wizard_caught_count++;
	}
	if(winner==0)
	{
		if(wizard_caught_count==0)
		{
			SelectObject(hdcBmp, m_result[0]);
			TransparentBlt(hdcBuffer, 200, 150, 800, 400,
				hdcBmp, 0, 0,
				800,400, RGB(0,0,0));
		}
		//wsprintf(szDist, _T("Heros are winners ! You have caught 0 wizards!"));
		if(wizard_caught_count==1)
		{
			SelectObject(hdcBmp, m_result[1]);
			TransparentBlt(hdcBuffer, 200, 150, 800, 400,
				hdcBmp, 0, 0,
				800,400, RGB(0,0,0));
		}
		//wsprintf(szDist, _T("Heros are winners ! You have caught 1 wizards!"));
		if(wizard_caught_count==2)
		{
			SelectObject(hdcBmp, m_result[2]);
			TransparentBlt(hdcBuffer, 200, 150, 800, 400,
				hdcBmp, 0, 0,
				800,400, RGB(0,0,0));
		}
		//wsprintf(szDist, _T("Heros are winners ! You have caught 2 wizards!"));
		if(wizard_caught_count==3)
		{
			SelectObject(hdcBmp, m_result[3]);
			TransparentBlt(hdcBuffer, 200, 150, 800, 400,
				hdcBmp, 0, 0,
				800,400, RGB(0,0,0));
		}
		//wsprintf(szDist, _T("Heros are winners ! You have caught 3 wizards!"));
	}
	else
	{
		if(wizard_caught_count==0)
		{
			SelectObject(hdcBmp, m_result[4]);
			TransparentBlt(hdcBuffer, 200, 150, 800, 400,
				hdcBmp, 0, 0,
				800,400, RGB(0,0,0));
		}
		if(wizard_caught_count==1)
		{
			SelectObject(hdcBmp, m_result[5]);
			TransparentBlt(hdcBuffer, 200, 150, 800, 400,
				hdcBmp, 0, 0,
				800,400, RGB(0,0,0));
		}
		if(wizard_caught_count==2)
		{
			SelectObject(hdcBmp, m_result[5]);
			TransparentBlt(hdcBuffer, 200, 150, 800, 400,
				hdcBmp, 0, 0,
				800,400, RGB(0,0,0));
		}
		//wsprintf(szDist, _T("Wizards are winners !"));
	}
	//TextOut(hdcBuffer, WNDWIDTH - 500, 15, szDist, _tcslen(szDist));

	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc, 0, 0, WNDWIDTH, WNDHEIGHT, hdcBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存
	DeleteObject(cptBmp);
	DeleteDC(hdcBuffer);
	DeleteDC(hdcBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);
	initial(hWnd);
}

VOID TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	for (int i=0;i<MAX_HERO_NUM;i++)
	{
		if(fly[i]==0)
		{
			
		if(herodead_all[i]==1)
			continue;
//		if(herocrashtestX(i) == -1 && herocrashtestYup(i) == -1 && herocrashtestYdown(i) == -1)
//		{
//			HeroUpdateX(i);
//			HeroUpdateY(i);
	
//		}
/*
		else if(herocrashtestYup(i) != -1)
		{
			m_hero[i].pos.y = m_terrian[herocrashtestYup(i)].pos.y - m_hero[i].size.cy;
			m_hero[i].vel.y=0;
			HeroUpdateX(i);
		}
		else if(herocrashtestYdown(i) != -1)
		{
			m_hero[i].vel.y=0;
			HeroUpdateX(i);
		}
		else if(herocrashtestX(i) != -1)
		{
			HeroUpdateY(i);
		}
*/
			if(herocrashtestYup(i) == -1 && herocrashtestYdown(i) == -1)
			{
				if(have_banged == 0)
				HeroUpdateY(i);
			}
			else
			{
				if(herocrashtestYup(i) != -1)
				{
					m_hero[i].pos.y = m_terrian[herocrashtestYup(i)].pos.y - m_hero[i].size.cy;
					m_hero[i].vel.y=0;
				//	HeroUpdateX(i);
				}
			/*	if(herocrashtestYdown(i) != -1)
			{
				m_hero[i].pos.y = m_terrian[herocrashtestYup(i)].pos.y;
				m_hero[i].vel.y=0;
			//	HeroUpdateX(i);
			}
		*/
			}
			if(herocrashtestX(i) == -1 )
			{
				if(have_banged == 0)
				HeroUpdateX(i);
			}
			else
			{
				int problem=herocrashtestX(i);
				if(m_terrian[problem+1].pos.y<=m_terrian[problem].pos.y + MAX_ALLOWED_HEIGHT
					|| m_terrian[problem+1].pos.y>=m_terrian[problem].pos.y-MAX_ALLOWED_HEIGHT)
				{
					HeroUpdateX(i);
					m_hero[i].pos.y=m_terrian[problem+1].pos.y - m_hero[i].size.cy ;
				}
			}
			}
		else
		{
			if(herocrashtestYup(i) == -1 && herocrashtestYdown(i) == -1)
			{
				if(have_banged == 0)
				HeroUpdateY(i);
				HeroUpdateX(i);
			}
			else
			{
				if(herocrashtestYup(i) != -1)
				{
					m_hero[i].pos.y = m_terrian[herocrashtestYup(i)].pos.y - m_hero[i].size.cy;
					m_hero[i].vel.y=0;
					m_hero[i].vel.x=0;
					fly[i]=0;
					flytst=0;
				}
	
			}
		}
	}
	
	
	
	
	if(force_status==1)
	{
		 ForceCount();
	}
	if(bangstatus!=0 )
	{
		if(bangcrashtestX(bangstatus-1)==-1
			&&bangcrashtestYup(bangstatus-1)==-1
			&&bangcrashtestYdown(bangstatus-1)==-1
			&&bang_out_range_judge(bangstatus-1)==0)
			BangUpdate();
		else if(bang_out_range_judge(bangstatus-1)==1)
		{
			/*do{
			heronum=(heronum+1)% MAX_HERO_NUM ;
			}while(herodead_all[heronum]==1);*/
			while(1)
			{
				heronum=(heronum+1)% MAX_HERO_NUM ;
				if(herodead_all[heronum]==0)
					break;
			}
			force=0;
			m_force.size.cx=force;
			have_banged=0;
			bangstatus=0;
	
		}
		else 
		{
			if(bangstatus==1)
				banggif=1;
			else if(bangstatus==2)
				ballgif=1;
			bang_gif_status=1;
			int k;
			if(bangcrashtestX(bangstatus-1)!=-1)
				k=bangcrashtestX(bangstatus-1);
			else if(bangcrashtestYup(bangstatus-1)!=-1)
				k=bangcrashtestYup(bangstatus-1);
			else if(bangcrashtestYdown(bangstatus-1)!=-1)
				k=bangcrashtestYdown(bangstatus-1);
			
			for(int i=k-MAX_BANG_RANGE ;(i<=k+MAX_BANG_RANGE)&&i<=MAX_TERRIAN_NUM ;i++)
			{
				if(bangstatus==2)
					break;
				if(i<0)
				{
					while(i<0)
					{
						i++;
					}
				}
				m_terrian[i].size.cy = m_terrian[i].size.cy - int(sqrt(double(MAX_BANG_RANGE*MAX_BANG_RANGE - (k-i)*(k-i))));
				m_terrian[i].pos.y=m_terrian[i].pos.y + int(sqrt(double(MAX_BANG_RANGE*MAX_BANG_RANGE - (k-i)*(k-i))));
			}
			for (int j=0;j<MAX_HERO_NUM;j++)
			{
				
				if(herodead_all[j]==1)
					continue;
				if (abs(m_hero[j].pos.x + m_hero[j].size.cx/2 - m_terrian[k].pos.x)<=MAX_BANG_RANGE )
				{
					double coefficient;
					coefficient = double((MAX_BANG_RANGE - abs(m_hero[j].pos.x + m_hero[j].size.cx/2 - m_terrian[k].pos.x))) / double(MAX_BANG_RANGE) ;
					m_herolife[j].size.cx -= coefficient * MAX_LIFE_DROP;
					
					if(bangstatus==1)
					{
					fly[j]=1;
					if(m_hero[j].pos.x + m_hero[j].size.cx/2 - m_terrian[k].pos.x <= 0)
						m_hero[j].vel.x = -HERO_VEL_X   /  2;
					else m_hero[j].vel.x = HERO_VEL_X   /  2;
					herojumptimer[j]=0;
					m_hero[j].vel.y = -HERO_VEL_Y;
					}
				}
			}
			bangstatus=0;
			for (int l=0;l<MAX_HERO_NUM;l++)
			{
				if(herodead_all[l]==1)
					continue;
				if(m_herolife[l].size.cx<=0)
					{
						if(l%2==1 && bangnum==2)
						{
							wizard_caught[l/2]=1;
							text01status=1;						
						}						
						if(l%2==1 && bangnum==1)
						{
							text03status=1;
						}
						if(l%2==0)
						{
							text02status=1;
						}
							m_herolife[l].size.cx=0;
						herodead_all[l]=1;
						if(l%2==0)
							herodead_team_a[l/2]=1;
						else
							herodead_team_b[(l-1)/2]=1;	
					}
			}
			/*do{
			heronum=(heronum+1)% MAX_HERO_NUM ;
			}while(herodead_all[heronum]==1);*/
			while(1)
			{
				heronum=(heronum+1)% MAX_HERO_NUM ;
				if(heronum%2==1)
				bangnum=1;
				if(herodead_all[heronum]==0)
					break;
			}
			if(heronum%2==0)
			{
				text04status=1;
				text05status=0;
			}
			if(heronum%2==1)
			{
				text05status=1;
				text04status=0;
			}
			force=0;
			m_force.size.cx=force;
			have_banged=0;
		}
	}
	if(bang_gif_count==50)
	{
		bang_gif_status = 0;
		bang_gif_count = 0;
		banggif=0;
		ballgif=0;
	}
	if(aid_status==0)
		aid_check();
	else
	{
		if(aid_crash()==-1)
			aid_update();
		if(aid_crash()!=-1)
		{
			//aid_vel=0;
			aidtimer=0;
			m_aid.pos.y = m_terrian[aid_crash()].pos.y - m_aid.size.cy;
		}
		if(m_aid.pos.y>=WNDHEIGHT)
			aid_status=0;
		hero_aid();
	}
	windchange();
	sealevelupdate();
	flytest();
	TerrianUpdate();
	GameStatusUpdate();
	hero_out_range_operate();
	heronum_check();
	InvalidateRect(hWnd, NULL, FALSE);
}
void heronum_check()
{
	int temp=heronum;
	while(1)
	{
		if(herodead_all[heronum]==0)
			break;
		heronum=(heronum+1)% MAX_HERO_NUM ;
		if(heronum%2==1)
				bangnum=1;
	}
	if(temp!=heronum)
	{
		if(heronum%2==0)
			{
				text04status=1;
				text05status=0;
			}
			if(heronum%2==1)
			{
				text05status=1;
				text04status=0;
			}
	}
}
void windchange()
{
	windcounter++;
	if(windcounter==3000)
	{
		windcounter=0;
	}
	if(windcounter/1000==0)
		gravityx = GRAVITYX;
	else if(windcounter/1000==1)
		gravityx=0;
	else 
		gravityx = - GRAVITYX;
}
void sealevelupdate()
{
	if(sealevelcount<=100)
	{
		sealevelcount++;
	}
	else
	{
		sealevel++;
		sealevelcount=0;
	}
}
void hero_out_range_operate()
{
	for (int i=0;i<MAX_HERO_NUM;i++)
	{
		if(herodead_all[i]==1)
			continue;
		if(m_hero[i].pos.x + m_hero[i].size.cx < 0)
		{
			m_hero[i].pos.x = 0;
			m_hero[i].pos.y = 0;
			m_hero[i].vel.x = - m_hero[i].vel.x;
		}
		if(m_hero[i].pos.x > SCENE_SIZE_X )
		{
			m_hero[i].pos.x = SCENE_SIZE_X  - m_hero[i].size.cx;
			m_hero[i].pos.y = 0;
			m_hero[i].vel.x = - m_hero[i].vel.x;
		}
		if(m_hero[i].pos.y + m_hero[i].size.cy * 3 / 4 > WNDHEIGHT - sealevel)
		{
			flytst=0;
			fly[i]=0;
			m_herolife[i].size.cx=0;
			if(i%2==0)
			{
				text02status=1;
			}
			if(i%2==1)
			{
				text03status=1;
			}
			m_hero[i].pos.x=0;
			m_hero[i].pos.y=WNDHEIGHT;
			/*do{
			heronum=(heronum+1)% MAX_HERO_NUM ;
			}while(herodead_all[heronum]==1);*/
			while(1)
			{
				if(herodead_all[heronum]==0)
					break;
				heronum=(heronum+1)% MAX_HERO_NUM ;
				if(heronum%2==1)
				bangnum=1;
			}
			herodead_all[i]=1;
			if(i%2==0)
				herodead_team_a[i/2]=1;
			else
				herodead_team_b[(i-1)/2]=1;	
			if(heronum%2==0)
			{
				text04status=1;
				text05status=0;
			}
			if(heronum%2==1)
			{
				text05status=1;
				text04status=0;
			}
			
		}
	}

}
int bang_out_range_judge(int i)
{
	if(m_bang[i].pos.x + m_bang[i].size.cx < 0
		|| m_bang[i].pos.x >SCENE_SIZE_X 
		|| m_bang[i].pos.y + m_bang[i].size.cy > WNDHEIGHT - sealevel)
	{
		return 1;
	}
	else 
		return 0;
}
int bangcrashtestX(int i)
{
	int x=-1;
	int k;
		for (k=0;k<MAX_TERRIAN_NUM;++k)
		{
			if((m_bang[i].pos.y < m_terrian[k].pos.y + m_terrian[k].size.cy)
				&&(m_bang[i].pos.y + m_bang[i].size.cy > m_terrian[k].pos.y))
			{
				if((m_bang[i].pos.x + m_bang[i].size.cx + m_bang[i].vel.x > m_terrian[k].pos.x)
					&&(m_bang[i].pos.x - m_bang[i].vel.x  < m_terrian[k].pos.x + m_terrian[k].size.cx))
				{
					x=k;
					break;
				}
			}
		}
	
	return x;
}
int bangcrashtestYup(int i)
{
	int x=-1;
	int k;
		for (k=0;k<MAX_TERRIAN_NUM;++k)
		{
			if((m_bang[i].pos.x < m_terrian[k].pos.x + m_terrian[k].size.cx)
			&&(m_bang[i].pos.x + m_bang[i].size.cx > m_terrian[k].pos.x))
			{
				if((m_bang[i].pos.y + m_bang[i].size.cy + (m_bang[i].vel.y + GRAVITY * herojumptimer[i] * TIMER_ELAPSE * 0.001) > m_terrian[k].pos.y)
					&&(m_bang[i].pos.y + m_bang[i].vel.y < m_terrian[k].pos.y))
				{
					x=k;
					break;
				}
			}
		}
	
	return x;
}
int bangcrashtestYdown(int i)
{
	int x=-1;
	int k;
		for (k=0;k<MAX_TERRIAN_NUM;++k)
		{
			if((m_bang[i].pos.x < m_terrian[k].pos.x + m_terrian[k].size.cx)
				&&(m_bang[i].pos.x + m_bang[i].size.cx > m_terrian[k].pos.x))
			{
				if((m_bang[i].pos.y + m_bang[i].size.cy + (m_bang[i].vel.y + GRAVITY * herojumptimer[i] * TIMER_ELAPSE * 0.001) > m_terrian[k].pos.y + m_terrian[k].size.cy)
					&&(m_bang[i].pos.y + m_bang[i].vel.y < m_terrian[k].pos.y + m_terrian[k].size.cy))
				{
					x=k;
					break;
				}
							
			}
		}
	/*	if(k<MAX_TERRIAN_NUM)
		{
			k++;
			while (((m_bang[i].pos.y + m_bang[i].size.cy + (m_bang[i].vel.y + GRAVITY * herojumptimer[i] * TIMER_ELAPSE * 0.001) > m_terrian[k].pos.y + m_terrian[k].size.cy)
				&&(m_bang[i].pos.y + m_bang[i].vel.y < m_terrian[k].pos.y + m_terrian[k].size.cy)))
				{
					k++;
				}
			x=k;
		}
	*/
		
	return x;
}
void flytest()
{
	for (int i=0;i<MAX_HERO_NUM;i++)
	{
		if(herodead_all[i]!=0) continue;
		if(fly[i]==1)
		{
			flytst=1;
			break;
		}
	}
}
int herocrashtestX(int i)
{
	int x=-1;
	int k;
	//for(int i=0;i<MAX_HERO_NUM;i++)
	
		for (k=0;k<MAX_TERRIAN_NUM;++k)
		{
			if((m_hero[i].pos.y < m_terrian[k].pos.y + m_terrian[k].size.cy)
				&&(m_hero[i].pos.y + m_hero[i].size.cy > m_terrian[k].pos.y))
			{
				if((m_hero[i].pos.x + m_hero[i].size.cx - HERO_SIZE_X / 4 + m_hero[i].vel.x > m_terrian[k].pos.x)
					&&(m_hero[i].pos.x + HERO_SIZE_X / 4 - m_hero[i].vel.x  < m_terrian[k].pos.x + m_terrian[k].size.cx))
				{
					x=k;
					break;
				}
			}
		}
	
	return x;
}
int herocrashtestYup(int i)
{
	int x=-1;
	int k;
		for (k=0;k<MAX_TERRIAN_NUM;++k)
		{
			if((m_hero[i].pos.x + HERO_SIZE_X / 4 < m_terrian[k].pos.x + m_terrian[k].size.cx)
			&&(m_hero[i].pos.x + m_hero[i].size.cx - HERO_SIZE_X / 4 > m_terrian[k].pos.x))
			{
				if((m_hero[i].pos.y + m_hero[i].size.cy + (m_hero[i].vel.y + GRAVITY * herojumptimer[i] * TIMER_ELAPSE * 0.001) > m_terrian[k].pos.y)
					&&(m_hero[i].pos.y + m_hero[i].vel.y < m_terrian[k].pos.y))
				{
					x=k;
					break;
				}
			}
		}
	
	return x;
}
int herocrashtestYdown(int i)
{
	int x=-1;
	int k;
		for (k=0;k<MAX_TERRIAN_NUM;++k)
		{
			if((m_hero[i].pos.x + HERO_SIZE_X / 4 < m_terrian[k].pos.x + m_terrian[k].size.cx)
				&&(m_hero[i].pos.x + m_hero[i].size.cx - HERO_SIZE_X / 4 > m_terrian[k].pos.x))
			{
				if((m_hero[i].pos.y + m_hero[i].size.cy + (m_hero[i].vel.y + GRAVITY * herojumptimer[i] * TIMER_ELAPSE * 0.001) > m_terrian[k].pos.y + m_terrian[k].size.cy)
					&&(m_hero[i].pos.y + m_hero[i].vel.y < m_terrian[k].pos.y + m_terrian[k].size.cy))
				{
					x=k;
					break;
				}
							
			}
		}
		if(k<MAX_TERRIAN_NUM)
		{
			k++;
			while (((m_hero[i].pos.y + m_hero[i].size.cy + (m_hero[i].vel.y + GRAVITY * herojumptimer[i] * TIMER_ELAPSE * 0.001) > m_terrian[k].pos.y + m_terrian[k].size.cy)
				&&(m_hero[i].pos.y + m_hero[i].vel.y < m_terrian[k].pos.y + m_terrian[k].size.cy)))
				{
					k++;
				}
			x=k;
		}
	
		
	return x;
}
VOID HeroUpdateX(int i)
{
	//for (int i=0;i<MAX_HERO_NUM;i++)
	
		m_hero[i].pos.x += m_hero[i].vel.x;
	
}

VOID HeroUpdateY(int i)
{
	//for (int i=0;i<MAX_HERO_NUM;i++)
	
		m_hero[i].pos.y += (m_hero[i].vel.y + GRAVITY * herojumptimer[i] * TIMER_ELAPSE * 0.001);
		if(herocrashtestX(i) == -1 && herocrashtestYup(i) == -1 && herocrashtestYdown(i) == -1)
			herojumptimer[i]++;
	
	// TODO
	//更新英雄位置、动作
}

VOID TerrianUpdate() 
{
	// TODO
	//更新地形
}

VOID GameStatusUpdate()
{
	int flaga=0;
	int flagb=0;
	// TODO
	//更新游戏状态
	for(int i=0;i<MAX_HERO_NUM/2;i++)
	{
		if(herodead_team_a[i]==0)
			flaga=1;
		if(herodead_team_b[i]==0)
			flagb=1;
	}
	if(flaga==0)
	{	
		winner=1;
		gameStatus.status=2;
	}
	if(flagb==0)
	{	
		winner=0;
		gameStatus.status=2;
	}
}

VOID BangUpdate()
{
	int current_vel=MAX_BANG_VEL*force/100;
	double lean;
	int a = -currentposx + currentpointx;
	int b = currentposy - currentpointy;
	lean = sqrt (double(a*a+b*b));
	m_bang[bangstatus-1].vel.x = (current_vel * a / lean) + gravityx * bangtimer * TIMER_ELAPSE * 0.001;
	m_bang[bangstatus-1].vel.y = ( -current_vel * b / lean) + GRAVITY * bangtimer * TIMER_ELAPSE * 0.001;
	m_bang[bangstatus-1].pos.x += m_bang[bangstatus-1].vel.x;
	m_bang[bangstatus-1].pos.y += m_bang[bangstatus-1].vel.y;
	bangtimer++;
} 

VOID ForceCount()
{
	if(force<=100)
	{
		force++;
		m_force.size.cx=force;
	}
}

VOID aid_check()
{
	//srand((unsigned)time(NULL));
	int a;
	a = rand()%(100000);
	if(a >= 0 && a <=1000)
	{
		aid_status=1;
		if(a%2==0)
		m_aid.pos.x=200+a;
		else
			m_aid.pos.x=1500-a;
		m_aid.pos.y=100;
		aidtimer=0;
		aid_vel=0;
	}
}
VOID aid_update()
{
	//aid_vel += GRAVITY * aidtimer * TIMER_ELAPSE * 0.001;
	aid_vel=10;
	m_aid.pos.y += 10;
	//aidtimer++;
}
int aid_crash()
{
	int x=-1;
	int k;
		for (k=0;k<MAX_TERRIAN_NUM;++k)
		{
			if((m_aid.pos.x + HERO_SIZE_X / 4 < m_terrian[k].pos.x + m_terrian[k].size.cx)
			&&(m_aid.pos.x + m_aid.size.cx - HERO_SIZE_X / 4 > m_terrian[k].pos.x))
			{
				if((m_aid.pos.y + m_aid.size.cy + (aid_vel)> m_terrian[k].pos.y)//+ GRAVITY * aidtimer * TIMER_ELAPSE * 0.001) > m_terrian[k].pos.y)
					&&(m_aid.pos.y + aid_vel < m_terrian[k].pos.y))
				{
					x=k;
					break;
				}
			}
		}
	
	return x;
}
VOID hero_aid()
{
	int k;
	//for(int i=0;i<MAX_HERO_NUM;i++)
	
		if((m_hero[heronum].pos.y < m_aid.pos.y + m_aid.size.cy)
			&&(m_hero[heronum].pos.y + m_hero[heronum].size.cy > m_aid.pos.y))
		{
			if((m_hero[heronum].pos.x + m_hero[heronum].size.cx - HERO_SIZE_X / 4 + m_hero[heronum].vel.x > m_aid.pos.x)
				&&(m_hero[heronum].pos.x + HERO_SIZE_X / 4 - m_hero[heronum].vel.x  < m_aid.pos.x + m_aid.size.cx))
			{
				aid_status=0;
				if(m_herolife[heronum].size.cx<=70)
				m_herolife[heronum].size.cx += 30;
				else
				m_herolife[heronum].size.cx =100;
			}
		}
		
	
}
BOOL ButtonClicked(POINT ptMouse, POINT buttonPos, SIZE buttonSize)
{
	RECT rectButton;
	rectButton.left = buttonPos.x;
	rectButton.top = buttonPos.y;
	rectButton.right = buttonPos.x + buttonSize.cx;
	rectButton.bottom = buttonPos.y + buttonSize.cy;

	return PtInRect(&rectButton, ptMouse);
}

VOID KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// TODO
	switch (wParam)
	{
	case VK_LEFT:
		vkstatus=1;
		if(movex>=10)
			movex-=10;
		break;
	case VK_RIGHT:
		vkstatus=1;
		if(movex<=611)
			movex+=10;
		break;
	case 'W':
		vkstatus=0;
		if(flytst==0)
		{
			if(!(herocrashtestX(heronum) == -1 && herocrashtestYup(heronum) == -1 && herocrashtestYdown(heronum) == -1)) 
			{
				herojumptimer[heronum]=0;
				m_hero[heronum].vel.y = -HERO_VEL_Y;
			}
		}
		break;
	/*case 'S':
		m_hero.vel.y = HERO_VEL_Y;
		break;*/
	case 'A':
		vkstatus=0;
		if(flytst==0)
		{
			if(heronum==0)
			{
				m_hero[heronum].hBmp=m_hHero01BmpRe;
				hero01counter_status=1;
			}
			else if(heronum==2)
			{
				m_hero[heronum].hBmp=m_hHero02BmpRe;
				hero02counter_status=1;
			}
			else if(heronum==4)
			{
				here=1;
				m_hero[heronum].hBmp=m_hHero03replaceBmpRe;
				hero03counter_status=1;
			}
			else if(heronum==1)
			{
				m_hero[heronum].hBmp=m_hWizard01replaceBmpRe;
			}
			else if(heronum==3)
			{
				m_hero[heronum].hBmp=m_hWizard02replaceBmpRe;
			}
				
			m_hero[heronum].vel.x = -HERO_VEL_X;
			
		}
		break;
	case 'D':
		vkstatus=0;
		if(flytst==0)
		{
			if(heronum==0)
			{
				m_hero[heronum].hBmp=m_hHero01Bmp;
				hero01counter_status=1;
			}
			else if(heronum==2)
			{
				m_hero[heronum].hBmp=m_hHero02Bmp;
				hero02counter_status=1;
			}
			else if(heronum==4)
			{
				m_hero[heronum].hBmp=m_hHero03Bmp;
				hero03counter_status=1;
			}
			else if(heronum==1)
			{
				m_hero[heronum].hBmp=m_hWizard01Bmp;
			}
			else if(heronum==3)
			{
				m_hero[heronum].hBmp=m_hWizard02Bmp;
			}
				
			m_hero[heronum].vel.x = HERO_VEL_X;
			
		}
		break;
	case 'Q':
		vkstatus=0;
		if(flytst==0)
		force_status=1;
		break;
	default:
		break;
	}
}

VOID KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// TODO
	switch (wParam)
	{
	case 'W':
		if(flytst==0)
		m_hero[heronum].vel.y = -HERO_VEL_Y ;
		break;
	/*case 'S':
		m_hero.vel.y = HERO_VEL_Y;
		break;*/
	case 'A':
		if(flytst==0)
		m_hero[heronum].vel.x = 0;
		if(heronum==0)
			hero01counter_status=0;
		else if(heronum==2)
			hero02counter_status=0;
		else if(heronum==4)
			hero03counter_status=0;
		break;
	case 'D':
		if(flytst==0)
		m_hero[heronum].vel.x = 0;
		if(heronum==0)
			hero01counter_status=0;
		else if(heronum==2)
			hero02counter_status=0;
		else if(heronum==4)
			hero03counter_status=0;
		break;
	case 'Q':
		if(flytst==0)
		{
			force_status=0;
			//在状态一中随意点击都会发出炮弹,但是只能打出一发
			if(gameStatus.status==1 && have_banged==0)
			{
				//创建炮弹
				m_bang[0] = CreateBang(m_hero[heronum].pos.x  , m_hero[heronum].pos.y - m_hero[heronum].size.cy/2, BANG_SIZE_X , BANG_SIZE_Y , m_hBangreplaceBmp, 0 , BANG_MAX_FRAME_NUM);
				m_bang[1] = CreateBang(m_hero[heronum].pos.x , m_hero[heronum].pos.y - m_hero[heronum].size.cy/2, BANG_SIZE_X , BANG_SIZE_Y , m_ball, 0 , BANG_MAX_FRAME_NUM);
				m_bang[bangstatus-1].pos.x = m_hero[heronum].pos.x ;
				m_bang[bangstatus-1].pos.y = m_hero[heronum].pos.y - m_hero[heronum].size.cy/2;
				currentposx = m_hero[heronum].pos.x ;//+ m_hero[heronum].size.cx/2;
				currentposy = m_hero[heronum].pos.y - m_hero[heronum].size.cy/2;
				currentpointx = point.x;
				currentpointy = point.y;
				bangstatus=bangnum;
				bangtimer = 1;
				have_banged = 1;
			}
		}
		break;
	default:
		break;
	}
}

VOID LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	POINT ptMouse; // 鼠标点击的坐标
	ptMouse.x = LOWORD(lParam);
	ptMouse.y = HIWORD(lParam);

	

	//在状态一中随意点击都会发出炮弹,但是只能打出一发
	/*if(gameStatus.status==1 && have_banged==0)
	{
		//创建炮弹
		m_bang[0] = CreateBang(m_hero[heronum].pos.x , m_hero[heronum].pos.y , BANG_SIZE_X , BANG_SIZE_Y , m_hBangBmp[0], 0 , BANG_MAX_FRAME_NUM);
		m_bang[bangstatus-1].pos.x = m_hero[heronum].pos.x;
		m_bang[bangstatus-1].pos.y = m_hero[heronum].pos.y;
		currentposx = m_hero[heronum].pos.x;
		currentposy = m_hero[heronum].pos.y;
		currentpointx = point.x;
		currentpointy = point.y;
		bangstatus = 1;
		bangtimer = 1;
		have_banged = 1;
	}
	*/
	//在选择背景界面
	if(gameStatus.status==5)
	{
		if(ButtonClicked(ptMouse, m_background01.pos, m_background01.size))
		{
			background_choose=1;
			SetTimer(hWnd, TIMER_ID, TIMER_ELAPSE, NULL);
			gameStatus.status=1;
		}
		if(ButtonClicked(ptMouse, m_background02.pos, m_background02.size))
		{
			background_choose=2;
			SetTimer(hWnd, TIMER_ID, TIMER_ELAPSE, NULL);
			gameStatus.status=1;
		}
		if(ButtonClicked(ptMouse, m_background03.pos, m_background03.size))
		{
			background_choose=3;
			SetTimer(hWnd, TIMER_ID, TIMER_ELAPSE, NULL);
			gameStatus.status=1;
		}
		if(ButtonClicked(ptMouse, m_background04.pos, m_background04.size))
		{
			background_choose=4;
			SetTimer(hWnd, TIMER_ID, TIMER_ELAPSE, NULL);
			gameStatus.status=1;
		}

	}
	//如果点击了游戏开始图标
	if (gameStatus.status==0 && ButtonClicked(ptMouse, m_gameStartButton.pos, m_gameStartButton.size))
	{
		// 启动计时器
		//SetTimer(hWnd, TIMER_ID, TIMER_ELAPSE, NULL);
		// 停止计时器
		//KillTimer(hWnd, TIMER_ID);

		// 更改游戏状态
		gameStatus.status=5;

		InvalidateRect(hWnd, NULL, TRUE);//第三个参数设为TRUE，重画整个画布。
	}
	if (gameStatus.status==0 && ButtonClicked(ptMouse, m_helpButton.pos, m_helpButton.size))
	{
		gameStatus.status=3;
		InvalidateRect(hWnd, NULL, TRUE);//第三个参数设为TRUE，重画整个画布。
	}
	if(gameStatus.status==3 && ButtonClicked(ptMouse, m_help_startButton.pos, m_help_startButton.size))
	{
		// 启动计时器
		//SetTimer(hWnd, TIMER_ID, TIMER_ELAPSE, NULL);
		// 停止计时器
		//KillTimer(hWnd, TIMER_ID);

		// 更改游戏状态
		gameStatus.status=5;

		InvalidateRect(hWnd, NULL, TRUE);//第三个参数设为TRUE，重画整个画布。
	}
	//在状态二中点击RESTART按钮
	if (gameStatus.status==2 && ButtonClicked(ptMouse, m_gamgRestartButton.pos, m_gamgRestartButton.size))
	{
		// 启动计时器
		//SetTimer(hWnd, TIMER_ID, TIMER_ELAPSE, NULL);
		// 停止计时器
		//KillTimer(hWnd, TIMER_ID);
		//VOID initial();
		// 更改游戏状态
		gameStatus.status=5;
		InvalidateRect(hWnd, NULL, TRUE);//第三个参数设为TRUE，重画整个画布。
		

	}
	//在状态2中点击menu
	if (gameStatus.status==2 && ButtonClicked(ptMouse, m_menuButton.pos, m_menuButton.size))
	{
		gameStatus.status=0;
		InvalidateRect(hWnd, NULL, TRUE);//第三个参数设为TRUE，重画整个画布。
	}
	//状态一中选择武器
	for(int i=0;i<=1;i++)
	{
		if(gameStatus.status==1 && ButtonClicked(ptMouse, m_weapon[i].pos, m_weapon[i].size) && have_banged==0)
		{
			if(heronum%2==0)
			{
				bangnum = i+1;	
			}
			else
				bangnum==1;
		}
	}
	//状态一中暂停游戏
	if(gameStatus.status==1 && ButtonClicked(ptMouse, m_pauseButton.pos, m_pauseButton.size))
	{
		gameStatus.status=4;
		InvalidateRect(hWnd, NULL, TRUE);//第三个参数设为TRUE，重画整个画布。
	}
	if(gameStatus.status==4 && ButtonClicked(ptMouse, m_VB01.pos, m_VB01.size))
	{
		gameStatus.status=1;
		InvalidateRect(hWnd, NULL, TRUE);//第三个参数设为TRUE，重画整个画布。
	}
	if(gameStatus.status==4 && ButtonClicked(ptMouse, m_VB02.pos, m_VB02.size))
	{
		gameStatus.status=0;
		initial(hWnd);
		InvalidateRect(hWnd, NULL, TRUE);//第三个参数设为TRUE，重画整个画布。
	}
}

VOID RButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if(gameStatus.status==1)
	{
		//bangstatus=-1;
		//have_banged=0;
	}
}
