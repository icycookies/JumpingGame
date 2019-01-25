#pragma once

#pragma region ͷ�ļ�����
#define _CRT_SECURE_NO_WARNINGS
// Windows ͷ�ļ�: 
#include <windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// ��Դͷ�ļ�
#include "resource.h"
#pragma comment(lib, "Msimg32.lib")


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include<vector>
#include<algorithm>
#include<string.h>
#include<math.h>
#include<cmath>


#pragma endregion


#pragma region �궨��

#define WINDOW_WIDTH			1000		//��Ϸ���ڿ��
#define WINDOW_HEIGHT			600		//��Ϸ���ڸ߶�
#define WINDOW_TITLEBARHEIGHT	32		//�������߶�

#define STAGE_STARTMENU			0		//��ʼ�����ID
#define STAGE_SELECT			1
#define STAGE_OPTION			2
#define STAGE_STORY				3
#define STAGE_HELP				30
#define STAGE_0					4		//��һ����Ϸ������ID

#define HERO_SIZE_X				30		//���ǵĿ��
#define HERO_SIZE_Y				30		//���ǵĸ߶�
#define HERO_FRAME_NUMBER		8		//���ǵĶ���֡����
#define HERO_ACCELERATION		0.8		//���Ǽ��ٶ�
#define HERO_MAXSPEED			4.0		//��������ٶ�
#define GRAVITY					0.4		//�������ٶ�

#define BOSS_WIDTH				120
#define BOSS_HEIGHT				120

#define BLOCK_SIZE_X			30		//�ذ�Ŀ��
#define BLOCK_SIZE_Y			30		//�ذ�ĸ߶�

#define MENU_WIDTH				300		//�˵��Ŀ��
#define MENU_HEIGHT				500		//�˵��ĸ߶�
#define MENU_X					450		//�˵���x����
#define MENU_Y					250		//�˵���y����

#define BUTTON_STARTGAME			1001	//��ʼ��Ϸ
#define BUTTON_OPTION				1002	//
#define BUTTON_HELP					1003	//
#define BUTTON_EXIT					1004	//�˳�
#define BUTTON_PAUSE				1005	//��ͣ
#define BUTTON_RESUME				1006	//����
#define BUTTON_RESTART				1007	//���¿�ʼ
#define BUTTON_RETURN				1008	//����
#define BUTTON_START				1009
#define BUTTON_PRESTAGE				1010
#define BUTTON_NEXTSTAGE			1011
#define BUTTON_RETURN1				1012
#define BUTTON_SKIP					1013
#define BUTTON_MUSICON				1014
#define BUTTON_PARTICLEON			1015
#define BUTTON_STORYON				1016
#define BUTTON_FLIP					1017


#define TIMER_GAMETIMER				1	//��Ϸ��Ĭ�ϼ�ʱ��ID
#define TIMER_GAMETIMER_ELAPSE		10	//Ĭ�ϼ�ʱ��ˢ�¼���ĺ�����


#pragma endregion


#pragma region �ṹ������

// �����ṹ��
struct Stage{
	int stageID;		//�������
	HBITMAP bg;			//����ͼƬ
	int time;	//��Ϸʱ�䵹��ʱ
	bool timerOn;		//��ʱ���Ƿ����У���Ϸ�Ƿ���ͣ��
	int x;		//������ʼx����
	int y;		//������ʼy����
	int n;		//��������
	int m;		//��������
	int un;
	int lm;
	int X;
	int Y;
};

//�˵��ṹ��
struct Menu{
	bool visible;
	HBITMAP img;
	int x;
	int y;
	int width;
	int height;
	int value;
};

// ��ť�ṹ��
struct Button{
	int buttonID;	//��ť���
	bool visible;	//��ť�Ƿ�ɼ�
	HBITMAP img;	//ͼƬ
	int x;			//����x
	int y;			//����y
	int width;		//���
	int height;		//�߶�
};

// ���ǽṹ��
struct Hero{
	HBITMAP img;	//ͼƬ
	int frame;		//��ǰ��ʾ��֡��
	int x;			//����x
	int y;			//����y
	int savex;		//��һ�δ浵������x
	int savey;		//��һ�δ浵������y
	double vx;		//�ٶ�x
	double vy;		//�ٶ�y
	bool on_ground; //�Ƿ��ڵذ���
	bool double_jump; //�ܷ������
	int direction;		//�沿����
	int stage;	//���ڳ���
	int time;	//��ʱ����ʱ
	int energy;
	int death_delay;
};
struct Bullet{
	HBITMAP img;
	int frame;
	int x;
	int y;
	int time;
	double v;
};

//����ṹ��
struct Block{
	HBITMAP img;
	double x;
	double y;
	int startx;
	int starty;
	int endx;
	int endy;
	int type;  //1=��ͨש��  2=��̬����  3=�浵�� 	 4=�յ�  5=��̬���� 6=����ש�� 7=�ƶ�ש�� 8=�������Ӧ���� 9=�����Ӧש�� 10=�����Ӧ���� 11=npc
	int frame;
	int time;
	int T;
	int direction;
	int status;
	int value;
	bool visible;
};
struct Item{
	HBITMAP img;
	double x;
	double y;
	double startx;
	double starty;
	int type;
	int frame;
	int stage;
	int time;
	int Time;
	int status;  //0=δ�õ�  1=���ڷ��� 2=�õ�
	bool visible;
};
struct Barrage{
	HBITMAP img;
	double x;
	double y;
	double vx;
	double vy;
	int width;
	int height;
	int type;
	int frame;
	int time;
};
struct Boss{
	HBITMAP img;
	double x;
	double y;
	int hp;
	int time;
	int Time;
	int type;
};
struct Col{
	int R,G,B;
};
struct Particle{
	double x;
	double y;
	double vx;
	double vy;
	int type; //1=������  2=������
	int time;
	Col col;
};
struct Story{
	bool on;
	int time;
	int x;
	int y;
	char s[210];
};
struct Charactor{
	bool visible;
	HBITMAP img;
	int frame;
};

//TODO: �����Ϸ��Ҫ�ĸ��������ݣ��ӵ���ש�顢���ˡ���Ļ�ȣ�


#pragma endregion


#pragma region �¼�����������


// ��ʼ����Ϸ���庯��
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// ���̰����¼�������
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// �����ɿ��¼�������
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// ����ƶ��¼�������
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// �����������¼�������
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// �������ɿ��¼�������
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// ��ʱ���¼�������
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

#pragma endregion


#pragma region ������Ϸ״̬����������

//��Ӳ˵�����
Menu* CreateMenu(HBITMAP img,int width,int height,int x,int y);

// ��Ӱ�ť����
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y);

// ������Ǻ���
Hero* CreateHero(HBITMAP img, int x, int y,int stage,int energy);

// ��ӵذ庯��
Block* CreateBlock(HBITMAP img,int startx,int starty,int endx,int endy,int type,int frame,int T,int value);

Item* CreateItem(HBITMAP img,double x,double y,int stage,int type);

Boss* CreateBoss(HBITMAP img,double x,double y,int type);

Barrage* CreateBarrage(HBITMAP img,double x,double y,double vx,double vy,int width,int height,int type,int frame);

//���΢������
Particle* CreateParticle(double x,double y,double vx,double vy,int type,Col col);

Story* CreateStory(int x,int y);

Charactor* CreateCharactor(HBITMAP img);

void InitChapter(HWND hWnd,int chapterID);
// ��ʼ����������
void InitStage(HWND hWnd, int stageID,int x,int y);

void Save();

void Load();

// ˢ������״̬����
void UpdateHero(HWND hWnd);

void NextStage_Detection(HWND hWnd);

int Boss_Detection();

void UpdateBoss(HWND hWnd);

int inside(int x,int y,int x1,int y1,int x2,int y2);

int Inside(int x,int y,int x1,int y1,int x2,int y2);

void UpdateBlocks();

void ResetBlocks();

void UpdateItems();

void ResetItems(int stage,int x,int y);

void PutbackItems();

// �������ǵĵ�ǰ֡��
int GetHeroFrame();

void reborn(HWND hWnd);

void ResetShadow();

void ShowPauseMenu();

void HidePauseMenu();

void ShowChapterAbstract(int chapterID);

void UpdateParticles();

void CreateAnimation(int type,int cnt,double x,double y);

//TODO: �����Ϸ��Ҫ�ĸ��ຯ��

#pragma endregion


#pragma region ��ͼ��������

// ��ͼ����
void Paint(HWND hWnd);

#pragma endregion
