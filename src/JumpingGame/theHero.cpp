#include "JumpingGame.h"
using namespace std;
extern HBITMAP bmp_Hero;
extern HBITMAP bmp_Boss;
extern HBITMAP bmp_Boss1;
extern Hero* theHero;
extern Bullet* bullet;
extern Stage* currentStage;
extern Boss* boss;
extern Story* story;
extern Charactor* charactorL;
extern Charactor* charactorR;
extern vector<Block*> blocks;
extern vector<Particle*> particles;
extern vector<Barrage*> barrages;
extern vector<Menu*> menus;
extern bool keyUpDown;
extern bool keyLeftDown;
extern bool keyRightDown;
extern bool keySpaceDown;
extern int mouseX;
extern int mouseY;
extern int MAP[110][110];
extern bool skip_story;
extern int Selected_Stage;
extern bool unlocked[110];
extern int info[110][2];
extern int death_count;
extern int reward_count;
// 添加主角函数
Hero* CreateHero(HBITMAP img, int x, int y,int stage,int energy){
	Hero* hero = new Hero();
	hero->img = img;
	hero->x = x;
	hero->y = y;
	hero->savex=x;
	hero->savey=y;
	hero->stage=stage;
	hero->frame = 0;
	hero->vx = 0;
	hero->vy = 0;
	hero->on_ground = true;
	hero->double_jump=false;
	hero->direction=1;
	hero->time=20;
	hero->energy=energy;
	hero->death_delay=0;
	return hero;
}
void NextStage_Detection(HWND hWnd){
	int x=currentStage->X,y=currentStage->Y,n=currentStage->n,m=currentStage->m;
	if (theHero->x<0&&y>0&&MAP[x][y-1])InitStage(hWnd,MAP[x][y-1],currentStage->lm*BLOCK_SIZE_X,0);
	if (theHero->x>currentStage->m*BLOCK_SIZE_X&&MAP[x][y+1])InitStage(hWnd,MAP[x][y+1],-m*BLOCK_SIZE_X,0);
	if (theHero->y<0&&x>0&&MAP[x-1][y])InitStage(hWnd,MAP[x-1][y],0,currentStage->un*BLOCK_SIZE_Y);
	if (theHero->y>currentStage->n*BLOCK_SIZE_Y&&MAP[x+1][y])InitStage(hWnd,MAP[x+1][y],0,-n*BLOCK_SIZE_Y);
}
void load_dialog(int frame){
	if (frame==0)freopen("res\\story\\dialog0.txt","r",stdin);
	if (frame==1)freopen("res\\story\\dialog1.txt","r",stdin);
	if (frame==2)freopen("res\\story\\dialog2.txt","r",stdin);
	if (frame==3)freopen("res\\story\\dialog3.txt","r",stdin);
	if (frame==4)freopen("res\\story\\dialog4.txt","r",stdin);
	menus[0]->visible=true;
	charactorR->visible=true;
	charactorR->frame=frame;
	scanf("%s",story->s);
}
//碰撞检测函数
int inside(int x,int y,int x1,int y1,int x2,int y2){
	return (x>x1&&x<x2&&y>y1&&y<y2);
}
int Collision_Detection(){
//	freopen("report.txt","a",stdout);
	theHero->on_ground=false;
	int x1=theHero->x,y1=theHero->y,x2=theHero->x+HERO_SIZE_X,y2=theHero->y+HERO_SIZE_Y;	
	for (int i=0;i<blocks.size();i++)
		if (blocks[i]->visible&&(inside(blocks[i]->x,blocks[i]->y,x1,y1,x2,y2)||
			inside(blocks[i]->x,blocks[i]->y+BLOCK_SIZE_Y,x1,y1,x2,y2)||
			inside(blocks[i]->x+BLOCK_SIZE_X,blocks[i]->y,x1,y1,x2,y2)||
			inside(blocks[i]->x+BLOCK_SIZE_X,blocks[i]->y+BLOCK_SIZE_Y,x1,y1,x2,y2)||
			blocks[i]->x==x1&&(blocks[i]->y>y1&&blocks[i]->y<y2||blocks[i]->y+BLOCK_SIZE_Y>y1&&blocks[i]->y+BLOCK_SIZE_Y<y2)||
			blocks[i]->y==y1&&(blocks[i]->x>x1&&blocks[i]->x<x2||blocks[i]->x+BLOCK_SIZE_X>x1&&blocks[i]->x+BLOCK_SIZE_X<x2))){
				if (blocks[i]->type==1||blocks[i]->type==6||blocks[i]->type==7||blocks[i]->type==9){
//					printf("%d %d %d %d %.2lf %.2lf\n",x1,y1,blocks[i]->x,blocks[i]->y,theHero->vx,theHero->vy);
					double t1,t2;
					if (theHero->vx>0)t1=1.0*(theHero->x+HERO_SIZE_X-blocks[i]->x)/theHero->vx;
					else if (theHero->vx<0)t1=-1.0*(blocks[i]->x+BLOCK_SIZE_X-theHero->x)/theHero->vx;
					else t1=2333;
					if (theHero->vy>0)t2=1.0*(theHero->y+HERO_SIZE_Y-blocks[i]->y)/theHero->vy;
					else if (theHero->vy<0){
						if (theHero->y+HERO_SIZE_Y<blocks[i]->y+BLOCK_SIZE_Y)t2=-1.0*(blocks[i]->y+BLOCK_SIZE_Y-theHero->y-HERO_SIZE_Y)/theHero->vy;
							else t2=-1.0*(blocks[i]->y+BLOCK_SIZE_Y-theHero->y)/theHero->vy;
					}else t2=2333;
//					printf("%.2lf %.2lf\n",t1,t2);
					if (t1<t2){
						theHero->x-=(int)((t1+0.2)*theHero->vx);
						theHero->y-=(int)(t1*theHero->vy);
						theHero->vx=0;
					}else{
						theHero->x-=(int)(t2*theHero->vx);
						theHero->y-=(int)((t2+0.1)*theHero->vy);
						theHero->vy=0;
//						printf("%d %d\n",theHero->x,theHero->y);
					}
					break;
				}
				if (blocks[i]->type==2||blocks[i]->type==5||blocks[i]->type==8||blocks[i]->type==10){
					if (blocks[i]->x>=x1-22&&blocks[i]->x<=x1+22&&blocks[i]->y>=y1-22&&blocks[i]->y<=y1+22)return 1;
				}
				if (blocks[i]->type==3){
					blocks[i]->visible=false;
					theHero->savex=blocks[i]->x;
					theHero->savey=blocks[i]->y;
					theHero->stage=currentStage->stageID;
				}
				if (blocks[i]->type==4)return 2;
		}else if (blocks[i]->visible&&blocks[i]->type==11&&!skip_story){
			int dist=(theHero->x-blocks[i]->x)*(theHero->x-blocks[i]->x)+(theHero->y-blocks[i]->y)*(theHero->y-blocks[i]->y);
			if (dist<1500){
				story->on=true;
				load_dialog(blocks[i]->frame);
				blocks[i]->visible=false;
			}
		}
	x1=theHero->x,x2=theHero->x+HERO_SIZE_X,y1=theHero->y,y2=theHero->y+HERO_SIZE_Y;
	for (int i=0;i<blocks.size();i++)
		if (blocks[i]->visible&&(blocks[i]->x==x1&&(blocks[i]->y>y1&&blocks[i]->y<y2||blocks[i]->y+BLOCK_SIZE_Y>y1&&blocks[i]->y+BLOCK_SIZE_Y<y2)||
			blocks[i]->y==y1&&(blocks[i]->x>x1&&blocks[i]->x<x2||blocks[i]->x+BLOCK_SIZE_X>x1&&blocks[i]->x+BLOCK_SIZE_X<x2)))return 0;
	for (int i=0;i<blocks.size();i++)
		if (blocks[i]->visible&&(theHero->x>=blocks[i]->x&&theHero->x<blocks[i]->x+BLOCK_SIZE_X||theHero->x+HERO_SIZE_X>blocks[i]->x&&theHero->x+HERO_SIZE_X<=blocks[i]->x+BLOCK_SIZE_X)&&
			theHero->y+HERO_SIZE_Y==blocks[i]->y){
			if (blocks[i]->type==2||blocks[i]->type==5||blocks[i]->type==8||blocks[i]->type==10)return 1;
			theHero->on_ground=true;
			if (blocks[i]->type==6&&!blocks[i]->time){blocks[i]->frame++;blocks[i]->time=30;}
			else if (blocks[i]->type==7){
				double vx=blocks[i]->direction*(blocks[i]->endx-blocks[i]->startx)*1.0/blocks[i]->T;
				if (vx>0)theHero->x+=(int)(vx);else theHero->x-=(int)(-vx);
				break;
			}
		}
	return 0;
}
void attack(){
	theHero->energy--;
	if (!theHero->energy){
		vector<Particle*>::iterator i=particles.begin();
		for (;i!=particles.end();){
			Particle* particle=*i;
			if (particle->type==3){
				particles.erase(i);
				delete particle;
				if (particles.empty())break;else continue;
			}else i++;
		}
	}
	bullet=new Bullet();
	bullet->x=theHero->x,bullet->y=theHero->y;
	if (theHero->direction)bullet->x+=HERO_SIZE_X+10,bullet->v=5.0;else bullet->x-=10,bullet->v=-5.0;
}
// 刷新主角状态函数
void UpdateHero(HWND hWnd){
	if (theHero != NULL) {
		if (theHero->death_delay){
			theHero->death_delay--;
			if (!theHero->death_delay)reborn(hWnd),PutbackItems();
		}else{
		//y方向速度
		if (keyUpDown){
			if (theHero->on_ground)theHero->vy=-HERO_ACCELERATION*10,theHero->on_ground=false;
			else if (theHero->double_jump&&theHero->vy>0)theHero->vy=-HERO_ACCELERATION*10,theHero->double_jump=false;
		}
		if (!theHero->on_ground&&theHero->vy<2.5*HERO_MAXSPEED)theHero->vy+=GRAVITY;
		//x方向速度
		if (keyLeftDown && !keyRightDown && theHero->vx > -1 * HERO_MAXSPEED)
			theHero->vx -= HERO_ACCELERATION;
		else if (!keyLeftDown && keyRightDown && theHero->vx < HERO_MAXSPEED)
			theHero->vx += HERO_ACCELERATION;
		else if (theHero->vx > 0)theHero->vx =max(theHero->vx-HERO_ACCELERATION,0);
		else if (theHero->vx < 0)theHero->vx =min(theHero->vx+HERO_ACCELERATION,0);
		if (theHero->vx>0)theHero->direction=1;
			else if (theHero->vx<0)theHero->direction=0;

		theHero->x += (int)(theHero->vx);
		theHero->y += (int)(theHero->vy);

		NextStage_Detection(hWnd);
		int state=Collision_Detection();
		if (boss!=NULL)state|=Boss_Detection();
		if (state==1){
			CreateAnimation(0,20,theHero->x+HERO_SIZE_X/2,theHero->y+HERO_SIZE_Y/2);
			theHero->death_delay=100;
			death_count++;
		}else if (state==2){
			if (Selected_Stage<4)unlocked[Selected_Stage+1]=true;
			info[Selected_Stage][0]=max(info[Selected_Stage][0],reward_count);
			if (info[Selected_Stage][1]==-1)info[Selected_Stage][1]=death_count;
			else info[Selected_Stage][1]=min(info[Selected_Stage][1],death_count);
			PlaySound(TEXT("res\\music1.wav"),NULL,SND_ASYNC|SND_LOOP);
			InitStage(hWnd,STAGE_SELECT,0,0);
		}

		if (theHero->on_ground)theHero->double_jump=true;
			else theHero->time=0;
		if (fabs(theHero->vx)>1.0)(theHero->time+=1)%=40;
		theHero->frame = GetHeroFrame();

		if (theHero->energy>=1){
			int cnt=0,n=particles.size();
			for (int i=0;i<n;i++)if (particles[i]->type==3)cnt++;
			if (cnt<10)CreateAnimation(3,1,theHero->x+HERO_SIZE_X/2,theHero->y);
		}
		
		if (keySpaceDown&&theHero->energy&&bullet==NULL)attack();
		}
	}
	if (bullet!=NULL){
		bullet->time++;
		if (!bullet->frame){
			if (bullet->time>=40)bullet->time-=40,bullet->frame=1;
		}else if (bullet->frame==1){
			if (bullet->time>=20)bullet->time-=20,bullet->frame=0;
		}
		bullet->x+=bullet->v;
		if (bullet->x<0||bullet->x>currentStage->m*BLOCK_SIZE_X){
			bullet=NULL;
			return;
		}
		int x1=bullet->x,x2=bullet->x+BLOCK_SIZE_X,y1=bullet->y,y2=bullet->y+BLOCK_SIZE_Y;
		int flag=0;
		int n=blocks.size();
		for (int i=0;i<n;i++)
			if (blocks[i]->visible&&(Inside(blocks[i]->x,blocks[i]->y,x1,y1,x2,y2)||
			Inside(blocks[i]->x,blocks[i]->y+BLOCK_SIZE_Y,x1,y1,x2,y2)||
			Inside(blocks[i]->x+BLOCK_SIZE_X,blocks[i]->y,x1,y1,x2,y2)||
			Inside(blocks[i]->x+BLOCK_SIZE_X,blocks[i]->y+BLOCK_SIZE_Y,x1,y1,x2,y2))&&(blocks[i]->type==5||blocks[i]->type==6)){
				CreateAnimation(4,20,bullet->x+BLOCK_SIZE_X/2,bullet->y+BLOCK_SIZE_Y);
				blocks[i]->visible=false;
				if (blocks[i]->type==6){
					blocks[i]->frame=3;
					CreateAnimation(2,10,blocks[i]->x+BLOCK_SIZE_X/2,blocks[i]->y+BLOCK_SIZE_Y/2);
				}
				flag=1;
			}
			if (boss!=NULL){
				if (Inside(x1,y1,boss->x,boss->y,boss->x+BOSS_WIDTH,boss->y+BOSS_HEIGHT)||
					Inside(x2,y1,boss->x,boss->y,boss->x+BOSS_WIDTH,boss->y+BOSS_HEIGHT)||
					Inside(x1,y2,boss->x,boss->y,boss->x+BOSS_WIDTH,boss->y+BOSS_HEIGHT)||
					Inside(x2,y2,boss->x,boss->y,boss->x+BOSS_WIDTH,boss->y+BOSS_HEIGHT)){
					flag=1;
					boss->hp--;
					if (boss->hp==0){
						boss=NULL;
						info[Selected_Stage][0]=max(info[Selected_Stage][0],reward_count);
						if (info[Selected_Stage][1]==-1)info[Selected_Stage][1]=death_count;
						else info[Selected_Stage][1]=min(info[Selected_Stage][1],death_count);
						PlaySound(TEXT("res\\music1.wav"),NULL,SND_ASYNC|SND_LOOP);
						if (!skip_story)InitStage(hWnd,STAGE_STORY,1,0);
						else InitStage(hWnd,STAGE_SELECT,0,0);
					}
					CreateAnimation(4,20,bullet->x+BLOCK_SIZE_X/2,bullet->y+BLOCK_SIZE_Y);
				}
			}
		if (flag)bullet=NULL;
	}
}
// 计算主角的当前帧数
int GetHeroFrame(){
	int frame;
	if (theHero->direction)frame=0;else frame=5;
	if (theHero->on_ground){
		int tmp=theHero->time/8;
		if (tmp==1||tmp==3)frame++;
		if (tmp==2)frame+=2;
	}else if (fabs(theHero->vy)<2.0)frame+=4;
	else if (fabs(theHero->vy)<4.0)frame+=3;
	return frame;
}
void reborn(HWND hWnd){
	int x=theHero->savex,y=theHero->savey,stage=theHero->stage,energy=theHero->energy;
	if (stage!=currentStage->stageID)InitStage(hWnd,stage,x,y);
	delete theHero;
	theHero=CreateHero(bmp_Hero,x,y,stage,energy);
	ResetBlocks();
	if (boss!=NULL){
		if (boss->type==0)boss=CreateBoss(bmp_Boss,390,120,0);
		else boss=CreateBoss(bmp_Boss1,390,90,1);
		barrages.clear();
	}
}
