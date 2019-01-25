// JumpingGame.cpp : ����Ӧ�ó������ڵ㡣
//

#include "JumpingGame.h"

using namespace std;



#pragma region ȫ�ֱ���

#define MAX_LOADSTRING			100		

// ȫ�ֱ���: 
HINSTANCE hInst; // ��ǰ����ʵ��
WCHAR szTitle[MAX_LOADSTRING]; // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING]; // ����������


// TODO: �ڴ��������ȫ�ֱ���

HBITMAP bmp_Background1; //����ͼ����Դ
HBITMAP bmp_Background2;
HBITMAP bmp_Background3;
HBITMAP bmp_Background4;
HBITMAP bmp_Background5;
HBITMAP bmp_shadow;	//��ͣ�˵���Դ
HBITMAP bmp_PauseMenu;
HBITMAP bmp_OptionMenu;
HBITMAP bmp_Lock;
HBITMAP bmp_STAGE0;
HBITMAP bmp_STAGE1;	
HBITMAP bmp_STAGE2;
HBITMAP bmp_STAGE3;
HBITMAP bmp_STAGE4;
HBITMAP bmp_STAGE5;
HBITMAP bmp_StartButton; //��ʼ��ťͼ����Դ
HBITMAP bmp_OptionButton;
HBITMAP bmp_HelpButton;
HBITMAP bmp_ExitButton; //�˳���ťͼ����Դ
HBITMAP bmp_PauseButton; //��ͣ��ťͼ����Դ
HBITMAP bmp_ResumeButton;	//������ťͼ����Դ
HBITMAP bmp_RestartButton;	//���¿�ʼ��ťͼ����Դ
HBITMAP bmp_ReturnButton;	//�������˵�ͼ����Դ
HBITMAP bmp_PreStageButton;
HBITMAP bmp_NextStageButton;
HBITMAP bmp_ReturnButton1;
HBITMAP bmp_OnButton;
HBITMAP bmp_OffButton;
HBITMAP bmp_AButton;
HBITMAP bmp_BButton;
HBITMAP bmp_Hero; //����ͼ����Դ
HBITMAP bmp_Hero_large;
HBITMAP bmp_Bullet;
HBITMAP bmp_Boss;
HBITMAP bmp_Boss1;
HBITMAP bmp_Barrage1;
HBITMAP bmp_Barrage2;
HBITMAP bmp_Barrage3;
HBITMAP bmp_npc;
HBITMAP bmp_npc_large;
HBITMAP bmp_Enemy; //����ͼ����Դ
HBITMAP bmp_Block; //�ذ�ͼ����Դ
HBITMAP bmp_FragileBlock; //�����ذ�ͼ����Դ
HBITMAP bmp_Trap; //����ͼ����Դ
HBITMAP bmp_Checkpoint; //�浵��ͼ����Դ
HBITMAP bmp_Destnation; //�յ�ͼ����Դ
HBITMAP bmp_Energy;
HBITMAP bmp_Reward;
HBITMAP bmp_Bside;
HBITMAP bmp_Info;

int Selected_Stage;
bool unlocked[110];
int info[110][2];
int death_count;
int reward_count;

const int max_reward[6]={12,18,18,2,5,0};

Stage* currentStage = NULL; //��ǰ����״̬
Hero* theHero=NULL;
Bullet* bullet=NULL;
Boss* boss=NULL;
Story* story=NULL;
Charactor* charactorL=NULL;
Charactor* charactorR=NULL;
vector<Barrage*> barrages;
vector<Button*> buttons; //��ť
vector<Block*> blocks; //�ذ�
vector<Item*> items;
vector<Particle*> particles;//����
vector<Menu*> menus;
int MAP[110][110];

int mouseX = 0;
int mouseY = 0;
bool mouseDown = false;
bool keyUpDown = false;
bool keyDownDown = false;
bool keyLeftDown = false;
bool keyRightDown = false;
bool keyEscDown=false;
bool keySpaceDown=false;

bool on_pause=false;
bool on_story=false;
bool skip_music=false;
bool skip_particle=false;
bool skip_story=false;

double const PI = acos(double(-1));
double const eps=1e-8;
#pragma endregion



#pragma region Win32������



// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_JUMPINGGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JUMPINGGAME));

    MSG msg;

    // ����Ϣѭ��: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_JUMPINGGAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   HWND hWnd = CreateWindow(szWindowClass, szTitle,
	   WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // ���ô�����ʽ�����ɸı��С���������,
	   CW_USEDEFAULT, 
	   CW_USEDEFAULT,
	   WINDOW_WIDTH,
	   WINDOW_HEIGHT + WINDOW_TITLEBARHEIGHT,
	   nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		// ��ʼ����Ϸ����
		InitGame(hWnd, wParam, lParam);
		break;
	case WM_KEYDOWN:
		// ���̰����¼�
		KeyDown(hWnd, wParam, lParam);
		break;
	case WM_KEYUP:
		// �����ɿ��¼�
		KeyUp(hWnd, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		// ����ƶ��¼�
		MouseMove(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONDOWN:
		// �����������¼�
		LButtonDown(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		// �������ɿ��¼�
		LButtonUp(hWnd, wParam, lParam);
		break;
	case WM_TIMER:
		// ��ʱ���¼�
		if(currentStage!=NULL && currentStage->timerOn) TimerUpdate(hWnd, wParam, lParam);
		break;
    case WM_PAINT:
		// ��ͼ
		Paint(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


#pragma endregion




#pragma region �¼�������

// ��ʼ����Ϸ���庯��
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//����ͼ����Դ
	bmp_Background1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BG1));
	bmp_Background2=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BG2));
	bmp_Background3=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BG3));
	bmp_Background4=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BG4));
	bmp_Background5=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BG5));
	bmp_shadow=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SHADOW));
	bmp_PauseMenu=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PAUSEMENU));
	bmp_OptionMenu=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_OPTIONMENU));
	bmp_Lock=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_LOCK));
	bmp_STAGE0=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STAGE0));
	bmp_STAGE1=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STAGE1));
	bmp_STAGE2=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STAGE2));
	bmp_STAGE3=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STAGE3));
	bmp_STAGE4=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STAGE4));
	bmp_STAGE5=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_STAGE5));
	bmp_StartButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_START));
	bmp_OptionButton=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_OPTION));
	bmp_HelpButton=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HELP));
	bmp_ExitButton=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_EXIT));
	bmp_PauseButton=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PAUSE));
	bmp_ResumeButton=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RESUME));
	bmp_RestartButton=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RESTART));
	bmp_ReturnButton=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RETURN));
	bmp_PreStageButton=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PRESTAGE));
	bmp_NextStageButton=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_NEXTSTAGE));
	bmp_ReturnButton1=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RETURN1));
	bmp_OnButton=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_ONBUTTON));
	bmp_OffButton=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_OFFBUTTON));
	bmp_AButton=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BUTTONA));
	bmp_BButton=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BUTTONB));
	bmp_Hero = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HERO));
	bmp_Hero_large=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HEROLARGE));
	bmp_npc=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_NPC));
	bmp_npc_large=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_NPCLARGE));
	bmp_Bullet=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BULLET));
	bmp_Boss=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BOSS));
	bmp_Boss1=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BOSS1));
	bmp_Barrage1=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BARRAGE1));
	bmp_Barrage2=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BARRAGE2));
	bmp_Barrage3=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BARRAGE3));
	bmp_Enemy=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_ENEMY));
	bmp_Block=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BLOCK1));
	bmp_FragileBlock=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BLOCK2));
	bmp_Trap=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_TRAP1));
	bmp_Checkpoint=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_CHECKPOINT1));
	bmp_Destnation=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_DESTNATION));
	bmp_Energy=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_ENERGY));
	bmp_Reward=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_REWARD));
	bmp_Bside=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BSIDE));
	bmp_Info=LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_INFO));

	//��Ӳ˵�
	Menu* shadow=CreateMenu(bmp_shadow,WINDOW_WIDTH,WINDOW_HEIGHT,0,0);shadow->value=180;
	Menu* pauseMenu=CreateMenu(bmp_PauseMenu,210,60,400,0);
	Menu* stageMenu=CreateMenu(bmp_STAGE0,600,400,200,100);
	Menu* optionMenu=CreateMenu(bmp_OptionMenu,300,300,200,130);
	menus.push_back(shadow);
	menus.push_back(pauseMenu);
	menus.push_back(stageMenu);
	menus.push_back(optionMenu);

	//��Ӱ�ť
	Button* startButton = CreateButton(BUTTON_STARTGAME,bmp_StartButton,210,60,50,50);
	Button* optionButton=CreateButton(BUTTON_OPTION,bmp_OptionButton,210,60,50,130);
	Button* helpButton=CreateButton(BUTTON_HELP,bmp_HelpButton,210,60,50,210);
	Button* exitButton=CreateButton(BUTTON_EXIT,bmp_ExitButton,210,60,50,290);
	Button* pauseButton=CreateButton(BUTTON_PAUSE,bmp_PauseButton,100,100,50,800);
	Button* resumeButton=CreateButton(BUTTON_RESUME,bmp_ResumeButton,210,60,400,120);
	Button* restartButton=CreateButton(BUTTON_RESTART,bmp_RestartButton,210,60,400,200);
	Button* returnButton=CreateButton(BUTTON_RETURN,bmp_ReturnButton,240,60,380,280);
	Button* preButton=CreateButton(BUTTON_PRESTAGE,bmp_PreStageButton,50,100,140,250);
	Button* nextButton=CreateButton(BUTTON_NEXTSTAGE,bmp_NextStageButton,50,100,810,250);
	Button* gameButton=CreateButton(BUTTON_START,bmp_StartButton,200,60,400,510);
	Button* returnButton1=CreateButton(BUTTON_RETURN1,bmp_ReturnButton1,50,50,20,20);
	Button* musiconButton=CreateButton(BUTTON_MUSICON,bmp_OnButton,160,60,600,150);
	Button* particleonButton=CreateButton(BUTTON_PARTICLEON,bmp_OnButton,160,60,600,250);
	Button* storyonButton=CreateButton(BUTTON_STORYON,bmp_OnButton,160,60,600,350);
	Button* flipButton=CreateButton(BUTTON_FLIP,bmp_AButton,50,50,175,275);
	buttons.push_back(startButton);
	buttons.push_back(optionButton);
	buttons.push_back(helpButton);
	buttons.push_back(exitButton);
	buttons.push_back(pauseButton);
	buttons.push_back(resumeButton);
	buttons.push_back(restartButton);
	buttons.push_back(returnButton);
	buttons.push_back(preButton);
	buttons.push_back(nextButton);
	buttons.push_back(gameButton);
	buttons.push_back(returnButton1);
	buttons.push_back(musiconButton);
	buttons.push_back(particleonButton);
	buttons.push_back(storyonButton);
	buttons.push_back(flipButton);

	//��ʼ����ʼ����
	InitStage(hWnd, STAGE_STARTMENU,0,0);

	//��ʼ������ʱ��
	SetTimer(hWnd, TIMER_GAMETIMER, TIMER_GAMETIMER_ELAPSE, NULL);

	unlocked[0]=true;
	for (int i=1;i<=10;i++)unlocked[i]=false;
	//for (int i=1;i<=10;i++)unlocked[i]=true;
	for (int i=0;i<=10;i++)info[i][1]=-1;

	story=CreateStory(0,0);
	charactorL=CreateCharactor(bmp_Hero_large);
	charactorR=CreateCharactor(bmp_npc_large);

	PlaySound(TEXT("res\\music1.wav"),NULL,SND_ASYNC|SND_LOOP);
}

// ���̰����¼�������
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_UP:
		keyUpDown = true;
		break;
	case VK_DOWN:
		keyDownDown = true;
		break;
	case VK_LEFT:
		keyLeftDown = true;
		break;
	case VK_RIGHT:
		keyRightDown = true;
		break;
	case VK_ESCAPE:
		keyEscDown=true;
		break;
	case VK_SPACE:
		keySpaceDown=true;
		break;
	default:
		break;
	}
}

// �����ɿ��¼�������
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// TODO
	switch (wParam)
	{
	case VK_UP:
		keyUpDown = false;
		break;
	case VK_DOWN:
		keyDownDown = false;
		break;
	case VK_LEFT:
		keyLeftDown = false;
		break;
	case VK_RIGHT:
		keyRightDown = false;
		break;
	case VK_ESCAPE:
		keyEscDown=false;
		break;
	case VK_SPACE:
		keySpaceDown=false;
		break;
	default:
		break;
	}
}

// ����ƶ��¼�������
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
}

// �����������¼�������
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = true;

	for(int i=0;i<buttons.size();i++){
		Button* button = buttons[i];
		if (button->visible){
			if (button->x <= mouseX&& button->x + button->width >= mouseX&& button->y <= mouseY&& button->y + button->height >= mouseY){
				switch (button->buttonID){
					case BUTTON_STARTGAME:{
						Load();
						InitStage(hWnd,STAGE_SELECT,0,0);
						buttons[15]->img=bmp_AButton;
						//InitChapter(hWnd,1);
					}
					break;
					case BUTTON_OPTION:{
						InitStage(hWnd,STAGE_OPTION,0,0);
					}
					break;
					case BUTTON_HELP:{
						InitStage(hWnd,STAGE_HELP,0,0);				 
					}
					break;
					case BUTTON_EXIT:{
						PostQuitMessage(0);
					}
					case BUTTON_PAUSE:{
						ShowPauseMenu();
					}
					break;
					case BUTTON_RESUME:{
						HidePauseMenu();
					}
					break;
					case BUTTON_RESTART:{
						HidePauseMenu();
						reborn(hWnd);
					}
					break;
					case BUTTON_RETURN:{
						HidePauseMenu();
						//delete theHero;
						story->on=false;
						charactorL->visible=charactorR->visible=false;
						Save();
						PlaySound(TEXT("res\\music1.wav"),NULL,SND_ASYNC|SND_LOOP);
						InitStage(hWnd,STAGE_STARTMENU,0,0);
					}
					break;
					case BUTTON_START:{
						//InitChapter(hWnd,Selected_Stage);		
						if (skip_story)InitChapter(hWnd,Selected_Stage);
							else InitStage(hWnd,STAGE_STORY,0,0);
					}
					break;
					case BUTTON_PRESTAGE:{
						if (Selected_Stage>=4)Selected_Stage-=4;
						Selected_Stage--;
						ShowChapterAbstract(Selected_Stage);
						buttons[9]->visible=true;
						if (!Selected_Stage)buttons[8]->visible=false;
					}
					break;
					case BUTTON_NEXTSTAGE:{
						if (Selected_Stage>=4)Selected_Stage-=4;
						Selected_Stage++;
						ShowChapterAbstract(Selected_Stage);
						buttons[8]->visible=true;
						if (Selected_Stage==3)buttons[9]->visible=false;
					}
					break;
					case BUTTON_RETURN1:{
						menus[3]->visible=false;
						InitStage(hWnd,STAGE_STARTMENU,0,0);				
					}
					break;
					case BUTTON_MUSICON:{
						if (!skip_music){
							skip_music=true;
							buttons[12]->img=bmp_OffButton;
							PlaySound(NULL,NULL,SND_PURGE);
						}else{
							skip_music=false;
							buttons[12]->img=bmp_OnButton;
							PlaySound(TEXT("res\\music1.wav"),NULL,SND_ASYNC|SND_LOOP);
						}		
					}
					break;
					case BUTTON_PARTICLEON:{
						if (!skip_particle){
							skip_particle=true;
							for (int i=0;i<particles.size();i++){
								Particle* particle=particles[i];
								delete particle;
							}
							particles.clear();
							buttons[13]->img=bmp_OffButton;
						}else{
							skip_particle=false;
							CreateAnimation(5,100,0,0);
							buttons[13]->img=bmp_OnButton;
						}		
					}
					break;
					case BUTTON_STORYON:{
						if (!skip_story){
							skip_story=true;
							buttons[14]->img=bmp_OffButton;
						}else{
							skip_story=false;
							buttons[14]->img=bmp_OnButton;
						}		
					}
					break;
					case BUTTON_FLIP:{
						if (Selected_Stage<4){
							Selected_Stage+=4;
							buttons[15]->img=bmp_BButton;
						}else{
							Selected_Stage-=4;
							buttons[15]->img=bmp_AButton;
						}
						ShowChapterAbstract(Selected_Stage);
					}
					break;
				}
			}
		}
	}

}

// �������ɿ��¼�������
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = false;
}

// ��ʱ���¼�������
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam){
	if (currentStage!=NULL){
		if (keyEscDown&&currentStage->stageID>=STAGE_0&&!story->on)ShowPauseMenu();
		if (currentStage->stageID==STAGE_SELECT){
			if (currentStage->time<100){
				currentStage->time++;
				if (currentStage->time<=50)menus[0]->value+=5;else menus[0]->value-=5;
				if (currentStage->time==50){
					currentStage->bg=bmp_Background1;
					for (int i=0;i<buttons.size();i++){
						Button* button=buttons[i];
						if (button->buttonID==BUTTON_START||button->buttonID==BUTTON_NEXTSTAGE||button->buttonID==BUTTON_RETURN1)button->visible=true;
						else button->visible=false;
					}
					ShowChapterAbstract(0);
				}
			}
		}
		UpdateParticles();
	}
	if (story->on){
		if (story->time/5*2>=strlen(story->s)){
			if (keySpaceDown){
				story->time=0;
				scanf("%s",story->s);
				if (story->s[0]=='#'&&story->s[1]=='#'){
					//delete story;
					story->on=false;
					if (currentStage->stageID==STAGE_STORY)InitChapter(hWnd,Selected_Stage);
					else{
						menus[0]->visible=false;
						charactorL->visible=false;
						charactorR->visible=false;
					}
				}else if (story->s[0]=='%'&&story->s[1]=='%'){
					story->on=false;
					InitStage(hWnd,STAGE_SELECT,0,0);
				}else if (currentStage->stageID!=STAGE_STORY){
					if (charactorR->visible)charactorL->visible=true,charactorR->visible=false;
					else charactorL->visible=false,charactorR->visible=true;
				}
			}
		}else story->time++;
	}else if (currentStage->stageID>=STAGE_0&&currentStage->stageID!=STAGE_HELP&&!on_pause){
		UpdateHero(hWnd);
		UpdateBlocks();
		UpdateItems();
		if (boss!=NULL)UpdateBoss(hWnd);
	}

	//ˢ����ʾ
	InvalidateRect(hWnd, NULL, FALSE);
}


#pragma endregion


#pragma region ������Ϸ״̬������



//TODO: �����Ϸ��Ҫ�ĸ��ຯ��
// ��Ӱ�ť����
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y){
	Button* button = new Button();
	button->buttonID = buttonID;
	button->img = img;
	button->width = width;
	button->height = height;
	button->x = x;
	button->y = y;
	button->visible = false;
	return button;
}
Story* CreateStory(int x,int y){
	Story* story=new Story();
	story->on=false;
	story->x=x;
	story->y=y;
	story->s[0]='\0';
	story->time=0;
	return story;
}
Charactor* CreateCharactor(HBITMAP img){
	Charactor* charactor=new Charactor();
	charactor->img=img;
	charactor->visible=false;
	charactor->frame=0;
	return charactor;
}

#pragma endregion


#pragma region ��ͼ����
// ��ͼ����
void Paint(HWND hWnd){
	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);

	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);
	//��ʼ������
	HBITMAP	blankBmp = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, blankBmp);

	// ���Ʊ���������
	SelectObject(hdc_loadBmp, currentStage->bg);
	BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

	int deltaX=0,deltaY=0;
	// ����������������ݵ�����
	if (currentStage->stageID<STAGE_0||currentStage->stageID==STAGE_HELP){

	}else{
		int centerX=theHero->x+HERO_SIZE_X/2,centerY=theHero->y+HERO_SIZE_Y/2;
		if (currentStage->m*30>WINDOW_WIDTH)deltaX=max(centerX-WINDOW_WIDTH/2,0)-max(centerX+WINDOW_WIDTH/2-currentStage->m*BLOCK_SIZE_X,0);
		if (currentStage->n*30>WINDOW_HEIGHT)deltaY=max(centerY-WINDOW_HEIGHT/2,0)-max(centerY+WINDOW_HEIGHT/2-currentStage->n*BLOCK_SIZE_Y,0);
		//���Ƶذ嵽����
		for (int i=0;i<blocks.size();i++){
			Block* block=blocks[i];
			if (block->visible||block->type==6){
				int x,y,z;
				if (block->type==3)x=0,y=0,z=0;
				else x=255,y=255,z=255;
				SelectObject(hdc_loadBmp, block->img);
				TransparentBlt(
					hdc_memBuffer, block->x-deltaX, block->y-deltaY,
					BLOCK_SIZE_X, BLOCK_SIZE_Y,
					hdc_loadBmp,block->frame%4*BLOCK_SIZE_X,block->frame/4*BLOCK_SIZE_Y,BLOCK_SIZE_X, BLOCK_SIZE_Y,
					RGB(x,y,z)
				);
			}
		}
		// �������ǵ�����
		if (!theHero->death_delay){
			SelectObject(hdc_loadBmp, theHero->img);
			TransparentBlt(
				hdc_memBuffer, theHero->x-deltaX, theHero->y-deltaY,
				HERO_SIZE_X, HERO_SIZE_Y,
				hdc_loadBmp, 0, HERO_SIZE_Y * theHero->frame, HERO_SIZE_X, HERO_SIZE_Y,
				RGB(255, 255, 255)
			);
		}
		if (bullet!=NULL){
			SelectObject(hdc_loadBmp, bmp_Bullet);
			TransparentBlt(
				hdc_memBuffer, bullet->x-deltaX, bullet->y-deltaY,
				BLOCK_SIZE_X, BLOCK_SIZE_Y,
				hdc_loadBmp,  BLOCK_SIZE_X * bullet->frame,0, BLOCK_SIZE_X, BLOCK_SIZE_Y,
				RGB(0, 0, 0)
			);
		}
		if (boss!=NULL){
			SelectObject(hdc_loadBmp, boss->img);
			TransparentBlt(
				hdc_memBuffer, boss->x-deltaX, boss->y-deltaY,
				BOSS_WIDTH, BOSS_HEIGHT,
				hdc_loadBmp,  boss->Time*BOSS_WIDTH,0, BOSS_WIDTH, BOSS_HEIGHT,
				RGB(0, 0, 0)
			);
			for (int i=0;i<barrages.size();i++){
				Barrage* barrage=barrages[i];
				SelectObject(hdc_loadBmp, barrage->img);
				TransparentBlt(
					hdc_memBuffer, barrage->x-deltaX, barrage->y-deltaY,
					barrage->width, barrage->height,
					hdc_loadBmp,barrage->frame*barrage->width,0,barrage->width, barrage->height,
					RGB(0,0,0)
				);
			}
		}
		for (int i=0;i<items.size();i++){
			Item* item=items[i];
			if (item->visible){
				SelectObject(hdc_loadBmp, item->img);
				TransparentBlt(
					hdc_memBuffer, item->x-deltaX, item->y-deltaY,
					BLOCK_SIZE_X, BLOCK_SIZE_Y,
					hdc_loadBmp,item->frame%4*BLOCK_SIZE_X,item->frame/4*BLOCK_SIZE_Y,BLOCK_SIZE_X, BLOCK_SIZE_Y,
					RGB(255,255,255)
				);
			}
		}
	}
	//���Ʋ˵�������
	if (menus[0]->visible){
		BLENDFUNCTION blend;
		blend.BlendOp=AC_SRC_OVER;
		blend.BlendFlags=0;
		blend.AlphaFormat=0;
		blend.SourceConstantAlpha=menus[0]->value;
		SelectObject(hdc_loadBmp, menus[0]->img);
		AlphaBlend(hdc_memBuffer,0,0,
				   WINDOW_WIDTH,WINDOW_HEIGHT,
				   hdc_loadBmp,0,0,WINDOW_WIDTH,WINDOW_HEIGHT,
				   blend);
	}
	for (int i=1;i<menus.size();i++){
		Menu* menu=menus[i];
		if (menu->visible){
			SelectObject(hdc_loadBmp, menu->img);
			if (i==1)TransparentBlt(
				hdc_memBuffer, menu->x, menu->y,
				menu->width, menu->height,
				hdc_loadBmp, 0, 0, menu->width, menu->height,
				RGB(0, 0, 0)
				);
			else TransparentBlt(
				hdc_memBuffer, menu->x, menu->y,
				menu->width, menu->height,
				hdc_loadBmp, 0, 0, menu->width, menu->height,
				RGB(0, 0, 1)
				);
		}
	}
	// ���ư�ť������
	for(int i=0;i<buttons.size();i++){
		Button* button = buttons[i];
		if (button->visible){
			SelectObject(hdc_loadBmp, button->img);
			TransparentBlt(
				hdc_memBuffer, button->x, button->y,
				button->width, button->height,
				hdc_loadBmp, 0, 0, button->width, button->height,
				RGB(0,0,0)
			);
		}
	}
	if (story->on){
		BLENDFUNCTION blend;
		blend.BlendOp=AC_SRC_OVER;
		blend.BlendFlags=0;
		blend.AlphaFormat=0;
		blend.SourceConstantAlpha=150;
		SelectObject(hdc_loadBmp, bmp_shadow);
		AlphaBlend(hdc_memBuffer,0,400,
				   1000,200,
				   hdc_loadBmp,0,0,1000,200,
				   blend);
	}
	if (charactorL->visible){
		SelectObject(hdc_loadBmp, charactorL->img);
		TransparentBlt(
			hdc_memBuffer, 80,400 ,
			100, 100,
			hdc_loadBmp, 0, 0, 100, 100,
			RGB(255,255,255)
		);
	}
	if (charactorR->visible){
		SelectObject(hdc_loadBmp, charactorR->img);
		TransparentBlt(
			hdc_memBuffer, 810,400 ,
			100, 100,
			hdc_loadBmp, 0, charactorR->frame*100, 100, 100,
			RGB(255,255,255)
		);
	}
	if (currentStage->stageID==STAGE_SELECT){
		if (unlocked[Selected_Stage]&&currentStage->time>=50){
			SelectObject(hdc_loadBmp,bmp_Info);
			TransparentBlt(
					hdc_memBuffer, 300, 440,
					40, 40,
					hdc_loadBmp,0,0,40,40,
					RGB(255,255,255)
				);
			TransparentBlt(
					hdc_memBuffer, 550, 440,
					40, 40,
					hdc_loadBmp,40,0,40,40,
					RGB(255,255,255)
				);
		}
	}
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);
	if (currentStage->stageID==STAGE_SELECT){
		if (unlocked[Selected_Stage]&&currentStage->time>=50){
			char *s=new char[100];s[0]='\0';
			char S[10];
			strcat(s,"��");
			itoa(info[Selected_Stage][0],S,10);
			strcat(s,S);
			strcat(s,"/");
			itoa(max_reward[Selected_Stage],S,10);
			strcat(s,S);
			int n=strlen(s);
			SetBkMode(hdc_window,0);
			SetTextColor(hdc_window,RGB(255,255,255));
			HFONT hFont=CreateFont(28,10,0,0,FW_BOLD,false,false,0,ANSI_CHARSET,OUT_CHARACTER_PRECIS,
CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("Comic Sans MS"));
			SelectObject(hdc_window,hFont);
			TextOutA(hdc_window,350,450,(LPCSTR)s,n);
			for (int i=2;i<n;i++)s[i]='\0';
			if (info[Selected_Stage][1]!=-1){
				itoa(info[Selected_Stage][1],S,10);
				strcat(s,S);
			}else strcat(s,"???");
			n=strlen(s);
			TextOutA(hdc_window,600,450,(LPCSTR)s,n);
			delete s;
			DeleteObject(hFont);
		}
	}
	if (story->on){
		SetBkMode(hdc_window,0);
		SetTextColor(hdc_window,RGB(255,255,255));
		HFONT hFont=CreateFont(20,10,0,0,600,false,false,0,ANSI_CHARSET,OUT_CHARACTER_PRECIS,
CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("����"));
		SelectObject(hdc_window,hFont);
		char* s=new char[61];
		int m=(story->time/5*2-1)/60;
		for (int i=0;i<m;i++){
			for (int j=i*60;j<(i+1)*60;j++)s[j-i*60]=story->s[j];
			TextOutA(hdc_window,180,450+i*20,(LPCSTR)s,60);
		}
		int tmp=story->time/5*2-m*60;
		for (int i=m*60;i<tmp+m*60;i++)s[i-m*60]=story->s[i];
		TextOutA(hdc_window,180,450+m*20,(LPCSTR)s,tmp);
		delete s;
		DeleteObject(hFont);
	}
	// ������е���Ϣ���Ƶ���Ļ��
	

	for (int i=0;i<particles.size();i++){
		Particle* particle=particles[i];
		Col col=particle->col;
		HPEN hpen=CreatePen(PS_SOLID,2,RGB(col.R,col.G,col.B));
		SelectObject(hdc_window,hpen);
		if (particle->type!=4&&particle->type!=5)Ellipse(hdc_window,(int)particle->x-deltaX,(int)particle->y-deltaY,(int)particle->x+3-deltaX,(int)particle->y+3-deltaY);
		if (particle->type==2){
			MoveToEx(hdc_window,(int)particle->x+2,(int)particle->y,NULL);
			LineTo(hdc_window,(int)particle->x+7,(int)particle->y-7);
		}
		if (particle->type==4){
			//hpen=CreatePen(PS_SOLID,1,RGB(col.R,col.G,col.B));
			MoveToEx(hdc_window,(int)particle->x,(int)particle->y,NULL);
			LineTo(hdc_window,(int)(particle->x-particle->vx*0.5),(int)(particle->y-particle->vy*0.5));
		}
		if (particle->type==5)Ellipse(hdc_window,(int)particle->x,(int)particle->y,(int)particle->x+3,(int)particle->y+3);
		DeleteObject(hpen);
	}
	// ������Դ��ռ���ڴ棨�ǳ���Ҫ��
	DeleteObject(blankBmp);
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	// ��������
	EndPaint(hWnd, &ps);
}
#pragma endregion