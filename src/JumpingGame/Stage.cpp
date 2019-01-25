#include "JumpingGame.h"
#include<ctime>
#include<cstring>
using namespace std;
extern HBITMAP bmp_Background1;
extern HBITMAP bmp_Background2;
extern HBITMAP bmp_Background3;
extern HBITMAP bmp_Background4;
extern HBITMAP bmp_Background5;
extern HBITMAP bmp_shadow;
extern HBITMAP bmp_Hero; //主角图像资源
extern HBITMAP bmp_Enemy; //怪物图像资源
extern HBITMAP bmp_Boss;
extern HBITMAP bmp_Boss1;
extern HBITMAP bmp_Block; //地板图像资源
extern HBITMAP bmp_FragileBlock; //脆弱地板图像资源
extern HBITMAP bmp_Trap; //陷阱图像资源
extern HBITMAP bmp_Checkpoint; //存档点图像资源
extern HBITMAP bmp_Destnation; //终点图像资源
extern HBITMAP bmp_Energy;
extern HBITMAP bmp_Reward;
extern HBITMAP bmp_Bside;
extern HBITMAP bmp_npc;
extern HBITMAP bmp_AButton;
extern Stage* currentStage;
extern Hero* theHero;
extern Bullet* bullet;
extern Boss* boss;
extern vector<Button*> buttons; //按钮
extern vector<Block*> blocks; //地板
extern vector<Item*> items;
extern vector<Particle*> particles;
extern vector<Menu*> menus;
extern vector<Barrage*> barrages;
extern int Selected_Stage;
extern bool unlocked[110];
extern Story* story;
extern bool skip_story;
int map[210][210];
extern int MAP[110][110];
extern int death_count;
extern int reward_count;
extern bool skip_music;

void InitChapter(HWND hWnd,int chapterID){
	if (theHero!=NULL)theHero=NULL;
	memset(MAP,0,sizeof MAP);
	if (chapterID==0){
		freopen("res\\chapter\\chapter1.txt","r",stdin);
		if (!skip_music)PlaySound(TEXT("res\\music2.wav"),NULL,SND_ASYNC|SND_LOOP);
	}
	if (chapterID==1){
		freopen("res\\chapter\\chapter2.txt","r",stdin);
		if (!skip_music)PlaySound(TEXT("res\\music3.wav"),NULL,SND_ASYNC|SND_LOOP);
	}
	if (chapterID==2){
		freopen("res\\chapter\\chapter3.txt","r",stdin);
		if (!skip_music)PlaySound(TEXT("res\\music4.wav"),NULL,SND_ASYNC|SND_LOOP);
	}
	if (chapterID==3){
		freopen("res\\chapter\\chapter4.txt","r",stdin);
		if (!skip_music)PlaySound(TEXT("res\\music5.wav"),NULL,SND_ASYNC|SND_LOOP);
	}
	if (chapterID==4){
		freopen("res\\chapter\\chapter5.txt","r",stdin);
		if (!skip_music)PlaySound(TEXT("res\\music6.wav"),NULL,SND_ASYNC|SND_LOOP);
	}
	if (chapterID==5){
		freopen("res\\chapter\\chapter6.txt","r",stdin);
		if (!skip_music)PlaySound(TEXT("res\\music6.wav"),NULL,SND_ASYNC|SND_LOOP);
	}
	death_count=0;
	reward_count=0;
	items.clear();
	int n,m,startx,starty,cnt,x,y,type,stage;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)scanf("%d",&MAP[i][j]);
	scanf("%d%d",&startx,&starty);
	scanf("%d",&cnt);
	for (int i=1;i<=cnt;i++){
		scanf("%d%d%d%d",&x,&y,&type,&stage);
		if (type==1)items.push_back(CreateItem(bmp_Energy,x,y,stage,type));
		else if (type==2)items.push_back(CreateItem(bmp_Reward,x,y,stage,type));
		else if (type==3)items.push_back(CreateItem(bmp_Energy,x,y,stage,type));
		else if (type==4)items.push_back(CreateItem(bmp_Bside,x,y,stage,type));
	}
	fclose(stdin);
	InitStage(hWnd,MAP[startx][starty],0,0);
	//InitStage(hWnd,22,0,0);
}
void ReadMap(int StageID){
	// 初始化地图
	for (int i=0;i<blocks.size();i++){
		Block* block=blocks[i];
		delete block;
	}
	blocks.clear();
	for (int i=0;i<barrages.size();i++){
		Barrage* barrage=barrages[i];
		delete barrage;
	}
	barrages.clear();
	boss=NULL;
	switch (StageID){
		case 1:
			freopen("res\\stage\\stage0.txt","r",stdin);
			break;
		case 2:
			freopen("res\\stage\\stage1.txt","r",stdin);
			break;
		case 3:
			freopen("res\\stage\\stage2.txt","r",stdin);
			break;
		case 4:
			freopen("res\\stage\\stage3.txt","r",stdin);
			break;
		case 5:
			freopen("res\\stage\\stage4.txt","r",stdin);
			break;
		case 6:
			freopen("res\\stage\\stage5.txt","r",stdin);
			break;
		case 7:
			freopen("res\\stage\\stage6.txt","r",stdin);
			break;
		case 8:
			freopen("res\\stage\\stage7.txt","r",stdin);
			break;
		case 9:
			freopen("res\\stage\\stage8.txt","r",stdin);
			break;
		case 10:
			freopen("res\\stage\\stage9.txt","r",stdin);
			break;
		case 11:
			freopen("res\\stage\\stage10.txt","r",stdin);
			break;
		case 12:
			freopen("res\\stage\\stage11.txt","r",stdin);
			break;
		case 13:
			freopen("res\\stage\\stage12.txt","r",stdin);
			break;
		case 14:
			freopen("res\\stage\\stage13.txt","r",stdin);
			break;
		case 15:
			freopen("res\\stage\\stage14.txt","r",stdin);
			break;
		case 16:
			freopen("res\\stage\\stage15.txt","r",stdin);
			break;
		case 17:
			freopen("res\\stage\\stage16.txt","r",stdin);
			boss=CreateBoss(bmp_Boss,390,120,0);
			break;
		case 18:
			freopen("res\\stage\\stage17.txt","r",stdin);
			break;
		case 19:
			freopen("res\\stage\\stage18.txt","r",stdin);
			break;
		case 20:
			freopen("res\\stage\\stage19.txt","r",stdin);
			break;
		case 21:
			freopen("res\\stage\\stage20.txt","r",stdin);
			break;
		case 22:
			freopen("res\\stage\\stage21.txt","r",stdin);
			break;
		case 23:
			freopen("res\\stage\\stage22.txt","r",stdin);
			break;
		case 24:
			freopen("res\\stage\\stage23.txt","r",stdin);
			boss=CreateBoss(bmp_Boss1,390,90,1);
			break;
	}
	int n,m,un,lm;
	scanf("%d%d%d%d",&n,&m,&un,&lm);
	currentStage->n=n;
	currentStage->m=m;
	currentStage->un=un;
	currentStage->lm=lm;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			scanf("%d",&map[i][j]);				
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++){
			int p=0,q=4;
			if (!j||map[i][j-1]!=1)p+=8;else q=3;
			if (i==n-1||map[i+1][j]!=1)p+=4;else q=2;
			if (j==m-1||map[i][j+1]!=1)p+=2;else q=1;
			if (!i||map[i-1][j]!=1)p++;else q=0;
			int x=j*BLOCK_SIZE_X,y=i*BLOCK_SIZE_Y;
			if (map[i][j]==1)blocks.push_back(CreateBlock(bmp_Block,x,y,x,y,1,p,0,0));
			else if (map[i][j]==2)blocks.push_back(CreateBlock(bmp_Trap,x,y,x,y,2,q,0,0));
			else if (map[i][j]==3)blocks.push_back(CreateBlock(bmp_Checkpoint,x,y,x,y,3,0,0,0));
			else if (map[i][j]==4)blocks.push_back(CreateBlock(bmp_Destnation,x,y,x,y,4,0,0,0));
			else if (map[i][j]==5)blocks.push_back(CreateBlock(bmp_FragileBlock,x,y,x,y,6,0,0,0));
		}
	int cnt,x,y,startx,starty,endx,endy,T,frame,type,value;
	scanf("%d",&cnt);
	for (int i=0;i<cnt;i++){
		scanf("%d%d%d%d%d%d",&startx,&starty,&endx,&endy,&T,&frame);
		blocks.push_back(CreateBlock(bmp_Enemy,startx,starty,endx,endy,5,frame,T,0));
	}
	scanf("%d",&cnt);
	for (int i=0;i<cnt;i++){
		scanf("%d%d%d%d%d%d",&startx,&starty,&endx,&endy,&T,&frame);
		blocks.push_back(CreateBlock(bmp_Block,startx,starty,endx,endy,7,frame,T,0));
	}
	scanf("%d",&cnt);
	for (int i=0;i<cnt;i++){
		scanf("%d%d%d%d%d%d%d",&startx,&starty,&endx,&endy,&T,&frame,&value);
		blocks.push_back(CreateBlock(bmp_Trap,(starty-1)*BLOCK_SIZE_Y,(startx-1)*BLOCK_SIZE_X,(endy-1)*BLOCK_SIZE_Y,(endx-1)*BLOCK_SIZE_X,8,frame,T,value));
		if (!value)blocks[blocks.size()-1]->visible=false;
	}
	scanf("%d",&cnt);
	for (int i=0;i<cnt;i++){
		scanf("%d%d%d%d%d",&x,&y,&value,&type,&frame);
		if (!type)blocks.push_back(CreateBlock(bmp_Block,(y-1)*BLOCK_SIZE_Y,(x-1)*BLOCK_SIZE_X,(y-1)*BLOCK_SIZE_Y,(x-1)*BLOCK_SIZE_X,9,frame,0,value));
		else blocks.push_back(CreateBlock(bmp_Trap,(y-1)*BLOCK_SIZE_Y,(x-1)*BLOCK_SIZE_X,(y-1)*BLOCK_SIZE_Y,(x-1)*BLOCK_SIZE_X,10,frame,0,value));
		blocks[blocks.size()-1]->visible=false;
	}
	scanf("%d",&cnt);
	for (int i=0;i<cnt;i++){
		scanf("%d%d%d",&x,&y,&frame);
		if (!skip_story)blocks.push_back(CreateBlock(bmp_npc,y*BLOCK_SIZE_Y,x*BLOCK_SIZE_X,y*BLOCK_SIZE_X,x*BLOCK_SIZE_Y,11,frame,0,0));
	}
	fclose(stdin);
	if(StageID!=17&&StageID!=24)CreateAnimation(6,40,0,0);
}
void loadHero(){
	if (theHero == NULL){
		theHero=new Hero();
		theHero = CreateHero(bmp_Hero, currentStage->x, currentStage->y,currentStage->stageID,0);
	}else theHero->x=currentStage->x,theHero->y=currentStage->y;	
}
void LoadStaticStage(){
	currentStage->time=0;
	currentStage->timerOn=true;
	currentStage->n=20;
	currentStage->m=40;
}
void loadStage(int stageID,int X,int Y,int x,int y,int newx,int newy){
	ResetShadow();
	currentStage->time=0;
	currentStage->timerOn=true;
	currentStage->X=X;
	currentStage->Y=Y;
	if (!x&&!y)currentStage->x=newx,currentStage->y=newy;
		else currentStage->x=theHero->x+x,currentStage->y=theHero->y+y;
	for(int i=0;i<buttons.size();i++){
		Button* button = buttons[i];
		if (button->buttonID==BUTTON_PAUSE)button->visible=true;
		else button->visible=false;
	}
	ReadMap(stageID-3);
	loadHero();
	ResetItems(stageID,x,y);
	bullet=NULL;
}
// 初始化游戏场景函数
void InitStage(HWND hWnd, int stageID,int x,int y){
	// 初始化场景实例
	HBITMAP img;
	if (currentStage != NULL) {img=currentStage->bg;delete currentStage;}
	currentStage = new Stage();
	currentStage->stageID = stageID;

	for (int i=0;i<particles.size();i++){
		Particle* particle=particles[i];
		delete particle;
	}
	particles.clear();

	for (int i=0;i<menus.size();i++)menus[i]->visible=false;

	if (stageID == STAGE_STARTMENU){
		LoadStaticStage();
		currentStage->bg = bmp_Background1;
		for(int i=0;i<buttons.size();i++){
			Button* button = buttons[i];
			if (button->buttonID>=BUTTON_STARTGAME&&button->buttonID<=BUTTON_EXIT)button->visible = true;
			else button->visible=false;
		}
		CreateAnimation(1,50,0,0);
	}
	if (stageID==STAGE_OPTION){
		LoadStaticStage();
		currentStage->bg=bmp_shadow;
		for (int i=0;i<buttons.size();i++){
			Button* button=buttons[i];
			if (button->buttonID>=BUTTON_MUSICON&&button->buttonID<=BUTTON_STORYON||button->buttonID==BUTTON_RETURN1)button->visible=true;
			else button->visible=false;
		}
		CreateAnimation(5,100,0,0);
		menus[3]->visible=true;
	}
	if (stageID==STAGE_SELECT){
		Selected_Stage=0;
		LoadStaticStage();
		currentStage->bg=img;
		for (int i=0;i<buttons.size();i++){
			buttons[i]->visible=false;
			if (buttons[i]->buttonID==BUTTON_FLIP)buttons[i]->img=bmp_AButton;
		}
		menus[0]->value=0;
		menus[0]->visible=true;
		CreateAnimation(5,100,0,0);
	}
	if(stageID==STAGE_STORY){
		LoadStaticStage();
		currentStage->bg=bmp_Background5;
		for (int i=0;i<buttons.size();i++){
			Button* button=buttons[i];
			if (button->buttonID==BUTTON_SKIP)button->visible=true;
			else button->visible=false;
		}
		story->on=true;
		if (x)freopen("res\\story\\story4.txt","r",stdin);
		else{
			switch (Selected_Stage){
			case 0:
				freopen("res\\story\\story0.txt","r",stdin);
				break;
			case 1:
				freopen("res\\story\\story1.txt","r",stdin);
				break;
			case 2:
				freopen("res\\story\\story2.txt","r",stdin);
				break;
			case 3:
				freopen("res\\story\\story3.txt","r",stdin);
				break;
			case 4:
				freopen("res\\story\\story5.txt","r",stdin);
				break;
			case 5:
				freopen("res\\story\\story6.txt","r",stdin);
				break;
			}
		}
		scanf("%s",story->s);
		CreateAnimation(6,30,0,0);
	}
	if (stageID==STAGE_HELP){
		LoadStaticStage();
		currentStage->bg=bmp_Background3;
		for(int i=0;i<buttons.size();i++){
			Button* button = buttons[i];
			if (button->buttonID==BUTTON_RETURN1)button->visible=true;
			else button->visible=false;
		}
		CreateAnimation(6,40,0,0);
	}
	if (stageID==4){
		currentStage->bg=bmp_Background2;
		//currentStage->bg=bmp_shadow;
		loadStage(stageID,1,1,x,y,30,540);
	}
	if (stageID==5){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,1,2,x,y,30,540);
	}
	if (stageID==6){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,2,2,x,y,30,540);
	}
	if (stageID==7){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,2,1,x,y,30,540);
	}
	if (stageID==8){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,2,2,x,y,30,1140);
	}
	if (stageID==9){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,2,3,x,y,30,1140);
	}
	if (stageID==10){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,3,3,x,y,1140,90);
	}
	if (stageID==11){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,2,1,x,y,1140,30);
	}
	if (stageID==12){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,3,1,x,y,270,30);
	}
	if (stageID==13){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,3,1,x,y,210,30);
	}
	if (stageID==14){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,3,2,x,y,30,30);
	}
	if (stageID==15){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,3,3,x,y,30,30);
	}
	if (stageID==16){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,2,3,x,y,30,3540);
	}
	if (stageID==17){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,1,3,x,y,30,1740);
	}
	if (stageID==18){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,1,2,x,y,1140,30);
	}
	if (stageID==19){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,2,2,x,y,210,30);
	}
	if (stageID==20){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,1,1,x,y,30,540);
	}
	if (stageID==21){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,1,4,x,y,30,540);
	}
	if (stageID==22){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,1,5,x,y,780,30);
	}
	if (stageID==23){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,2,5,x,y,780,30);
	}
	if (stageID==24){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,1,3,x,y,780,30);
	}
	if (stageID==25){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,1,2,x,y,780,30);
	}
	if (stageID==26){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,1,1,x,y,780,30);
	}
	if (stageID==27){
		currentStage->bg=bmp_Background2;
		loadStage(stageID,1,1,x,y,540,540);
	}
	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}