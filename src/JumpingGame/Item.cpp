#include "JumpingGame.h"
using namespace std;
extern vector<Item*> items;
extern Hero* theHero;
extern int reward_count;
extern bool unlocked[110];
extern int Selected_Stage;
extern Stage* currentStage;
Item* CreateItem(HBITMAP img,double x,double y,int stage,int type){
	Item* item=new Item();
	item->img=img;
	item->startx=x;
	item->starty=y;
	item->x=x;
	item->y=y;
	item->stage=stage;
	item->type=type;
	item->frame=0;
	item->status=0;
	item->visible=true;
	item->time=0;
	item->Time=0;
	return item;
}
int Inside(int x,int y,int x1,int y1,int x2,int y2){
	return (x>=x1&&x<=x2&&y>=y1&&y<=y2);
}
void UpdateItems(){
	if (theHero==NULL||theHero->death_delay)return;
	int n=items.size();
	int x1=theHero->x,x2=theHero->x+HERO_SIZE_X,y1=theHero->y,y2=theHero->y+HERO_SIZE_Y;
	for (int i=0;i<n;i++){
		Item* item=items[i];
		if (item->stage!=currentStage->stageID)continue;
		item->Time++;
		if (item->Time>20){
			item->Time-=20;
			item->frame++;
			if (item->type==1||item->type==3)item->frame%=2;
			else if (item->type==2)item->frame%=3;
			else item->frame=0;
		}
		if (item->time>0){
			item->time--;
			if (item->time==0){
				if (item->status==0)item->status=1;
				else{
					item->status=0;
					item->visible=true;
					item->x=item->startx;
					item->y=item->starty;
				}
			}
		}
		if (item->status==0){
			double dist=(item->x-theHero->x)*(item->x-theHero->x)+(item->y-theHero->y)*(item->y-theHero->y);
			if (dist<=1600)item->time=10;
		}
		if (item->status==1){
			double dirX=item->x-theHero->x,dirY=item->y-theHero->y;
			double dist=sqrt(dirX*dirX+dirY*dirY);
			item->x-=dirX/dist*3.0;
			item->y-=dirY/dist*3.0;
			if (Inside(item->x,item->y,x1,y1,x2,y2)||
				Inside(item->x+BLOCK_SIZE_X,item->y,x1,y1,x2,y2)||
				Inside(item->x,item->y+BLOCK_SIZE_Y,x1,y1,x2,y2)||
				Inside(item->x+BLOCK_SIZE_X,item->y+BLOCK_SIZE_Y,x1,y1,x2,y2)){
				item->status=2;
				if (item->type==3)item->time=500;
				item->visible=false;
				if (item->type==1||item->type==3){
					theHero->energy++;
				}else if (item->type==2)reward_count++;
				else unlocked[Selected_Stage+4]=true;
			}
		}
	}
}
void ResetItems(int stage,int x,int y){
	int n=items.size();
	for (int i=0;i<n;i++){
		Item* item=items[i];
		if (item->status==1){
			item->x+=x;
			item->y+=y;
			continue;
		}
		if (item->stage!=stage)item->visible=false;
			else if (item->status==0)item->visible=true;
	}
}
void PutbackItems(){
	int n=items.size();
	for (int i=0;i<n;i++){
		if (items[i]->time>0)items[i]->time=0;
		if (items[i]->status==1){
			items[i]->x=items[i]->startx;
			items[i]->y=items[i]->starty;
			items[i]->status=0;
		}else if (items[i]->type==3&&items[i]->status==2){
			items[i]->x=items[i]->startx;
			items[i]->y=items[i]->starty;
			if (theHero->energy)theHero->energy--;
			items[i]->status=0;
			items[i]->visible=true;
			items[i]->time=0;
		}
	}
}