#pragma once

#pragma region 头文件引用
#define _CRT_SECURE_NO_WARNINGS
// Windows 头文件: 
#include <windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// 资源头文件
#include "resource.h"
#pragma comment(lib, "Msimg32.lib")


// TODO:  在此处引用程序需要的其他头文件
#include<vector>
#include<algorithm>
#include<string.h>
#include<math.h>
#include<cmath>


#pragma endregion


#pragma region 宏定义

#define WINDOW_WIDTH			1000		//游戏窗口宽度
#define WINDOW_HEIGHT			600		//游戏窗口高度
#define WINDOW_TITLEBARHEIGHT	32		//标题栏高度

#define STAGE_STARTMENU			0		//开始画面的ID
#define STAGE_SELECT			1
#define STAGE_OPTION			2
#define STAGE_STORY				3
#define STAGE_HELP				30
#define STAGE_0					4		//第一个游戏场景的ID

#define HERO_SIZE_X				30		//主角的宽度
#define HERO_SIZE_Y				30		//主角的高度
#define HERO_FRAME_NUMBER		8		//主角的动画帧数量
#define HERO_ACCELERATION		0.8		//主角加速度
#define HERO_MAXSPEED			4.0		//主角最大速度
#define GRAVITY					0.4		//重力加速度

#define BOSS_WIDTH				120
#define BOSS_HEIGHT				120

#define BLOCK_SIZE_X			30		//地板的宽度
#define BLOCK_SIZE_Y			30		//地板的高度

#define MENU_WIDTH				300		//菜单的宽度
#define MENU_HEIGHT				500		//菜单的高度
#define MENU_X					450		//菜单的x坐标
#define MENU_Y					250		//菜单的y坐标

#define BUTTON_STARTGAME			1001	//开始游戏
#define BUTTON_OPTION				1002	//
#define BUTTON_HELP					1003	//
#define BUTTON_EXIT					1004	//退出
#define BUTTON_PAUSE				1005	//暂停
#define BUTTON_RESUME				1006	//继续
#define BUTTON_RESTART				1007	//重新开始
#define BUTTON_RETURN				1008	//返回
#define BUTTON_START				1009
#define BUTTON_PRESTAGE				1010
#define BUTTON_NEXTSTAGE			1011
#define BUTTON_RETURN1				1012
#define BUTTON_SKIP					1013
#define BUTTON_MUSICON				1014
#define BUTTON_PARTICLEON			1015
#define BUTTON_STORYON				1016
#define BUTTON_FLIP					1017


#define TIMER_GAMETIMER				1	//游戏的默认计时器ID
#define TIMER_GAMETIMER_ELAPSE		10	//默认计时器刷新间隔的毫秒数


#pragma endregion


#pragma region 结构体声明

// 场景结构体
struct Stage{
	int stageID;		//场景编号
	HBITMAP bg;			//背景图片
	int time;	//游戏时间倒计时
	bool timerOn;		//计时器是否运行（游戏是否被暂停）
	int x;		//场景初始x坐标
	int y;		//场景初始y坐标
	int n;		//场景行数
	int m;		//场景列数
	int un;
	int lm;
	int X;
	int Y;
};

//菜单结构体
struct Menu{
	bool visible;
	HBITMAP img;
	int x;
	int y;
	int width;
	int height;
	int value;
};

// 按钮结构体
struct Button{
	int buttonID;	//按钮编号
	bool visible;	//按钮是否可见
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int height;		//高度
};

// 主角结构体
struct Hero{
	HBITMAP img;	//图片
	int frame;		//当前显示的帧数
	int x;			//坐标x
	int y;			//坐标y
	int savex;		//上一次存档点坐标x
	int savey;		//上一次存档点坐标y
	double vx;		//速度x
	double vy;		//速度y
	bool on_ground; //是否在地板上
	bool double_jump; //能否二段跳
	int direction;		//面部朝向
	int stage;	//所在场景
	int time;	//计时器计时
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

//方块结构体
struct Block{
	HBITMAP img;
	double x;
	double y;
	int startx;
	int starty;
	int endx;
	int endy;
	int type;  //1=普通砖块  2=静态陷阱  3=存档点 	 4=终点  5=动态陷阱 6=脆弱砖块 7=移动砖块 8=横纵向感应陷阱 9=横向感应砖块 10=横向感应陷阱 11=npc
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
	int status;  //0=未拿到  1=正在飞来 2=拿到
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
	int type; //1=重力型  2=匀速型
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

//TODO: 添加游戏需要的更多种数据（子弹、砖块、敌人、弹幕等）


#pragma endregion


#pragma region 事件处理函数声明


// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

#pragma endregion


#pragma region 其它游戏状态处理函数声明

//添加菜单函数
Menu* CreateMenu(HBITMAP img,int width,int height,int x,int y);

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y);

// 添加主角函数
Hero* CreateHero(HBITMAP img, int x, int y,int stage,int energy);

// 添加地板函数
Block* CreateBlock(HBITMAP img,int startx,int starty,int endx,int endy,int type,int frame,int T,int value);

Item* CreateItem(HBITMAP img,double x,double y,int stage,int type);

Boss* CreateBoss(HBITMAP img,double x,double y,int type);

Barrage* CreateBarrage(HBITMAP img,double x,double y,double vx,double vy,int width,int height,int type,int frame);

//添加微粒函数
Particle* CreateParticle(double x,double y,double vx,double vy,int type,Col col);

Story* CreateStory(int x,int y);

Charactor* CreateCharactor(HBITMAP img);

void InitChapter(HWND hWnd,int chapterID);
// 初始化场景函数
void InitStage(HWND hWnd, int stageID,int x,int y);

void Save();

void Load();

// 刷新主角状态函数
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

// 计算主角的当前帧数
int GetHeroFrame();

void reborn(HWND hWnd);

void ResetShadow();

void ShowPauseMenu();

void HidePauseMenu();

void ShowChapterAbstract(int chapterID);

void UpdateParticles();

void CreateAnimation(int type,int cnt,double x,double y);

//TODO: 添加游戏需要的更多函数

#pragma endregion


#pragma region 绘图函数声明

// 绘图函数
void Paint(HWND hWnd);

#pragma endregion
