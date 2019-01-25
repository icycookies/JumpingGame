#include "JumpingGame.h"
using namespace std;
extern Hero* theHero;
extern vector<Block*> blocks;
//Ìí¼Ó·½¿éº¯Êý
Block* CreateBlock(HBITMAP img,int startx,int starty,int endx,int endy,int type,int frame,int T,int value){
	Block* block=new Block();
	block->img=img;
	block->x=startx;
	block->y=starty;
	block->startx=startx;
	block->starty=starty;
	block->endx=endx;
	block->endy=endy;
	block->time=0;
	block->type=type;
	block->frame=frame;
	block->T=T;
	block->value=value;
	block->direction=1;
	block->visible=true;
	return block;
}
void UpdateBlocks(){
	int n=blocks.size();
	for (int i=0;i<n;i++){
		Block* block=blocks[i];
		if (block->type==5||block->type==7){
			block->x+=block->direction*(block->endx-block->startx)*1.0/block->T;
			block->y+=block->direction*(block->endy-block->starty)*1.0/block->T;
			block->time++;
			if (block->time>=block->T){
				block->direction*=-1;
				block->time-=block->T;
			}
		}
		if (block->type==6&&block->time){
			block->time--;
			if (!block->time){
				if (block->frame==1){
					CreateAnimation(2,10,block->x+BLOCK_SIZE_X/2,block->y+BLOCK_SIZE_Y/2);
					block->time=500;
					block->frame++;
					block->visible=false;
				}else if (block->frame==2)block->frame=0,block->visible=true;
			}
		}
		if (block->type==8){
			if (block->status==0){
				if ((theHero->x>=block->x&&theHero->x<=block->x+BLOCK_SIZE_X||theHero->x+HERO_SIZE_X>=block->x&&theHero->x+HERO_SIZE_X<=block->x+BLOCK_SIZE_X)
				&&(block->frame==0&&theHero->y-block->y>=0&&theHero->y-block->y<=200||block->frame==2&&theHero->y-block->y<=0&&theHero->y-block->y>=-200))block->status=1,block->visible=true;
				if ((theHero->y>=block->y&&theHero->y<=block->y+BLOCK_SIZE_Y||theHero->y+HERO_SIZE_Y>=block->y&&theHero->y+HERO_SIZE_Y<=block->y+BLOCK_SIZE_Y)
				&&(block->frame==3&&theHero->x-block->x>=0&&theHero->x-block->x<=200||block->frame==1&&theHero->x-block->x<=0&&theHero->x-block->x>=-200))block->status=1,block->visible=true;
			}
			if (block->status==1){
				/*if (block->frame==0)block->y+=15;
				if (block->frame==1)block->x-=15;
				if (block->frame==2)block->y-=15;
				if (block->frame==3)block->x+=15;*/
				block->x+=(block->endx-block->startx)*1.0/block->T;
				block->y+=(block->endy-block->starty)*1.0/block->T;
				block->time++;
				if (block->time>=block->T)block->status=2;
				//if (block->x<-300||block->x>WINDOW_WIDTH+300||block->y<-300||block->y>WINDOW_HEIGHT+300)block->status=2,block->visible=false;
			}
		}
		if (block->type==9||block->type==10){
			if (!block->visible){
				if (block->value>0&&theHero->x>=block->value&&theHero->y<=block->y+30)block->visible=true;
				if (block->value<0&&theHero->x<=-block->value&&theHero->y<=block->y+30)block->visible=true;
			}
		}
	}
}
void ResetBlocks(){
	int n=blocks.size();
	for (int i=0;i<n;i++){
		Block* block=blocks[i];
		if (block->type==5||block->type==7){
			block->x=block->startx;
			block->y=block->starty;
			block->direction=1;
			block->time=0;
		}
		if (block->type==6&&block->frame!=3){
			block->frame=0;
			block->time=0;
			block->visible=true;
		}
		if (block->type==8){
			block->status=0;
			block->time=0;
			block->x=block->startx;
			block->y=block->starty;
			if (!block->value)block->visible=false;
		}
		if (block->type==9||block->type==10){
			block->visible=false;
		}
	}
}