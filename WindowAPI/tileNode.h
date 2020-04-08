#pragma once

//게임화면 타일
#define TILESIZE 48
#define TILEX 120
#define TILEY 150
#define TILESIZEX (TILEX * TILESIZE)
#define TILESIZEY (TILEY * TILESIZE)
#define LAYERCOUNT 3

//이미지 타일(화면 우측상단에 붙여놓을 샘플타일)
#define SAMPLETILEX 12
#define SAMPLETILEY 6

//맵툴에서 사용할 컨트롤들
enum CTRL
{
	CTRL_SAVE, CTRL_LOAD,
	CTRL_TERRAIN, CTRL_OBJECT, CTRL_ERASER,
	CTRL_MAP1, CTRL_MAP2, CTRL_MAP3, CTRL_END
};

//지형
enum TERRAIN
{
	TR_CEMENT, TR_GROUND, TR_GRASS, TR_WATER, TR_END
};

//오브젝트
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_TANK1, OBJ_TANK2,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_NONE
};

//타일구조체
//한 타일당 레이어 개수 3개에요
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	bool canMove[LAYERCOUNT] = { false, };	//이 타일 위를 이동할 수 있는지 확인해주는 bool 변수
											//기본값 false
											//하나라도 false면 이 타일 위로는 이동할 수 없음
	bool direct[4] = { false, };		//이동이 가능하다면 어떤 방향으로 이동할 수 있는지 정의
										//true일 경우에만 이동 가능.
										//기본값 == false
										//0: 위, 1: 아래, 2: 좌, 3: 우
	int imagePage[LAYERCOUNT] = { -1, };
	int tileFrameX[LAYERCOUNT];
	int tileFrameY[LAYERCOUNT];
};

//이미지 타일 구조체
struct tagSampleTile
{
	RECT rc;

	int imagePage;
	int tileFrameX;
	int tileFrameY;
	
	bool canMove;
	bool direct[4];
};

//현재타일 구조체
struct tagCurrentTile
{
	int x, y;
};