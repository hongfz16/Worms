#ifndef EVENT_H
#define EVENT_H

#include <Windows.h>

// 窗体过程函数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


// 初始化
VOID Init(HWND hWnd, WPARAM wParam, LPARAM lParam);

//双缓冲绘制
VOID Render(HWND hWnd);
VOID Render_Start(HWND hWnd);//绘制游戏开始界面
VOID Render_Game(HWND hWnd);//绘制游戏界面
VOID Render_Over(HWND hWnd);//绘制结束界面
VOID Render_help(HWND hWnd);//绘制帮助界面
VOID Render_Pause(HWND hWnd);//绘制暂停界面
VOID Render_pick(HWND hWnd);//绘制选择界面
//创建急救箱
VOID aid_check();
VOID aid_update();
int aid_crash();
VOID hero_aid();
//炮弹飞出边界
int bang_out_range_judge(int bangstatus);

//人物出边界
VOID hero_out_range_operate();

//海水上涨
void sealevelupdate();

//风向
void windchange();

//判断当前英雄是否还活着
void heronum_check();

//判断人物飞翔
VOID flytest();

//restart初始化
VOID initial(HWND hWnd, WPARAM wParam, LPARAM lParam);

//BANG蓄力
VOID ForceCount();

//定时器事件
VOID TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

//炮弹事件
VOID BangUpdate();

//炮弹碰撞事件
int bangcrashtestX(int i);
int bangcrashtestYdown(int i);
int bangcrashtestYup(int i);

//hero碰撞判断
int herocrashtestX(int i);
int herocrashtestYup(int i);
int herocrashtestYdown(int i);

//hero更新
VOID HeroUpdateX(int i);
VOID HeroUpdateY(int i);

//地形更新
VOID TerrianUpdate();

//游戏状态更新
VOID GameStatusUpdate();

//判断是否点击按钮
BOOL ButtonClicked(POINT, RECT);

//键盘按下事件处理
VOID KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

//键盘松开事件处理
VOID KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

//左鼠标点击事件
VOID LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

//右鼠标点击事件
VOID RButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif // !EVENT_H
