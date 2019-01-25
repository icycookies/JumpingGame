#include "JumpingGame.h"
using namespace std;
extern HBITMAP bmp_Lock;
extern HBITMAP bmp_STAGE0;
extern HBITMAP bmp_STAGE1;
extern HBITMAP bmp_STAGE2;
extern HBITMAP bmp_STAGE3;
extern HBITMAP bmp_STAGE4;
extern HBITMAP bmp_STAGE5;
extern HBITMAP bmp_AButton;
extern HBITMAP bmp_BButton;
extern vector<Button*> buttons;
extern vector<Menu*> menus;
extern bool on_pause;
extern bool unlocked[110];
extern int info[110][2];
char s[110];
//Ìí¼Ó²Ëµ¥º¯Êý
Menu* CreateMenu(HBITMAP img,int width,int height,int x,int y){
	Menu* menu=new Menu();
	menu->img=img;
	menu->width=width;
	menu->height=height;
	menu->x=x;
	menu->y=y;
	menu->visible=false;
	menu->value=0;
	return menu;
}
void ResetShadow(){
	menus[0]->visible=false;
	menus[0]->value=180;
}
void ShowPauseMenu(){
	menus[0]->visible=true;
	menus[1]->visible=true;
	buttons[5]->visible=true;
	buttons[6]->visible=true;
	buttons[7]->visible=true;
	on_pause=true;
}
void HidePauseMenu(){
	menus[0]->visible=false;
	menus[1]->visible=false;
	buttons[5]->visible=false;
	buttons[6]->visible=false;
	buttons[7]->visible=false;
	on_pause=false;
}
void ShowChapterAbstract(int chapterID){
	menus[2]->visible=true;
	if (!unlocked[chapterID])menus[2]->img=bmp_Lock;
	else if (chapterID==0)menus[2]->img=bmp_STAGE0;
	else if (chapterID==1)menus[2]->img=bmp_STAGE1;
	else if (chapterID==2)menus[2]->img=bmp_STAGE2;
	else if (chapterID==3)menus[2]->img=bmp_STAGE3;
	else if (chapterID==4)menus[2]->img=bmp_STAGE4;
	else if (chapterID==5)menus[2]->img=bmp_STAGE5;
	if (unlocked[chapterID])buttons[10]->visible=true;else buttons[10]->visible=false;
	if (chapterID>=4||unlocked[chapterID+4]){
		buttons[15]->visible=true;
		if (chapterID>=4)buttons[15]->img=bmp_BButton;
		else buttons[15]->img=bmp_AButton;
	}else{
			buttons[15]->img=bmp_AButton;
			buttons[15]->visible=false;
		}
}
void Save(){
	freopen("res\\save\\save.json","w",stdout);
	puts("{");
	printf("	\"stage\" :\"");for (int i=0;i<=5;i++)if (unlocked[i])printf("1");else printf("0");printf("\",\n");
	printf("	\"strawberries\" :\"");for (int i=0;i<5;i++)printf("%d,",info[i][0]);printf("%d\",\n",info[5][0]);
	printf("	\"deaths\" :\"");for (int i=0;i<5;i++)printf("%d,",info[i][1]);printf("%d\",\n",info[5][1]);
	puts("}");
}
void Load(){
	freopen("res\\save\\save.json","r",stdin);
	scanf("%s",s);
	if (s[0]!='{')return;
	scanf("%s",s);
	getchar();getchar();
	scanf("%s",s);
	for (int i=0;i<=5;i++)if (s[i]=='0')unlocked[i]=0;else unlocked[i]=1;
	scanf("%s",s);
	getchar();getchar();getchar();
	for (int i=0;i<5;i++)scanf("%d,",&info[i][0]);scanf("%d",&info[5][0]);
	scanf("%s",s);scanf("%s",s);
	getchar();getchar();getchar();
	for (int i=0;i<5;i++)scanf("%d,",&info[i][1]);scanf("%d",&info[5][1]);
}