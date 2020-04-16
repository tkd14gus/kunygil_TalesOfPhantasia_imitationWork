#pragma once
#include "gameNode.h"
#include "tileNode.h"
#define VK_D	0x44
#define VK_1	0x31
#define VK_2	0x32
#define VK_3	0x33

class maptoolScene : public gameNode
{
private:
	bool _editMode;					//맵파일 속성 입력 모드.
	bool _editCanMove;				//해당 타일로 이동을 변경할 수 있는지 판단해주는 bool 변수
	bool _editMoveDirect;			//해당 타일에서 이동 방향을 변경할 수 있는지 판단해주는 bool 변수
	bool _canMove;					//현재 선택한 타일이 이동 가능한 타일인가?
	bool _direct[4] = { false, };	//현재 선택한 타일에서 어떤 방향으로 이동할 수 있는가?
									//0:상	1:하	  2:좌  3:우
	bool _setSaveLoad;				//세이브/로드창 띄워져있는가 없는가 판단
	bool _slideTool;				//맵툴창이 최대화되어있는지 최소화되어있는지 판단

	int _setSaveSlot;				//세이브 슬롯 활성화
	char _palettePageNum[128];

	char _canMoveChar[8] = { 0, };		//에디트 모드에서 사용
										//각 샘플 타일로 이동할 수 있는지 표시.
										//0 : 이동 불가		1 : 이동 가능
	char _moveDirectChar[5] = { 0, };	//에디트 모드에서 사용
										//각 생플타일에서 어떤 방향으로 이동할 수 있는지를 표시.
										//0:상  1:하  2:좌  3:우


	char _fileName[128] = { 0, };	//맵 파일의 이름을 받아올 변수 
	char _mapName[128] = { 0, };
									//파일 이름(맵, 맵 데이터)을 받아올 변수
	char _imageName[128] = { 0, };	//맵 이미지 파일의 이름을 받아올 변수
	char _dataName[128] = { 0, };	//맵 데이터 파일의 이름을 받아올 변수

	int _startFile;			/*파일 명은 0번부터 시작
							ex) MAP0.map	MAP0.mapdata
							*/



/////////////////////////////////////////////////////////////////////////////////////////-YSH- unsigned 제거함
	int _palettePage;		//지금 샘플 타일에 몇번째 샘플 이미지가 그려지는지를 저장한 변수.
	bool _layer[LAYERCOUNT];		//몇 번째 레이어 층인지 표시.

private:
	tagTile _tiles[TILEX * TILEY];	//인게임화면에 사용되는 타일 총 400개
	tagTile _saveTile[TILEX * TILEY];
	tagSampleTile _sampleTile[60]; //샘플타일 총 (12-2)*6 = 60개
	tagCurrentTile _currentTile;	//현재타일


private:
	RECT _rcScreen;		//화면 카메라 Rect;
						//이 Rect와 충돌한 타일만 화면에 그려진다.
	RECT _rcArrow[2];	//샘플타일을 변경할 화살표를 그려주는 Rect
						//0번 : LeftArrow, 1번 : RightArrow
	RECT _rcArrow5[2];
	RECT _rcPalette;	//샘플타일을 그려줄 Rect;

	RECT _rcMouse;		//마우스 포인터를 따라다니는 Rect
						//중심점은 마우스 포인터의 좌표이며
						//이 Rect가 화면 끝에 닿으면 타일이 움직인다.

	RECT _rcSaveLoad;		//세이브/로드버튼
	RECT _rcSaveWindow;		//세이브 창
	RECT _rcSaveSlot[3];		//세이브슬롯3개
	
	RECT _rcSave;			//세이브로드 UI안에서의 세이브
	RECT _rcLoad;			//세이브로드 UI안에서의 로드



	RECT _rcEraser;			//2번째칸	예정사항	지형 
	RECT _rcDummy2;			//3번째칸	오브젝트
	RECT _rcDummy3;			//4번째칸	지우개(오브젝트만 지운다, 지형은 덮어씌운다)
	RECT _rcslide;			//5번째칸	최대화 / 최소화시키기

	dragRect _dragRect;		//팔레트 드래그 선택영역 보기
	drawField _drawField;	//타일 내 드래그 선택영역용
	RECT selectRect;		//그림이 그려질 위치 미리보기


	char _pageNum[100];
	char _pageName[100];

	char drag[1024];	//드래그 좌표 미리보기용
	char count[1042];

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//맵툴세팅
	void maptoolSetup();
	void setSample();
	void setMap();						//일반 채우기
	void setAllMap();					//전체 채우기	
	void setFieldMap();					//영역을 지정하여 같은 타일로 채우기
	void uiMove();
	void save(char* str);				//제작한 맵을 저장하는 함수
	void load(char* str);				//제작된 맵을 불러오는 함수
	void saveMapData(char *str);		//샘플타일의 속성을 프로젝트 폴더의 하위 폴더인 MapData에
										//.mapdata 확장자로 저장된다.
										//현재 버그로 미동작.
	void loadMapData(char *str);		//샘플타일의 속성을 프로젝트 폴더의 하위 폴더인 MapData에서
										//.mapdata 확장자를 불러온다.


	void frameBoxRender(int left, int top, int width, int height, float scale);			//팝업창(텍스트등)에 프레임씌우기
																						
	void frameBoxRender(RECT rc, float scale);											//프레임씌우기 사각형 넣어서 간편하게
																						


	void selectLayer1();	//1번 레이어 선택
	void selectLayer2();	//2번 레이어 선택
	void selectLayer3();	//3번 레이어 선택

	//지형, 오브젝트 세터
	TERRAIN terrainSelect(int frameX, int frameY);

	maptoolScene() {}
	~maptoolScene() {}
};

