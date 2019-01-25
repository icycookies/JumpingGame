#include "JumpingGame.h"
#include<ctime>
using namespace std;
extern HBITMAP bmp_Barrage1;
extern HBITMAP bmp_Barrage2;
extern HBITMAP bmp_Barrage3;
extern Hero* theHero;
extern Boss* boss;
extern vector<Barrage*> barrages;
extern int info[110][2];
extern int Selected_Stage;
extern int death_count;
const double pi=acos(-1);
Boss* CreateBoss(HBITMAP img,double x,double y,int type){
	srand(time(NULL));
	Boss* boss=new Boss();
	boss->img=img;
	boss->x=x;
	boss->y=y;
	if (type==0)boss->hp=5;else boss->hp=30;
	boss->time=0;
	boss->Time=0;
	boss->type=type;
	return boss;
}
Barrage* CreateBarrage(HBITMAP img,double x,double y,double vx,double vy,int width,int height,int type,int frame){
	Barrage* barrage=new Barrage();
	barrage->img=img;
	barrage->x=x;
	barrage->y=y;
	barrage->vx=vx;
	barrage->vy=vy;
	barrage->width=width;
	barrage->height=height;
	barrage->type=type;
	barrage->frame=frame;
	barrage->time=0;
	return barrage;
}
void attack(int type){
	if (type==1){
		double x=rand()%900,y=rand()%50;
		for (int i=0;i<25;i++){
			barrages.push_back(CreateBarrage(bmp_Barrage1,x,y,6.0*sin(2*pi*i/25),6.0*cos(2*pi*i/25),10,10,1,rand()%2));
		}
	}
	if (type==2){
		double dirX=boss->x-theHero->x,dirY=boss->y-theHero->y;
		double dist=sqrt(dirX*dirX+dirY*dirY);
		barrages.push_back(CreateBarrage(bmp_Barrage1,boss->x+60,boss->y+60,-dirX/dist*4.0,-dirY/dist*4.0,10,10,2,rand()%2));
	}
	if (type==3){
		double x=rand()%900,y=-rand()%600;
		double v=rand()%1000*1.0/400+3;
		int type=rand()%2;
		barrages.push_back(CreateBarrage(bmp_Barrage2,x,y,0,v,30,30,1,type));
		barrages.push_back(CreateBarrage(bmp_Barrage2,x+30,y,0,v,30,30,1,type));
		barrages.push_back(CreateBarrage(bmp_Barrage2,x+60,y,0,v,30,30,1,type));
	}
	if (type==4){
		double vx=rand()%1000*1.0/100-5,vy=-rand()%800*1.0/100;
		while (fabs(vx)<1)vx=rand()%1000*1.0/100-5;
		barrages.push_back(CreateBarrage(bmp_Barrage3,boss->x+60,boss->y+60,vx,vy,10,10,3,0));
	}
	if (type==5){
		double vx=4.0*sin(3*pi/50*(boss->time-1000)/20),vy=4.0*cos(3*pi/50*(boss->time-1000)/20);
		barrages.push_back(CreateBarrage(bmp_Barrage3,boss->x+60,boss->y+60,vx,vy,10,10,1,1));
		barrages.push_back(CreateBarrage(bmp_Barrage3,boss->x+60,boss->y+60,vy,-vx,10,10,1,1));
		barrages.push_back(CreateBarrage(bmp_Barrage3,boss->x+60,boss->y+60,-vx,-vy,10,10,1,1));
		barrages.push_back(CreateBarrage(bmp_Barrage3,boss->x+60,boss->y+60,-vy,vx,10,10,1,1));
	}
	if (type==6){
		double vx=rand()%400*1.0/100-2,vy=rand()%400*1.0/100-2;
		barrages.push_back(CreateBarrage(bmp_Barrage3,boss->x+60,boss->y+60,vx,vy,10,10,4,2));
	}
	if (type==7){
		double vx=rand()%100*1.0/200-0.25;
		for (int i=0;i<10;i++){
			barrages.push_back(CreateBarrage(bmp_Barrage3,i*90,0,vx,3,10,10,5,3));
		}
	}
	if (type==8){
		double v=rand()%400*1.0/200+2.0,theta=12*pi/50*boss->time/20+rand()%10*1.0/200-0.025;
		double vx=v*sin(theta),vy=v*cos(theta);
		if (rand()%5)barrages.push_back(CreateBarrage(bmp_Barrage3,boss->x+60,boss->y+60,vx,vy,10,10,1,4));
		else{
			barrages.push_back(CreateBarrage(bmp_Barrage3,boss->x+60,boss->y+60,vx,vy,10,10,1,4));
			barrages.push_back(CreateBarrage(bmp_Barrage3,boss->x+60,boss->y+60,vx*1.2,vy*1.2,10,10,1,4));
			barrages.push_back(CreateBarrage(bmp_Barrage3,boss->x+60,boss->y+60,vx*1.5,vy*1.5,10,10,1,4));
			barrages.push_back(CreateBarrage(bmp_Barrage3,boss->x+60,boss->y+60,vx*1.8,vy*1.8,10,10,1,4));
		}
	}
	if (type==9){
		double vx=rand()%200*1.0/50-2.0,vy=rand()%200*1.0/100;
		barrages.push_back(CreateBarrage(bmp_Barrage3,boss->x+60,boss->y+60,vx,vy,10,10,6,5));
	}
	if (type==10){
		double y=rand()%19*30;
		barrages.push_back(CreateBarrage(bmp_Barrage3,0,y,1.0,0,10,10,1,6));
		y=rand()%19*30;
		barrages.push_back(CreateBarrage(bmp_Barrage3,870,y,-1.0,0,10,10,1,6));
		y=rand()%19*30;
		barrages.push_back(CreateBarrage(bmp_Barrage3,0,y,1.0,0,10,10,1,6));
		y=rand()%19*30;
		barrages.push_back(CreateBarrage(bmp_Barrage3,870,y,-1.0,0,10,10,1,6));
	}
}
void UpdateBarrage(){
	Barrage* tmp=NULL;
	vector<Barrage*>::iterator p;
	vector<Barrage*>::iterator i=barrages.begin();
	for (;i!=barrages.end();){
		Barrage* barrage=*i;
		barrage->x+=barrage->vx;
		barrage->y+=barrage->vy;
		if (barrage->type==3){
			if (barrage->y>=560){
				barrage->y=560;
				barrage->vy=-barrage->vy*0.5;
			}else barrage->vy+=GRAVITY;
		}
		if (barrage->type==4){
			if (barrage->x<30)barrage->x=30,barrage->vx=-barrage->vx;
			if (barrage->x>860)barrage->x=860,barrage->vx=-barrage->vx;
			if (barrage->y<30)barrage->y=30,barrage->vy=-barrage->vy;
			if (barrage->y>560)barrage->y=560,barrage->vy=-barrage->vy;
			if (boss->time==999){
				barrages.erase(i);
				delete barrage;
				if (barrages.empty())break;
				continue;
			}
		}
		if (barrage->type==5&&barrage->y>=300)barrage->vy=0.8;
		if (barrage->type==6){
			barrage->time++;
			if (barrage->time==80){
				tmp=CreateBarrage(bmp_Barrage1,barrage->x,barrage->y,barrage->vx,barrage->vy,10,10,1,1);
				barrages.erase(i);
				delete barrage;
				if (barrages.empty())break;
				continue;
			}
		}
		if (barrage->x<-500||barrage->x>1500||barrage->y<-500||barrage->y>1000){
			barrages.erase(i);
			delete barrage;
			if (barrages.empty())break;
		}else i++;
	}
	if (tmp!=NULL){
		barrages.push_back(CreateBarrage(bmp_Barrage3,tmp->x,tmp->y,tmp->vx*cos(pi/4)-tmp->vy*sin(pi/4),tmp->vx*sin(pi/4)+tmp->vy*cos(pi/4),10,10,1,5));
		barrages.push_back(CreateBarrage(bmp_Barrage3,tmp->x,tmp->y,tmp->vx*cos(3*pi/4)-tmp->vy*sin(3*pi/4),tmp->vx*sin(3*pi/4)+tmp->vy*cos(3*pi/4),10,10,1,5));
		barrages.push_back(CreateBarrage(bmp_Barrage3,tmp->x,tmp->y,tmp->vx*cos(5*pi/4)-tmp->vy*sin(5*pi/4),tmp->vx*sin(5*pi/4)+tmp->vy*cos(5*pi/4),10,10,1,5));
		barrages.push_back(CreateBarrage(bmp_Barrage3,tmp->x,tmp->y,tmp->vx*cos(7*pi/4)-tmp->vy*sin(7*pi/4),tmp->vx*sin(7*pi/4)+tmp->vy*cos(7*pi/4),10,10,1,5));
		delete tmp;
	}
}
void UpdateBoss(HWND hWnd){
	boss->time++;
	if (boss->type==0){
		if (boss->time>=3000)boss->time=0;
		if (boss->Time)boss->Time--;
		if (boss->time<1000&&boss->time%100==0)attack(1);
		if (boss->time>=1000&&boss->time<2000){
			if (boss->time%10==0&&boss->time%200<=100)attack(2);
			if (boss->time<=1250||boss->time>=1750)boss->x--;
				else boss->x++;
		}
		if (boss->time>2000&&boss->time%20==0)attack(3);
	}
	if (boss->type==1){
		if (boss->time>=1000){
			boss->time=0;
			boss->Time=rand()%7;
			boss->hp--;
			if (boss->hp==0){
				boss=NULL;
				if (info[Selected_Stage][1]==-1)info[Selected_Stage][1]=death_count;
				else info[Selected_Stage][1]=min(info[Selected_Stage][1],death_count);
				InitStage(hWnd,STAGE_SELECT,0,0);
				return;
			}
		}
		if (boss->Time==0&&boss->time%40==0)attack(4);
		if (boss->Time==1&&boss->time%20==0)attack(5);
		if (boss->Time==2&&boss->time%35==0)attack(6);
		if (boss->Time==3&&boss->time%150==0)attack(7);
		if (boss->Time==4&&boss->time%5==0)attack(8);
		if (boss->Time==5&&boss->time%30==0)attack(9);
		if (boss->Time==6&&boss->time%90==0)attack(10);
	}
	UpdateBarrage();
}
int Boss_Detection(){
	int x1=boss->x,x2=boss->x+BOSS_WIDTH,y1=boss->y,y2=boss->y+BOSS_HEIGHT;
	int x=theHero->x,y=theHero->y;
	if (inside(x,y,x1,y1,x2,y2)||inside(x+HERO_SIZE_X,y,x1,y1,x2,y2)||
		inside(x,y+HERO_SIZE_Y,x1,y1,x2,y2)||inside(x+HERO_SIZE_X,y+HERO_SIZE_Y,x1,y1,x2,y2))return 1;
	x1=theHero->x,x2=theHero->x+HERO_SIZE_X,y1=theHero->y,y2=theHero->y+HERO_SIZE_Y;
	int n=barrages.size();
	for (int i=0;i<n;i++)
		if (inside(barrages[i]->x,barrages[i]->y,x1,y1,x2,y2)||inside(barrages[i]->x+barrages[i]->width,y,x1,y1,x2,y2)||
		inside(barrages[i]->x,barrages[i]->y+barrages[i]->height,x1,y1,x2,y2)||inside(barrages[i]->x+barrages[i]->width,barrages[i]->y+barrages[i]->height,x1,y1,x2,y2))return 1;
	return 0;
}