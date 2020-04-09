#pragma once
#include "gameNode.h"
#include "tileNode.h"

class maptoolScene : public gameNode
{
private:
	bool _tileSetting;
	bool _canMove;
	bool _setSaveLoad;		//세이브/로드창 띄워져있는가 없는가 판단
	char _fileName[128];	//파일 이름(맵, 맵 데이터)을 받아올 변수
	int _startFile;			/*파일 명은 0번부터 시작
							ex) MAP0.map	MAP0.mapdata
							*/
	unsigned int _palettePage;
	bool _layer[3];

private:
	tagTile _tiles[TILEX * TILEY];	//인게임화면에 사용되는 타일 총 400개
	tagSampleTile _sampleTile[60]; //샘플타일 총 (12-2)*6 = 60개
	tagCurrentTile _currentTile;	//현재타일
private:
	RECT _rcScreen;		//화면 카메라 Rect;
						//이 Rect와 충돌한 타일만 화면에 그려진다.
	RECT _rcArrow[2];	//샘플타일을 변경할 화살표를 그려주는 Rect
						//0번 : LeftArrow, 1번 : RightArrow
	RECT _rcPalette;	//샘플타일을 그려줄 Rect;

	RECT _rcSaveLoad;		//세이브/로드버튼
	RECT _rcSaveWindow;		//세이브 창
	RECT _rcSaveSlot[3];		//세이브슬롯3개
	
	RECT _rcSave;			//세이브로드 UI안에서의 세이브
	RECT _rcLoad;			//세이브로드 UI안에서의 로드



	RECT _rcDummy1;			//2번째칸	예정사항	
	RECT _rcDummy2;			//3번째칸	지형 
	RECT _rcDummy3;			//4번째칸	오브젝트
	RECT _rcDummy4;			//5번째칸	지우개(오브젝트만 지운다, 지형은 덮어씌운다)

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//맵툴세팅
	void maptoolSetup();
	void setMap();
	void uiMove();
	void save(char* str);
	void load(char* str);

	void frameBoxRender(int left, int top, int width, int height, float scale);			//프레임 랜더시키기 인자는 RectMake랑같음 ※스케일값은 가능하면 정수로
																						//사각형에 프레임 씌우기 인자는 사각형	※scale값은 가능하면 정수로
	void frameBoxRender(RECT rc, float scale);											//프레임 랜더시키기 인자는 RectMake랑같음 ※스케일값은 가능하면 정수로
																						//오버로드-> 렉트넣어서 간편하게		※scale < 1 => 제대로 안그려짐

	void selectLayer1();
	void selectLayer2();
	void selectLayer3();

	//지형, 오브젝트 세터
	TERRAIN terrainSelect(int frameX, int frameY);

	maptoolScene() {}
	~maptoolScene() {}
};

