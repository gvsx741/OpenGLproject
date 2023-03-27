#include <windows.h>
#include <gl/gl.h>

int width = 1600;
int heigth = 900;

typedef struct {
	float x, y, z;
}TCell;

typedef struct {
	float r, g, b;
}TColor;

typedef struct {
	float u, v;
}TUV;

typedef struct {
	float x, y, z;
	int type;
	float scale;
}TObject;

#define mapW 100
#define mapH 100
TCell map[mapW][mapH];
TCell mapNormal[mapW][mapH];
TUV mapUV[mapW][mapH];

GLuint mapInd[mapW - 1][mapH - 1][6];
int mapIndCnt = sizeof(mapInd) / sizeof(GLuint);

float plant[] = {
   -0.5, 0, 0,
	0.5, 0, 0,
	0.5, 0, 1,
   -0.5, 0, 1,

    0,-0.5, 0,
    0, 0.5, 0,
    0, 0.5, 1,
    0,-0.5, 1,
};

float plantUV[] = { 0,1, 1,1, 1,0, 0,0, 0,1, 1,1, 1,0, 0,0 };

GLuint plantInd[] = { 
0,1,2,
2,3,0,
4,5,6,
6,7,4, 
};

int plantIndCnt = sizeof(plantInd) / sizeof(GLuint);

int tex_pole, tex_trava, tex_flower, tex_flower2, tex_grib, tex_tree, tex_tree2;	
int tex_ico_runBuff;
int tex_ico_mortar, tex_ico_potion_life, tex_ico_potion_speed;
int tex_textID;

float rectCoord[] = { 0,1, 1,1, 1,0, 0,0 };
float rectTex[] = { 0,1, 1,1, 1,0, 0,0 };

TObject* plantMas = NULL;

int plantCnt = 0;

float sun[] = {
	-1,-1, 0,
	 1,-1, 0,
	 1, 1, 0,
	-1, 1, 0,
};

BOOL selectMode = FALSE;

#define ObjListCnt 255

typedef struct {
	int plantMas_Idex;
	int colorIndex;
}TSelectObj;

TSelectObj selectMas[ObjListCnt];
int selectMasCnt = 0;

typedef struct {
	TObject* obj;
	float dx, dy, dz;
	int cnt;
}TAnim;

TAnim animation = { 0,0,0,0,0 };

POINT scrSize;
float scrKoef;

typedef struct {
	int type;
	int x,y;
	int width, height;
}TSlot;
#define bagSize 16
TSlot bag[bagSize];

float bagRect[] = { 0,0, 1,0, 1,1, 0,1 };
float bagRectUV[] = { 0,0, 1,0, 1,1, 0,1 };

int health = 15;
int healthMax = 20;

float heart[] = {
	0.5, 0.25,
	0.25, 0,
	0, 0.25,
	0.5, 1,
	1, 0.25,
	0.75, 0,
};

BOOL mouseBind = TRUE;

typedef struct {
	int stackToBuff;
	int time;
	int timeMax;
	int pos_x;
}TBuff;

struct {
	TBuff speed;
	TBuff potionSpeed;
	TBuff potionLife;
}buffs = {0,0};

unsigned int buff_pos_x = 10;
unsigned int tBuff_pos_x = 10;

float mySpeed = 0.1;

int handItemType;

POINT mousePos;

struct {
	int x,y;
	int width, height;
	TSlot items[3][3];
	TSlot itemOut;
	BOOL show;
}craft_menu;

typedef struct {
	int items[3][3];
	int itemOut;
}TRecipe;

TRecipe* recipe;
int recipeCnt = 0;

float Map_GetHeight(float x, float y);//сделай эффекты зелькам