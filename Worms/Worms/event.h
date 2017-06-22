#ifndef EVENT_H
#define EVENT_H

#include <Windows.h>

// ������̺���
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


// ��ʼ��
VOID Init(HWND hWnd, WPARAM wParam, LPARAM lParam);

//˫�������
VOID Render(HWND hWnd);
VOID Render_Start(HWND hWnd);//������Ϸ��ʼ����
VOID Render_Game(HWND hWnd);//������Ϸ����
VOID Render_Over(HWND hWnd);//���ƽ�������
VOID Render_help(HWND hWnd);//���ư�������
VOID Render_Pause(HWND hWnd);//������ͣ����
VOID Render_pick(HWND hWnd);//����ѡ�����
//����������
VOID aid_check();
VOID aid_update();
int aid_crash();
VOID hero_aid();
//�ڵ��ɳ��߽�
int bang_out_range_judge(int bangstatus);

//������߽�
VOID hero_out_range_operate();

//��ˮ����
void sealevelupdate();

//����
void windchange();

//�жϵ�ǰӢ���Ƿ񻹻���
void heronum_check();

//�ж��������
VOID flytest();

//restart��ʼ��
VOID initial(HWND hWnd, WPARAM wParam, LPARAM lParam);

//BANG����
VOID ForceCount();

//��ʱ���¼�
VOID TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

//�ڵ��¼�
VOID BangUpdate();

//�ڵ���ײ�¼�
int bangcrashtestX(int i);
int bangcrashtestYdown(int i);
int bangcrashtestYup(int i);

//hero��ײ�ж�
int herocrashtestX(int i);
int herocrashtestYup(int i);
int herocrashtestYdown(int i);

//hero����
VOID HeroUpdateX(int i);
VOID HeroUpdateY(int i);

//���θ���
VOID TerrianUpdate();

//��Ϸ״̬����
VOID GameStatusUpdate();

//�ж��Ƿ�����ť
BOOL ButtonClicked(POINT, RECT);

//���̰����¼�����
VOID KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

//�����ɿ��¼�����
VOID KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

//��������¼�
VOID LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

//��������¼�
VOID RButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif // !EVENT_H
